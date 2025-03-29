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

void blink_led_wrapper(void)
{
    blink_leds(0, nullptr);
}

LOCAL ID id_led_task;
LOCAL T_CTSK led_task = {
	nullptr,
	(TA_HLNG | TA_RNG3),
	blink_led_wrapper,
	10,
	1024,
	nullptr
};

extern "C" EXPORT INT usermain(void)
{
	id_led_task = tk_cre_tsk(&led_task);
	tk_sta_tsk(id_led_task, 0);

	tk_slp_tsk(TMO_FEVR);
	return 0;
}