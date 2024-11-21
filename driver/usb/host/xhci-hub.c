struct xhci_hub *xhci_get_rhub(struct usb_hcd *hcd)
{
	struct xhci_hcd *xhci = hcd_to_xhci(hcd);

	if (hcd->speed >= HCD_USB3)
		return &xhci->usb3_rhub;
	return &xhci->usb2_rhub;
}

int xhci_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	unsigned long flags;
	u32 status;
	int retval;
	int max_prots;
	struct xhci_hub *rhub;


	rhub = xhci_get_rhub(hcd);
	max_prots = rhub->ports;		// hub上端口的数量
	
	retval = (max_ports + 8) / 8;
	memset(buf, 0, retval);

	spin_lock_irqsave(&xhci->lock, flags);

	status = bus_state->resuming_ports;

	for (i = 0; i < max_ports; i++) {
		temp = readl(ports[i]->addr);   // 读取每一个端口状态和控制寄存器. (portsc)
		if (temp == ~(u32)0) {
			xhci_hc_died(xhci);
			retval = -ENODEV;
			break;
		}
		
		trace_xhci_hub_status_data(i, temp);

		if (temp & mask) {
			buf[(i + 1) / 8] |= 1 << (i + 1) % 8;
			status = 1;
		}

		if (temp & PORT_RC)
			reset_change = true;
		if (temp & PORT_OC)		// 过流
			status = 1;
	}

	/*
	 * 端口没有状态. 定时器停止轮询该port. 
	 */	
	if (!status && !reset_change) {
		xhci_dbg(xhci, "%s: stopping usb%d port polling\n",
				__func__, hcd->self.busnum);
		clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	}
	spin_unlock_irqrestore(&xhci->lock, flags);
	return status ? retval : 0;
}
