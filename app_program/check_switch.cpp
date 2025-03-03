#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "check_switch.h"
#include "event_flag.h"

void check_switch(INT stacd, void *exinf)
{
    gpio_set_pin(22,GPIO_MODE_IN);
    while (1)
    {
        UINT is_pushed = gpio_get_val(22);
        if(is_pushed){
            tk_set_flg(id_switch_flag, SWITCH_ON);
        }
        tk_dly_tsk(100);
    }
}