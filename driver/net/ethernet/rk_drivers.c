
static int rk_gmac_probe(struct platform_device *pdev)
{
	struct plat_stmmacenet_data *plat_dat;
	struct stmmac_resources stmmac_res;
	const struct rk_gmac_ops *data;
	int ret;

	/*
	 * get the data of rk_gmac_dwmac_match[]
	 */
	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_err(&pdev->dev, "no of match data provided\n");
		return -EINVAL;
	}
}

/*
 * Define chip-specific operation functinos and the GMAC 
 * base address
 */
static const struct rk_gmac_ops rk3588_ops = {
	.set_to_rgmill = rk3588_set_to_rgmii,
	.set_to_rmii = rk3588_set_to_rmii,
	.set_rgmii_speed = rk3588_set_gmac_speed,
	.set_rmii_speed = rk3588_set_gmac_speed,
	.set_clock_selection = rk3588_set_clock_selection,
	.regs_valid = true,
	.regs = {
		0xfe1b0000,
		0xfe1c0000,
		0x0
	},
};
