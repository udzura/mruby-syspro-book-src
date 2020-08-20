#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int x;
  printf("x = %d\n", x);

  struct stat *s;
  stat("/etc/hosts", s);
  printf("Size: %ld\n", s->st_size);
  free(s);
}
