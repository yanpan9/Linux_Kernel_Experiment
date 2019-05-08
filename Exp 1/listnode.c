#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>


MODULE_LICENSE("GPL");

static char* whom = "world";
static int num = 1;

struct listnode{
    int val_;
    struct listnode* next_;
}

int insert(struct listnode* head, val)
{
    struct listnode* node = head;
    while (node->next_ != NULL)
    {
        node = node->next_;
    }
    struct listnode new_node = {->val=val, ->next_=NULL};
    node->next_ = &new_node;
    return 1;
}

int delete(struct listnode* head, val)
{
    if (head->val==val)
    {
        head = head->next_
        return 1;
    }
    else
    {
        struct listnode* slow = head;
        struct listnode* fast = head->next_;
        while (fast!=NULL)
        {
            if (fast->val==val)
            {
                slow->next_=fast->next_;
                return 1;
            }
            else
            {
                slow = fast;
                fast = fast->next_;
            }
        }
        return -1;
    }
}

int lookup(struct listnode* head, val)
{
    struct listnode* node = head;
    while (node!=NULL)
    {
        if (node->val_==val)
        {
            return 1;
        }
        else
        {
            node = node->next_;
        }
    }
    return -1;
}

int print(struct listnode* head)
{
    struct listnode* node = head;
    int i = 0;
    while (node!=NULL)
    {
        printk(KEAR_ALERT "The %d'th element is %d", i++, node->val);
        node = node->next_;
    }
}

//传递命令参数 S_IRUGO 指明参数可以被所有人读取 
module_param(whom,charp,S_IRUGO);
module_param(num,int,S_IRUGO);

//程序中必须有下列两个函数
static int listnode_init(void)
{
    printk(KERN_ALERT "Init the link list.\n");
    struct listnode head = {.val_=0, .next_=NULL};
    struct listnode* node = &head;
    for (int i=1; i<num; i++)
    {
        struct listnode new_node = {.val=i, .next=NULL}
        node->next = &new_node;
        node = node->next_;
    }
    printk(KERN_ALERT "Init complete. The link list is: \n");
    print(&head)

    int insert_val = 99;
    insert(&head, insert_val);
    printk(KERN_ALERT "After insert integer %d, the link list is: \n", insert_val)

    int delete_val = 0;
    if (delete(&head, delete_val)==1)
    {
        printk(KERN_ALERT "Delete success. After detete, the link list is: \n");
        print(&head);
    }
    else
    {
        printk(KERN_ALERT "Delete failed.\n");
    }
    return 0;

    int lookup_val = 99;
    if (lookup(&head, lookup_val)==1)
    {
        printk(KERN_ALERT "Lookup %d success.\n", lookup_val);
    }
    else
    {
        printk(KERN_ALERT "Lookup %d failed.\n", lookup_val);
    }
}

static void listnode_exit(void)
{
    printk(KERN_ALERT "goodbye, link list kernel./n");
}

//加载or卸载模块
module_init(listnode_init);
module_exit(listnode_exit);
// 可选 
MODULE_AUTHOR("yan pan");
MODULE_DESCRIPTION("This is a simple example of link list!/n");
MODULE_VERSION("v1.0");
MODULE_ALIAS("A simplest example of link list");
