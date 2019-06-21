#include <complex.h>

struct complex complex_mul(struct complex a,struct complex b)
{
struct complex c;
c.a = (a.a*b.a-a.i*b.i);
c.i = (a.a*b.i + a.i*b.a);
return c; 
}
