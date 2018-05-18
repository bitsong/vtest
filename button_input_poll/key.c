#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/gpio.h>
#include <linux/gpio_keys.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/module.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>

#include <mach/cp_intc.h>
#include <mach/da8xx.h>
#include <mach/mux.h>

#define	DA850_LCDK_USER_KEY1            GPIO_TO_PIN(2, 5)

#define        DA850_LCDK_KEYS_DEBOUNCE_MS     10
#define        DA850_LCDK_GPIO_KEYS_POLL_MS    200

static const short omapl138_lcdk_keys_pin_mux[] __initconst = {
	DA850_GPIO2_5,
	-1
};

static struct gpio_keys_button omapl138_lcdk_evm_keys[] = {
	{
		.type                   = EV_KEY,
		.active_low             = 1,
		.wakeup                 = 0,
		.debounce_interval      = DA850_LCDK_KEYS_DEBOUNCE_MS,
		.code                   = KEY_K,
		.gpio                   = DA850_LCDK_USER_KEY1,
		.desc                   = "pb1",
	},
};

static struct gpio_keys_platform_data omapl138_lcdk_evm_keys_pdata = {
	.buttons = omapl138_lcdk_evm_keys,
	.nbuttons = ARRAY_SIZE(omapl138_lcdk_evm_keys),
	.poll_interval = DA850_LCDK_GPIO_KEYS_POLL_MS,
};

static struct platform_device omapl138_lcdk_evm_keys_device = {
	.name = "gpio-keys-polled",
	.id = 0,
	.dev = {
		.platform_data = &omapl138_lcdk_evm_keys_pdata
	},
};

static  __init int omapl138_lcdk_keys_init(void)
{
	int err;

	//davinci_cfg_reg_list(omapl138_lcdk_keys_pin_mux);
	err = platform_device_register(&omapl138_lcdk_evm_keys_device);
	if (err)
		pr_err("failed to register omapl138_lcdk_evm_keys_device\n");
    else
        printk(KERN_INFO "key regiseter!\n");
    return err;
};

static __exit void omapl138_lcdk_keys_exit(void)
{

    platform_device_unregister(&omapl138_lcdk_evm_keys_device);
    printk(KERN_INFO "key unregiseter!\n");
}

module_init(omapl138_lcdk_keys_init);
module_exit(omapl138_lcdk_keys_exit);

MODULE_DESCRIPTION("key platform driver");
MODULE_AUTHOR("ws@haotongtech.com");
MODULE_LICENSE("GPL");
