#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void myfunc(int count)
{
  char dummy[65536 - 64] = "--mark--";
  int newcnt = count + 1;

  printf("stack #%d:   %p, %p, %p\n", count, &count, &newcnt, dummy);
  if (newcnt > 5)
    return;
  else {
    myfunc(newcnt);
    return;
  }
}

int main(int argc, char *argv[], char *environ[])
{
  char cmd[256] = {0};
  snprintf(cmd, 256,\
           "cat /proc/%d/maps | grep stack | grep -v ssstack", getpid());
  system(cmd);

  puts("");
  printf("main stack: %p, %p, %p, %p\n", &argc, &argv, cmd, environ);
  puts("");

  printf("            %-14s  %-14s  %-14s\n", "&count", "&newcnt", "dummy");
  myfunc(1);

  return 0;
}
