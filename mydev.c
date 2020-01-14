#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define SUCCESS 0;

MODULE_LICENSE("GPL");

#define DEVICE_NAME "mydevice"

/*prototypes of device functions  */

static int device_open(struct inode* ,struct file*);
static int device_release(struct inode* ,struct file*);
static ssize_t device_read(struct file* ,char* , size_t , loff_t *);
static ssize_t device_write(struct file* ,const char* , size_t , loff_t *);

static int Major;
static int device_open_count;
int Z;

int calc (int Z)
{

    return (Z*Z)%1024;

};

/*This structure points to all device functions*/

static struct file_operations file_ops = {

	.read=device_read,
	.write=device_write,
	.open=device_open,
	.release=device_release

	};

/*When a process read from our device, this gets called.*/

static ssize_t device_read(struct file *flip, char *buffer, size_t len, loff_t *offset)
	{
	
	int count = 0;
   count = put_user(Z, buffer);
return count;
}
/*Called when a process tries to write to our device */

static ssize_t device_write(struct file *flip,const char *buffer, size_t len, loff_t *offset)
	{
	int written;
	written=get_user(Z,buffer);
	Z=calc(Z);	
   	printk(" Value of Z is %d",Z);

   return written;
}




/*Called when a process opens our device*/

static int device_open(struct inode *inode, struct file *file)
	{
	/*If device is open, return busy*/
	if (device_open_count)
		{
		return -EBUSY;
		}
	device_open_count++;
	try_module_get(THIS_MODULE);
	return 0;
	}

/* Called when a process closes our device */

static int device_release(struct inode *inode, struct file *file)
	{
	/*Decrement the open counter  and usage count. Without this, hte module would not unload. */

	device_open_count--;
	module_put(THIS_MODULE);
	return 0;
	}
	

static int __init mydevice_init(void)
	{

	/* Set the msg_ptr to the buffer*/

 Major = register_chrdev(0, "mydevice", &file_ops);
 if (Major<0) 
	{
	printk(KERN_ALERT "Could not register device: %d \n", Major);
	return Major;
	}
	else
	{
	printk("mydevice module loaded with device major number %d \n", Major);
	return 0;
	}

	}

static void __exit mydevice_exit(void)
	{
	/* Remember - we have to clean up  after ourslves. Unregister the chracter device*/

unregister_chrdev(Major, "mydevice");
printk(KERN_INFO "Goodbye\n");
	}

/* Register module function */

module_init(mydevice_init);
module_exit(mydevice_exit);
