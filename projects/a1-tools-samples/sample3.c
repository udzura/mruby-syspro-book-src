#include <stdio.h>
#include <stdlib.h>
char *crypt(const char *src) {
  char *dst = malloc(sizeof(src));

  for (int i = 0; src[i] != '\0'; i++) {
    switch(src[i]) {
    case 'A':
      dst[i] = '@';
      break;
    case 'e':
      dst[i] = '3';
      break;
    default:
      if (src[i] >= 'a' && src[i] <= 'z')
        dst[i] = 'a' + ('z' - src[i]);
      else
        dst[i] = src[i];
    }
  }
  return dst;
}

int main(int argc, char *argv[]) {
  char *ret = crypt("A crypt will be crypted!");
  printf("%s\n", ret);
  free(ret);
}
