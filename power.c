/*
 * power.c
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "pulse_gen.h"
#include "power.h"
#include "pulse_gen_emxutil.h"
#include <stdio.h>

/* Function Definitions */

/*
 *
 */
void power(const emxArray_real_T *a, emxArray_real_T *y)
{
  unsigned int unnamed_idx_0;
  int k;
  unnamed_idx_0 = (unsigned int)a->size[0];
  k = y->size[0];
  y->size[0] = (int)unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
  for (k = 0; k < (int)unnamed_idx_0; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

/* End of code generation (power.c) */
