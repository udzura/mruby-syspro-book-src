#include <stdio.h>
#include <stdlib.h>

char *ret_str(int size)
{
  char *ret = malloc(sizeof(char) * size);
  for(int i = 0; i < size-1; i++) {
    ret[i] = 'a';
  }
  ret[size-1] = '\0';
  free(ret);
  return ret;
}
int main(int argc, char *argv[])
{
  char* str = ret_str(100);
  printf("%s\n", str);
  free(str);
  exit(0);
}
