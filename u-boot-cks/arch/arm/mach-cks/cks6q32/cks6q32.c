// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2016 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <spl.h>
#include <asm/io.h>


void reset_cpu(ulong addr)
{
        // system reset

        while (1)
                ;
}

int arch_cpu_init(void)
{
        return 0;
}

int print_cpuinfo(void)
{
        puts("CPU: CKS6Q 32");
        return 0;
}