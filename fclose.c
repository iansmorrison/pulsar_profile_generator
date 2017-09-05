/*
 * fclose.c
 *
 * Code generation for function 'fclose'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "pulse_gen.h"
#include "fclose.h"
#include "fileManager.h"
#include <stdio.h>

/* Function Definitions */

/*
 *
 */
void b_fclose(double fileID)
{
  c_fileManager(fileID);
}

/* End of code generation (fclose.c) */
