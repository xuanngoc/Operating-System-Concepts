#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;	
};

struct list_head birthday_list;

struct birthday *createBirthday(int day, int month, int year) {
	struct birthday *person = kmalloc(sizeof(struct birthday), GFP_KERNEL);
	person->day = day;
	person->month = month;
	person->year = year;
	return person;
}

/* This function is called when the module is loaded. */
int birthdayModule_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	
	LIST_HEAD(birthday_list);

        struct birthday *person = createBirthday(13, 4, 1999);
	list_add_tail(&person->list, &birthday_list);
	person = createBirthday(14, 1, 1999);
	list_add_tail(&person->list, &birthday_list);
	person = createBirthday(2, 6, 1999);
	list_add_tail(&person->list, &birthday_list);
	person = createBirthday(13, 8, 1999);
	list_add_tail(&person->list, &birthday_list);
	person = createBirthday(6, 6, 2019);
	list_add_tail(&person->list, &birthday_list);

	struct birthday *ptr;

	list_for_each_entry(ptr, &birthday_list, list) {
		printk(KERN_INFO "OS Module: Day %d.%d.%d\n", ptr->day, ptr->month, ptr->year);
	}

       return 0;
}

/* This function is called when the module is removed. */
void birthdayModule_exit(void) {
	printk(KERN_INFO "Removing Module\n");

	struct birthday *tmp;
	struct list_head *ptr, *next;

	if (list_empty(&birthday_list)) {
		printk(KERN_INFO "List is empty");
		return;
	}

	list_for_each_safe(ptr, next, &birthday_list){
		tmp = list_entry(ptr, struct birthday, list);
		printk(KERN_INFO "OS Module: Removing %d.%d.%d\n", tmp->day, tmp->month, tmp->year);
		list_del(ptr);
		kfree(tmp);
	}

	

	printk(KERN_INFO "Module removed\n");
}

/* Macros for registering module entry and exit points. */
module_init( birthdayModule_init );
module_exit( birthdayModule_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday Module");
MODULE_AUTHOR("Bui Xuan Ngoc");