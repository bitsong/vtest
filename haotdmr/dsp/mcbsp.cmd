SECTIONS
{
    .init_array:     load >> L1DSRAM
    .mcbsp:          load >> DSP_PROG
    .mcbspSharedMem: load >> DSP_PROG
    systemHeap:     load >> IRAM


    /* place all the knl APIs in IRAM */
	.knl: { *.*(.text:*ti_sysbios_knl*) 	} > L3_CBA_RAM
	/* place all the Hwi APIs in IROM */
	.hwi: { *.*(.text:*ti_sysbios*_Hwi_*) 	} > L3_CBA_RAM
	/* place the remainder of the SYS/BIOS APIs in DDR */
	.sysbios: { *.*(.text:*ti_sysbios*) 	} > L3_CBA_RAM
}

