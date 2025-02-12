#include "charDevDriver.h"
#include "DriverFileOperation.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yanpan");
MODULE_DESCRIPTION("a simple linux char driver example");

/**
 * linux操作系统中一切都是文件，设备也是文件。
 * linux/fs.h定义file_operations结构体
 * 这里定义文件操作的相关联的回调函数
 * 字符设备的基本功能包括打开，关闭，读取，写入
 */

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open  = DriverOpen,
    .release = DriverRelease,
    .read = DriverRead,
    .write = DriverWrite,
};

static int __init charMsgDriverInit(void)
{
    printk("charMsgDriver init...");
    //
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if(majorNumber < 0)
    {
        printk("charMsgDriver: failed to register a major number.\n");
        return majorNumber;
    }

    printk("charMsgDriver: registered major number :%d successfully\n", majorNumber);

    //注册设备类
    pcharMsgDriverClass = class_create(THIS_MODULE, CLASS_NAME);
    if(IS_ERR(pcharMsgDriverClass))
    {
        //注册失败，清理环境
        unregister_chrdev(majorNumber, DEVICE_NAME);

        printk("charMsgDriver: failed to register device class.\n");
        return PTR_ERR(pcharMsgDriverClass);
    }

    //注册设备驱动
    pCharMsgDriverDevice = device_create(pcharMsgDriverClass, NULL, MKDEV(majorNumber,0), NULL, DEVICE_NAME);
    if(IS_ERR(pCharMsgDriverDevice))
    {
        //注册失败，清理环境
        class_destroy(pcharMsgDriverClass);
        unregister_chrdev(majorNumber,DEVICE_NAME);

        printk("charMsgDriver: failed to create device.\n");
        return PTR_ERR(pCharMsgDriverDevice);
    }

    printk("charMsgDriver: device create correctly.\n");
    return 0;
}

static void __exit charMsgDriverExit(void)
{
    device_destroy(pcharMsgDriverClass, MKDEV(majorNumber,0));
    class_unregister(pcharMsgDriverClass);
    class_destroy(pcharMsgDriverClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk("charMsgDriver: goodbye.\n");
}

module_init(charMsgDriverInit);
module_exit(charMsgDriverExit);
