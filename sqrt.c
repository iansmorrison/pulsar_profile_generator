/*
 * sqrt.c
 *
 * Code generation for function 'sqrt'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "pulse_gen.h"
#include "sqrt.h"
#include <stdio.h>

/* Function Definitions */

/*
 *
 */
void b_sqrt(emxArray_real_T *x)
{
  int i3;
  int k;
  i3 = x->size[0];
  for (k = 0; k < i3; k++) {
    x->data[k] = sqrt(x->data[k]);
  }
}

/* End of code generation (sqrt.c) */
