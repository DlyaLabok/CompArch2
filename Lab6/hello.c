#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include <linux/list.h>
#include <linux/bug.h>

MODULE_AUTHOR("IO-31 Teteruk");
MODULE_DESCRIPTION("Lab 6 - Debugging and OOPS");
MODULE_LICENSE("GPL");

static uint howmany = 1;
module_param(howmany, uint, 0644);
MODULE_PARM_DESC(howmany, "Number of times to print Hello World");

struct my_struct {
    struct list_head list;
    ktime_t time;
};

static LIST_HEAD(my_list_head);

static int __init hello_init(void)
{
    int i;
    struct my_struct *ptr;

    if (howmany > 10) {
        pr_emerg("Lab6: howmany is too big! Triggering BUG_ON!\n");
        BUG_ON(howmany > 10); 
    }

    for (i = 0; i < howmany; i++) {
        ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);

        if (i == 2) {
            pr_emerg("Lab6: Simulating kmalloc failure at i=%d\n", i);
            kfree(ptr);
            ptr = NULL;
        }

        BUG_ON(!ptr);

        ptr->time = ktime_get();
        list_add_tail(&ptr->list, &my_list_head);
        pr_info("Hello, world! iteration %d\n", i);
    }

    return 0;
}

static void __exit hello_exit(void)
{
    struct my_struct *ptr, *next;
    list_for_each_entry_safe(ptr, next, &my_list_head, list) {
        pr_info("Time: %lld ns\n", ktime_to_ns(ptr->time));
        list_del(&ptr->list);
        kfree(ptr);
    }
    pr_info("Module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
