#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static int ls_tasks_show(struct seq_file *m, void *v) {
  seq_printf(m, "ls_tasks: placeholder\n");
  return 0;
}

static int ls_tasks_open(struct inode *inode, struct  file *file) {
  return single_open(file, ls_tasks_show, NULL);
}

static const struct file_operations ls_tasks_fops = {
  .owner = THIS_MODULE,
  .open = ls_tasks_open,
  .read = seq_read,
  .llseek = seq_lseek,
  .release = single_release,
};

MODULE_LICENSE("GPL");

static int __init ls_tasks_init(void)
{
    proc_create("ls_tasks", 0, NULL, &ls_tasks_fops);
    struct task_struct *task = current;
    printk(KERN_NOTICE "ls_tasks: current proc: %s, PID: %d", task->comm, task->pid);
    do
    {
        task = task->parent;
        printk(KERN_NOTICE "ls_tasks: parent proc: %s, PID: %d", task->comm, task->pid);
    } while (task->pid != 0);
    return 0;
}

static void __exit ls_tasks_exit(void) {
    remove_proc_entry("ls_tasks", NULL);
    printk(KERN_NOTICE "ls_tasks: exiting...");
}

module_init(ls_tasks_init);
module_exit(ls_tasks_exit);
