/*
 * fprintf.c
 *
 * Code generation for function 'fprintf'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "pulse_gen.h"
#include "fprintf.h"
#include "fileManager.h"
#include <stdio.h>

/* Function Definitions */

/*
 *
 */
void b_fprintf(double fileID, double varargin_1, double varargin_2, double
               varargin_3, double varargin_4)
{
  FILE * b_NULL;
  boolean_T autoflush;
  FILE * filestar;
  static const char cfmt[25] = { '%', '.', '1', '5', 'e', ' ', '%', '.', '1',
    '5', 'e', ' ', '%', '.', '1', '5', 'e', ' ', '%', '.', '1', '5', 'e', '\x0a',
    '\x00' };

  b_NULL = NULL;
  b_fileManager(fileID, &filestar, &autoflush);
  if (filestar == b_NULL) {
  } else {
    fprintf(filestar, cfmt, varargin_1, varargin_2, varargin_3, varargin_4);
    if (autoflush) {
      fflush(filestar);
    }
  }
}

/* End of code generation (fprintf.c) */
