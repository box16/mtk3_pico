#include <tk/tkernel.h>
#include "tasks.h"
#include "settings.h"
#include "event_flags.h"

void check_user_input(INT stacd, void *exinf)
{
    static UINT flag_tmp;
    while(TRUE){
        tk_wai_flg(id_game_flag, WAITING_CHECK, (TWF_ANDW|TWF_CLR), &flag_tmp, TMO_FEVR);
        for (UB i = 0; i < NOW_NODE_NUM; i++)
        {
            if(NODES[i] != USER_INPUTS[i]){
                tk_clr_flg(id_game_flag, 0);
                tk_set_flg(id_game_flag, GAME_OVER);
                goto skip;
            }
        }
        tk_clr_flg(id_game_flag, 0);
        tk_set_flg(id_game_flag, WAITING_SYSTEM_TURN);
    skip:
    }
}
