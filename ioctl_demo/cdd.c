#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/kfifo.h>
#include "pchar_ioctl.h"

// psuedo char device
#define MAXLEN 32
static struct kfifo buffer;

// function declarations
static int pchar_open(struct inode *pinode, struct file *pfile);
static int pchar_close(struct inode *pinode, struct file *pfile);
static ssize_t pchar_write(struct file *pfile, const char * __user pubuf, size_t length, loff_t *pfpos);
static ssize_t pchar_read(struct file *pfile, char * __user pubuf, size_t length, loff_t *pfpos);
static long pchar_ioctl(struct file *pfile, unsigned int cmd, unsigned long param);

// global variables
static int major = 250;
static dev_t devno;
static struct class *pclass;
static struct cdev pchar_cdev;

static struct file_operations pchar_fops = {
    .owner = THIS_MODULE,
    .open = pchar_open,
    .release = pchar_close,
    .write = pchar_write,
    .read = pchar_read,
    .unlocked_ioctl = pchar_ioctl
};

// device driver -- initialization code
static int __init pchar_init(void) {
    int ret;
    struct device * pdevice;
    printk("%s: pchar_init() called.\n", THIS_MODULE->name);
    // allocate device kfifo (buffer)
    ret = kfifo_alloc(&buffer, MAXLEN, GFP_KERNEL);
    if(ret < 0) {
        printk("%s: kfifo_alloc() failed.\n", THIS_MODULE->name);
        return ret;
    }
    printk("%s: kfifo_alloc() allocated device buffer.\n", THIS_MODULE->name);
    // allocate device number dynamically
    devno = MKDEV(major, 0);
    ret = alloc_chrdev_region(&devno, 0, 1, "pchar");
    if(ret < 0) {
        printk("%s: alloc_chrdev_region() failed.\n", THIS_MODULE->name);
        kfifo_free(&buffer);
        return -1;
    }
    major = MAJOR(devno);
    printk("%s: alloc_chrdev_region() allocated device number %d/%d.\n", 
                        THIS_MODULE->name, major, MINOR(devno));
    // create device class
    pclass = class_create(THIS_MODULE, "pchar_class");
    if(IS_ERR(pclass)) {
        printk("%s: class_create() failed.\n", THIS_MODULE->name);
        unregister_chrdev_region(devno, 1);
        kfifo_free(&buffer);
        return -1;
    }
    printk("%s: class_create() created the device class.\n", THIS_MODULE->name);
    // create device file
    pdevice = device_create(pclass, NULL, devno, NULL, "pchar%d", 0);
    if(IS_ERR(pdevice)) {
        printk("%s: device_create() failed.\n", THIS_MODULE->name);
        class_destroy(pclass);
        unregister_chrdev_region(devno, 1);
        kfifo_free(&buffer);
        return -1;
    }
    printk("%s: device_create() created the device file.\n", THIS_MODULE->name);
    // initialize cdev var and add into kernel database
    cdev_init(&pchar_cdev, &pchar_fops);
    ret = cdev_add(&pchar_cdev, devno, 1);
    if(ret < 0) {
        printk("%s: cdev_add() failed.\n", THIS_MODULE->name);
        device_destroy(pclass, devno);
        class_destroy(pclass);
        unregister_chrdev_region(devno, 1);
        kfifo_free(&buffer);
        return -1;
    }
    printk("%s: cdev_add() added char device into kernel.\n", THIS_MODULE->name);
    return 0;
}

// device driver -- de-initialization code
static void __exit pchar_exit(void) {
    printk("%s: pchar_exit() called.\n", THIS_MODULE->name);
    // delete cdev from kernel database
    cdev_del(&pchar_cdev);
    printk("%s: cdev_del() deleted char device from kernel.\n", THIS_MODULE->name);
    // device device file
    device_destroy(pclass, devno);
    printk("%s: device_destroy() destroyed device file.\n", THIS_MODULE->name);
    // destroy device class
    class_destroy(pclass);
    printk("%s: class_destroy() destroyed device class.\n", THIS_MODULE->name);
    // release device number
    unregister_chrdev_region(devno, 1);
    // release device kfifo (buffer)
    kfifo_free(&buffer);
    printk("%s: kfifo_free() released device buffer.\n", THIS_MODULE->name);
    printk("%s: unregister_chrdev_region() released device number.\n", THIS_MODULE->name);
}

// pchar device -- open() operation
int pchar_open(struct inode *pinode, struct file *pfile) {
    printk("%s: pchar_open() called.\n", THIS_MODULE->name);
    return 0;
}

// pchar device -- release() operation
int pchar_close(struct inode *pinode, struct file *pfile) {
    printk("%s: pchar_close() called.\n", THIS_MODULE->name);
    return 0;
}

// pchar device -- write() operation
ssize_t pchar_write(struct file *pfile, const char * __user pubuf, size_t length, loff_t *pfpos) {
    int avail_bytes, bytes_to_write, nbytes, ret;
    printk("%s: pchar_write() called.\n", THIS_MODULE->name);
    // get available bytes (for writing -- empty space) from device buffer
    avail_bytes = kfifo_avail(&buffer);
    // how many bytes to be copied into device buffer i.e. MIN(available bytes, length of user buffer)
    bytes_to_write = avail_bytes < length ? avail_bytes : length;
    // if number of bytes to write is zero, return error (no space available)
    if(bytes_to_write == 0) {
        printk("%s: pchar_write() - device buffer full.\n", THIS_MODULE->name);
        return -ENOSPC;
    }
    // copy the bytes from user buffer to device buffer
    ret = kfifo_from_user(&buffer, pubuf, bytes_to_write, &nbytes);
    // return numnber of bytes successfully copied
    printk("%s: pchar_write() copied %d bytes. new file pos = %lld\n", THIS_MODULE->name, nbytes, *pfpos);
    return nbytes;
}

// pchar device -- read() operation
ssize_t pchar_read(struct file *pfile, char * __user pubuf, size_t length, loff_t *pfpos) {
    int avail_bytes, bytes_to_read, nbytes, ret;
    printk("%s: pchar_read() called.\n", THIS_MODULE->name);
    // get available bytes (for reading -- filled space) from device buffer
    avail_bytes = kfifo_len(&buffer);
    // how many bytes to be copied into user buffer i.e. MIN(available bytes, length of user buffer)
    bytes_to_read = avail_bytes < length ? avail_bytes : length;
    // if number of bytes to read is zero, return 0 (end of device)
    if(bytes_to_read == 0) {
        printk("%s: pchar_read() - end of device buffer reached.\n", THIS_MODULE->name);
        return 0; // read() syscall returns 0 on EOF.
    }
    // copy the bytes from device buffer to user buffer
    ret = kfifo_to_user(&buffer, pubuf, bytes_to_read, &nbytes);
    // return numnber of bytes successfully copied
    printk("%s: pchar_read() copied %d bytes. new file pos = %lld\n", THIS_MODULE->name, nbytes, *pfpos);
    return nbytes;
}

// pchar device -- ioctl() operation
long pchar_ioctl(struct file *pfile, unsigned int cmd, unsigned long param) {
    info_t info;
    int nbytes;
    switch(cmd) {
        case FIFO_CLEAR:
            kfifo_reset(&buffer);
            printk("%s: pchar_ioctl() - cleared kfifo buffer.\n", THIS_MODULE->name);
            break;
        case FIFO_GET_INFO:
            info.size = kfifo_size(&buffer);
            info.len = kfifo_len(&buffer);
            info.avail = kfifo_avail(&buffer);
            nbytes = sizeof(info_t) - copy_to_user((void*)param, &info, sizeof(info_t));
            printk("%s: pchar_ioctl() - collected buffer info (%d bytes).\n", THIS_MODULE->name, nbytes);
            break;
        //case FIFO_RESIZE:
            //1. allocate an array dynamically to hold kfifo data (len).
            //2. read all data from kfifo into that array.
            //3. release the current kfifo buffer.
            //4. allocate new kfifo buffer according to new size (param).
            //5. write all data from temp array to kfifo.
            //6. release temp array.
        default:
            printk("%s: pchar_ioctl() - invalid operation.\n", THIS_MODULE->name);
            return -EINVAL;
    }
    return 0;
}

module_init(pchar_init);
module_exit(pchar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nilesh Ghule <nilesh@sunbeaminfo.com>");
MODULE_DESCRIPTION("Simple Pseudo Char Device Driver");