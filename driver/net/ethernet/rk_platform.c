
static struct plat_stmmacenet_data *
stmmac_probe_config_dt(struct platform_device *pdev, u8 *mac)
{
	struct plat_stmmacenet_data *plat;

	plat = devm_kzalloc(&pdev->dev, sizeof(*plat), GFP_KERNEL);
	if (!plat)
		return ERR_PTR(-ENOMEM);

	rc = of_get_mac_address(np, mac);
	if (rc) {
		if (rc == -EPROBE_DEFER)
			return ERR_PTR(rc);

		eth_zero_addr(mac);
	}
}
