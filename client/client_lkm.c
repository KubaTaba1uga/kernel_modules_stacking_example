#include <linux/init.h>
#include <linux/module.h>

#define THE_ONE 0xfedface

#if 1
MODULE_LICENSE("Dual MIT/GPL");
#else
MODULE_LICENSE("MIT");
#endif

extern int exp_int;

#if (BITS_PER_LONG == 32)
extern u32 get_skey(int p);
#else
extern u64 get_skey(int p);
#endif

static int __init client_lkm_init(void) {
  pr_info("Inserted\n");

  u64 sk = get_skey(THE_ONE);
  pr_debug("Called get_sky, ret=0x%llx = %llu\n", sk, sk);
  pr_debug("Got exp_int, %d\n", exp_int);

  return 0;
}

static void __exit client_lkm_exit(void) { pr_info("Bye bye my module...\n"); }

module_init(client_lkm_init);
module_exit(client_lkm_exit);
