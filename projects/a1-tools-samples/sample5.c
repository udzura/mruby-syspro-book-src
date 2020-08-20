#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char data[] = "longdata1 longdata2 longdata3 longdata4 longdata5 "
  "longdata6 longdata7 longdata8 longdata9 longdata10" "..." ;

int main(int argc, char *argv[]) {
  char *d1 = malloc(512);
  strcpy(d1, data);
  char *d2 = (d1 + 128);

  strncpy(d2, d1, 256);
  printf("d1: %s\n", d1);
  return 0;
}
