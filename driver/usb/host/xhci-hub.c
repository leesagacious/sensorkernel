int xhci_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	u32 status;

	status = bus_state->resuming_ports;

	for (i = 0; i < max_ports; i++) {
		temp = readl(ports[i]->addr);   // 读取每一个端口状态和控制寄存器. (portsc)

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

	return status ? retval : 0;
}
