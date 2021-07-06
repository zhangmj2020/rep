// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <debug_uart.h>
#include <dm.h>
#include <ram.h>
#include <spl.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

u32 spl_boot_device(void)
{
	u32 boot_device = BOOT_DEVICE_UART;
	return boot_device;
}

#ifdef CONFIG_SPL_OS_BOOT
int spl_start_uboot(void)
{
        return 0;
}
#endif

static void spl_ddr_init(void)
{

}

void board_init_f(ulong dummy)
{
#ifdef CONFIG_DEBUG_UART
        /*
         * Debug UART can be used from here if required:
         */
        debug_uart_init();
#endif

        spl_ddr_init();
        
	arch_cpu_init();
        board_early_init_f();
        
	timer_init();
		
	spl_early_init();

        preloader_console_init();

        memset(__bss_start, 0, __bss_end - __bss_start);
        board_init_r(NULL, 0);
}
#if 0
void board_init_f(ulong dummy)
{
#ifdef CONFIG_DEBUG_UART
        debug_uart_init();
#endif
	//g-timer init	
	writel(0x1, CONFIG_SYS_GTIMER_BASE);

	spl_early_init();

	preloader_console_init();
}
#endif