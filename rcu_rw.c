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

static int writer_thread_function(void *data)
{
	struct my_data *new_data;
	int value = 0;

	while (!kthread_should_stop()) {
		
		new_data = kmalloc(sizeof(struct my_data), GFP_KERNEL);
		if (!new_data)
			break;

		new_data->a = value;  // 在副本上修改

		/*
		 * 修改完成后, 更新全局指针，使其指向新修改的副本。
		 * 这个宏保证了指针更新操作的正确性，特别是在多核处理器环境中
		 */
		rcu_assign_pointer(global_ptr, new_data);
	}

	return 0;
}

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


