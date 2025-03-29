#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "tasks.h"
#include "event_flags.h"

void check_switch(INT stacd, void *exinf)
{
    static constexpr UB SWITCH_NUM = 5; // 後々共通化
    static constexpr UB SWITCHS[SWITCH_NUM] = {16,22,6,7,5};// 後々共通化。ピンによっては他のデバイス用にとられてて意図しない動きをする
    static BOOL pre_is_pushed[SWITCH_NUM];
    static BOOL is_pushed[SWITCH_NUM];
    for(UB i=0; i<SWITCH_NUM; i++){
        /**(_UW*)(0x4001c000 + 0x04 * SWITCHS[i]) = 0x00000000 |
                                                  0 << 7 |
                                                  1 << 6  |
                                                  1 << 4 |
                                                  0 << 3 |
                                                  1 << 2 |
                                                  1 << 1 |
                                                  1;*/
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
        for(UB i=0; i<SWITCH_NUM; i++){
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