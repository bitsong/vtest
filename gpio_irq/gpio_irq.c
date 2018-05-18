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

#define	DA850_LCDK_USER_KEY1	GPIO_TO_PIN(2, 5)

#define DA850_USER_LED0		GPIO_TO_PIN(6, 12)

static irqreturn_t button_interrupt(int irq, void *data)
{
	static int led_flag;

	led_flag=gpio_get_value(DA850_LCDK_USER_KEY1);
	printk("%d :irq handler value=%d, \n",irq, led_flag);
	gpio_set_value(DA850_USER_LED0, led_flag);

	return IRQ_HANDLED;
}


static  __init int gpio_irq_init(void)
{
	int ret;
	
	ret = gpio_request(DA850_USER_LED0, "led");
	if(ret)
	{
		printk("request led failed!\n");
		return ret;
	}

	gpio_direction_output(DA850_USER_LED0, 0);
	ret= gpio_request(DA850_LCDK_USER_KEY1, "key");
	if(ret)
	{
		printk("request key failed!\n");
		goto ERR_request_key;
	}
	ret= request_irq(gpio_to_irq(DA850_LCDK_USER_KEY1), button_interrupt, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "key", "intrerrupt");
	if(ret)
	{
		printk(KERN_ERR "can not request interrupt!\n");
		goto ERR_request_irq;
	}
	else
	{
		printk(KERN_INFO "gpio irq register!\n");
		return ret;
	}
 
ERR_request_irq:
	gpio_free(DA850_LCDK_USER_KEY1);
ERR_request_key:
	gpio_free(DA850_USER_LED0);
    return ret;
}

static __exit void gpio_irq_exit(void)
{
	printk(KERN_INFO "gpio irq unregiseter!\n");
	free_irq(gpio_to_irq(DA850_LCDK_USER_KEY1), "intrerrupt");
	gpio_free(DA850_LCDK_USER_KEY1);
	gpio_free(DA850_USER_LED0);
}

module_init(gpio_irq_init);
module_exit(gpio_irq_exit);

MODULE_DESCRIPTION("gpio irq driver");
MODULE_AUTHOR("ws@haotongtech.com");
MODULE_LICENSE("GPL");
