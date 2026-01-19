
static void 
entity_tick(struct cfs_rq *cfs_rq, struct sched_entity *curr, int queued)
{
	
	/*
	 * This means that check_preempt_tick() is invoked to check whether
	 * preemption is needed only when the number of runnable task in the
	 * CFS run queue(cfs_rq) is greater than one.
	 */
	if (cfs_rq->nr_running > 1)
		check_preempt_tick(cfs_rq, curr);
}
