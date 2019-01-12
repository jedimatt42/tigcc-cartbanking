#include "banking.h"
#include <conio.h>

// declare our current bank
#define MYBANK BANK_2

#include "fourth.h"

DECLARE_BANKED_VOID(cputs, BANK_1, bk_cputs, (const char* s), (s))
DECLARE_BANKED_VOID(fourth, BANK_3, bk_fourth, (), ())

void third() {
  // even though constant, copy it into stack space for cross bank visibility
  const char msg[] = "Hello from >6004!";
  gotoxy(0,2);
  bk_cputs(msg);
  bk_fourth();
}

