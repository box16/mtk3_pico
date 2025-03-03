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
#include "check_switch.h"
#include "event_flag.h"

LOCAL ID id_led_task;
LOCAL T_CTSK led_task = {
	.itskpri = 10,
	.stksz = 1024,
	.task = blink_led,
	.tskatr = TA_HLNG | TA_RNG3,
};

LOCAL ID id_switch_task;
LOCAL T_CTSK switch_task = {
	.itskpri = 10,
	.stksz = 1024,
	.task = check_switch,
	.tskatr = TA_HLNG | TA_RNG3,
};

EXPORT INT usermain(void)
{
	id_switch_flag = tk_cre_flg(&switch_flag);

	id_switch_task = tk_cre_tsk(&switch_task);
	tk_sta_tsk(id_switch_task, 0);

	id_led_task = tk_cre_tsk(&led_task);
	tk_sta_tsk(id_led_task, 0);

	tk_slp_tsk(TMO_FEVR);
	return 0;
}