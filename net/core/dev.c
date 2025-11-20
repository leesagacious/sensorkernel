
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
	 *
	 * enum {
  		  NAPI_STATE_SCHED,           // bit0
    		  NAPI_STATE_MISSED,          //    1 
    		  NAPI_STATE_DISABLE,         //    2 
    		  NAPI_STATE_NPSVC,           //    3 
    		  NAPI_STATE_LISTED,          //    4 
    	  	  NAPI_STATE_NO_BUSY_POLL,    //    5 
    		  NAPI_STATE_IN_BUSY_POLL,    //    6 
    		  NAPI_STATE_PREFER_BUSY_POLL,//    7
    		  NAPI_STATE_THREADED,        //    8
    		  NAPI_STATE_SCHED_THREADED,  //    9 

		Indeed, considering the number of status bits.
		the int type seems sufficient

   		Atomic bit operations in the kernel are typically
       		based on unsigned long.

                static inline void set_bit(long nr, volatile unsigned long *addr);
	   };
	 */
	if (WARN_ON(test_and_set_bit(NAPI_STATE_LISTED, &napi->state)))
		return;

	/*
	 * When network data arrives. NAPI is added to
	 * the CPU's processing queue
	 *
	 * list_add_tail(&napi->poll_list, &sd->poll_list);
	 */
	INIT_LIST_HEAD(&napi->poll_list);
	INIT_HLIST_NODE(&napi->napi_hash_node);
	hrtimer_init(&napi->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL_PINNED);
	napi->timer_function = napi_watchdog;
}	
