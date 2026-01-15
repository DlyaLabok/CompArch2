
/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h> // Потрібно для параметрів
#include <linux/ktime.h>       // Потрібно для часу
#include <linux/slab.h>        // Потрібно для kmalloc
#include <linux/list.h>        // Потрібно для списків
#include <linux/errno.h>       // Коди помилок

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

// === ЗАВДАННЯ 1: Параметр howmany ===
static uint howmany = 1;
module_param(howmany, uint, 0644);
MODULE_PARM_DESC(howmany, "Number of times to print Hello World");

// === ЗАВДАННЯ 2: Структура для списку ===
struct my_struct {
    struct list_head list;
    ktime_t time;
};

// Голова списку
static LIST_HEAD(my_list_head);

static int __init hello_init(void)
{
    int i;
    struct my_struct *ptr;

    // Перевірка значення параметра (за методичкою)
    if (howmany == 0 || (howmany >= 5 && howmany <= 10)) {
        pr_warn("WARNING: howmany is %d (either 0 or between 5 and 10)\n", howmany);
    } else if (howmany > 10) {
        pr_err("ERROR: howmany is %d (greater than 10). Module not loaded.\n", howmany);
        return -EINVAL; // Повертаємо помилку, модуль не завантажиться
    }

    // Цикл друку
    for (i = 0; i < howmany; i++) {
        // Виділяємо пам'ять під елемент списку
        ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
        if (!ptr) {
            pr_err("Failed to allocate memory\n");
            return -ENOMEM;
        }

        // Записуємо час і додаємо в список
        ptr->time = ktime_get();
        list_add_tail(&ptr->list, &my_list_head);

        printk(KERN_EMERG "Hello, world!\n");
    }
    return 0;
}

static void __exit hello_exit(void)
{
    struct my_struct *ptr, *next;

    // Проходимо по списку, виводимо час і чистимо пам'ять
    list_for_each_entry_safe(ptr, next, &my_list_head, list) {
        pr_info("Time: %lld ns\n", ktime_to_ns(ptr->time));
        list_del(&ptr->list);
        kfree(ptr);
    }
    printk(KERN_EMERG "Module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
