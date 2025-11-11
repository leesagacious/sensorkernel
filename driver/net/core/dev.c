
static __latent_entropy void net_rx_action(void)
{

	/*
	 * Read the netdev_budget field from the global struct net_hotdata
	 * 
	 * netdev_budge: defines the maximum number of packets that can be 
	 * processed during a single softirq
	 */
	int budget = READ_ONCE(net_hotdata.netdev_budget);

	LIST_HEAD(list);
	LIST_HEAD(repoll);
}
