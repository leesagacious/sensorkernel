
prog = """
#include <uapi/linux/limits.h>


BPF_PERF_OUTPUT(monitor_alarm);

int alarm_monitor_entrace(struct pt_regs *ctx) 
{

    return 0;
}

int alarm_monitor_ret(struct pt_regs *ctx)
{
    return 0;
}

"""

b = BPF(test=prog)
b.attach_kprobe(event=b.get_syscall_fnname("alarm"), fn_name="alarm_monitor_entrace")
b.attach_kretprobe(event=b.get_syscall_fname("alarm"), fn_name="alarm_monitor_ret")


b["monitor_alarm"].open_perf_buffer(print_alarm)
while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
