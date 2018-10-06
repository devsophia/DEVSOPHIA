#include <stdio.h>

int main()
{
	int n = 0;
	int x = -3;
	printf("%d\n", (x>>(n + ~0x0) & 0x1));
	return 0;
}
