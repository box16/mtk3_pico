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

void wait_user_input(INT stacd, void *exinf)
{
    if(!has_been_initialized)
    {
        init();
    }

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
                counter++;
            }
            else if(pre_is_pushed[pin_index] && !is_pushed[pin_index]){
                pre_is_pushed[pin_index] = FALSE;
            }
            else{
            }
        }
        if(counter >= NOW_NODE_NUM){
            counter = 0;
            tk_sta_tsk(id_check_input,0);
            tk_ext_tsk();
        }
    }
}