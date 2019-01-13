#ifndef _BANKING_H
#define _BANKING_H 1

#include "banks.h"

extern volatile int* tramp_data;

extern void* trampoline();

/* -- Thanks PeteE! - suggested alternative by PeteE
 * realname - the function you want to be able to call
 * bank - the bank switch address for this function
 * return_type - the type of value returned by the function
 * banked_name - the new name 
 * param_types - the parenthesized parameter signature list
 * param_list - the parameter name list
 *
 * Use DECLARE_BANKED in your header files to create
 * convenient banking calls with the same signatures
 * as the original functions. 
 * 
 * example:  given function in BANK_1, int sum(int a, int b)
 *
 *   DECLARE_BANKED(sum, BANK_1, int, far_sum, (int a, int b), (a, b))
 *
 * generates a static inline function:
 *
 *   static inline int far_sum(int a, int b);
 * 
 * functions with a void return type use a different macro. Given
 * function such as void cputc(const char c):
 * 
 *   DECLARE_BANKED_VOID(cputc, BANK_1, far_cputc, (const char c), (c))
 * 
 * generates a static inline function:
 * 
 *   static inline void far_cputc(const char c);
 *
 * Assumes MYBANK is defined as the callers bank switch address
 * 
 * Trampoline code abuses R12, and R0
 */

#define DECLARE_BANKED(realname, bank, return_type, banked_name, param_types, param_list) \
__attribute__ ((gnu_inline, always_inline)) \
static inline return_type banked_name param_types { \
  static const int foo[]={(int)MYBANK, (int)realname, (int)bank}; \
  __asm__("li r12, %0\n\tmov r12,@tramp_data\n\t" : : "i" (foo): "r12" ); \
  return trampoline param_list; \
}

#define DECLARE_BANKED_VOID(realname, bank, banked_name, param_types, param_list) \
__attribute__ ((gnu_inline, always_inline)) \
static inline void banked_name param_types { \
  static const int foo[]={(int)MYBANK, (int)realname, (int)bank}; \
  __asm__("li r12, %0\n\tmov r12,@tramp_data\n\t" : : "i" (foo): "r12" ); \
  trampoline param_list; \
}

#endif

