#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_AUTHOR("IO-31 Teteruk");
MODULE_DESCRIPTION("Hello 2 - Uses exported function");
MODULE_LICENSE("GPL");

// Оголошуємо, що така функція існує десь зовні
extern void my_print_function(void);

static int __init hello_2_init(void)
{
    printk(KERN_EMERG "Module 2 loaded. Calling function from Module 1...\n");
    my_print_function(); // Виклик чужої функції
    return 0;
}

static void __exit hello_2_exit(void)
{
    printk(KERN_EMERG "Module 2 unloaded\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);
