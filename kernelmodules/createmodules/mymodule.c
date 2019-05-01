#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

// This function is called when when the module is loaded.
int myModule_init(void){
    printk(KERN_INFO "My module is loaded.\n");
    return 0;
}

//This function is called when the module is removed.
void myModule_exit(void){
    printk(KERN_INFO "Removing my module.\n");
}

module_init(myModule_init);
module_exit(myModule_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("My first kernel module");
MODULE_AUTHOR("Xuan Ngoc");
MODULE_VERSION("0.01");

