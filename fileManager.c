/*
 * fileManager.c
 *
 * Code generation for function 'fileManager'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "pulse_gen.h"
#include "fileManager.h"
#include "pulse_gen_rtwutil.h"
#include <stdio.h>

/* Variable Definitions */
static FILE * eml_openfiles[20];
static boolean_T eml_autoflush[20];

/* Function Declarations */
static FILE * d_fileManager(signed char varargin_1);
static signed char filedata(void);

/* Function Definitions */

/*
 *
 */
static FILE * d_fileManager(signed char varargin_1)
{
  FILE * f;
  signed char fileid;
  fileid = varargin_1;
  if (varargin_1 < 0) {
    fileid = -1;
  }

  if (fileid >= 3) {
    f = eml_openfiles[fileid - 3];
  } else if (fileid == 0) {
    f = stdin;
  } else if (fileid == 1) {
    f = stdout;
  } else if (fileid == 2) {
    f = stderr;
  } else {
    f = NULL;
  }

  return f;
}

/*
 *
 */
static signed char filedata(void)
{
  signed char f;
  signed char k;
  boolean_T exitg1;
  f = 0;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 21)) {
    if (eml_openfiles[k - 1] == (FILE *)NULL) {
      f = k;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return f;
}

/*
 *
 */
void b_fileManager(double varargin_1, FILE * *f, boolean_T *a)
{
  signed char fileid;
  fileid = (signed char)rt_roundd_snf(varargin_1);
  if ((fileid < 0) || (varargin_1 != fileid)) {
    fileid = -1;
  }

  if (fileid >= 3) {
    fileid = (signed char)(fileid - 2);
    *f = eml_openfiles[fileid - 1];
    *a = eml_autoflush[fileid - 1];
  } else if (fileid == 0) {
    *f = stdin;
    *a = true;
  } else if (fileid == 1) {
    *f = stdout;
    *a = true;
  } else if (fileid == 2) {
    *f = stderr;
    *a = true;
  } else {
    *f = NULL;
    *a = true;
  }
}

/*
 *
 */
int c_fileManager(double varargin_1)
{
  int f;
  signed char fileid;
  FILE * filestar;
  int cst;
  f = -1;
  fileid = (signed char)rt_roundd_snf(varargin_1);
  if ((fileid < 0) || (varargin_1 != fileid)) {
    fileid = -1;
  }

  filestar = d_fileManager(fileid);
  if ((filestar == (FILE *)NULL) || (fileid < 3)) {
  } else {
    cst = fclose(filestar);
    if (cst == 0) {
      f = 0;
      fileid = (signed char)(fileid - 2);
      eml_openfiles[fileid - 1] = NULL;
      eml_autoflush[fileid - 1] = true;
    }
  }

  return f;
}

/*
 *
 */
signed char fileManager(void)
{
  signed char f;
  signed char j;
  char cv0[10];
  int i0;
  static const char cv1[10] = { 'p', 'u', 'l', 's', 'e', '.', 't', 'x', 't',
    '\x00' };

  char cv2[3];
  static const char cv3[3] = { 'w', 'b', '\x00' };

  FILE * filestar;
  f = -1;
  j = filedata();
  if (j < 1) {
  } else {
    for (i0 = 0; i0 < 10; i0++) {
      cv0[i0] = cv1[i0];
    }

    for (i0 = 0; i0 < 3; i0++) {
      cv2[i0] = cv3[i0];
    }

    filestar = fopen(cv0, cv2);
    if (filestar != (FILE *)NULL) {
      eml_openfiles[j - 1] = filestar;
      eml_autoflush[j - 1] = true;
      i0 = j + 2;
      if (i0 > 127) {
        i0 = 127;
      }

      f = (signed char)i0;
    }
  }

  return f;
}

void filedata_init(void)
{
  FILE * a;
  int i;
  a = NULL;
  for (i = 0; i < 20; i++) {
    eml_autoflush[i] = false;
    eml_openfiles[i] = a;
  }
}

/* End of code generation (fileManager.c) */
