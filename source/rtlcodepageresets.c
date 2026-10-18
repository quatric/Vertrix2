#include "rtlcodepageresets.h"
#include "rtlcodepages.h"

/* Original 0x4e5ef0: sets code page 0 (eax = 0, which 0x4e6f60 takes as 1), the original jumping to
 * 0x4e6f60, whose rewrite runs here on the same stack. */
uint32_t vertrix_port_rtl_code_page_reset_4e5ef0(PORT_SIGNATURE)
{
    LiftEntry jumped = *entry;
    jumped.eax = 0;
    return vertrix_port_rtl_set_code_page_4e6f60(calls, services, globals, &jumped);
}
