#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x6b664b27, "module_layout" },
	{ 0xf20dabd8, "free_irq" },
	{ 0xfe990052, "gpio_free" },
	{ 0x2072ee9b, "request_threaded_irq" },
	{ 0x11f447ce, "__gpio_to_irq" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x368c1ac5, "davinci_soc_info" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0x27e1a049, "printk" },
	{ 0x6c8d5ae8, "__gpio_get_value" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

