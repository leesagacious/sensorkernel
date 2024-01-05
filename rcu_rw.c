#include <linux/module.h>
#include <linux/slab.h>
#include <linux/rcupdate.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>

struct my_data {
    int a;
    struct rcu_head rcu;
};

static struct my_data __rcu *global_ptr;
