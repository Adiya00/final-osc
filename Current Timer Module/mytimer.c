#include <linux/module.h>
#include <linux/init.h>
#include <linux/hrtimer.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL")
MODULE_AUTHOR("Noyan")
MODULE_DESCRIPTION("Current Timer - Linux Kernel Module");

static struct hrtimer mytimer;
u64 start_t;

static enum hrtimer_restart test_hrtimer_handler(struct hrtimer *timer) {
  u64 now_t = jiffies;
  printk("start_t - now_t = %u\n", jiffies_to_msecs(now_t - start_t));
  return HRTIMER_NORESTART;
}

static int __init ModuleInit(void) {
  printk("Hello, LKM!\n");
  hrtimer_init(&mytimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
  mytimer.function = &test_hrtimer_handler;
  start_t = jiffies;
  hrtimer_start(&mytimer, ms_to_ktime(100), HRTIMER_MODE_REL);
  return 0;
}

static void __exit ModuleExit(void) {
  hrtimer_cancel(&mytimer);
  printk("Goodbye, LKM\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
