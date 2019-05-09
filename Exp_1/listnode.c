#include<linux/init.h>
#include<linux/slab.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>


MODULE_LICENSE("GPL");

static int num = 10;

struct listnode{
    int val_;
    struct listnode* next_;
};


struct listnode* init_node(int val)
{
    struct listnode *node = (struct listnode*)kmalloc(sizeof(struct listnode), GFP_KERNEL);
    node->val_=val;
    node->next_=NULL;
    return node;
}

int insert(struct listnode* head, int val)
{
    struct listnode* node = head->next_;
    while (node->next_ != NULL)
    {
        node = node->next_;
    }
    struct listnode* new_node = init_node(val);
    node->next_ = new_node;
    return 1;
}

int delete(struct listnode* head, int val)
{
    struct listnode* slow = head;
    struct listnode* fast = head->next_;
    while (fast!=NULL)
    {
        if (fast->val_==val)
        {
            slow->next_=fast->next_;
            kfree(fast);
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

int lookup(struct listnode* head, int val)
{
    struct listnode* node = head->next_;
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

void print(struct listnode* head)
{
    struct listnode* node = head->next_;
    int i = 0;
    while (node!=NULL)
    {
        printk(KERN_ALERT "The %d'th element is %d.\n", i++, node->val_);
        node = node->next_;
        if (i>50)break;
    }
}

int destroy(struct listnode* head)
{
    while (head != NULL)
    {
        struct listnode* node = head;
        head = head->next_;
        kfree(node);
    }
    return 1;
}

//传递命令参数 S_IRUGO 指明参数可以被所有人读取 
module_param(num,int,S_IRUGO);

//程序中必须有下列两个函数
static int listnode_init(void)
{
    printk(KERN_ALERT "Init the link list.\n");
    struct listnode *head = init_node(-1);
    struct listnode* node = head;
    int i;
    for (i=0; i<num; i++)
    {
        struct listnode *new_node = init_node(i);
        node->next_ = new_node;
        node = node->next_;
    }
    printk(KERN_ALERT "Init complete. The link list is: \n");
    print(head);
    
    int insert_val = 99;
    insert(head, insert_val);
    printk(KERN_ALERT "After insert integer %d, the link list is: \n", insert_val);
    print(head);
    
    int delete_val = 0;
    if (delete(head, delete_val)==1)
    {
        printk(KERN_ALERT "Delete success. After detete, the link list is: \n");
        print(head);
    }
    else
    {
        printk(KERN_ALERT "Delete failed.\n");
    }

    int lookup_val = 99;
    if (lookup(head, lookup_val)==1)
    {
        printk(KERN_ALERT "Lookup %d success.\n", lookup_val);
    }
    else
    {
        printk(KERN_ALERT "Lookup %d failed.\n", lookup_val);
    }
    destroy(head);
}

static void listnode_exit(void)
{
    printk(KERN_ALERT "goodbye, link list kernel.\n");
}

//加载or卸载模块
module_init(listnode_init);
module_exit(listnode_exit);
// 可选 
MODULE_AUTHOR("yan pan");
MODULE_DESCRIPTION("This is a simple example of link list!/n");
MODULE_VERSION("v1.0");
MODULE_ALIAS("A simplest example of link list");
