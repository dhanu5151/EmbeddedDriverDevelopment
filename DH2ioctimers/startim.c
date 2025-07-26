#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include "myheader.h"

static dev_t dev = 0;
static struct class *dev_class;
static struct device *cdevice;
static struct cdev my_cdev;
static struct hrtimer my_timer;
static int timer_started = 0;

static enum hrtimer_restart timer_func(struct hrtimer *timer) {
    pr_info("Timer callback called\n");
    return HRTIMER_NORESTART;
}

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    if (cmd == MY_START_TIMER) {
        /*if (timer_started == 0) {
            hrtimer_init(&my_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
            my_timer.function = timer_func;
            hrtimer_start(&my_timer, ktime_set(1, 0), HRTIMER_MODE_REL);
            timer_started = 1;
            pr_info("Timer started\n");*/
            
            switch(cmd)
            {
            	case MY_START_TIMER:
			hrtimer_init(&my_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
			my_timer.function = timer_func;
			hrtimer_start(&my_timer, ktime_set(1, 0), HRTIMER_MODE_REL);
			timer_started = 1;
			pr_info("Timer started\n");

            		break;
            	case MY_STOP_TIMER:
			hrtimer_cancel(&my_timer);
			timer_started = 0;
			pr_info("Timer stopped\n");
			
			break;
            }
            
        }
    }
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = my_ioctl,
};

static int __init my_mod_init(void) {
    int ans;
    pr_info("Hello world from %s!\n", KBUILD_MODNAME);
    ans = alloc_chrdev_region(&dev, 0, 1, MY_DEV_NAME);
    if (ans < 0) {
        pr_err("Error in major:minor allotment!\n");
        return -1;
    }
    pr_info("major:minor %d:%d allotted!\n", MAJOR(dev), MINOR(dev));

    cdev_init(&my_cdev, &fops);
    ans = cdev_add(&my_cdev, dev, 1);
    if (ans < 0) {
        pr_err("Could not add cdev to kernel!\n");
        goto r_cdev;
    }

    dev_class = class_create(THIS_MODULE, MY_CLASS_NAME);
    if (IS_ERR(dev_class)) {
        pr_err("Could not create device class %s\n", MY_CLASS_NAME);
        goto r_class;
    }

    cdevice = device_create(dev_class, NULL, dev, NULL, MY_DEV_NAME);
    if (IS_ERR(cdevice)) {
        pr_err("Could not create device %s\n", MY_DEV_NAME);
        goto r_device;
    }

    return 0;

r_device:
    class_destroy(dev_class);
r_class:
    cdev_del(&my_cdev);
r_cdev:
    unregister_chrdev_region(dev, 1);

    return -1;
}

static void __exit my_mod_exit(void) {
    if (timer_started == 1) {
        hrtimer_cancel(&my_timer);
        timer_started = 0;
    }
    pr_info("Goodbye world from %s!\n", KBUILD_MODNAME);
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev, 1);
    pr_info("major:minor numbers freed up...\n");
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Start Timer IOCTL on char device!");

