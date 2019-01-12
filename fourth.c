#include "banking.h"
#include <conio.h>

// declare our current bank
#define MYBANK BANK_3

DECLARE_BANKED_VOID(cputs, BANK_1, bk_cputs, (const char* s), (s))

void fourth() {
  // even though constant, copy it into stack space for cross bank visibility
  const char msg[] = "Hello from >6006!";
  gotoxy(0,3);
  bk_cputs(msg);
}

