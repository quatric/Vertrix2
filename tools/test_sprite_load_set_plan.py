"""Reject corrupted saved original-executable plan evidence."""
import copy
import unittest
from verify_sprite_load_set import INITIAL_TOKENS, validated_initial_plan

class PlanEvidenceTests(unittest.TestCase):
    def setUp(self):
        self.report = {'status': 'passed', 'initial_image_settings_plan':
            [{'token': hex(token), 'slot': index % 23} for index, token in enumerate(INITIAL_TOKENS)]}

    def test_valid_plan(self):
        self.assertEqual(validated_initial_plan(self.report), self.report['initial_image_settings_plan'])

    def test_corrupt_reports(self):
        mutations = [
            lambda r: r.update(status='failed'),
            lambda r: r.pop('status'),
            lambda r: r['initial_image_settings_plan'].pop(),
            lambda r: r['initial_image_settings_plan'].append(r['initial_image_settings_plan'][0]),
            lambda r: r['initial_image_settings_plan'].reverse(),
            lambda r: r['initial_image_settings_plan'][0].update(token='0xdeadbeef'),
        ]
        for slot in [-1, 23, True, '1', None]:
            mutations.append(lambda r, slot=slot: r['initial_image_settings_plan'][0].update(slot=slot))
        for index, mutate in enumerate(mutations):
            with self.subTest(corruption=index):
                report = copy.deepcopy(self.report)
                mutate(report)
                with self.assertRaises(ValueError):
                    validated_initial_plan(report)

if __name__ == '__main__':
    unittest.main()
