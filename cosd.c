/*
 * cosd.c
 *
 * Code generation for function 'cosd'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "pulse_gen.h"
#include "cosd.h"
#include "sind.h"
#include "pulse_gen_rtwutil.h"
#include <stdio.h>

/* Function Definitions */

/*
 *
 */
void b_cosd(emxArray_real_T *x)
{
  int i2;
  int k;
  double b_x;
  double absx;
  signed char n;
  i2 = x->size[0];
  for (k = 0; k < i2; k++) {
    if (!((!rtIsInf(x->data[k])) && (!rtIsNaN(x->data[k])))) {
      b_x = rtNaN;
    } else {
      b_x = rt_remd_snf(x->data[k], 360.0);
      absx = fabs(b_x);
      if (absx > 180.0) {
        if (b_x > 0.0) {
          b_x -= 360.0;
        } else {
          b_x += 360.0;
        }

        absx = fabs(b_x);
      }

      if (absx <= 45.0) {
        b_x *= 0.017453292519943295;
        n = 0;
      } else if (absx <= 135.0) {
        if (b_x > 0.0) {
          b_x = 0.017453292519943295 * (b_x - 90.0);
          n = 1;
        } else {
          b_x = 0.017453292519943295 * (b_x + 90.0);
          n = -1;
        }
      } else if (b_x > 0.0) {
        b_x = 0.017453292519943295 * (b_x - 180.0);
        n = 2;
      } else {
        b_x = 0.017453292519943295 * (b_x + 180.0);
        n = -2;
      }

      if (n == 0) {
        b_x = cos(b_x);
      } else if (n == 1) {
        b_x = -sin(b_x);
      } else if (n == -1) {
        b_x = sin(b_x);
      } else {
        b_x = -cos(b_x);
      }
    }

    x->data[k] = b_x;
  }
}

/*
 *
 */
void cosd(double *x)
{
  double absx;
  signed char n;
  if (!((!rtIsInf(*x)) && (!rtIsNaN(*x)))) {
    *x = rtNaN;
  } else {
    *x = rt_remd_snf(*x, 360.0);
    absx = fabs(*x);
    if (absx > 180.0) {
      if (*x > 0.0) {
        *x -= 360.0;
      } else {
        *x += 360.0;
      }

      absx = fabs(*x);
    }

    if (absx <= 45.0) {
      *x *= 0.017453292519943295;
      n = 0;
    } else if (absx <= 135.0) {
      if (*x > 0.0) {
        *x = 0.017453292519943295 * (*x - 90.0);
        n = 1;
      } else {
        *x = 0.017453292519943295 * (*x + 90.0);
        n = -1;
      }
    } else if (*x > 0.0) {
      *x = 0.017453292519943295 * (*x - 180.0);
      n = 2;
    } else {
      *x = 0.017453292519943295 * (*x + 180.0);
      n = -2;
    }

    if (n == 0) {
      *x = cos(*x);
    } else if (n == 1) {
      *x = -sin(*x);
    } else if (n == -1) {
      *x = sin(*x);
    } else {
      *x = -cos(*x);
    }
  }
}

/* End of code generation (cosd.c) */
