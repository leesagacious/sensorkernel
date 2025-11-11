
static __latent_entropy void net_rx_action(void)
{

	/*
	 * Read the netdev_budget field from the global struct net_hotdata
	 */
	int budget = READ_ONCE(net_hotdata.netdev_budget);

	LIST_HEAD(list);
	LIST_HEAD(repoll);
}
