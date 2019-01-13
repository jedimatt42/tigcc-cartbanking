#include "banking.h"
#include <conio.h>
#include <system.h>

// declare our current bank
#define MYBANK BANK_0

#include "second.h"

DECLARE_BANKED_VOID(set_text, BANK_1, bk_set_text, (), ())
DECLARE_BANKED_VOID(charsetlc, BANK_1, bk_charsetlc, (), ())
DECLARE_BANKED_VOID(halt, BANK_1, bk_halt, (), ())
DECLARE_BANKED_VOID(second, BANK_1, bk_second, (), ())
// this one passes arguments
DECLARE_BANKED_VOID(cputs, BANK_1, bk_cputs, (const char* s), (s))

DECLARE_BANKED(second_retint, BANK_1, int, bk_second_retint, (), ())

void assertEquals(int found, int expected);

void main() {
  bk_set_text();
  bk_charsetlc();

  // even though constant, copy it into stack space for cross bank visibility
  const char msg[] = "Hello from >6000!";
  gotoxy(0,0);
  bk_cputs(msg);

  bk_second();

  // next, functions that return values.
  int x = bk_second_retint(0x0FF3);
  assertEquals(x, 0x0FF3);
  x = bk_second_retint(0xFFF3);
  assertEquals(x, 0xFFF3);

  gotoxy(0,4);
  const char msg2[] = "passed: int (*)(int)";
  bk_cputs(msg2);

  bk_halt();
}

void assertEquals(int found, int expected) {
  if (found != expected) {
    const char emsg[] = "error, halting";
    bk_cputs(emsg);
    bk_halt(); 
  }
}

