#include <linux/fs.h>
#include <linux/cdev.h>

#define MY_MAJOR 42
#define MY_MAX_MINORS 5

static dev_t dev_num;

// Structure to use that contains the information about this device
struct my_device_data {
    struct cdev cdev;
};

struct my_device_data my_device_data;

static int my_device_open(struct inode *inode, struct file *file)
{
    struct my_device_data *my_data;
    my_data = container_of(inode->i_cdev, struct my_device_data, cdev);
    return 0;

}

static ssize_t my_device_read(struct file *file, char *user_buffer, size_t size, loff_t *offset)
{
    struct my_device_data *my_data;
    my_data = (struct my_device_data *) file->private_data;
    return 0;

}

static ssize_t my_device_write(struct file *file, const char __user *user_buffer, size_t size, loff_t *offset)
{
    
    return 0;
}

static int my_device_release(struct inode *inode, struct file *file)
{

    return 0;
}

static long my_device_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    return 0;
}

const struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_device_open,
    .read = my_device_read,
    .write = my_device_write,
    .release = my_device_release,
    .unlocked_ioctl = my_device_ioctl
};

int init_module(void)
{
    int ret;

    // Dynamic allocate device number
    ret = alloc_chrdev_region(&dev_num, 0, MY_MAX_MINORS, "my_device");    
    if (ret < 0) return ret;

    printk(KERN_INFO "Allocated major %d\n", MAJOR(dev_num));

    // Register cdev
    cdev_init(&my_device_data.cdev, &my_fops);
    cdev_add(&my_device_data.cdev, dev_num, MY_MAX_MINORS);

    return 0;
}

void cleanup_module(void)
{
    cdev_del(&my_device_data.cdev);
    unregister_chrdev_region(dev_num, MY_MAX_MINORS);
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("My custom driver");
