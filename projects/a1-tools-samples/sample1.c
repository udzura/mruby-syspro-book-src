#include <stdlib.h>
#include <string.h>

struct mydata {
  int x;
  int y;
  struct mydata *next;
};

void do_main(char flag)
{
  char *dummy = NULL;
  struct mydata *d1 = calloc(1, sizeof(struct mydata));
  d1->next = calloc(1, sizeof(struct mydata));
  d1->next->next = calloc(1, sizeof(struct mydata));

  switch(flag) {
  case '1':
    free(d1->next);
    free(d1);
    break;
  case '2':
    break;
  case '3':
    printf("dummy: %c", dummy[1]);
    break;
  default:
    free(d1->next->next);
    free(d1->next);
    free(d1);
    break;
  }
}

int main(int argc, char *argv[])
{
  if(argc < 2) {
    fprintf(stderr, "Usage: sample1 [1|2|3]\n");
    exit(1);
  }
  do_main(argv[1][0]);
  printf("Program run successful!\n");
  exit(0);
}
