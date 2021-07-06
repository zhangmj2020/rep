// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2016 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>

int dram_init()
{
	return 0;
}

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

