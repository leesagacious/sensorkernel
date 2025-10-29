
/*
 * This function servers as the bridge between the wireless driver
 * and the upper network subsystem
 * responsible for handing RSSI threshold event notifications
 *
 * 1. Ultimately, this event will be notified to user-space programs
 *    via the Netlink interface
 *
 * *dev: 
 * 	which device triggered the RSSI event (e.g: wlan0 wlan1)
 * *rssi_event:
 * 	RSSI threshold event type
 * 	1. NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW    	Signal strength is below the configured threshold
 * 	2. NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH	Signal strength is above the configured threshold
 * 	3. NL80211_CQM_RSSI_BEACON_LOSS_EVENT		Reserved value, never actually sent
 */
void cfg80211_cqm_rssi_notify(struct net_device *dev,
		enum nl80211_cqm_rssi_threshold_event rssi_event,
		s32 rssi_level, gfp_t gfp)
{
	
}	
