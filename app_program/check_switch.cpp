#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include "tasks.h"
#include "event_flags.h"

void check_switch(INT stacd, void *exinf)
{
    gpio_set_pin(22,GPIO_MODE_IN);
    static BOOL is_pushed = FALSE;
    static BOOL pre_is_pushed = FALSE;
    static BOOL state = FALSE;
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
        is_pushed = gpio_get_val(22);
        
        if(!pre_is_pushed && is_pushed){
            tk_clr_flg(id_game_flag, 0);
            tk_set_flg(id_game_flag, WAITING_SYSTEM_TURN);
            pre_is_pushed = TRUE;
        }
        else if(pre_is_pushed && !is_pushed){
            pre_is_pushed = FALSE;
        }
        else{
        }
    }
}