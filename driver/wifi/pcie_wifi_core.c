
struct brcmf_pciedev_info {
	
	struct pci_dev *pdev;
};

static struct platform_driver brcmf_pd = {
	.remove = brcmf_common_pd_remove,
	.driver = {
		.name = BRCMFMAC_PDATA_NAME,
	}
};

static int brcm_pcie_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int ret;
	/*
	 * this structure serves as the central data hub for Broadcom PCIe wifi devices,
	 * comprehensively encapsulating hardware state management,firmware control,
	 * memory mapping, communication protocols, and debugging support, while acting
	 * as the core interface for interaction between the driver and the chip
	 */
	struct brcmf_pciedev_info *devinfo;

	ret = -ENOMEM;
	devinfo = kzalloc(sizeof(*devinfo), GFP_KERNEL);
	if (devinfo == NULL)
		return ret;

	/*
	 * populate the pci_dev structre maintained by it
	 */
	devinfo->pdev = pdev;

	pcie_bus_dev->devinfo = devinfo;

	return 0;
}

static int __init brcmfmac_module_init(void)
{
	int err;

	/*
	 * register the platform driver with the name brcmfmac
	 */
	err = platform_driver_probe(&brcmf_pd, brcmf_common_pd_probe);
	if (err == -ENODEV)
		brcmf_dbg(INFO, "No platform data available. \n");


       /*
	* this is a multi-bus registration entry function. which internally
	* registers the corresponding driver based on different interface by 
	* types.
	* brcmf_core_init()
	* 	---> brcmf_sdio_register()	registger sdio interface driver
	* 	---> brcmf_usb_register()	register usb interface driver
	* 	---> brcmf_pcie_register()	register pcie interface driver
	*
	* Dynamic Adaptation process:
	* 	when the module is loaded. the system detects the actual hardware
	* 	interface type.
	* 	the kernel's device-driver matching mechanism automatically selects
	* 	the appropriate driver
	*
	* detection of a PCIe wifi chip -> triggers the driver registered by brcmf_pcie_register()
	* detection of a USB wifi adapter -> triggers the driver registered by brcmf_usb_register()
	* detection of an SDIO interface chip -> triggers the driver register by brcmf_sdio_register()
	*
	* encapsulate hardware differences through the unified entry point brcmf_core_init()
	* driver developers only need to maintain a single initialization path
	*
	* automatic interface detection:
	* 	leverage the kernel's driver_register() mechanism to automatically match hardware 
	* 	IDs defined in MODULE_DEVICE_TABLE
	*
	* ---
	*    baseed on the actual hardware interface type. the corresponding bus driver is dynamically
	*    registered, it embodies the "write once, adapt to multiple buses" principle in the linux
	*    kerenl device driver model
	*/
	err = brcmf_core_init();
	if (err) {
		if (brcmfmac_pdata)
			platform_driver_unregister(&brcmf_pd);
	}


	return err;
}
