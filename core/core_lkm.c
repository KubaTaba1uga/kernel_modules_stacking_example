#include <linux/init.h>
#include <linux/module.h>

#define THE_ONE 0xfedface

MODULE_LICENSE("Dual MIT/GPL");

int exp_int = 200;

EXPORT_SYMBOL_GPL(exp_int);

#if (BITS_PER_LONG == 32)
u32 get_skey(int p);
#else
u64 get_skey(int p);
#endif
{

#if (BITS_PER_LONG == 32)
  u32 secret = 0x567def;
#else
  u32 secret = 0x123abc4567def;
#endif

  if (p == THE_ONE) {
    return secret;
  }

  return 0;
}

EXPORT_SYMBOL_GPL(get_skey);
