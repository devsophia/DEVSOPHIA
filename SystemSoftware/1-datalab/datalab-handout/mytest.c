#include <stdio.h>

int main() {
	int x = 0x80000001;
	int sign, exp, Bias, E, frac, t, n, rest, comp, LSB;
	t = 0x1 << 31;
	Bias = 127;
	sign = x & t;
	if(x == 0)
		return 0x0;
	if(x == 0x80000000)
		return 0xcf000000;
	if(sign)
		x = -x;
	t = 0x1 << 30;
	E = 30;
	while((t & x) == 0) {
		--E;
		t = t >> 1;
	}
	exp = (E + Bias) << 23;

	if(E < 23)
		frac = (x >> (23 - E)) & 0x7fffff;
	else if(E > 23) {
		frac = (x >> (E - 23)) & 0x7fffff;
		printf("frac = %x\n", frac);
		n = E-23;
		printf("n = %d\n", n);
		rest = 0x1;
		while(--n)
			rest |= rest << 1;
		rest &= x;
		printf("rest = %x\n", rest);
		comp = 0x1 << (E-24);
		printf("comp = %x\n", comp);
		if(rest > comp) {
			frac++;
			printf("frac = %x\n", frac);
		}
		else if(rest == comp) {
			comp = comp << 1;
			LSB = (comp & x);
			if(rest)
				frac++;
		}
	}
	else
		frac = x & 0x7fffff;
	
	return sign | exp | frac;
}

