
static void 
entity_tick(struct cfs_rq *cfs_rq, struct sched_entity *curr, int queued)
{
#ifdef CONFIG_SCHED_HRTICK
	/*
	 * when queued is 1, it indicates that this clock interrupt was
	 * queued and triggerred by a high-resolution timer(hrtick)
	 *
	 * when queued is 0, it indicates a normal perodic clock interrupt
	 *
	 * Because the entity_tick function needs to know:
	 * 	- who is calling me ? is it the periodic tick or the HRTICK ?
	 * 	- what behavior should i take ?
	 * 	- if it's HRTICK: reschedule immediately (as the time slice has precisely expired)
	 * 	- if it's the periodic tick: first check whether HRTICK is active to avoid interference
	 */
	if (queued) {
		/*
		 * Rescheduling flag for processes running on this cpu core
		 */
		resched_curr(rq_of(cfs_rq));
		return;
	}

	/*
	 * Return directly when both of the following conditions are met:
	 * - The DOUBLE_TICK feature is not enabled
	 * - The HRTICK timer is already running
	 *
	 *  when the DOUBLE_TICK feature is enabled. coexistence of both is allowed
	 *  by default. this feature is disabled, as the "double check" provides no 
	 *  benefit in most cases
	 *
	 *  Timeline example:
		  Periodic tick    HRTICK
    			↓           ↓
 		 [---|--------------|-----] Time axis
   		    t=10ms     t=15ms (exact end of time slice)

	  If both triggers are allowed to invoke scheduling checks:
	  1. At t=10ms, the periodic tick triggers check_preempt_tick().
	  2. The task may continue running because its time slice hasn’t been exhausted yet.
	  3. At t=15ms, HRTICK triggers another precise scheduling check.
	  4. In effect, the check at t=10ms is "premature and unnecessary."

	 */
	if (!sched_feat(DOUBLE_TICK) &&
			hrtimer_active(&rq_of(cfs_rq)->hrtick_timer))
		return;
#endif	
	/*
	 * This means that check_preempt_tick() is invoked to check whether
	 * preemption is needed only when the number of runnable task in the
	 * CFS run queue(cfs_rq) is greater than one.
	 */
	if (cfs_rq->nr_running > 1)
		check_preempt_tick(cfs_rq, curr);
}
