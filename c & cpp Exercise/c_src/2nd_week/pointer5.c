#include <stdio.h>

int add(int a, int b) {
	return a + b;
}

int substract(int a, int b) {
	return a - b;
}

int main(void) {

	int (*fp)(int, int);
	fp = &add;
	int re = (*fp)(4, 3);	// result = 7
	printf("re: %d\n", re);
	
	fp = &substract;
	re = (*fp)(4, 3); 		// result = 1
	printf("re: %d\n", re);

	return 0;
}
