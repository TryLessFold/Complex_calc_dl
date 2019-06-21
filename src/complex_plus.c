#include <complex.h>

struct complex complex_plus(struct complex a,struct complex b)
{
	struct complex c;
	c.a = a.a + b.a;
	c.i = a.i + b.i;
	return c;
}
