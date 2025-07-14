#include <linux/init.h>
#include <linux/module.h>
#include <linux/sysfs.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/time.h>

#define LOW 0
#define HIGH 1

#define GPIO_TRIG 23
#define GPIO_ECHO 24

static ssize_t sonic_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    gpio_set_value(GPIO_TRIG, HIGH);
    udelay(10);
    gpio_set_value(GPIO_TRIG, LOW);

    struct timespec64 start, end, diff;
    while (gpio_get_value(GPIO_ECHO) == LOW)
        ;
    ktime_get_real_ts64(&start);

    while (gpio_get_value(GPIO_ECHO) == HIGH)
        ;
    ktime_get_real_ts64(&end);

    unsigned long ns;
    diff = timespec64_sub(end, start);
    ns = timespec64_to_ns(&diff);
    
    unsigned long distance;
    distance = (ns * 343 )/(1000000 * 2);

    return sprintf(buf, "%lu\n", distance);
}

static struct kobj_attribute sonic_attr =
    __ATTR(sonic, 0444, sonic_show, NULL);

static int __init sonic_init(void)
{
    int err;
    
    printk("sonic init\n");

    err = sysfs_create_file(kernel_kobj, &sonic_attr.attr);
    if (err)
        return err;

    gpio_direction_output(GPIO_TRIG, LOW);
    gpio_direction_input(GPIO_ECHO);

    return 0;
}

static void __exit sonic_exit(void)
{
    printk("sonic exit\n");

    sysfs_remove_file(kernel_kobj, &sonic_attr.attr);
}

module_init(sonic_init);
module_exit(sonic_exit);

MODULE_LICENSE("GPL");
