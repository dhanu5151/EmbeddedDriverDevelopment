#ifndef _MYHEADER_H_
#define _MYHEADER_H_

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>

#define MY_CLASS_NAME        "cdac_cls"
#define MY_DEV_NAME          "cdac_dev"
#define MY_KBUF_SZ           (1024)

#define MY_START_TIMER _IO('t', 1)
#define MY_STOP_TIMER _IO('t', 2)

extern dev_t dev;
extern struct class *dev_class;
extern struct device *cdevice;
extern struct cdev my_cdev;

extern struct hrtimer my_hrtimer;
extern ktime_t interval;

extern struct file_operations fops;

extern int my_open(struct inode *inode, struct file *file);
extern int my_release(struct inode *inode, struct file *file);
extern long my_ioctl(struct file *file, unsigned int cmd, unsigned long args);
extern enum hrtimer_restart my_hrtimer_callback(struct hrtimer *timer);

#endif 


