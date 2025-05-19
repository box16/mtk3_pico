#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "tasks.h"
#include "settings.h"

static BOOL has_been_initialized = FALSE;
LOCAL void init()
{
    for(UB i=0; i<UNIT_NUM; i++){
        gpio_set_pin(SWITCHS[i],GPIO_MODE_IN);
    }
    has_been_initialized = TRUE;
}

LOCAL ID id_timer;
LOCAL void time_up(void)
{
    tk_sta_tsk(id_game_over, 0);
    tk_ter_tsk(id_wait_input);
    tk_del_alm(id_timer);
    return;
}
LOCAL T_CALM timer = {
    nullptr,
    TA_HLNG,
    time_up,
};

void wait_user_input(INT stacd, void *exinf)
{
    if(!has_been_initialized)
    {
        init();
    }

    id_timer = tk_cre_alm(&timer);
    tk_sta_alm(id_timer, 3000 + 1000 * NOW_NODE_NUM);
    BOOL pre_is_pushed[UNIT_NUM] = {FALSE};
    BOOL is_pushed[UNIT_NUM] = {FALSE};
    UB counter = 0;
    while (TRUE)
    {
        /*
            前回 | 現在 | 意味        | 動き|
            --------------------------------
            オン | オン | 押しっぱなし | 変化なし
            オン | オフ | 離した瞬間   | 変化なし
            オフ | オン | 押した瞬間   | 変化あり
            オフ | オフ | 放置         | 変化なし
        */
        for(UB pin_index=0; pin_index<UNIT_NUM; pin_index++){
            is_pushed[pin_index] = gpio_get_val(SWITCHS[pin_index]);
        
            if(!pre_is_pushed[pin_index] && is_pushed[pin_index]){
                pre_is_pushed[pin_index] = TRUE;
                USER_INPUTS[counter] = pin_index;
                if(pin_index != NODES[counter]){
                    tk_del_alm(id_timer);
                    tk_sta_tsk(id_game_over,0);
                    tk_ext_tsk();
                }
                counter++;
            }
            else if(pre_is_pushed[pin_index] && !is_pushed[pin_index]){
                pre_is_pushed[pin_index] = FALSE;
            }
            else{
            }
        }
        if(counter >= NOW_NODE_NUM){
            tk_del_alm(id_timer);
            tk_sta_tsk(id_show_pattern,0);
            tk_ext_tsk();
        }
    }
}