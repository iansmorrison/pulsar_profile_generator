/*
 * pulse_gen.h
 *
 * Code generation for function 'pulse_gen'
 *
 */

#ifndef __PULSE_GEN_H__
#define __PULSE_GEN_H__

/* Include files */
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "pulse_gen_types.h"

/* Function Declarations */
extern void pulse_gen(int N, double noise, double esig, double epeak, double
                      flin, double zeta, double alpha, int showplot);

#endif

/* End of code generation (pulse_gen.h) */
