#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/gpio.h>
#include <linux/gpio_keys.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/irq.h>
#include <asm/io.h>

#include <mach/cp_intc.h>
#include <mach/da8xx.h>
#include <mach/mux.h>

#define	DA850_LCDK_USER_KEY1            GPIO_TO_PIN(2, 5)

static struct input_dev *button_dev;

static irqreturn_t button_interrupt(int irq, void *data)
{
	/*** input_event() - report new input event */
	struct input_dev *dev;  

	dev = data;
	printk("%d :irq handler, \n",irq);
	input_report_key(dev, KEY_K, gpio_get_value(DA850_LCDK_USER_KEY1));
	input_sync(dev);

	return IRQ_HANDLED;
}


static  __init int keys_init(void)
{
	int err;
	/*** input_allocate_device - allocate memory for new input device */
	button_dev= input_allocate_device();
	if(IS_ERR_OR_NULL(button_dev))
	{
		err = -ENOMEM;
		return err;
	}
	button_dev->name="PTT";
	/*** input_set_capability - mark device as capable of a certain event*/
	input_set_capability(button_dev, EV_KEY, BTN_0);
	/*** input_register_device - register device with input core */
	err = input_register_device(button_dev);
	//davinci_cfg_reg_list(omapl138_lcdk_keys_pin_mux);
	if (err)
	{
		pr_err("failed to register input keys_device\n");
		goto ERR_input_reg;
	}
	/*** static inline int __must_check request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char *name, void *dev)	*/
	err = request_irq(gpio_to_irq(DA850_LCDK_USER_KEY1), button_interrupt, IRQF_TRIGGER_FALLING |IRQF_TRIGGER_RISING, "BUTTON", (void *)button_dev);
	if(err)
	{
		printk(KERN_ERR "can not alllcate irq %d\n", gpio_to_irq(DA850_LCDK_USER_KEY1));
		goto ERR_request_irq;
	}
    else
	{
		printk(KERN_INFO "input key regiseter!\n");
		printk(KERN_INFO " alllcate irq %d\n", gpio_to_irq(DA850_LCDK_USER_KEY1));
		return err;
	}
 
ERR_request_irq:
	input_unregister_device(button_dev);
ERR_input_reg:
	input_free_device(button_dev);
    return err;
}

static __exit void keys_exit(void)
{
	printk(KERN_INFO "input key unregiseter!\n");
	free_irq(gpio_to_irq(DA850_LCDK_USER_KEY1), button_dev);
	input_unregister_device(button_dev);
	input_free_device(button_dev);
}

module_init(keys_init);
module_exit(keys_exit);

MODULE_DESCRIPTION("key input driver");
MODULE_AUTHOR("ws@haotongtech.com");
MODULE_LICENSE("GPL");
