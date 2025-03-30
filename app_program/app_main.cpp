/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP
 *
 *    Copyright (C) 2022-2023 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2023/05.
 *
 *----------------------------------------------------------------------
 */

/*
 *	app_main.c
 *	Application main program for RaspberryPi Pico
 */

#include <tk/tkernel.h>
#include "tasks.h"


void game_control_wrapper(void)
{
	game_control(0, nullptr);
}

LOCAL ID id_game_control;
LOCAL T_CTSK game_control_task = {
	nullptr,
	(TA_HLNG | TA_RNG3),
	game_control_wrapper,
	10,
	10240,
	nullptr
};

extern "C" EXPORT INT usermain(void)
{
	id_game_control = tk_cre_tsk(&game_control_task);
	tk_sta_tsk(id_game_control, 0);

	tk_slp_tsk(TMO_FEVR);
	return 0;
}