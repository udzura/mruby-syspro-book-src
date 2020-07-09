#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *mybin = "MyData";
char datachar = 'X';
char datastr[32] = "MyData2";
char bsschar;
char bssstr[32];

int func1(int foo, const char *bar)
{
  static char staticdatastr2[32] = "MyData3";
  static char staticbssstr2[32];

  int mystack1;
  char mystack2[32];
  char *myheap1, *myheap2;
  myheap1 = malloc(sizeof(char) * 32);
  myheap2 = malloc(sizeof(char) * 64);

  printf("binary:    %p\n", mybin);
  printf("data:      %p, %p, %p\n", &datachar, datastr, staticdatastr2);
  printf("bss:       %p, %p, %p\n", staticbssstr2, &bsschar, bssstr);
  /* bssint = 1234; */
  /* bssstr[0] = 'H'; */
  /* bssstr[1] = 'i'; */
  /* printf("bss1:      %p, %p\n", &bssint, bssstr); */

  printf("var:       %p, %p\n", &foo, &bar);
  printf("stacks:    %p, %p\n", &mystack1, &mystack2);
  printf("heaps:     %p, %p\n", myheap1, myheap2);

  free(myheap1);
  myheap1 = malloc(sizeof(char) * 16);
  printf("heaps(2):  %p, %p\n", myheap1, myheap2);
  free(myheap1);
  myheap1 = malloc(sizeof(char) * 64);
  printf("heaps(3):  %p, %p\n", myheap1, myheap2);

  puts("");
  char cmd[256];
  snprintf(cmd, 256, "cat /proc/%d/maps", getpid());
  system(cmd);

  for(;;)
    sleep(1);

  return 0;
}

int main(int argc, char *argv[])
{
  int ret;
  //printf("PID=%d\n", getpid());
  //char mainstack1[32], mainstack2[32];

  ret = func1(123, mybin);

  return 0;
}
