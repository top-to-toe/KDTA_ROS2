#include <stdio.h>
#define BOLD    (0x01 << 0)
#define ITALIC  (0x01 << 1)
#define SHADOW  (0x01 << 2)
#define UL      (0x01 << 3)

int main(void) {
	unsigned char attr;
	
	attr = attr ^ attr;		// attr = 0;
	attr = attr | BOLD;
	attr = attr | (ITALIC + SHADOW);
	attr = attr & ~BOLD;
	
	printf("attr: 0x%02x\n", attr);
	// = printf("attr: 0x%02x\n", (int)attr);
	return 0;
}
