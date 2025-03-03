#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "check_switch.h"
#include "event_flag.h"

void check_switch(INT stacd, void *exinf)
{
    gpio_set_pin(22,GPIO_MODE_IN);
    BOOL is_pushed = FALSE;
    BOOL state = FALSE;
    while (1)
    {
        is_pushed = gpio_get_val(22);
        if(is_pushed){
            state = !state;
        }

        if(state){
            tk_set_flg(id_switch_flag, SWITCH_ON);
        }
        else{
            tk_clr_flg(id_switch_flag, 0x00);
        }
        tk_dly_tsk(100);
    }
}