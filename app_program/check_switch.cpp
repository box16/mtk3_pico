#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "check_switch.h"
#include "event_flag.h"

void check_switch(INT stacd, void *exinf)
{
    gpio_set_pin(22,GPIO_MODE_IN);
    BOOL is_pushed = FALSE;
    BOOL pre_is_pushed = FALSE;
    BOOL state = FALSE;

    while (1)
    {
        /*
            前回 | 現在 | 意味        | 動き|
            --------------------------------
            オン | オン | 押しっぱなし | 変化なし
            オン | オフ | 離した瞬間   | 変化なし
            オフ | オン | 押した瞬間   | 変化あり
            オフ | オフ | 放置         | 変化なし
        */
        is_pushed = gpio_get_val(22);
        if(!pre_is_pushed && is_pushed){
            state = !state;
            pre_is_pushed = TRUE;
        }
        else if(pre_is_pushed && !is_pushed){
            pre_is_pushed = FALSE;
        }
        else{

        }

        if(state){
            tk_set_flg(id_switch_flag, SWITCH_ON);
        }
        else{
            tk_clr_flg(id_switch_flag, 0x00);
        }
        tk_dly_tsk(50);
    }
}