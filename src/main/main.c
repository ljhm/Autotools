#include <stdio.h>
#include <signal.h>
#include <sanitizer/lsan_interface.h>
#include <assert.h>
#include "foo.h"

void handlerCont(int signum){
  printf("SIGCONT %d\n", signum);
#ifndef NDEBUG
  __lsan_do_recoverable_leak_check();
#endif
}

int main() {
  signal(SIGCONT, handlerCont); // kill -CONT <pid>
  printf("main\n");
  foo();
  assert(0); //

  int a[1024];
  int n = 10240;
  a[n] = 1;
  assert(0);
}
