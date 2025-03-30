#include <tk/tkernel.h>
#include "tasks.h"
#include "settings.h"
#include "event_flags.h"

UB NODES[NODES_MAX] = {};
UB USER_INPUTS[NODES_MAX] = {};
UB NOW_NODE_NUM = 0;

void show_lighting_wrapper(void)
{
    show_lighting_pattern(0, nullptr);
}
LOCAL ID id_led_task;
LOCAL T_CTSK led_task = {
	nullptr,
	(TA_HLNG | TA_RNG3),
	show_lighting_wrapper,
	10,
	1024,
	nullptr
};

void check_switch_wrapper(void)
{
	check_switch(0, nullptr);
}
LOCAL ID id_switch_task;
LOCAL T_CTSK switch_task = {
	nullptr,
	(TA_HLNG | TA_RNG3),
	check_switch_wrapper,
	10,
	1024,
	nullptr
};

void game_control(INT stacd, void *exinf)
{
    id_game_flag = tk_cre_flg(&game_flag);
	tk_set_flg(id_game_flag, WAITING_SYSTEM_TURN);

    id_led_task = tk_cre_tsk(&led_task);
    id_switch_task = tk_cre_tsk(&switch_task);
	tk_sta_tsk(id_led_task, 0);
	tk_sta_tsk(id_switch_task, 0);
    tk_slp_tsk(TMO_FEVR);
}