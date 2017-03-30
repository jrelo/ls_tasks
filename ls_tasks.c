#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

void device_exit(void);
int device_init(void);
  
module_init(device_init);
module_exit(device_exit);

int device_init(void)
{
    struct task_struct *task = current;
    printk(KERN_NOTICE "ls_tasks: current proc: %s, PID: %d", task->comm, task->pid);
    do
    {
        task = task->parent;
        printk(KERN_NOTICE "ls_tasks: parent proc: %s, PID: %d", task->comm, task->pid);
    } while (task->pid != 0);
    return 0;
}

void device_exit(void) {
    printk(KERN_NOTICE "ls_tasks: exiting...");
}
