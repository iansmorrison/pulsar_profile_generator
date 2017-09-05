/*
 * pulse_gen_emxutil.h
 *
 * Code generation for function 'pulse_gen_emxutil'
 *
 */

#ifndef __PULSE_GEN_EMXUTIL_H__
#define __PULSE_GEN_EMXUTIL_H__

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
extern void b_emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (pulse_gen_emxutil.h) */
