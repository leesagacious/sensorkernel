
static __latent_entropy void net_rx_action(void)
{

	/*
	 * The total execution time of a single network RX softirq. include
	 * the cumulative processing time for all network device queues,
	 * not the processing time of an individual queue
	 *
	 * - Limits the execution time of the 'net_rx_action()' function
	 * - Includes the cumulative processing time of all queued netowrk 
	 *   devices
	 * - Represents a global time budget, not a per-queue allocation
	 */
	unsigned long time_limit = jiffies +
		usecs_to_jiffies(READ_ONCE(net_hotdata.netdev_budget_usecs));
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
