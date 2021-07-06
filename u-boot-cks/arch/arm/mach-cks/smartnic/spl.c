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
	u32 boot_device = BOOT_DEVICE_MMC1;
	return boot_device;
}

void board_init_f(ulong dummy)
{
#ifdef CONFIG_DEBUG_UART
        /*
         * Debug UART can be used from here if required:
         */
        debug_uart_init();
#endif
	//g-timer init	
	writel(0x1, CONFIG_SYS_GTIMER_BASE);


	spl_early_init();

	preloader_console_init();
}
