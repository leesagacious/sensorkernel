

#define WDAT_DEFAULT_TIMEOUT	30

static int timeout = 	WDAT_DEFAULT_TIMEOUT;
module_param(timeout, int, 0);
MODULE_PARM_DESC(timeout, "Watchdog timeout in seconds (default=)"
		__MODULE_STRING(WDAT_DEFAULT_TIMEOUT) ")");

