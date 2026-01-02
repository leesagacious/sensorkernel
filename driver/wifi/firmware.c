/*
 * The request contains firmware items: n_items > 0
 * Each firmware item has a path: item->path != NULL
 */
static bool brcmf_fw_request_is_valid(struct brcmf_fw_request *req)
{
	struct brcmf_fw_item *item;
	int i;

	if (!req->n_items)
		return false;

	for (i = 0, item = &req->items[0]; i < req->n_items; i++, item++) {
		if (!item->path)
			return false;
	}
}

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
		return -EINVAL;					// Notify the driver when firmware loading is complete
	
	/* check the request item */
	if (!brcmf_fw_request_is_valid(req))
		return -EINVAL;

	/*
	 * allocate and initizalize a context structure for asynchronous
	 * operation to store device information,firmware request details
	 * and callback function
	 */
	fwctx = kzalloc(sizeof(*fwctx), GFP_KERNEL);
	if (!fwctx)
		return -ENOMEM;

	fwctx->dev = dev;
	fwctx->req = req;
	fwctx->done = fw_cb;

	/* asynchronous version of request_firmware */
	ret = request_firmware_nowait(THIS_MODULE, true, first->path,
			fwctx->dev, GFP_KERNEL, fwctx,
			brcmf_fw_request_done);

	if (ret < 0)
		brcmf_fw_request_done(NULL, fwctx);

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
