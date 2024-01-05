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

static struct task_struct *writer_thread;
static struct task_struct *reader_thread;

static int __init rcu_rw_init(void)
{

	return 0;
}

static void __exit rcu_rw_exit(void)
{
	
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("lizhe");


