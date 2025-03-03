#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "task1.h"

void task_1(INT stacd, void *exinf)
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