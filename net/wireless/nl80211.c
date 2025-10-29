
/*
 * This function servers as the bridge between the wireless driver
 * and the upper network subsystem
 * responsible for handing RSSI threshold event notifications
 *
 * 1. Ultimately, this event will be notified to user-space programs
 *    via the Netlink interface
 */
void cfg80211_cqm_rssi_notify(struct net_device *dev,
		enum nl80211_cqm_rssi_threshold_event rssi_event,
		s32 rssi_level, gfp_t gfp)
{
	
}	
