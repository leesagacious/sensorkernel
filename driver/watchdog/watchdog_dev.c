

static ktime_t watchdog_next_keepalive(struct watchdog_device *wdd)
{
	struct watchdog_core_data *wd_data = wdd->wd_data;
	unsigned int timeout_ms = wdd->timeout * 1000;
	ktime_t keepalive_interval;
	ktime_t virt_timeout;

	if (watchdog_active(wdd))
		virt_timeout = ktime_add(wd_data->last_keepalive,
				ms_to_ktime(timeout_ms));
	

	return keepalive_interval;
}
