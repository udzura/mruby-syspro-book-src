#include <stdio.h>
int main(int argc, char *argv[]){
	int n;
	printf("%s%n\n", "Hello", &n);
	printf("%d\n", n);
}
