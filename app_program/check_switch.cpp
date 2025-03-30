#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "tasks.h"
#include "settings.h"
#include "event_flags.h"

void check_switch(INT stacd, void *exinf)
{
    static BOOL pre_is_pushed[UNIT_NUM];
    static BOOL is_pushed[UNIT_NUM];
    for(UB i=0; i<UNIT_NUM; i++){
        gpio_set_pin(SWITCHS[i],GPIO_MODE_IN);
        pre_is_pushed[i] = FALSE;
        is_pushed[i] = FALSE;
    }

    static UB now_node_num = 0;
    static UINT flag_tmp;
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
        for(UB i=0; i<UNIT_NUM; i++){
            is_pushed[i] = gpio_get_val(SWITCHS[i]);
        
            if(!pre_is_pushed[i] && is_pushed[i]){
                pre_is_pushed[i] = TRUE;
                now_node_num++;
            }
            else if(pre_is_pushed[i] && !is_pushed[i]){
                pre_is_pushed[i] = FALSE;
            }
            else{
            }
        }
        if(now_node_num > 5){
            tk_clr_flg(id_game_flag, 0);
            tk_set_flg(id_game_flag, WAITING_SYSTEM_TURN);
            now_node_num = 0;
        }
    }
}