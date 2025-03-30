#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "tasks.h"
#include "settings.h"
#include "event_flags.h"

void wait_user_input(INT stacd, void *exinf)
{
    static BOOL pre_is_pushed[UNIT_NUM];
    static BOOL is_pushed[UNIT_NUM];
    for(UB i=0; i<UNIT_NUM; i++){
        gpio_set_pin(SWITCHS[i],GPIO_MODE_IN);
        pre_is_pushed[i] = FALSE;
        is_pushed[i] = FALSE;
    }

    static UINT flag_tmp;
    static UB counter = 0;
    while (TRUE)
    {
        tk_wai_flg(id_game_flag, WAITING_PLAYER_TURN, TWF_ANDW, &flag_tmp, TMO_FEVR);
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
            tk_clr_flg(id_game_flag, 0);
            tk_set_flg(id_game_flag, WAITING_SYSTEM_TURN);
            counter = 0;
        }
    }
}