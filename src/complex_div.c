#include <complex.h>

struct complex complex_divi(struct complex a, struct complex b)
{
	struct complex c;
	c.a = (a.a*b.a+a.i*b.i)/(b.a*b.a+b.i*b.i);
	c.i = (a.i*b.a-a.a*b.i)/(b.a*b.a+b.i*b.i);
}
