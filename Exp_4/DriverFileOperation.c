#include "DriverFileOperation.h"

int DriverOpen(struct inode *pInodeStruct, struct file *pFileStruct)
{
    DeviceOpenNumbers++;
    printk(DEVICE_NAME ":device opened %d times.\n",DeviceOpenNumbers);
    return 0;
}

int DriverRelease(struct inode *pInodeStruct, struct file *pFileStruct)
{
    printk(DEVICE_NAME ": close invoked.\n");
    return 0;
}

ssize_t DriverRead(struct file *pFileStruct, char __user *pBuffer, size_t count, loff_t *pOffset)
{
    int error_count = 0;
    error_count = copy_to_user(pBuffer,msg,size_of_msg);
    if(error_count==0)
    {
        printk(DEVICE_NAME ":send %d characters to user.\n", size_of_msg);
        return (size_of_msg=0);
    }
    else
    {
        printk(DEVICE_NAME ":failed to read from device.\n");
        return -EFAULT;
    }
    //printk(DEVICE_NAME ":read invoked.\n");
    //return 0;
}

ssize_t DriverWrite(struct file *pFileStruct, const char __user *pBuffer, size_t count, loff_t *pOffset)
{
    printk("Entering driver write.\n");
    char temp_msg[MSG_COUNT] = {0};
    copy_from_user(temp_msg, pBuffer, count);
    sprintf(msg, "%s(%d letters)", temp_msg, count);
    size_of_msg=strlen(msg);
    printk(DEVICE_NAME ":received %d characters from the user.\n",count);
    return 0;
}

