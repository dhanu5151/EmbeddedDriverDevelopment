#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x3726c6aa, "module_layout" },
	{ 0x39f5802, "sysfs_remove_file_ns" },
	{ 0x56c87b84, "kobject_put" },
	{ 0x7e1c4af9, "sysfs_create_file_ns" },
	{ 0x868f8b1f, "kobject_create_and_add" },
	{ 0xb849be00, "kernel_kobj" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0xc5850110, "printk" },
};

MODULE_INFO(depends, "");

