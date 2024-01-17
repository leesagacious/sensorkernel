#!/usr/bin/python3

from bcc import BPF

bpf_monitor_timer_create = """
#include <uapi/linux/ptrace.h>

int kprobe__sys_timer_create(struct pt_regs *ctx)
{
    bpf_trace_printk("timer_create called by PID: %d\n", bpf_get_current_pid_tgid() >> 32);

    return 0;
}

"""

b = BPF(text=bpf_monitor_timer_create)

b.attach_kprobe(event="sys_timer_create", fn_name="kprobe__sys_timer_create")
