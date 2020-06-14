#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

char *get_hostname(void) {
  struct utsname uts;
  char *ret;
  //uname(&uts);
  if (uname(&uts) == -1) {
    fprintf(stderr, "error getting utsname\n");
    exit(1);
  }

  ret = malloc(sizeof(uts.nodename));
  if (!ret) {
    fprintf(stderr, "error malloc\n");
    exit(1);
  }
  strncpy(ret, uts.nodename, sizeof(uts.nodename));

  return ret;
}

int main(int argc, char* argv[]) {
  char *hostname = get_hostname();
  printf("%s\n", hostname);
  free(hostname);
  exit(0);
}
