/*
 * fprintf.h
 *
 * Code generation for function 'fprintf'
 *
 */

#ifndef __FPRINTF_H__
#define __FPRINTF_H__

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
extern void b_fprintf(double fileID, double varargin_1, double varargin_2,
                      double varargin_3, double varargin_4);

#endif

/* End of code generation (fprintf.h) */
