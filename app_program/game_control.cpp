#include <tk/tkernel.h>
#include "tasks.h"
#include "settings.h"

UB NODES[NODES_MAX] = {};
UB USER_INPUTS[NODES_MAX] = {};
UB NOW_NODE_NUM = 0;
ID id_show_pattern;
ID id_wait_input;
ID id_game_over;

LOCAL void show_lighting_wrapper(void)
{
    show_lighting_pattern(0, nullptr);
}
LOCAL T_CTSK led_task = {
	nullptr,
	(TA_HLNG | TA_RNG3),
	show_lighting_wrapper,
	10,
	1024,
	nullptr
};

LOCAL void wait_user_input_wrapper(void)
{
	wait_user_input(0, nullptr);
}
LOCAL T_CTSK switch_task = {
	nullptr,
	(TA_HLNG | TA_RNG3),
	wait_user_input_wrapper,
	10,
	1024,
	nullptr
};

LOCAL void game_over_wrapper(void)
{
	game_over(0,nullptr);
}
LOCAL T_CTSK game_over_task = {
	nullptr,
	(TA_HLNG | TA_RNG3),
	game_over_wrapper,
	10,
	1024,
	nullptr
};

void control_game(INT stacd, void *exinf)
{
    id_show_pattern = tk_cre_tsk(&led_task);
    id_wait_input = tk_cre_tsk(&switch_task);
	id_game_over = tk_cre_tsk(&game_over_task);
	tk_sta_tsk(id_show_pattern, 0);
    tk_slp_tsk(TMO_FEVR);
}