#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
MODULE_LICENSE("Dual BSD/GPL");

struct timer_list mytimer;

static void mytimer_handler(unsigned long data)
{
    printk("mytimer_handler called.\n");
    printk("jiffies at init_timer:%lu.\n",data);
    printk("jiffies now:%lu.\n",jiffies);
    mod_timer(&mytimer,jiffies + HZ);
}


static int  __init mytimer_init(void)
{
    printk("In function:%s\n",__func__);
    init_timer(&mytimer);
    mytimer.expires = jiffies + HZ;
    mytimer.data = jiffies;
    mytimer.function = mytimer_handler;
    add_timer(&mytimer);
    return 0;
}

static void  __exit mytimer_exit(void)
{
    printk("In function:%s\n",__func__);
    del_timer(&mytimer);
}

module_init(mytimer_init);
module_exit(mytimer_exit);
