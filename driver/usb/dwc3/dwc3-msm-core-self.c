
static void dwc3_ext_event_notify(struct dwc3_msm *mdwc)
{
	/* Flush processing any pending events before handling new ones */
	flush_work(&mdwc->sm_work);
}
