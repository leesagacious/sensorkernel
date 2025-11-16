
void netif_napi_add_weight(struct net_device *dev, struct napi_struct *napi,
		int (*poll)(struct napi_struct *, int), int weight)
{
	/*
	 * if the flag was not previously set, 
	 * set it and return 0
	 *
	 * if the flag was previously set,
	 * return 1
	 *
	 * Ensure that NAPI is added only once
	 *
	 * NAPI_STATE_LISTED: 
	 * 	NAPI has been added to the system's NAPI 
	 * 	list
	 */
	if (WARN_ON(test_and_set_bit(NAPI_STATE_LISTED, &napi->state)))
		return;

	INIT_LIST_HEAD(&napi->poll_list);
	INIT_HLIST_NODE(&napi->napi_hash_node);
	hrtimer_init(&napi->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL_PINNED);
	napi->timer_function = napi_watchdog;
}	
