/*
 * pulse_gen.c
 *
 * Code generation for function 'pulse_gen'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "pulse_gen.h"
#include "fprintf.h"
#include "fclose.h"
#include "pulse_gen_emxutil.h"
#include "sind.h"
#include "cosd.h"
#include "power.h"
#include "sqrt.h"
#include "fopen.h"
#include <stdio.h>

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(double)(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/*
 * function pulse_gen(N,noise,esig,epeak,flin,zeta,alpha,showplot)
 */
void pulse_gen(int N, double noise, double esig, double epeak, double flin,
               double zeta, double alpha, int showplot)
{
  double out_fid;
  int ixstart;
  emxArray_real_T *y;
  int ix;
  double delta1;
  emxArray_real_T *p;
  emxArray_real_T *S0;
  emxArray_real_T *S3;
  double d0;
  double d1;
  emxArray_real_T *psi;
  int n;
  emxArray_real_T *b_p;
  double b;
  emxArray_real_T *thetaE;
  emxArray_real_T *b_thetaE;
  boolean_T exitg2;
  boolean_T exitg1;
  (void)showplot;

  /*  Generates an ASCII file containing a simulated pulsar pulse profile, */
  /*    suitable for use with the "test_vec_gen" utility. */
  /*  Uses the rotating vector model for pulsar emission to generate the */
  /*    phase-dependent Stokes parameters for each phase bin. */
  /*  Derived from Damien Hicks's "signalgen.m" code. */
  /*  DATA SETTINGS */
  /*  N         - number of bins within a pulse period */
  /*  noise     - set to 0.0 for no noise, 1.0 for noise (max(S/N)=1) */
  /*  */
  /*  PULSAR MODEL SETTINGS */
  /*  esig      - emission half angle (polar angle, degrees) */
  /*  epeak     - emission peak angle (polar angle, degrees) */
  /*  flin      - linear polarized fraction amplitude */
  /*  zeta      - observing angle (degrees) relative to rotation axis */
  /*  alpha     - magnetic axis (degrees) relative to rotation axis */
  /*  */
  /*  OUTPUTS: */
  /*  fname -  file containing N rows with four Stokes parameters per row */
  /*  */
  /*  Changes: */
  /*  -------- */
  /*  */
  /*  Author           Date         Comments */
  /*  ---------------  -----------  ---------------------------------------- */
  /*  I. Morrison      29-Oct-2015  Original version */
  /*  */
  /*  ---------------------------------------------------------------------- */
  /* 'pulse_gen:31' if (0) */
  /*  Open output file for writing */
  /* 'pulse_gen:62' out_fid = fopen('pulse.txt','w'); */
  out_fid = b_fopen();

  /* 'pulse_gen:64' pmin = -180.0; */
  /* 'pulse_gen:65' pmax = 180.0; */
  /*  Angle of rotation: p=0 for aligned dipole.  */
  /*  This is equivalent to pulsar longitude or phase */
  /* 'pulse_gen:69' p = transpose(linspace(pmin, pmax, N)); */
  ixstart = N;
  if (N < 0) {
    ixstart = 0;
  }

  b_emxInit_real_T(&y, 2);
  ix = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = ixstart;
  emxEnsureCapacity((emxArray__common *)y, ix, (int)sizeof(double));
  if (ixstart >= 1) {
    y->data[ixstart - 1] = 180.0;
    if (y->size[1] >= 2) {
      y->data[0] = -180.0;
      if (y->size[1] >= 3) {
        delta1 = 360.0 / ((double)y->size[1] - 1.0);
        ix = y->size[1];
        for (ixstart = 0; ixstart <= ix - 3; ixstart++) {
          y->data[ixstart + 1] = -180.0 + (1.0 + (double)ixstart) * delta1;
        }
      }
    }
  }

  emxInit_real_T(&p, 1);
  ix = p->size[0];
  p->size[0] = y->size[1];
  emxEnsureCapacity((emxArray__common *)p, ix, (int)sizeof(double));
  ixstart = y->size[1];
  for (ix = 0; ix < ixstart; ix++) {
    p->data[ix] = y->data[y->size[0] * ix];
  }

  emxFree_real_T(&y);
  emxInit_real_T(&S0, 1);

  /*  Polarization angle w.r.t projected rotation axis from observing direction */
  /* psi = atand(sind(alpha)*sind(p)./(sind(zeta)*cosd(alpha) - ... */
  /*     sind(alpha)*cosd(zeta)*cosd(p))); */
  /* 'pulse_gen:74' psi = atan2d(sind(alpha)*sind(p),  ... */
  /* 'pulse_gen:75'     (sind(zeta)*cosd(alpha) - sind(alpha)*cosd(zeta)*cosd(p))); */
  delta1 = alpha;
  sind(&delta1);
  ix = S0->size[0];
  S0->size[0] = p->size[0];
  emxEnsureCapacity((emxArray__common *)S0, ix, (int)sizeof(double));
  ixstart = p->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S0->data[ix] = p->data[ix];
  }

  b_sind(S0);
  ix = S0->size[0];
  emxEnsureCapacity((emxArray__common *)S0, ix, (int)sizeof(double));
  ixstart = S0->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S0->data[ix] *= delta1;
  }

  emxInit_real_T(&S3, 1);
  d0 = alpha;
  sind(&d0);
  d1 = zeta;
  cosd(&d1);
  delta1 = d0 * d1;
  ix = S3->size[0];
  S3->size[0] = p->size[0];
  emxEnsureCapacity((emxArray__common *)S3, ix, (int)sizeof(double));
  ixstart = p->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S3->data[ix] = p->data[ix];
  }

  b_cosd(S3);
  d0 = zeta;
  sind(&d0);
  d1 = alpha;
  cosd(&d1);
  d0 *= d1;
  ix = S3->size[0];
  emxEnsureCapacity((emxArray__common *)S3, ix, (int)sizeof(double));
  ixstart = S3->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S3->data[ix] = d0 - delta1 * S3->data[ix];
  }

  emxInit_real_T(&psi, 1);
  n = S0->size[0];
  ix = psi->size[0];
  psi->size[0] = n;
  emxEnsureCapacity((emxArray__common *)psi, ix, (int)sizeof(double));
  for (ixstart = 0; ixstart < n; ixstart++) {
    psi->data[ixstart] = 57.295779513082323 * rt_atan2d_snf(S0->data[ixstart],
      S3->data[ixstart]);
  }

  emxInit_real_T(&b_p, 1);

  /*  Polar observation angle in magnetic axis reference frame */
  /* 'pulse_gen:78' cosO = cosd(p)*sind(zeta)*sind(alpha) + cosd(alpha)*cosd(zeta); */
  b_cosd(p);
  delta1 = zeta;
  sind(&delta1);
  b = alpha;
  sind(&b);

  /* 'pulse_gen:79' tanO = sqrt(1./(cosO.^2)-1); */
  d0 = alpha;
  cosd(&d0);
  d1 = zeta;
  cosd(&d1);
  d0 *= d1;
  ix = b_p->size[0];
  b_p->size[0] = p->size[0];
  emxEnsureCapacity((emxArray__common *)b_p, ix, (int)sizeof(double));
  ixstart = p->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    b_p->data[ix] = p->data[ix] * delta1 * b + d0;
  }

  power(b_p, p);
  ix = p->size[0];
  emxEnsureCapacity((emxArray__common *)p, ix, (int)sizeof(double));
  ixstart = p->size[0];
  emxFree_real_T(&b_p);
  for (ix = 0; ix < ixstart; ix++) {
    p->data[ix] = 1.0 / p->data[ix] - 1.0;
  }

  b_sqrt(p);

  /*  Polar emission angle in magnetic axis reference frame */
  /* 'pulse_gen:82' thetaE = atand(1.5*(sqrt(1+(8/9)*tanO.^2) - 1)./tanO); */
  power(p, S0);
  ix = S0->size[0];
  emxEnsureCapacity((emxArray__common *)S0, ix, (int)sizeof(double));
  ixstart = S0->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S0->data[ix] = 1.0 + 0.88888888888888884 * S0->data[ix];
  }

  b_sqrt(S0);
  ix = S0->size[0];
  emxEnsureCapacity((emxArray__common *)S0, ix, (int)sizeof(double));
  ixstart = S0->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S0->data[ix]--;
  }

  ix = S0->size[0];
  emxEnsureCapacity((emxArray__common *)S0, ix, (int)sizeof(double));
  ixstart = S0->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S0->data[ix] = 1.5 * S0->data[ix] / p->data[ix];
  }

  emxInit_real_T(&thetaE, 1);
  ix = thetaE->size[0];
  thetaE->size[0] = S0->size[0];
  emxEnsureCapacity((emxArray__common *)thetaE, ix, (int)sizeof(double));
  ixstart = S0->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    thetaE->data[ix] = S0->data[ix];
  }

  for (ixstart = 0; ixstart < S0->size[0]; ixstart++) {
    thetaE->data[ixstart] = 57.295779513082323 * atan(thetaE->data[ixstart]);
  }

  emxInit_real_T(&b_thetaE, 1);

  /* thetaE = atand(1.5*(-sqrt(1+(8/9)*tanO.^2) - 1)./tanO); */
  /*  Intensity (model-based assumption) */
  /* 'pulse_gen:86' S0 = (1./sqrt(2*pi()*esig^2))*exp(-(thetaE-epeak).^2/(2.*esig^2)); */
  delta1 = 1.0 / sqrt(6.2831853071795862 * (esig * esig));
  ix = b_thetaE->size[0];
  b_thetaE->size[0] = thetaE->size[0];
  emxEnsureCapacity((emxArray__common *)b_thetaE, ix, (int)sizeof(double));
  ixstart = thetaE->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    b_thetaE->data[ix] = thetaE->data[ix] - epeak;
  }

  power(b_thetaE, p);
  ix = p->size[0];
  emxEnsureCapacity((emxArray__common *)p, ix, (int)sizeof(double));
  ixstart = p->size[0];
  emxFree_real_T(&b_thetaE);
  for (ix = 0; ix < ixstart; ix++) {
    p->data[ix] = -p->data[ix];
  }

  b = 2.0 * (esig * esig);
  ix = p->size[0];
  emxEnsureCapacity((emxArray__common *)p, ix, (int)sizeof(double));
  ixstart = p->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    p->data[ix] /= b;
  }

  ix = S0->size[0];
  S0->size[0] = p->size[0];
  emxEnsureCapacity((emxArray__common *)S0, ix, (int)sizeof(double));
  ixstart = p->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S0->data[ix] = p->data[ix];
  }

  for (ixstart = 0; ixstart < p->size[0]; ixstart++) {
    S0->data[ixstart] = exp(S0->data[ixstart]);
  }

  ix = S0->size[0];
  emxEnsureCapacity((emxArray__common *)S0, ix, (int)sizeof(double));
  ixstart = S0->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S0->data[ix] *= delta1;
  }

  /* 'pulse_gen:87' S0 = S0/max(S0); */
  ixstart = 1;
  n = S0->size[0];
  delta1 = S0->data[0];
  if (S0->size[0] > 1) {
    if (rtIsNaN(S0->data[0])) {
      ix = 2;
      exitg2 = false;
      while ((!exitg2) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(S0->data[ix - 1])) {
          delta1 = S0->data[ix - 1];
          exitg2 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < S0->size[0]) {
      while (ixstart + 1 <= n) {
        if (S0->data[ixstart] > delta1) {
          delta1 = S0->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ix = S0->size[0];
  emxEnsureCapacity((emxArray__common *)S0, ix, (int)sizeof(double));
  ixstart = S0->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S0->data[ix] /= delta1;
  }

  /* normalize max to 1 */
  /*  Linear polarization fraction (model-based assumption) */
  /* 'pulse_gen:90' L = flin*S0.*cosd(thetaE); */
  b_cosd(thetaE);
  ix = thetaE->size[0];
  thetaE->size[0] = S0->size[0];
  emxEnsureCapacity((emxArray__common *)thetaE, ix, (int)sizeof(double));
  ixstart = S0->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    thetaE->data[ix] *= flin * S0->data[ix];
  }

  /*  Other Stokes parameters */
  /* 'pulse_gen:93' S1 = L.*cosd(2*psi); */
  ix = p->size[0];
  p->size[0] = psi->size[0];
  emxEnsureCapacity((emxArray__common *)p, ix, (int)sizeof(double));
  ixstart = psi->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    p->data[ix] = 2.0 * psi->data[ix];
  }

  b_cosd(p);
  ix = p->size[0];
  p->size[0] = thetaE->size[0];
  emxEnsureCapacity((emxArray__common *)p, ix, (int)sizeof(double));
  ixstart = thetaE->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    p->data[ix] *= thetaE->data[ix];
  }

  /* 'pulse_gen:94' S2 = L.*sind(2*psi); */
  ix = psi->size[0];
  emxEnsureCapacity((emxArray__common *)psi, ix, (int)sizeof(double));
  ixstart = psi->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    psi->data[ix] *= 2.0;
  }

  b_sind(psi);

  /* 'pulse_gen:95' S3 = -(1-flin)*S1; */
  ix = S3->size[0];
  S3->size[0] = p->size[0];
  emxEnsureCapacity((emxArray__common *)S3, ix, (int)sizeof(double));
  ixstart = p->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S3->data[ix] = -(1.0 - flin) * p->data[ix];
  }

  /*  Fake circular polarization to avoid zero signal */
  /* S3 = single(zeros(N,1)); % Zero circular polarization component */
  /*  Add noise, typically such that max(S/N) = 1 */
  /* 'pulse_gen:99' S0 = S0 + noise; */
  ix = S0->size[0];
  emxEnsureCapacity((emxArray__common *)S0, ix, (int)sizeof(double));
  ixstart = S0->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S0->data[ix] += noise;
  }

  /*  Normalize Stokes 4-vector so that S0 = 1.  */
  /* 'pulse_gen:102' factor = max(S0); */
  ixstart = 1;
  n = S0->size[0];
  delta1 = S0->data[0];
  if (S0->size[0] > 1) {
    if (rtIsNaN(S0->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(S0->data[ix - 1])) {
          delta1 = S0->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < S0->size[0]) {
      while (ixstart + 1 <= n) {
        if (S0->data[ixstart] > delta1) {
          delta1 = S0->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  /* 'pulse_gen:103' S0 = S0/factor; */
  ix = S0->size[0];
  emxEnsureCapacity((emxArray__common *)S0, ix, (int)sizeof(double));
  ixstart = S0->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S0->data[ix] /= delta1;
  }

  /* 'pulse_gen:104' S1 = S1/factor; */
  ix = p->size[0];
  emxEnsureCapacity((emxArray__common *)p, ix, (int)sizeof(double));
  ixstart = p->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    p->data[ix] /= delta1;
  }

  /* 'pulse_gen:105' S2 = S2/factor; */
  ix = thetaE->size[0];
  emxEnsureCapacity((emxArray__common *)thetaE, ix, (int)sizeof(double));
  ixstart = thetaE->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    thetaE->data[ix] = thetaE->data[ix] * psi->data[ix] / delta1;
  }

  emxFree_real_T(&psi);

  /* 'pulse_gen:106' S3 = S3/factor; */
  ix = S3->size[0];
  emxEnsureCapacity((emxArray__common *)S3, ix, (int)sizeof(double));
  ixstart = S3->size[0];
  for (ix = 0; ix < ixstart; ix++) {
    S3->data[ix] /= delta1;
  }

  /*  Create Coherency matrix */
  /* 'pulse_gen:109' Jxx = 0.5*(S0 + S1); */
  /* 'pulse_gen:110' Jyy = 0.5*(S0 - S1); */
  /* 'pulse_gen:111' Jxy = 0.5*(S2 + 1i*S3); */
  /* 'pulse_gen:112' Jyx = 0.5*(S2 - 1i*S3); */
  /*  Plot results, if desired */
  /* 'pulse_gen:115' if (int32(showplot)) */
  /*  Write Stokes parameters to file */
  /* 'pulse_gen:150' for i = int32(1):N */
  for (ixstart = 0; ixstart + 1 <= N; ixstart++) {
    /* 'pulse_gen:151' fprintf(out_fid, '%.15e %.15e %.15e %.15e\n',S0(i), S1(i), S2(i), S3(i)); */
    b_fprintf(out_fid, S0->data[ixstart], p->data[ixstart], thetaE->data[ixstart],
              S3->data[ixstart]);
  }

  emxFree_real_T(&S3);
  emxFree_real_T(&S0);
  emxFree_real_T(&thetaE);
  emxFree_real_T(&p);

  /* 'pulse_gen:155' fclose(out_fid); */
  b_fclose(out_fid);
}

/* End of code generation (pulse_gen.c) */
