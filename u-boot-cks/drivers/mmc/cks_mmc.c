// SPDX-License-Identifier: GPL-2.0+
/*
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <malloc.h>
#include <sdhci.h>

#define CKS_SDHC_MIN_FREQ	400000
#define CKS_SDHC_MAX_FREQ	25000000

#ifdef CONFIG_TARGET_FPGA_CKS_C01
#define CKS_EMMC_MAX_FREQ	20000000
#else
#define CKS_EMMC_MAX_FREQ	50000000
#endif


#define	SDHCI_TUNNING_REG		0x70

#ifndef CONFIG_DM_MMC
void cks_set_control_reg(struct sdhci_host *host)
{
	struct  mmc *mmc = host->mmc;
	if(IS_SD(mmc))
		sdhci_writel(host,0x30,SDHCI_TUNNING_REG);
	else
		sdhci_writel(host,0x10,SDHCI_TUNNING_REG);
}

int cks_sdhci_init()
{
	struct sdhci_host *host;

	host = (struct sdhci_host *)calloc(1, sizeof(struct sdhci_host));
	if (!host) {
		printf("%s: sdhci_host calloc failed\n", __func__);
		return -ENOMEM;
	}

	host->name = "cks_sdhci";
	host->ioaddr = CKS_SDMMC0_BASE;
	host->quirks = SDHCI_QUIRK_WAIT_SEND_CMD | SDHCI_QUIRK_REG32_RW | SDHCI_QUIRK_BROKEN_R1B;
	host->index = 0;
	host->max_clk = CKS_SDHC_MAX_FREQ;

	return add_sdhci(host, 0, CKS_SDHC_MIN_FREQ);
}

int cks_emmc_init()
{
	struct sdhci_host *host;

	host = (struct sdhci_host *)calloc(1, sizeof(struct sdhci_host));
	if (!host) {
		printf("%s: sdhci_host calloc failed\n", __func__);
		return -ENOMEM;
	}

	host->name = "cks_emmc";
	host->ioaddr = CKS_SDMMC0_BASE;
	host->quirks = SDHCI_QUIRK_WAIT_SEND_CMD | SDHCI_QUIRK_REG32_RW | SDHCI_QUIRK_BROKEN_R1B;
	host->index = 1;
	host->host_caps = MMC_MODE_8BIT;
	host->max_clk = CKS_EMMC_MAX_FREQ;

	return add_sdhci(host, 0, CKS_SDHC_MIN_FREQ);
}


#else
#define CKS_SDHC_GCK_RATE	240000000

DECLARE_GLOBAL_DATA_PTR;

struct cks_sdhci_plat {
	struct mmc_config cfg;
	struct mmc mmc;
};

static int cks_sdhci_probe(struct udevice *dev)
{
	struct mmc_uclass_priv *upriv = dev_get_uclass_priv(dev);
	struct cks_sdhci_plat *plat = dev_get_platdata(dev);
	struct sdhci_host *host = dev_get_priv(dev);
	u32 max_clk;
	struct clk clk;
	int ret;

	ret = clk_get_by_index(dev, 0, &clk);
	if (ret)
		return ret;

	ret = clk_enable(&clk);
	if (ret)
		return ret;

	host->name = dev->name;
	host->ioaddr = (void *)devfdt_get_addr(dev);

	host->quirks = SDHCI_QUIRK_WAIT_SEND_CMD;
	host->bus_width	= fdtdec_get_int(gd->fdt_blob, dev_of_offset(dev),
					 "bus-width", 4);

	ret = clk_get_by_index(dev, 1, &clk);
	if (ret)
		return ret;

	ret = clk_set_rate(&clk, CKS_SDHC_GCK_RATE);
	if (ret)
		return ret;

	max_clk = clk_get_rate(&clk);
	if (!max_clk)
		return -EINVAL;

	host->max_clk = max_clk;
	host->mmc = &plat->mmc;
	host->mmc->dev = dev;

	ret = sdhci_setup_cfg(&plat->cfg, host, 0, CKS_SDHC_MIN_FREQ);
	if (ret)
		return ret;

	host->mmc->priv = host;
	upriv->mmc = host->mmc;

	clk_free(&clk);

	return sdhci_probe(dev);
}

static int cks_sdhci_bind(struct udevice *dev)
{
	struct cks_sdhci_plat *plat = dev_get_platdata(dev);

	return sdhci_bind(dev, &plat->mmc, &plat->cfg);
}

static const struct udevice_id cks_sdhci_ids[] = {
	{ .compatible = "cks,cks-sdhci" },
	{ }
};

U_BOOT_DRIVER(cks_sdhci_drv) = {
	.name		= "cks_sdhci",
	.id		= UCLASS_MMC,
	.of_match	= cks_sdhci_ids,
	.ops		= &sdhci_ops,
	.bind		= cks_sdhci_bind,
	.probe		= cks_sdhci_probe,
	.priv_auto_alloc_size = sizeof(struct sdhci_host),
	.platdata_auto_alloc_size = sizeof(struct cks_sdhci_plat),
};
#endif
