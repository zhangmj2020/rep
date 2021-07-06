// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2016 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>

#if !defined(CONFIG_SYS_SDRAM_BASE) && !defined(CONFIG_SYS_SDRAM_SIZE)
int dram_init_banksize(void)
{
        return fdtdec_setup_memory_banksize();
}

int dram_init(void)
{
        if (fdtdec_setup_mem_size_base() != 0)
                return -EINVAL;

        return 0;
}
#else
int dram_init(void)
{
        gd->ram_size = get_ram_size((void *)CONFIG_SYS_SDRAM_BASE,
                                    CONFIG_SYS_SDRAM_SIZE);

        return 0;
}
#endif

int board_init(void)
{
        return 0;
}

#ifndef CONFIG_SPL_BUILD
int board_early_init_f(void)
{
	return 0;
}
#endif

int board_late_init(void)
{
	return 0;
}

#ifdef CONFIG_SPL_LOAD_FIT
int board_fit_config_name_match(const char *name)
{
        /* Just empty function now - can't decide what to choose */
        debug("%s: %s\n", __func__, name);

        return 0;
}
#endif

