#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<moduleparam.h>


MODULE_LICENSE("GPL");

static char* whom = "world";
static int num = 1;

//传递命令参数 S_IRUGO 指明参数可以被所有人读取 
module_param(whom,charp,S_IRUGO);
module_param(num,int,S_IRUGO);

//程序中必须有下列两个函数
static int hello_init(void)
{
   int i;
   for (i=0;i<num;i++){
   //使用的是printk 不是printf（其是C库函数）
      printk(KERN_ALERT "hello,%s\n",whom);
   }
   return 0;
}

static void hello_exit(void)
{
   printk(KERN_ALERT "goodbye,kernel/n");
}

//加载or卸载模块
module_init(hello_init);
module_exit(hello_exit);
// 可选 
MODULE_AUTHOR("zhou-silence");
MODULE_DESCRIPTION("This is a simple example!/n");
MODULE_VERSION("v1.0");
MODULE_ALIAS("A simplest example");
