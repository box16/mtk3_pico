#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "blink_led.h"
#include "event_flag.h"

void blink_led(INT stacd, void *exinf)
{
    /* P25 : On board LED*/
    UINT flag_pattern;
    while (1)
    {
        tk_wai_flg(id_switch_flag, SWITCH_ON, (TWF_ANDW | TWF_BITCLR), &flag_pattern, TMO_FEVR);
        gpio_set_val(25, 1);
        tk_dly_tsk(500);

        gpio_set_val(25, 0);
        tk_dly_tsk(500);
    }
}