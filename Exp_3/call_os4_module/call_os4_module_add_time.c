#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/delay.h>

MODULE_LICENSE("Dual BSD/GPL");

extern int (*fptr_Operation)(int*,int,int,char*);

static int call_os4_module_init(void)
{
    printk("call_os4_module_init...\n");
    long count = 10000*10000;
    printk("The count is %ld.\n", count);
    struct timeval tstart,tend;
    do_gettimeofday(&tstart);
    int i = 0;
    for(i=0;i<count;i++) // +
    {
        int result;
        char op_add = '+';
        fptr_Operation(&result, i, 10, &op_add);
    }
    for(i=0;i<count;i++) // -
    {
        int result;
        char op_sub = '-';
        fptr_Operation(&result, i, 10, &op_sub);
    }
    for(i=0;i<count;i++) // *
    {
        int result;
        char op_mul = '*';
        fptr_Operation(&result, i, 2, &op_mul);
    }
    for(i=0;i<count;i++) // '//'
    {
        int result;
        char op_div = '\\';
        fptr_Operation(&result, i, 10, &op_div);
    }
    do_gettimeofday(&tend);
	long delta_time = 1000*(tend.tv_sec - tstart.tv_sec) + (tend.tv_usec - tstart.tv_usec)/1000;
    printk("The start time is %ld.\n", tstart.tv_sec*1000+tstart.tv_usec/1000);
	printk("The end time is %ld.\n", tend.tv_sec*1000+tend.tv_usec/1000);
	printk("Os4 mod time use:%ld msec", delta_time);
    return 0;
}

static void call_os4_module_exit(void)
{
    printk("call_os4_module_exit...\n");
    return;
}
module_init(call_os4_module_init);
module_exit(call_os4_module_exit);
