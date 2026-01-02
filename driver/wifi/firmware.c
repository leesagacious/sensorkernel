

/*
 * Firmware is loaded from disk using an asynchronous.
 */
int brcmf_fw_get_firmware(struct device *dev, struct brcmf_fw_request *req,
		void (*fw_cb)(struct device *dev, int err,
			struct brcmf_fw_request *req))
{
	int ret;

	brcmf_dbg(TRACE, "enter: dev=%s\n", dev_name(dev));	// add debug code
	if (!fw_cb)						// check invoke. 
		return -EINVAL;

	/* asynchronous version of request_firmware */
	ret = request_firmware_nowait(THIS_MODULE, true, first->path,
			fwctx->dev, GFP_KERNEL, fwctx,
			brcmf_fw_request_done);

	return 0;
}	

/*
 * Specifically traverse and filter NVRAM data entries related to 
 * PCIe configurations
 */
static void brcmf_fw_strip_multi_v2(struct nvram_parser *nvp, u16 domain_nr,
			u16 bus_nr)
{
	u8 *nvram;

	/*
	 * What nvp->nvram points to is no longer a conglomerate containing 
	 * configurations for all devices, but rather a collection of configuratios
	 * required solely for the current device.
	 * this significantly reduces the amount of data needs to be uploaded
	 * to the NIC firmware and ensures the correctness of the configurations
	 */
	nvram = kzalloc(nvp->nvram_len + 1 + 3 + sizeof(u32), GFP_KERNEL);
	if (!nvram) {
		nvp->nvram_len = 0;
		return;
	}
}	
