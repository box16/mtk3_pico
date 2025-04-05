#include <tk/tkernel.h>
#include "tasks.h"
#include "settings.h"

void check_user_input(INT stacd, void *exinf)
{
    for (UB i = 0; i < NOW_NODE_NUM; i++)
    {
        if(NODES[i] != USER_INPUTS[i]){
            tk_sta_tsk(id_game_over,0);
            tk_ext_tsk();
        }
    }
    tk_sta_tsk(id_show_pattern,0);
    tk_ext_tsk();
}
