#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "blink_led.h"

void blink_led(INT stacd, void *exinf)
{
    /* P25 : On board LED*/
    while (1)
    {
        gpio_set_val(25, 1);
        tk_dly_tsk(500);

        gpio_set_val(25, 0);
        tk_dly_tsk(500);
    }
}