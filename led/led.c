// #include <linux/init.h>
// #include <linux/module.h>
// #include <linux/kernel.h>
// #include <linux/types.h>
// #include <linux/gpio.h>
// #include <linux/leds.h>
// #include <linux/platform_device.h>

// #include <asm/mach-types.h>
// #include <asm/mach/arch.h>
// #include <mach/da8xx.h>
// #include <mach/mux.h>

#include <linux/module.h>

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <linux/i2c-gpio.h>
#include <linux/leds.h>
#include <linux/gpio_keys.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
#include <linux/mfd/davinci_aemif.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>

#include <mach/cp_intc.h>
#include <mach/da8xx.h>
#include <mach/mux.h>
#include <mach/nand.h>

#define DA850_USER_LED0	GPIO_TO_PIN(6, 12)
#define DA850_USER_LED1	GPIO_TO_PIN(6, 13)
#define DA850_USER_LED2	GPIO_TO_PIN(2, 12)
#define DA850_USER_LED3	GPIO_TO_PIN(0, 9)

#define CONFIG_DAVINCI_MUX 1

static const short omapl138_lcdk_led_pin_mux[] __initconst = {
	DA850_GPIO6_12,
	DA850_GPIO6_13,
	DA850_GPIO2_12,
	DA850_GPIO0_9,
	-1
};


static struct gpio_led da850_evm_ht_leds[] = {
	{
		.active_low = 0,
		.gpio = DA850_USER_LED0,
		.name = "user_led0",
		.default_trigger = "default-on",
	},
	{
		.active_low = 0,
		.gpio = DA850_USER_LED1,
		.name = "user_led1",
		.default_trigger = "default-on",
	},
	{
		.active_low = 0,
		.gpio = DA850_USER_LED2,
		.name = "user_led2",
		.default_trigger = "default-on",
	},
	{
		.active_low = 0,
		.gpio = DA850_USER_LED3,
		.name = "user_led3",
		.default_trigger = "default-on",
	},
};

static struct gpio_led_platform_data da850_evm_ht_leds_pdata = {
	.leds = da850_evm_ht_leds,
	.num_leds = ARRAY_SIZE(da850_evm_ht_leds),
};

static void led_dev_release(struct device *dev)
{
};

static struct platform_device da850_evm_ht_leds_device = {
	.name		= "leds-gpio",
	.id		= 1,
	.dev = {
		.platform_data = &da850_evm_ht_leds_pdata,
		.release = led_dev_release,
	}
};

static int __init led_platform_init(void)
{
	int ret;
#if 0
	ret = davinci_cfg_reg_list(omapl138_lcdk_led_pin_mux);
	if (ret)
		pr_warning("User LED mux failed :ret= %d\n", ret);
	else
		printk("LED mux success!");
#endif
	ret = platform_device_register(&da850_evm_ht_leds_device);
	if (ret)
		pr_warning("Could not register som GPIO expander LEDS");
	else
		printk(KERN_INFO "LED register sucessful!\n");

	return ret;
}

static void __exit led_platform_exit(void)
{
	platform_device_unregister(&da850_evm_ht_leds_device);

	printk(KERN_INFO "LED unregister!\n");
}

module_init(led_platform_init);
module_exit(led_platform_exit);

MODULE_DESCRIPTION("Led platform driver");
MODULE_AUTHOR("Haotong");
MODULE_LICENSE("GPL");
