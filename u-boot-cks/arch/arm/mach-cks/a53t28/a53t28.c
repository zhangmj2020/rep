// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2016 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <spl.h>
#include <asm/io.h>
#include <asm/armv8/mmu.h>

DECLARE_GLOBAL_DATA_PTR;

static struct mm_region a53t28_mem_map[] = {
        {
                .virt = 0x0UL,
                .phys = 0x0UL,
                .size = 0x40000000UL,
                .attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
                         PTE_BLOCK_NON_SHARE |
                         PTE_BLOCK_PXN | PTE_BLOCK_UXN
        }, {
                .virt = 0x40000000UL,
                .phys = 0x40000000UL,
                .size = 0x80000000UL,
                .attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
                         PTE_BLOCK_INNER_SHARE
       }, {
                /* List terminator */
                0,
        }
};

struct mm_region *mem_map = a53t28_mem_map;


void reset_cpu(ulong addr)
{
        // system reset


        while (1)
                ;
}

int arch_cpu_init(void)
{
	//g-timer init	
	writel(0x1, CONFIG_SYS_GTIMER_BASE);
	writel(0x0, CPU_RELEASE_ADDR);
        return 0;
}


int cpu_mmc_init(bd_t *bis)
{
	cks_sdhci_init();
	return 0;
}
