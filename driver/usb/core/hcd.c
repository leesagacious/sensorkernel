void usb_hcd_poll_rh_status(struct usb_hcd *hcd) 
{
	int length;
	unsigned long flags;
	char buffer[6];

	length = hcd->driver->hub_status_data(hcd, buffer);
	if (length > 0) {
		spin_lock_irqsave(&hcd_root_hub_lock, flags);

		spin_unlock_irqrestore(&hcd_root_hub_lock, flags);
	}
}
