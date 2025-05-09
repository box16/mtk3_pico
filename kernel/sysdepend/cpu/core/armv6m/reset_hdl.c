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

#include <sys/machine.h>
#ifdef CPU_CORE_ARMV6M

/*
 *	reset_hdr.c (ARMv6-M)
 *	Reset handler
 */

#include "kernel.h"
#include "../../../sysdepend.h"

#include <tm/tmonitor.h>


/* Low level memory manager information */
EXPORT	void	*knl_lowmem_top;		// Head of area (Low address)
EXPORT	void	*knl_lowmem_limit;		// End of area (High address)

IMPORT	const void *__data_org;
IMPORT	const void *__data_start;
IMPORT	const void *__data_end;
IMPORT	const void *__bss_start;
IMPORT	const void *__bss_end;
#if USE_NOINIT
IMPORT	const void *__noinit_end;
#endif

IMPORT const void (*vector_tbl[])();

EXPORT void Reset_Handler(void)
{
	UW	*src, *top, *end;
	INT	i;

	/* Startup Hardware */
	knl_startup_hw();

#if !USE_STATIC_IVT
	/* Load Vector Table from ROM to RAM */
	src = (UW*)vector_tbl;;
	top = (UW*)exchdr_tbl;

	for(i=0; i < ((N_SYSVEC + N_INTVEC)); i++) {
		*top++ = *src++;
	}
	
	/* Set Vector Table offset to SRAM */
	*(_UW*)SCB_VTOR = (UW)exchdr_tbl;
#endif

	/* Load .data to ram */
	src = (UW*)&__data_org;;
	top = (UW*)&__data_start;
	end = (UW*)&__data_end;
	while(top != end) {
		*top++ = *src++;
	}

	/* Initialize .bss */
#if USE_NOINIT
	top = (UW*)&__noinit_end;
#else 
	top = (UW*)&__bss_start;
#endif
	for(i = ((INT)&__bss_end - (INT)&__bss_start)/sizeof(UW); i > 0 ; i--) {
		*top++ = 0;
	}

#if USE_IMALLOC
	/* Set System memory area */
	if(INTERNAL_RAM_START > SYSTEMAREA_TOP) {
		knl_lowmem_top = (UW*)INTERNAL_RAM_START;
	} else {
		knl_lowmem_top = (UW*)SYSTEMAREA_TOP;
	}
	if((UW)knl_lowmem_top < (UW)&__bss_end) {
		knl_lowmem_top = (UW*)&__bss_end;
	}

	if((SYSTEMAREA_END != 0) && (INTERNAL_RAM_END > CNF_SYSTEMAREA_END)) {
		knl_lowmem_limit = (UW*)(SYSTEMAREA_END - EXC_STACK_SIZE);
	} else {
		knl_lowmem_limit = (UW*)(INTERNAL_RAM_END - EXC_STACK_SIZE);
	}
#endif

	/* Configure exception priorities */
	*(_UW*)SCB_SHPR2 = SCB_SHPR2_VAL;	// SVC pri = 0
	*(_UW*)SCB_SHPR3 = SCB_SHPR3_VAL;	// SysTick = 0 , PendSV = 3

	/* Startup Kernel */
	main();		/**** No return ****/
	while(1);	/* guard - infinite loops */
}

#endif	/* CPU_CORE_ARMV6M */