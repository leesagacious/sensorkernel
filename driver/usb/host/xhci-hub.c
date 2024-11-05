int xhci_hub_status_data(struct usb_hcd *hcd, char *buf)
{

	/*
	 * 端口没有状态. 定时器停止轮询该port. 
	 */	
	if (!status && !reset_change) {
		xhci_dbg(xhci, "%s: stopping usb%d port polling\n",
				__func__, hcd->self.busnum);
		clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	}

	return status ? retval : 0;
}
