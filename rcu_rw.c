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

static void my_data_free(struct rcu_head *rcu)
{
	struct my_data *data = container_of(rcu, struct my_data, rcu);
	kfree(data);	// 延迟释放旧数据
}

static int writer_thread_function(void *data)
{
	struct my_data *new_data;
	int value = 0;

	while (!kthread_should_stop()) {
		
		schedule_timeout_interruptible(HZ);
		
		new_data = kmalloc(sizeof(struct my_data), GFP_KERNEL);
		if (!new_data)
			break;

		new_data->a = value;  // 在副本上修改

		/*
		 * 修改完成后, 更新全局指针，使其指向新修改的副本。
		 * 这个宏保证了指针更新操作的正确性，特别是在多核处理器环境中
		 */
		rcu_assign_pointer(global_ptr, new_data);
	
		/*
		 * 它仅注册了一个回调函数 (my_data_free)，my_data_free() 会在所有现有的 RCU 读侧临界区结束后才执行
		 * call_rcu() 函数本身不会阻塞调用者
		 */
		if (global_ptr)
			call_rcu(&global_ptr->rcu, my_data_free);

		value++;
	}

	return 0;
}

static int reader_thread_function(void *data)
{
	struct my_data *my_data_ptr;

	while (!kthread_should_stop()) {
		rcu_read_lock();
		
		my_data_ptr = rcu_dereference(global_ptr);
		if (my_data_ptr)
			printk(KERN_INFO "read data : %d\n", my_data_ptr->a);

		rcu_read_unlock();

		msleep(500);
	}

	return 0;
}

static int __init rcu_rw_init(void)
{
	writer_thread = kthread_run(writer_thread_function, NULL, "writer_thread");
	if (IS_ERR(writer_thread))
		return PTR_ERR(writer_thread);

	reader_thread = kthread_run(reader_thread_function, NULL, "reader_thread");
	if (IS_ERR(reader_thread))
		return PTR_ERR(reader_thread);

	return 0;
}

static void __exit rcu_rw_exit(void)
{
	if (writer_thread)
		kthread_stop(writer_thread);

	if (reader_thread)
		ktrhead_stop(reader_thread);

	/*
	 * 在RCU读侧临界区访问到了global_ptr
	 * 在模块退出时, 以确保在释放 global_ptr 之前, 所有相关的 RCU 读操作都已经安全地完成
	 */
	synchronize_rcu();

	if (global_ptr)
		kfree(global_ptr);	
}

module_init(rcu_rw_init);
module_exit(rcu_rw_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("lizhe");


