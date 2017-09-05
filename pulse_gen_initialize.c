/*
 * pulse_gen_initialize.c
 *
 * Code generation for function 'pulse_gen_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "pulse_gen.h"
#include "pulse_gen_initialize.h"
#include "fileManager.h"
#include <stdio.h>

/* Function Definitions */
void pulse_gen_initialize(void)
{
  rt_InitInfAndNaN(8U);
  filedata_init();
}

/* End of code generation (pulse_gen_initialize.c) */
