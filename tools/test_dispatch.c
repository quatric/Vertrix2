/* Host check of source/lifted_dispatch.c: cc -std=c11 -I source tools/test_dispatch.c $(ls source/*.c | grep -v /wii_) */
#include <string.h>
#include <stdio.h>
#include "lifted_dispatch.h"
static unsigned inner_calls;
static uint32_t inner(VertrixCallSite *s, void *c){(void)c;inner_calls++;printf("boundary %x\n",s->target);return 7;}
static uint32_t rd(uint32_t a, void *c){(void)c;(void)a;return 0;}
static int res(uint32_t h, void **s, size_t *l, void *c){(void)h;(void)s;(void)l;(void)c;return 0;}
int main(void){
  VertrixCalls in={inner,0}; VertrixGlobals g={rd,0}; VertrixFactoryServices sv; memset(&sv,0,sizeof sv); sv.resolve=res;
  VertrixLiftedCalls a; vertrix_lifted_calls_init(&a,&in,&sv,&g);
  VertrixCallSite s; memset(&s,0,sizeof s); s.target=0x40aae0;
  printf("count %u has %d\n",vertrix_lifted_count(),vertrix_lifted_has(0x40aae0));
  uint32_t r=a.calls.call(&s,a.calls.context); printf("r=%x boundary calls %u\n",r,inner_calls);
  s.target=0x401000; r=a.calls.call(&s,a.calls.context); printf("fallthrough r=%u\n",r);
  return 0;}
