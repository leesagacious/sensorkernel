
prog = """
#include <uapi/linux/limits.h>


BPF_PERF_OUTPUT(monitor_alarm);

int alarm_monitor_entrace(struct pt_regs *ctx, int arg1, int arg2) 
{

    return 0;
}

int alarm_monitor_ret(struct pt_regs *ctx)
{
    return 0;
}

"""

b = BPF(test=prog)
b.attach_kprobe(event=b.get_syscall_fnname("my_alarm"), fn_name="my_alarm_monitor_entrace")
b.attach_kretprobe(event=b.get_syscall_fname("my_alarm"), fn_name="my_alarm_monitor_ret")

def print_alarm(cpu, data, size):
    monitor_alarm = b["monitor_alarm"].event(data)


b["monitor_alarm"].open_perf_buffer(print_alarm)
while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
