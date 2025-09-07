
struct brcmf_pciedev_info {
	
	struct pci_dev *pdev;
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
