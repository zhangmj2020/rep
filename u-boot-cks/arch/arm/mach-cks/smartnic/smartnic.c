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
		{  //QSPI FLash
					.virt = 0x00000000UL,
					.phys = 0x00000000UL,
					.size = 0x08000000UL,
					.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
							 PTE_BLOCK_NON_SHARE |
                         				 PTE_BLOCK_PXN | PTE_BLOCK_UXN
		},
		{  //IRAM
					.virt = 0x08000000UL,
					.phys = 0x08000000UL,
					.size = 0x00200000UL,
					.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
							 PTE_BLOCK_INNER_SHARE
		},
		{  //peripheral
                .virt = 0x10000000UL,
                .phys = 0x10000000UL,
                .size = 0x18000000UL,
                .attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
                         PTE_BLOCK_NON_SHARE |
                         PTE_BLOCK_PXN | PTE_BLOCK_UXN
        },
        {
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

	gd->ram_top = CONFIG_IRAM_ADDR + CONFIG_IRAM_SIZE;
	gd->ram_base = CONFIG_IRAM_ADDR;
	gd->ram_size = CONFIG_IRAM_SIZE;
        
	return 0;
}


