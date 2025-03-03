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
#include <tm/tmonitor.h>
#include "blink_led.h"

LOCAL ID id_led_task;
LOCAL T_CTSK led_task = {
	.itskpri = 10,
	.stksz = 1024,
	.task = blink_led,
	.tskatr = TA_HLNG | TA_RNG3,
};

EXPORT INT usermain(void)
{
	tm_printf((UB *)"User program started\n");

	id_led_task = tk_cre_tsk(&led_task);
	tk_sta_tsk(id_led_task, 0);

	tk_slp_tsk(TMO_FEVR);
	return 0;
}