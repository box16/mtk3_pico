/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP
 *
 *    Copyright (C) 2021-2022 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2022/08.
 *
 *----------------------------------------------------------------------
 */

/*
 *	cpudef.h
 *
 *	CPU dependent definition  (ARMv6-M core depended)
 */

#ifndef __TK_CPUDEF_CORE_H__
#define __TK_CPUDEF_CORE_H__

#include <config.h>

#define	TA_COPS		0
#define TA_FPU		TA_COP0		/* dummy. An error occurs when checking API calls. */

/*
 * General purpose register		tk_get_reg tk_set_reg
 */
typedef struct t_regs {
	VW	r[13];		/* General purpose register R0-R12 */
	void	*lr;		/* Link register R14 */
} T_REGS;

/*
 * Exception-related register		tk_get_reg tk_set_reg
 */
typedef struct t_eit {
	void	*pc;		/* Program counter R15 */
	UW	xpsr;		/* Program status register */
	UW	taskmode;	/* Task mode flag */
} T_EIT;

/*
 * Control register			tk_get_reg tk_set_reg
 */
typedef struct t_cregs {
	void	*ssp;		/* System stack pointer R13_svc */
} T_CREGS;

#endif /* __TK_CPUDEF_CORE_H__ */
