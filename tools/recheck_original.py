"""Rerun original-execution verifiers with recognized required inputs."""
import argparse
import ast
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
from pathlib import Path
import subprocess
import sys
import time


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--music', type=Path)
    parser.add_argument('--references', type=Path)
    parser.add_argument('--resume', action='store_true', help='Keep successful checks; run failures/new entries')
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    inputs = {'executable': str(args.executable.resolve()), 'archive': str(args.archive.resolve())}
    for key in ('music', 'references'):
        if getattr(args, key):
            inputs[key] = str(getattr(args, key).resolve())
    plans, skipped = [], []
    for script in sorted((root / 'tools').glob('verify_*.py')):
        source = script.read_text()
        if 'from original import' not in source:
            continue
        tree = ast.parse(source)
        if not any(isinstance(n, ast.If) and '__main__' in ast.unparse(n.test) for n in tree.body):
            skipped.append({'script': script.name, 'reason': 'helper module without executable test entry point'})
            continue
        positional, optional, unknown = [], [], []
        for node in ast.walk(tree):
            if not isinstance(node, ast.Call) or not isinstance(node.func, ast.Attribute) or node.func.attr != 'add_argument':
                continue
            declarations = []
            if node.args and isinstance(node.args[0], ast.Constant) and isinstance(node.args[0].value, str):
                declarations = [node.args[0].value]
            elif node.args and isinstance(node.args[0], ast.Name):
                for parent in ast.walk(tree):
                    if isinstance(parent, ast.For) and isinstance(parent.target, ast.Name) and parent.target.id == node.args[0].id and isinstance(parent.iter, ast.Tuple) and node in list(ast.walk(parent)):
                        if all(isinstance(n, ast.Constant) and isinstance(n.value, str) for n in parent.iter.elts):
                            declarations = [n.value for n in parent.iter.elts]
                            break
            if not declarations:
                unknown.append('dynamic argument declaration')
                continue
            required = any(k.arg == 'required' and isinstance(k.value, ast.Constant) and k.value.value for k in node.keywords)
            for name in declarations:
                if name.startswith('-') and not required:
                    continue
                key = name.lstrip('-').replace('-', '_')
                value = (str(build / script.stem) if key == 'build_dir' else str(build / (script.stem + '-output.json')) if key == 'output' else inputs.get(key))
                if value is None:
                    unknown.append(name)
                elif name.startswith('-'):
                    optional.extend((name, value))
                else:
                    positional.append(value)
        if unknown:
            skipped.append({'script': script.name, 'unresolved_inputs': unknown})
        else:
            plans.append((script.name, [sys.executable, str(script), * positional, * optional]))
    report_path = build / 'original-recheck.json'
    previous = json.loads(report_path.read_text()) if args.resume and report_path.exists() else {}
    eligible = {name for name, _ in plans}
    retained = [r for r in previous.get('results', []) if not r['exit_code'] and r['script'] in eligible]
    report = {'status': 'running', 'eligible_checks': len(plans), 'skipped': skipped, 'results': retained}
    completed = {r['script'] for r in retained}
    plans = [p for p in plans if p[0] not in completed]
    report_path.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({'checks_to_run': len(plans), 'retained_successes': len(retained), 'skipped': skipped}), flush=True)
    def run(plan):
        name, command = plan
        start = time.monotonic()
        with (build / (name + '.log')).open('w') as log:
            result = subprocess.run(command, cwd=root, stdout=log, stderr=subprocess.STDOUT)
        return {'script': name, 'exit_code': result.returncode, 'seconds': round(time.monotonic() - start, 2)}
    with ThreadPoolExecutor(max_workers=2) as pool:
        for future in as_completed([pool.submit(run, plan) for plan in plans]):
            result = future.result()
            report['results'].append(result)
            report_path.write_text(json.dumps(report, indent=2) + '\n')
            print(json.dumps(result), flush=True)
    report['status'] = 'failed' if any(r['exit_code'] for r in report['results']) else 'passed'
    report['scope'] = 'Original-execution verifier entry points with recognized required inputs; '
    report['scope'] += 'skipped scripts are explicitly listed and are not established by this run.'
    report_path.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({'status': report['status'], 'completed': len(report['results'])}), flush=True)
    return int(report['status'] != 'passed')
if __name__ == '__main__':
    raise SystemExit(main())
