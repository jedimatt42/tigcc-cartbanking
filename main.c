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

void main() {
  bk_set_text();
  bk_charsetlc();

  // even though constant, copy it into stack space for cross bank visibility
  const char msg[] = "Hello from >6000!";
  gotoxy(0,0);
  bk_cputs(msg);

  bk_second();

  bk_halt();
}

