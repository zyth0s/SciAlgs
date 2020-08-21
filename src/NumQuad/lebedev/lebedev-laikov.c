/*
 * =====================================================================================
 *
 *       Filename:  lebedev-laikov.cpp
 *
 *    Description:  This routine computes the grid points and weights of an 
 *                  angular Lebedev quadrature.
 *
 *         Author:  J. Burkhardt, modified
 *
 *        Version:  1.0
 *        Created:  10/09/2017 08:53:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *        License:  LGPL
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>

#include "lebedev-laikov.h"

int gen_oh(int code, double a, double b, double v, double *x, double *y,
           double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    GEN_OH generates points under OH symmetry.
//
//  Discussion:
//
//    Given a point on a sphere, specified by A and B, this routine generates
//    all the equivalent points under OH symmetry, making grid points with
//    weight V.
//
//    The variable NUM is increased by the number of different points
//    generated.
//
//    Depending on CODE, there are from 6 to 48 different but equivalent
//    points that are generated:
//
//      CODE=1:   (0,0,1) etc            (  6 points)
//      CODE=2:   (0,A,A) etc, A=1/sqrt(2)         ( 12 points)
//      CODE=3:   (A,A,A) etc, A=1/sqrt(3)         (  8 points)
//      CODE=4:   (A,A,B) etc, B=sqrt(1-2 A^2)     ( 24 points)
//      CODE=5:   (A,B,0) etc, B=sqrt(1-A^2), A input   ( 24 points)
//      CODE=6:   (A,B,C) etc, C=sqrt(1-A^2-B^2), A, B input ( 48 points)
//
//  Modified:
//
//    11 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Input, int CODE, selects the symmetry group.
//
//    Input/output, int NUM, the number of points.  This is incremented
//    upon output by the number of points generated on this call.
//
//    Input, double A, B, information that may be needed to
//    generate the coordinates of the points (for code = 5 or 6 only).
//
//    Input, double V, the weight to be assigned the points.
//
//    Output, double X[*], Y[*], Z[*], W[*], the coordinates
//    and weights of the symmetric points generated on this call.
//
//    Output, int GEN_OH, the number of points generated on this call.
//
{
  double c;
  int num;

  if (code == 1) {
    a    = 1.0;
    x[0] = a;
    y[0] = 0.0;
    z[0] = 0.0;
    w[0] = v;
    x[1] = -a;
    y[1] = 0.0;
    z[1] = 0.0;
    w[1] = v;
    x[2] = 0.0;
    y[2] = a;
    z[2] = 0.0;
    w[2] = v;
    x[3] = 0.0;
    y[3] = -a;
    z[3] = 0.0;
    w[3] = v;
    x[4] = 0.0;
    y[4] = 0.0;
    z[4] = a;
    w[4] = v;
    x[5] = 0.0;
    y[5] = 0.0;
    z[5] = -a;
    w[5] = v;
    num  = 6;
  } else if (code == 2) {
    a     = sqrt(0.5);
    x[0]  = 0;
    y[0]  = a;
    z[0]  = a;
    w[0]  = v;
    x[1]  = 0;
    y[1]  = -a;
    z[1]  = a;
    w[1]  = v;
    x[2]  = 0;
    y[2]  = a;
    z[2]  = -a;
    w[2]  = v;
    x[3]  = 0;
    y[3]  = -a;
    z[3]  = -a;
    w[3]  = v;
    x[4]  = a;
    y[4]  = 0;
    z[4]  = a;
    w[4]  = v;
    x[5]  = -a;
    y[5]  = 0;
    z[5]  = a;
    w[5]  = v;
    x[6]  = a;
    y[6]  = 0;
    z[6]  = -a;
    w[6]  = v;
    x[7]  = -a;
    y[7]  = 0;
    z[7]  = -a;
    w[7]  = v;
    x[8]  = a;
    y[8]  = a;
    z[8]  = 0;
    w[8]  = v;
    x[9]  = -a;
    y[9]  = a;
    z[9]  = 0;
    w[9]  = v;
    x[10] = a;
    y[10] = -a;
    z[10] = 0;
    w[10] = v;
    x[11] = -a;
    y[11] = -a;
    z[11] = 0;
    w[11] = v;
    num   = 12;
  } else if (code == 3) {
    a    = sqrt(1.0 / 3.0);
    x[0] = a;
    y[0] = a;
    z[0] = a;
    w[0] = v;
    x[1] = -a;
    y[1] = a;
    z[1] = a;
    w[1] = v;
    x[2] = a;
    y[2] = -a;
    z[2] = a;
    w[2] = v;
    x[3] = -a;
    y[3] = -a;
    z[3] = a;
    w[3] = v;
    x[4] = a;
    y[4] = a;
    z[4] = -a;
    w[4] = v;
    x[5] = -a;
    y[5] = a;
    z[5] = -a;
    w[5] = v;
    x[6] = a;
    y[6] = -a;
    z[6] = -a;
    w[6] = v;
    x[7] = -a;
    y[7] = -a;
    z[7] = -a;
    w[7] = v;
    num  = 8;
  } else if (code == 4) {
    b     = sqrt(1.0 - 2.0 * a * a);
    x[0]  = a;
    y[0]  = a;
    z[0]  = b;
    w[0]  = v;
    x[1]  = -a;
    y[1]  = a;
    z[1]  = b;
    w[1]  = v;
    x[2]  = a;
    y[2]  = -a;
    z[2]  = b;
    w[2]  = v;
    x[3]  = -a;
    y[3]  = -a;
    z[3]  = b;
    w[3]  = v;
    x[4]  = a;
    y[4]  = a;
    z[4]  = -b;
    w[4]  = v;
    x[5]  = -a;
    y[5]  = a;
    z[5]  = -b;
    w[5]  = v;
    x[6]  = a;
    y[6]  = -a;
    z[6]  = -b;
    w[6]  = v;
    x[7]  = -a;
    y[7]  = -a;
    z[7]  = -b;
    w[7]  = v;
    x[8]  = a;
    y[8]  = b;
    z[8]  = a;
    w[8]  = v;
    x[9]  = -a;
    y[9]  = b;
    z[9]  = a;
    w[9]  = v;
    x[10] = a;
    y[10] = -b;
    z[10] = a;
    w[10] = v;
    x[11] = -a;
    y[11] = -b;
    z[11] = a;
    w[11] = v;
    x[12] = a;
    y[12] = b;
    z[12] = -a;
    w[12] = v;
    x[13] = -a;
    y[13] = b;
    z[13] = -a;
    w[13] = v;
    x[14] = a;
    y[14] = -b;
    z[14] = -a;
    w[14] = v;
    x[15] = -a;
    y[15] = -b;
    z[15] = -a;
    w[15] = v;
    x[16] = b;
    y[16] = a;
    z[16] = a;
    w[16] = v;
    x[17] = -b;
    y[17] = a;
    z[17] = a;
    w[17] = v;
    x[18] = b;
    y[18] = -a;
    z[18] = a;
    w[18] = v;
    x[19] = -b;
    y[19] = -a;
    z[19] = a;
    w[19] = v;
    x[20] = b;
    y[20] = a;
    z[20] = -a;
    w[20] = v;
    x[21] = -b;
    y[21] = a;
    z[21] = -a;
    w[21] = v;
    x[22] = b;
    y[22] = -a;
    z[22] = -a;
    w[22] = v;
    x[23] = -b;
    y[23] = -a;
    z[23] = -a;
    w[23] = v;
    num   = 24;
  } else if (code == 5) {
    b     = sqrt(1.0 - a * a);
    x[0]  = a;
    y[0]  = b;
    z[0]  = 0;
    w[0]  = v;
    x[1]  = -a;
    y[1]  = b;
    z[1]  = 0;
    w[1]  = v;
    x[2]  = a;
    y[2]  = -b;
    z[2]  = 0;
    w[2]  = v;
    x[3]  = -a;
    y[3]  = -b;
    z[3]  = 0;
    w[3]  = v;
    x[4]  = b;
    y[4]  = a;
    z[4]  = 0;
    w[4]  = v;
    x[5]  = -b;
    y[5]  = a;
    z[5]  = 0;
    w[5]  = v;
    x[6]  = b;
    y[6]  = -a;
    z[6]  = 0;
    w[6]  = v;
    x[7]  = -b;
    y[7]  = -a;
    z[7]  = 0;
    w[7]  = v;
    x[8]  = a;
    y[8]  = 0;
    z[8]  = b;
    w[8]  = v;
    x[9]  = -a;
    y[9]  = 0;
    z[9]  = b;
    w[9]  = v;
    x[10] = a;
    y[10] = 0;
    z[10] = -b;
    w[10] = v;
    x[11] = -a;
    y[11] = 0;
    z[11] = -b;
    w[11] = v;
    x[12] = b;
    y[12] = 0;
    z[12] = a;
    w[12] = v;
    x[13] = -b;
    y[13] = 0;
    z[13] = a;
    w[13] = v;
    x[14] = b;
    y[14] = 0;
    z[14] = -a;
    w[14] = v;
    x[15] = -b;
    y[15] = 0;
    z[15] = -a;
    w[15] = v;
    x[16] = 0;
    y[16] = a;
    z[16] = b;
    w[16] = v;
    x[17] = 0;
    y[17] = -a;
    z[17] = b;
    w[17] = v;
    x[18] = 0;
    y[18] = a;
    z[18] = -b;
    w[18] = v;
    x[19] = 0;
    y[19] = -a;
    z[19] = -b;
    w[19] = v;
    x[20] = 0;
    y[20] = b;
    z[20] = a;
    w[20] = v;
    x[21] = 0;
    y[21] = -b;
    z[21] = a;
    w[21] = v;
    x[22] = 0;
    y[22] = b;
    z[22] = -a;
    w[22] = v;
    x[23] = 0;
    y[23] = -b;
    z[23] = -a;
    w[23] = v;
    num   = 24;
  } else if (code == 6) {
    c     = sqrt(1.0 - a * a - b * b);
    x[0]  = a;
    y[0]  = b;
    z[0]  = c;
    w[0]  = v;
    x[1]  = -a;
    y[1]  = b;
    z[1]  = c;
    w[1]  = v;
    x[2]  = a;
    y[2]  = -b;
    z[2]  = c;
    w[2]  = v;
    x[3]  = -a;
    y[3]  = -b;
    z[3]  = c;
    w[3]  = v;
    x[4]  = a;
    y[4]  = b;
    z[4]  = -c;
    w[4]  = v;
    x[5]  = -a;
    y[5]  = b;
    z[5]  = -c;
    w[5]  = v;
    x[6]  = a;
    y[6]  = -b;
    z[6]  = -c;
    w[6]  = v;
    x[7]  = -a;
    y[7]  = -b;
    z[7]  = -c;
    w[7]  = v;
    x[8]  = a;
    y[8]  = c;
    z[8]  = b;
    w[8]  = v;
    x[9]  = -a;
    y[9]  = c;
    z[9]  = b;
    w[9]  = v;
    x[10] = a;
    y[10] = -c;
    z[10] = b;
    w[10] = v;
    x[11] = -a;
    y[11] = -c;
    z[11] = b;
    w[11] = v;
    x[12] = a;
    y[12] = c;
    z[12] = -b;
    w[12] = v;
    x[13] = -a;
    y[13] = c;
    z[13] = -b;
    w[13] = v;
    x[14] = a;
    y[14] = -c;
    z[14] = -b;
    w[14] = v;
    x[15] = -a;
    y[15] = -c;
    z[15] = -b;
    w[15] = v;
    x[16] = b;
    y[16] = a;
    z[16] = c;
    w[16] = v;
    x[17] = -b;
    y[17] = a;
    z[17] = c;
    w[17] = v;
    x[18] = b;
    y[18] = -a;
    z[18] = c;
    w[18] = v;
    x[19] = -b;
    y[19] = -a;
    z[19] = c;
    w[19] = v;
    x[20] = b;
    y[20] = a;
    z[20] = -c;
    w[20] = v;
    x[21] = -b;
    y[21] = a;
    z[21] = -c;
    w[21] = v;
    x[22] = b;
    y[22] = -a;
    z[22] = -c;
    w[22] = v;
    x[23] = -b;
    y[23] = -a;
    z[23] = -c;
    w[23] = v;
    x[24] = b;
    y[24] = c;
    z[24] = a;
    w[24] = v;
    x[25] = -b;
    y[25] = c;
    z[25] = a;
    w[25] = v;
    x[26] = b;
    y[26] = -c;
    z[26] = a;
    w[26] = v;
    x[27] = -b;
    y[27] = -c;
    z[27] = a;
    w[27] = v;
    x[28] = b;
    y[28] = c;
    z[28] = -a;
    w[28] = v;
    x[29] = -b;
    y[29] = c;
    z[29] = -a;
    w[29] = v;
    x[30] = b;
    y[30] = -c;
    z[30] = -a;
    w[30] = v;
    x[31] = -b;
    y[31] = -c;
    z[31] = -a;
    w[31] = v;
    x[32] = c;
    y[32] = a;
    z[32] = b;
    w[32] = v;
    x[33] = -c;
    y[33] = a;
    z[33] = b;
    w[33] = v;
    x[34] = c;
    y[34] = -a;
    z[34] = b;
    w[34] = v;
    x[35] = -c;
    y[35] = -a;
    z[35] = b;
    w[35] = v;
    x[36] = c;
    y[36] = a;
    z[36] = -b;
    w[36] = v;
    x[37] = -c;
    y[37] = a;
    z[37] = -b;
    w[37] = v;
    x[38] = c;
    y[38] = -a;
    z[38] = -b;
    w[38] = v;
    x[39] = -c;
    y[39] = -a;
    z[39] = -b;
    w[39] = v;
    x[40] = c;
    y[40] = b;
    z[40] = a;
    w[40] = v;
    x[41] = -c;
    y[41] = b;
    z[41] = a;
    w[41] = v;
    x[42] = c;
    y[42] = -b;
    z[42] = a;
    w[42] = v;
    x[43] = -c;
    y[43] = -b;
    z[43] = a;
    w[43] = v;
    x[44] = c;
    y[44] = b;
    z[44] = -a;
    w[44] = v;
    x[45] = -c;
    y[45] = b;
    z[45] = -a;
    w[45] = v;
    x[46] = c;
    y[46] = -b;
    z[46] = -a;
    w[46] = v;
    x[47] = -c;
    y[47] = -b;
    z[47] = -a;
    w[47] = v;
    num   = 48;
  } else {
    fprintf(stderr, "\nGEN_OH - Fatal error!\nIllegal value of code.\n");
    return 1; //exit(1);
  }
  return num;
}
//****************************************************************************80

int ld0006(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0006 computes the 6 point Lebedev angular grid.
//
//  Modified:
//
//    11 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.1666666666666667;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0014(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0014 computes the 14 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.6666666666666667e-1;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.7500000000000000e-1;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0026(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0026 computes the 26 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.4761904761904762e-1;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.3809523809523810e-1;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.3214285714285714e-1;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0038(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0038 computes the 38 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.9523809523809524e-2;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.3214285714285714e-1;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4597008433809831;
  v = 0.2857142857142857e-1;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0050(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0050 computes the 50 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.1269841269841270e-1;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.2257495590828924e-1;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.2109375000000000e-1;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3015113445777636;
  v = 0.2017333553791887e-1;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0074(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0074 computes the 74 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.5130671797338464e-3;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.1660406956574204e-1;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = -0.2958603896103896e-1;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4803844614152614;
  v = 0.2657620708215946e-1;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3207726489807764;
  v = 0.1652217099371571e-1;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0086(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0086 computes the 86 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.1154401154401154e-1;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.1194390908585628e-1;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3696028464541502;
  v = 0.1111055571060340e-1;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6943540066026664;
  v = 0.1187650129453714e-1;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3742430390903412;
  v = 0.1181230374690448e-1;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0110(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0110 computes the 110 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.3828270494937162e-2;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.9793737512487512e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1851156353447362;
  v = 0.8211737283191111e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6904210483822922;
  v = 0.9942814891178103e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3956894730559419;
  v = 0.9595471336070963e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4783690288121502;
  v = 0.9694996361663028e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0146(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0146 computes the 146 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.5996313688621381e-3;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.7372999718620756e-2;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.7210515360144488e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6764410400114264;
  v = 0.7116355493117555e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4174961227965453;
  v = 0.6753829486314477e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1574676672039082;
  v = 0.7574394159054034e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1403553811713183;
  b = 0.4493328323269557;
  v = 0.6991087353303262e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0170(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0170 computes the 170 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.5544842902037365e-2;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.6071332770670752e-2;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.6383674773515093e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2551252621114134;
  v = 0.5183387587747790e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6743601460362766;
  v = 0.6317929009813725e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4318910696719410;
  v = 0.6201670006589077e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2613931360335988;
  v = 0.5477143385137348e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4990453161796037;
  b = 0.1446630744325115;
  v = 0.5968383987681156e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0194(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0194 computes the 194 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.1782340447244611e-2;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.5716905949977102e-2;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.5573383178848738e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6712973442695226;
  v = 0.5608704082587997e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2892465627575439;
  v = 0.5158237711805383e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4446933178717437;
  v = 0.5518771467273614e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1299335447650067;
  v = 0.4106777028169394e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3457702197611283;
  v = 0.5051846064614808e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1590417105383530;
  b = 0.8360360154824589;
  v = 0.5530248916233094e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0230(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0230 computes the 230 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = -0.5522639919727325e-1;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.4450274607445226e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4492044687397611;
  v = 0.4496841067921404e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2520419490210201;
  v = 0.5049153450478750e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6981906658447242;
  v = 0.3976408018051883e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6587405243460960;
  v = 0.4401400650381014e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4038544050097660e-1;
  v = 0.1724544350544401e-1;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5823842309715585;
  v = 0.4231083095357343e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3545877390518688;
  v = 0.5198069864064399e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2272181808998187;
  b = 0.4864661535886647;
  v = 0.4695720972568883e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0266(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0266 computes the 266 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = -0.1313769127326952e-2;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = -0.2522728704859336e-2;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.4186853881700583e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7039373391585475;
  v = 0.5315167977810885e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1012526248572414;
  v = 0.4047142377086219e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4647448726420539;
  v = 0.4112482394406990e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3277420654971629;
  v = 0.3595584899758782e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6620338663699974;
  v = 0.4256131351428158e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8506508083520399;
  v = 0.4229582700647240e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3233484542692899;
  b = 0.1153112011009701;
  v = 0.4080914225780505e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2314790158712601;
  b = 0.5244939240922365;
  v = 0.4071467593830964e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0302(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0302 computes the 302 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.8545911725128148e-3;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.3599119285025571e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3515640345570105;
  v = 0.3449788424305883e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6566329410219612;
  v = 0.3604822601419882e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4729054132581005;
  v = 0.3576729661743367e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9618308522614784e-1;
  v = 0.2352101413689164e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2219645236294178;
  v = 0.3108953122413675e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7011766416089545;
  v = 0.3650045807677255e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2644152887060663;
  v = 0.2982344963171804e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5718955891878961;
  v = 0.3600820932216460e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2510034751770465;
  b = 0.8000727494073952;
  v = 0.3571540554273387e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1233548532583327;
  b = 0.4127724083168531;
  v = 0.3392312205006170e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0350(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0350 computes the 350 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.3006796749453936e-2;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.3050627745650771e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7068965463912316;
  v = 0.1621104600288991e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4794682625712025;
  v = 0.3005701484901752e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1927533154878019;
  v = 0.2990992529653774e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6930357961327123;
  v = 0.2982170644107595e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3608302115520091;
  v = 0.2721564237310992e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6498486161496169;
  v = 0.3033513795811141e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1932945013230339;
  v = 0.3007949555218533e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3800494919899303;
  v = 0.2881964603055307e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2899558825499574;
  b = 0.7934537856582316;
  v = 0.2958357626535696e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9684121455103957e-1;
  b = 0.8280801506686862;
  v = 0.3036020026407088e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1833434647041659;
  b = 0.9074658265305127;
  v = 0.2832187403926303e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0434(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0434 computes the 434 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.5265897968224436e-3;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.2548219972002607e-2;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.2512317418927307e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6909346307509111;
  v = 0.2530403801186355e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1774836054609158;
  v = 0.2014279020918528e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4914342637784746;
  v = 0.2501725168402936e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6456664707424256;
  v = 0.2513267174597564e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2861289010307638;
  v = 0.2302694782227416e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7568084367178018e-1;
  v = 0.1462495621594614e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3927259763368002;
  v = 0.2445373437312980e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8818132877794288;
  v = 0.2417442375638981e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9776428111182649;
  v = 0.1910951282179532e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2054823696403044;
  b = 0.8689460322872412;
  v = 0.2416930044324775e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5905157048925271;
  b = 0.7999278543857286;
  v = 0.2512236854563495e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5550152361076807;
  b = 0.7717462626915901;
  v = 0.2496644054553086e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9371809858553722;
  b = 0.3344363145343455;
  v = 0.2236607760437849e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0590(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0590 computes the 590 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.3095121295306187e-3;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.1852379698597489e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7040954938227469;
  v = 0.1871790639277744e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6807744066455243;
  v = 0.1858812585438317e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6372546939258752;
  v = 0.1852028828296213e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5044419707800358;
  v = 0.1846715956151242e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4215761784010967;
  v = 0.1818471778162769e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3317920736472123;
  v = 0.1749564657281154e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2384736701421887;
  v = 0.1617210647254411e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1459036449157763;
  v = 0.1384737234851692e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6095034115507196e-1;
  v = 0.9764331165051050e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6116843442009876;
  v = 0.1857161196774078e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3964755348199858;
  v = 0.1705153996395864e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1724782009907724;
  v = 0.1300321685886048e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5610263808622060;
  b = 0.3518280927733519;
  v = 0.1842866472905286e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4742392842551980;
  b = 0.2634716655937950;
  v = 0.1802658934377451e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5984126497885380;
  b = 0.1816640840360209;
  v = 0.1849830560443660e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3791035407695563;
  b = 0.1720795225656878;
  v = 0.1713904507106709e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2778673190586244;
  b = 0.8213021581932511e-1;
  v = 0.1555213603396808e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5033564271075117;
  b = 0.8999205842074875e-1;
  v = 0.1802239128008525e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0770(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0770 computes the 770 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.2192942088181184e-3;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.1436433617319080e-2;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.1421940344335877e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5087204410502360e-1;
  v = 0.6798123511050502e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1228198790178831;
  v = 0.9913184235294912e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2026890814408786;
  v = 0.1180207833238949e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2847745156464294;
  v = 0.1296599602080921e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3656719078978026;
  v = 0.1365871427428316e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4428264886713469;
  v = 0.1402988604775325e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5140619627249735;
  v = 0.1418645563595609e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6306401219166803;
  v = 0.1421376741851662e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6716883332022612;
  v = 0.1423996475490962e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6979792685336881;
  v = 0.1431554042178567e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1446865674195309;
  v = 0.9254401499865368e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3390263475411216;
  v = 0.1250239995053509e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5335804651263506;
  v = 0.1394365843329230e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6944024393349413e-1;
  b = 0.2355187894242326;
  v = 0.1127089094671749e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2269004109529460;
  b = 0.4102182474045730;
  v = 0.1345753760910670e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8025574607775339e-1;
  b = 0.6214302417481605;
  v = 0.1424957283316783e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1467999527896572;
  b = 0.3245284345717394;
  v = 0.1261523341237750e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1571507769824727;
  b = 0.5224482189696630;
  v = 0.1392547106052696e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2365702993157246;
  b = 0.6017546634089558;
  v = 0.1418761677877656e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7714815866765732e-1;
  b = 0.4346575516141163;
  v = 0.1338366684479554e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3062936666210730;
  b = 0.4908826589037616;
  v = 0.1393700862676131e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3822477379524787;
  b = 0.5648768149099500;
  v = 0.1415914757466932e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld0974(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD0974 computes the 974 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.1438294190527431e-3;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.1125772288287004e-2;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4292963545341347e-1;
  v = 0.4948029341949241e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1051426854086404;
  v = 0.7357990109125470e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1750024867623087;
  v = 0.8889132771304384e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2477653379650257;
  v = 0.9888347838921435e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3206567123955957;
  v = 0.1053299681709471e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3916520749849983;
  v = 0.1092778807014578e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4590825874187624;
  v = 0.1114389394063227e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5214563888415861;
  v = 0.1123724788051555e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6253170244654199;
  v = 0.1125239325243814e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6637926744523170;
  v = 0.1126153271815905e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6910410398498301;
  v = 0.1130286931123841e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7052907007457760;
  v = 0.1134986534363955e-2;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1236686762657990;
  v = 0.6823367927109931e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2940777114468387;
  v = 0.9454158160447096e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4697753849207649;
  v = 0.1074429975385679e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6334563241139567;
  v = 0.1129300086569132e-2;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5974048614181342e-1;
  b = 0.2029128752777523;
  v = 0.8436884500901954e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1375760408473636;
  b = 0.4602621942484054;
  v = 0.1075255720448885e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3391016526336286;
  b = 0.5030673999662036;
  v = 0.1108577236864462e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1271675191439820;
  b = 0.2817606422442134;
  v = 0.9566475323783357e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2693120740413512;
  b = 0.4331561291720157;
  v = 0.1080663250717391e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1419786452601918;
  b = 0.6256167358580814;
  v = 0.1126797131196295e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6709284600738255e-1;
  b = 0.3798395216859157;
  v = 0.1022568715358061e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7057738183256172e-1;
  b = 0.5517505421423520;
  v = 0.1108960267713108e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2783888477882155;
  b = 0.6029619156159187;
  v = 0.1122790653435766e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1979578938917407;
  b = 0.3589606329589096;
  v = 0.1032401847117460e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2087307061103274;
  b = 0.5348666438135476;
  v = 0.1107249382283854e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4055122137872836;
  b = 0.5674997546074373;
  v = 0.1121780048519972e-2;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld1202(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD1202 computes the 1202 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.1105189233267572e-3;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.9205232738090741e-3;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.9133159786443561e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3712636449657089e-1;
  v = 0.3690421898017899e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9140060412262223e-1;
  v = 0.5603990928680660e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1531077852469906;
  v = 0.6865297629282609e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2180928891660612;
  v = 0.7720338551145630e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2839874532200175;
  v = 0.8301545958894795e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3491177600963764;
  v = 0.8686692550179628e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4121431461444309;
  v = 0.8927076285846890e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4718993627149127;
  v = 0.9060820238568219e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5273145452842337;
  v = 0.9119777254940867e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6209475332444019;
  v = 0.9128720138604181e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6569722711857291;
  v = 0.9130714935691735e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6841788309070143;
  v = 0.9152873784554116e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7012604330123631;
  v = 0.9187436274321654e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1072382215478166;
  v = 0.5176977312965694e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2582068959496968;
  v = 0.7331143682101417e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4172752955306717;
  v = 0.8463232836379928e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5700366911792503;
  v = 0.9031122694253992e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9827986018263947;
  b = 0.1771774022615325;
  v = 0.6485778453163257e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9624249230326228;
  b = 0.2475716463426288;
  v = 0.7435030910982369e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9402007994128811;
  b = 0.3354616289066489;
  v = 0.7998527891839054e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9320822040143202;
  b = 0.3173615246611977;
  v = 0.8101731497468018e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9043674199393299;
  b = 0.4090268427085357;
  v = 0.8483389574594331e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8912407560074747;
  b = 0.3854291150669224;
  v = 0.8556299257311812e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8676435628462708;
  b = 0.4932221184851285;
  v = 0.8803208679738260e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8581979986041619;
  b = 0.4785320675922435;
  v = 0.8811048182425720e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8396753624049856;
  b = 0.4507422593157064;
  v = 0.8850282341265444e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8165288564022188;
  b = 0.5632123020762100;
  v = 0.9021342299040653e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8015469370783529;
  b = 0.5434303569693900;
  v = 0.9010091677105086e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7773563069070351;
  b = 0.5123518486419871;
  v = 0.9022692938426915e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7661621213900394;
  b = 0.6394279634749102;
  v = 0.9158016174693465e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7553584143533510;
  b = 0.6269805509024392;
  v = 0.9131578003189435e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7344305757559503;
  b = 0.6031161693096310;
  v = 0.9107813579482705e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7043837184021765;
  b = 0.5693702498468441;
  v = 0.9105760258970126e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld1454(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD1454 computes the 1454 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.7777160743261247e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.7557646413004701e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3229290663413854e-1;
  v = 0.2841633806090617e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8036733271462222e-1;
  v = 0.4374419127053555e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1354289960531653;
  v = 0.5417174740872172e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1938963861114426;
  v = 0.6148000891358593e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2537343715011275;
  v = 0.6664394485800705e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3135251434752570;
  v = 0.7025039356923220e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3721558339375338;
  v = 0.7268511789249627e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4286809575195696;
  v = 0.7422637534208629e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4822510128282994;
  v = 0.7509545035841214e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5320679333566263;
  v = 0.7548535057718401e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6172998195394274;
  v = 0.7554088969774001e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6510679849127481;
  v = 0.7553147174442808e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6777315251687360;
  v = 0.7564767653292297e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6963109410648741;
  v = 0.7587991808518730e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7058935009831749;
  v = 0.7608261832033027e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9955546194091857;
  v = 0.4021680447874916e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9734115901794209;
  v = 0.5804871793945964e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9275693732388626;
  v = 0.6792151955945159e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8568022422795103;
  v = 0.7336741211286294e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7623495553719372;
  v = 0.7581866300989608e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5707522908892223;
  b = 0.4387028039889501;
  v = 0.7538257859800743e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5196463388403083;
  b = 0.3858908414762617;
  v = 0.7483517247053123e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4646337531215351;
  b = 0.3301937372343854;
  v = 0.7371763661112059e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4063901697557691;
  b = 0.2725423573563777;
  v = 0.7183448895756934e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3456329466643087;
  b = 0.2139510237495250;
  v = 0.6895815529822191e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2831395121050332;
  b = 0.1555922309786647;
  v = 0.6480105801792886e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2197682022925330;
  b = 0.9892878979686097e-1;
  v = 0.5897558896594636e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1564696098650355;
  b = 0.4598642910675510e-1;
  v = 0.5095708849247346e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6027356673721295;
  b = 0.3376625140173426;
  v = 0.7536906428909755e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5496032320255096;
  b = 0.2822301309727988;
  v = 0.7472505965575118e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4921707755234567;
  b = 0.2248632342592540;
  v = 0.7343017132279698e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4309422998598483;
  b = 0.1666224723456479;
  v = 0.7130871582177445e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3664108182313672;
  b = 0.1086964901822169;
  v = 0.6817022032112776e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2990189057758436;
  b = 0.5251989784120085e-1;
  v = 0.6380941145604121e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6268724013144998;
  b = 0.2297523657550023;
  v = 0.7550381377920310e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5707324144834607;
  b = 0.1723080607093800;
  v = 0.7478646640144802e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5096360901960365;
  b = 0.1140238465390513;
  v = 0.7335918720601220e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4438729938312456;
  b = 0.5611522095882537e-1;
  v = 0.7110120527658118e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6419978471082389;
  b = 0.1164174423140873;
  v = 0.7571363978689501e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5817218061802611;
  b = 0.5797589531445219e-1;
  v = 0.7489908329079234e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld1730(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD1730 computes the 1730 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.6309049437420976e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.6398287705571748e-3;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.6357185073530720e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2860923126194662e-1;
  v = 0.2221207162188168e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7142556767711522e-1;
  v = 0.3475784022286848e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1209199540995559;
  v = 0.4350742443589804e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1738673106594379;
  v = 0.4978569136522127e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2284645438467734;
  v = 0.5435036221998053e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2834807671701512;
  v = 0.5765913388219542e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3379680145467339;
  v = 0.6001200359226003e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3911355454819537;
  v = 0.6162178172717512e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4422860353001403;
  v = 0.6265218152438485e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4907781568726057;
  v = 0.6323987160974212e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5360006153211468;
  v = 0.6350767851540569e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6142105973596603;
  v = 0.6354362775297107e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6459300387977504;
  v = 0.6352302462706235e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6718056125089225;
  v = 0.6358117881417972e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6910888533186254;
  v = 0.6373101590310117e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7030467416823252;
  v = 0.6390428961368665e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8354951166354646e-1;
  v = 0.3186913449946576e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2050143009099486;
  v = 0.4678028558591711e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3370208290706637;
  v = 0.5538829697598626e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4689051484233963;
  v = 0.6044475907190476e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5939400424557334;
  v = 0.6313575103509012e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1394983311832261;
  b = 0.4097581162050343e-1;
  v = 0.4078626431855630e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1967999180485014;
  b = 0.8851987391293348e-1;
  v = 0.4759933057812725e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2546183732548967;
  b = 0.1397680182969819;
  v = 0.5268151186413440e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3121281074713875;
  b = 0.1929452542226526;
  v = 0.5643048560507316e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3685981078502492;
  b = 0.2467898337061562;
  v = 0.5914501076613073e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4233760321547856;
  b = 0.3003104124785409;
  v = 0.6104561257874195e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4758671236059246;
  b = 0.3526684328175033;
  v = 0.6230252860707806e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5255178579796463;
  b = 0.4031134861145713;
  v = 0.6305618761760796e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5718025633734589;
  b = 0.4509426448342351;
  v = 0.6343092767597889e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2686927772723415;
  b = 0.4711322502423248e-1;
  v = 0.5176268945737826e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3306006819904809;
  b = 0.9784487303942695e-1;
  v = 0.5564840313313692e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3904906850594983;
  b = 0.1505395810025273;
  v = 0.5856426671038980e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4479957951904390;
  b = 0.2039728156296050;
  v = 0.6066386925777091e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5027076848919780;
  b = 0.2571529941121107;
  v = 0.6208824962234458e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5542087392260217;
  b = 0.3092191375815670;
  v = 0.6296314297822907e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6020850887375187;
  b = 0.3593807506130276;
  v = 0.6340423756791859e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4019851409179594;
  b = 0.5063389934378671e-1;
  v = 0.5829627677107342e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4635614567449800;
  b = 0.1032422269160612;
  v = 0.6048693376081110e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5215860931591575;
  b = 0.1566322094006254;
  v = 0.6202362317732461e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5758202499099271;
  b = 0.2098082827491099;
  v = 0.6299005328403779e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6259893683876795;
  b = 0.2618824114553391;
  v = 0.6347722390609353e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5313795124811891;
  b = 0.5263245019338556e-1;
  v = 0.6203778981238834e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5893317955931995;
  b = 0.1061059730982005;
  v = 0.6308414671239979e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6426246321215801;
  b = 0.1594171564034221;
  v = 0.6362706466959498e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6511904367376113;
  b = 0.5354789536565540e-1;
  v = 0.6375414170333233e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld2030(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD2030 computes the 2030 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.4656031899197431e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.5421549195295507e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2540835336814348e-1;
  v = 0.1778522133346553e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6399322800504915e-1;
  v = 0.2811325405682796e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1088269469804125;
  v = 0.3548896312631459e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1570670798818287;
  v = 0.4090310897173364e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2071163932282514;
  v = 0.4493286134169965e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2578914044450844;
  v = 0.4793728447962723e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3085687558169623;
  v = 0.5015415319164265e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3584719706267024;
  v = 0.5175127372677937e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4070135594428709;
  v = 0.5285522262081019e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4536618626222638;
  v = 0.5356832703713962e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4979195686463577;
  v = 0.5397914736175170e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5393075111126999;
  v = 0.5416899441599930e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6115617676843916;
  v = 0.5419308476889938e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6414308435160159;
  v = 0.5416936902030596e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6664099412721607;
  v = 0.5419544338703164e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6859161771214913;
  v = 0.5428983656630975e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6993625593503890;
  v = 0.5442286500098193e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7062393387719380;
  v = 0.5452250345057301e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7479028168349763e-1;
  v = 0.2568002497728530e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1848951153969366;
  v = 0.3827211700292145e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3059529066581305;
  v = 0.4579491561917824e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4285556101021362;
  v = 0.5042003969083574e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5468758653496526;
  v = 0.5312708889976025e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6565821978343439;
  v = 0.5438401790747117e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1253901572367117;
  b = 0.3681917226439641e-1;
  v = 0.3316041873197344e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1775721510383941;
  b = 0.7982487607213301e-1;
  v = 0.3899113567153771e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2305693358216114;
  b = 0.1264640966592335;
  v = 0.4343343327201309e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2836502845992063;
  b = 0.1751585683418957;
  v = 0.4679415262318919e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3361794746232590;
  b = 0.2247995907632670;
  v = 0.4930847981631031e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3875979172264824;
  b = 0.2745299257422246;
  v = 0.5115031867540091e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4374019316999074;
  b = 0.3236373482441118;
  v = 0.5245217148457367e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4851275843340022;
  b = 0.3714967859436741;
  v = 0.5332041499895321e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5303391803806868;
  b = 0.4175353646321745;
  v = 0.5384583126021542e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5726197380596287;
  b = 0.4612084406355461;
  v = 0.5411067210798852e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2431520732564863;
  b = 0.4258040133043952e-1;
  v = 0.4259797391468714e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3002096800895869;
  b = 0.8869424306722721e-1;
  v = 0.4604931368460021e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3558554457457432;
  b = 0.1368811706510655;
  v = 0.4871814878255202e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4097782537048887;
  b = 0.1860739985015033;
  v = 0.5072242910074885e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4616337666067458;
  b = 0.2354235077395853;
  v = 0.5217069845235350e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5110707008417874;
  b = 0.2842074921347011;
  v = 0.5315785966280310e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5577415286163795;
  b = 0.3317784414984102;
  v = 0.5376833708758905e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6013060431366950;
  b = 0.3775299002040700;
  v = 0.5408032092069521e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3661596767261781;
  b = 0.4599367887164592e-1;
  v = 0.4842744917904866e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4237633153506581;
  b = 0.9404893773654421e-1;
  v = 0.5048926076188130e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4786328454658452;
  b = 0.1431377109091971;
  v = 0.5202607980478373e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5305702076789774;
  b = 0.1924186388843570;
  v = 0.5309932388325743e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5793436224231788;
  b = 0.2411590944775190;
  v = 0.5377419770895208e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6247069017094747;
  b = 0.2886871491583605;
  v = 0.5411696331677717e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4874315552535204;
  b = 0.4804978774953206e-1;
  v = 0.5197996293282420e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5427337322059053;
  b = 0.9716857199366665e-1;
  v = 0.5311120836622945e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5943493747246700;
  b = 0.1465205839795055;
  v = 0.5384309319956951e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6421314033564943;
  b = 0.1953579449803574;
  v = 0.5421859504051886e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6020628374713980;
  b = 0.4916375015738108e-1;
  v = 0.5390948355046314e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6529222529856881;
  b = 0.9861621540127005e-1;
  v = 0.5433312705027845e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld2354(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD2354 computes the 2354 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.3922616270665292e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.4703831750854424e-3;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.4678202801282136e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2290024646530589e-1;
  v = 0.1437832228979900e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5779086652271284e-1;
  v = 0.2303572493577644e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9863103576375984e-1;
  v = 0.2933110752447454e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1428155792982185;
  v = 0.3402905998359838e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1888978116601463;
  v = 0.3759138466870372e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2359091682970210;
  v = 0.4030638447899798e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2831228833706171;
  v = 0.4236591432242211e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3299495857966693;
  v = 0.4390522656946746e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3758840802660796;
  v = 0.4502523466626247e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4204751831009480;
  v = 0.4580577727783541e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4633068518751051;
  v = 0.4631391616615899e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5039849474507313;
  v = 0.4660928953698676e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5421265793440747;
  v = 0.4674751807936953e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6092660230557310;
  v = 0.4676414903932920e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6374654204984869;
  v = 0.4674086492347870e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6615136472609892;
  v = 0.4674928539483207e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6809487285958127;
  v = 0.4680748979686447e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6952980021665196;
  v = 0.4690449806389040e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7041245497695400;
  v = 0.4699877075860818e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6744033088306065e-1;
  v = 0.2099942281069176e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1678684485334166;
  v = 0.3172269150712804e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2793559049539613;
  v = 0.3832051358546523e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3935264218057639;
  v = 0.4252193818146985e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5052629268232558;
  v = 0.4513807963755000e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6107905315437531;
  v = 0.4657797469114178e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1135081039843524;
  b = 0.3331954884662588e-1;
  v = 0.2733362800522836e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1612866626099378;
  b = 0.7247167465436538e-1;
  v = 0.3235485368463559e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2100786550168205;
  b = 0.1151539110849745;
  v = 0.3624908726013453e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2592282009459942;
  b = 0.1599491097143677;
  v = 0.3925540070712828e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3081740561320203;
  b = 0.2058699956028027;
  v = 0.4156129781116235e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3564289781578164;
  b = 0.2521624953502911;
  v = 0.4330644984623263e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4035587288240703;
  b = 0.2982090785797674;
  v = 0.4459677725921312e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4491671196373903;
  b = 0.3434762087235733;
  v = 0.4551593004456795e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4928854782917489;
  b = 0.3874831357203437;
  v = 0.4613341462749918e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5343646791958988;
  b = 0.4297814821746926;
  v = 0.4651019618269806e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5732683216530990;
  b = 0.4699402260943537;
  v = 0.4670249536100625e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2214131583218986;
  b = 0.3873602040643895e-1;
  v = 0.3549555576441708e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2741796504750071;
  b = 0.8089496256902013e-1;
  v = 0.3856108245249010e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3259797439149485;
  b = 0.1251732177620872;
  v = 0.4098622845756882e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3765441148826891;
  b = 0.1706260286403185;
  v = 0.4286328604268950e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4255773574530558;
  b = 0.2165115147300408;
  v = 0.4427802198993945e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4727795117058430;
  b = 0.2622089812225259;
  v = 0.4530473511488561e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5178546895819012;
  b = 0.3071721431296201;
  v = 0.4600805475703138e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5605141192097460;
  b = 0.3508998998801138;
  v = 0.4644599059958017e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6004763319352512;
  b = 0.3929160876166931;
  v = 0.4667274455712508e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3352842634946949;
  b = 0.4202563457288019e-1;
  v = 0.4069360518020356e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3891971629814670;
  b = 0.8614309758870850e-1;
  v = 0.4260442819919195e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4409875565542281;
  b = 0.1314500879380001;
  v = 0.4408678508029063e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4904893058592484;
  b = 0.1772189657383859;
  v = 0.4518748115548597e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5375056138769549;
  b = 0.2228277110050294;
  v = 0.4595564875375116e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5818255708669969;
  b = 0.2677179935014386;
  v = 0.4643988774315846e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6232334858144959;
  b = 0.3113675035544165;
  v = 0.4668827491646946e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4489485354492058;
  b = 0.4409162378368174e-1;
  v = 0.4400541823741973e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5015136875933150;
  b = 0.8939009917748489e-1;
  v = 0.4514512890193797e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5511300550512623;
  b = 0.1351806029383365;
  v = 0.4596198627347549e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5976720409858000;
  b = 0.1808370355053196;
  v = 0.4648659016801781e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6409956378989354;
  b = 0.2257852192301602;
  v = 0.4675502017157673e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5581222330827514;
  b = 0.4532173421637160e-1;
  v = 0.4598494476455523e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6074705984161695;
  b = 0.9117488031840314e-1;
  v = 0.4654916955152048e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6532272537379033;
  b = 0.1369294213140155;
  v = 0.4684709779505137e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6594761494500487;
  b = 0.4589901487275583e-1;
  v = 0.4691445539106986e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld2702(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD2702 computes the 2702 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.2998675149888161e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.4077860529495355e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2065562538818703e-1;
  v = 0.1185349192520667e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5250918173022379e-1;
  v = 0.1913408643425751e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8993480082038376e-1;
  v = 0.2452886577209897e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1306023924436019;
  v = 0.2862408183288702e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1732060388531418;
  v = 0.3178032258257357e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2168727084820249;
  v = 0.3422945667633690e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2609528309173586;
  v = 0.3612790520235922e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3049252927938952;
  v = 0.3758638229818521e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3483484138084404;
  v = 0.3868711798859953e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3908321549106406;
  v = 0.3949429933189938e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4320210071894814;
  v = 0.4006068107541156e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4715824795890053;
  v = 0.4043192149672723e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5091984794078453;
  v = 0.4064947495808078e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5445580145650803;
  v = 0.4075245619813152e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6072575796841768;
  v = 0.4076423540893566e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6339484505755803;
  v = 0.4074280862251555e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6570718257486958;
  v = 0.4074163756012244e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6762557330090709;
  v = 0.4077647795071246e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6911161696923790;
  v = 0.4084517552782530e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7012841911659961;
  v = 0.4092468459224052e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7064559272410020;
  v = 0.4097872687240906e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6123554989894765e-1;
  v = 0.1738986811745028e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1533070348312393;
  v = 0.2659616045280191e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2563902605244206;
  v = 0.3240596008171533e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3629346991663361;
  v = 0.3621195964432943e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4683949968987538;
  v = 0.3868838330760539e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5694479240657952;
  v = 0.4018911532693111e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6634465430993955;
  v = 0.4089929432983252e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1033958573552305;
  b = 0.3034544009063584e-1;
  v = 0.2279907527706409e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1473521412414395;
  b = 0.6618803044247135e-1;
  v = 0.2715205490578897e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1924552158705967;
  b = 0.1054431128987715;
  v = 0.3057917896703976e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2381094362890328;
  b = 0.1468263551238858;
  v = 0.3326913052452555e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2838121707936760;
  b = 0.1894486108187886;
  v = 0.3537334711890037e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3291323133373415;
  b = 0.2326374238761579;
  v = 0.3700567500783129e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3736896978741460;
  b = 0.2758485808485768;
  v = 0.3825245372589122e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4171406040760013;
  b = 0.3186179331996921;
  v = 0.3918125171518296e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4591677985256915;
  b = 0.3605329796303794;
  v = 0.3984720419937579e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4994733831718418;
  b = 0.4012147253586509;
  v = 0.4029746003338211e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5377731830445096;
  b = 0.4403050025570692;
  v = 0.4057428632156627e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5737917830001331;
  b = 0.4774565904277483;
  v = 0.4071719274114857e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2027323586271389;
  b = 0.3544122504976147e-1;
  v = 0.2990236950664119e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2516942375187273;
  b = 0.7418304388646328e-1;
  v = 0.3262951734212878e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3000227995257181;
  b = 0.1150502745727186;
  v = 0.3482634608242413e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3474806691046342;
  b = 0.1571963371209364;
  v = 0.3656596681700892e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3938103180359209;
  b = 0.1999631877247100;
  v = 0.3791740467794218e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4387519590455703;
  b = 0.2428073457846535;
  v = 0.3894034450156905e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4820503960077787;
  b = 0.2852575132906155;
  v = 0.3968600245508371e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5234573778475101;
  b = 0.3268884208674639;
  v = 0.4019931351420050e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5627318647235282;
  b = 0.3673033321675939;
  v = 0.4052108801278599e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5996390607156954;
  b = 0.4061211551830290;
  v = 0.4068978613940934e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3084780753791947;
  b = 0.3860125523100059e-1;
  v = 0.3454275351319704e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3589988275920223;
  b = 0.7928938987104867e-1;
  v = 0.3629963537007920e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4078628415881973;
  b = 0.1212614643030087;
  v = 0.3770187233889873e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4549287258889735;
  b = 0.1638770827382693;
  v = 0.3878608613694378e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5000278512957279;
  b = 0.2065965798260176;
  v = 0.3959065270221274e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5429785044928199;
  b = 0.2489436378852235;
  v = 0.4015286975463570e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5835939850491711;
  b = 0.2904811368946891;
  v = 0.4050866785614717e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6216870353444856;
  b = 0.3307941957666609;
  v = 0.4069320185051913e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4151104662709091;
  b = 0.4064829146052554e-1;
  v = 0.3760120964062763e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4649804275009218;
  b = 0.8258424547294755e-1;
  v = 0.3870969564418064e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5124695757009662;
  b = 0.1251841962027289;
  v = 0.3955287790534055e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5574711100606224;
  b = 0.1679107505976331;
  v = 0.4015361911302668e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5998597333287227;
  b = 0.2102805057358715;
  v = 0.4053836986719548e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6395007148516600;
  b = 0.2518418087774107;
  v = 0.4073578673299117e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5188456224746252;
  b = 0.4194321676077518e-1;
  v = 0.3954628379231406e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5664190707942778;
  b = 0.8457661551921499e-1;
  v = 0.4017645508847530e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6110464353283153;
  b = 0.1273652932519396;
  v = 0.4059030348651293e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6526430302051563;
  b = 0.1698173239076354;
  v = 0.4080565809484880e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6167551880377548;
  b = 0.4266398851548864e-1;
  v = 0.4063018753664651e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6607195418355383;
  b = 0.8551925814238349e-1;
  v = 0.4087191292799671e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld3074(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD3074 computes the 3074 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.2599095953754734e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.3603134089687541e-3;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.3586067974412447e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1886108518723392e-1;
  v = 0.9831528474385880e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4800217244625303e-1;
  v = 0.1605023107954450e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8244922058397242e-1;
  v = 0.2072200131464099e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1200408362484023;
  v = 0.2431297618814187e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1595773530809965;
  v = 0.2711819064496707e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2002635973434064;
  v = 0.2932762038321116e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2415127590139982;
  v = 0.3107032514197368e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2828584158458477;
  v = 0.3243808058921213e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3239091015338138;
  v = 0.3349899091374030e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3643225097962194;
  v = 0.3430580688505218e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4037897083691802;
  v = 0.3490124109290343e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4420247515194127;
  v = 0.3532148948561955e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4787572538464938;
  v = 0.3559862669062833e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5137265251275234;
  v = 0.3576224317551411e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5466764056654611;
  v = 0.3584050533086076e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6054859420813535;
  v = 0.3584903581373224e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6308106701764562;
  v = 0.3582991879040586e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6530369230179584;
  v = 0.3582371187963125e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6718609524611158;
  v = 0.3584353631122350e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6869676499894013;
  v = 0.3589120166517785e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6980467077240748;
  v = 0.3595445704531601e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7048241721250522;
  v = 0.3600943557111074e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5591105222058232e-1;
  v = 0.1456447096742039e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1407384078513916;
  v = 0.2252370188283782e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2364035438976309;
  v = 0.2766135443474897e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3360602737818170;
  v = 0.3110729491500851e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4356292630054665;
  v = 0.3342506712303391e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5321569415256174;
  v = 0.3491981834026860e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6232956305040554;
  v = 0.3576003604348932e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9469870086838469e-1;
  b = 0.2778748387309470e-1;
  v = 0.1921921305788564e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1353170300568141;
  b = 0.6076569878628364e-1;
  v = 0.2301458216495632e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1771679481726077;
  b = 0.9703072762711040e-1;
  v = 0.2604248549522893e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2197066664231751;
  b = 0.1354112458524762;
  v = 0.2845275425870697e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2624783557374927;
  b = 0.1750996479744100;
  v = 0.3036870897974840e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3050969521214442;
  b = 0.2154896907449802;
  v = 0.3188414832298066e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3472252637196021;
  b = 0.2560954625740152;
  v = 0.3307046414722089e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3885610219026360;
  b = 0.2965070050624096;
  v = 0.3398330969031360e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4288273776062765;
  b = 0.3363641488734497;
  v = 0.3466757899705373e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4677662471302948;
  b = 0.3753400029836788;
  v = 0.3516095923230054e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5051333589553359;
  b = 0.4131297522144286;
  v = 0.3549645184048486e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5406942145810492;
  b = 0.4494423776081795;
  v = 0.3570415969441392e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5742204122576457;
  b = 0.4839938958841502;
  v = 0.3581251798496118e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1865407027225188;
  b = 0.3259144851070796e-1;
  v = 0.2543491329913348e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2321186453689432;
  b = 0.6835679505297343e-1;
  v = 0.2786711051330776e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2773159142523882;
  b = 0.1062284864451989;
  v = 0.2985552361083679e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3219200192237254;
  b = 0.1454404409323047;
  v = 0.3145867929154039e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3657032593944029;
  b = 0.1854018282582510;
  v = 0.3273290662067609e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4084376778363622;
  b = 0.2256297412014750;
  v = 0.3372705511943501e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4499004945751427;
  b = 0.2657104425000896;
  v = 0.3448274437851510e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4898758141326335;
  b = 0.3052755487631557;
  v = 0.3503592783048583e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5281547442266309;
  b = 0.3439863920645423;
  v = 0.3541854792663162e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5645346989813992;
  b = 0.3815229456121914;
  v = 0.3565995517909428e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5988181252159848;
  b = 0.4175752420966734;
  v = 0.3578802078302898e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2850425424471603;
  b = 0.3562149509862536e-1;
  v = 0.2958644592860982e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3324619433027876;
  b = 0.7330318886871096e-1;
  v = 0.3119548129116835e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3785848333076282;
  b = 0.1123226296008472;
  v = 0.3250745225005984e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4232891028562115;
  b = 0.1521084193337708;
  v = 0.3355153415935208e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4664287050829722;
  b = 0.1921844459223610;
  v = 0.3435847568549328e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5078458493735726;
  b = 0.2321360989678303;
  v = 0.3495786831622488e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5473779816204180;
  b = 0.2715886486360520;
  v = 0.3537767805534621e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5848617133811376;
  b = 0.3101924707571355;
  v = 0.3564459815421428e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6201348281584888;
  b = 0.3476121052890973;
  v = 0.3578464061225468e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3852191185387871;
  b = 0.3763224880035108e-1;
  v = 0.3239748762836212e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4325025061073423;
  b = 0.7659581935637135e-1;
  v = 0.3345491784174287e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4778486229734490;
  b = 0.1163381306083900;
  v = 0.3429126177301782e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5211663693009000;
  b = 0.1563890598752899;
  v = 0.3492420343097421e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5623469504853703;
  b = 0.1963320810149200;
  v = 0.3537399050235257e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6012718188659246;
  b = 0.2357847407258738;
  v = 0.3566209152659172e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6378179206390117;
  b = 0.2743846121244060;
  v = 0.3581084321919782e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4836936460214534;
  b = 0.3895902610739024e-1;
  v = 0.3426522117591512e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5293792562683797;
  b = 0.7871246819312640e-1;
  v = 0.3491848770121379e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5726281253100033;
  b = 0.1187963808202981;
  v = 0.3539318235231476e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6133658776169068;
  b = 0.1587914708061787;
  v = 0.3570231438458694e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6515085491865307;
  b = 0.1983058575227646;
  v = 0.3586207335051714e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5778692716064976;
  b = 0.3977209689791542e-1;
  v = 0.3541196205164025e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6207904288086192;
  b = 0.7990157592981152e-1;
  v = 0.3574296911573953e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6608688171046802;
  b = 0.1199671308754309;
  v = 0.3591993279818963e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6656263089489130;
  b = 0.4015955957805969e-1;
  v = 0.3595855034661997e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld3470(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD3470 computes the 3470 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.2040382730826330e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.3178149703889544e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1721420832906233e-1;
  v = 0.8288115128076110e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4408875374981770e-1;
  v = 0.1360883192522954e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7594680813878681e-1;
  v = 0.1766854454542662e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1108335359204799;
  ;
  v = 0.2083153161230153e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1476517054388567;
  v = 0.2333279544657158e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1856731870860615;
  v = 0.2532809539930247e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2243634099428821;
  v = 0.2692472184211158e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2633006881662727;
  v = 0.2819949946811885e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3021340904916283;
  v = 0.2920953593973030e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3405594048030089;
  v = 0.2999889782948352e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3783044434007372;
  v = 0.3060292120496902e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4151194767407910;
  v = 0.3105109167522192e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4507705766443257;
  v = 0.3136902387550312e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4850346056573187;
  v = 0.3157984652454632e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5176950817792470;
  v = 0.3170516518425422e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5485384240820989;
  v = 0.3176568425633755e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6039117238943308;
  v = 0.3177198411207062e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6279956655573113;
  v = 0.3175519492394733e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6493636169568952;
  v = 0.3174654952634756e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6677644117704504;
  v = 0.3175676415467654e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6829368572115624;
  v = 0.3178923417835410e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6946195818184121;
  v = 0.3183788287531909e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7025711542057026;
  v = 0.3188755151918807e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7066004767140119;
  v = 0.3191916889313849e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5132537689946062e-1;
  v = 0.1231779611744508e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1297994661331225;
  v = 0.1924661373839880e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2188852049401307;
  v = 0.2380881867403424e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3123174824903457;
  v = 0.2693100663037885e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4064037620738195;
  v = 0.2908673382834366e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4984958396944782;
  v = 0.3053914619381535e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5864975046021365;
  v = 0.3143916684147777e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6686711634580175;
  v = 0.3187042244055363e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8715738780835950e-1;
  b = 0.2557175233367578e-1;
  v = 0.1635219535869790e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1248383123134007;
  b = 0.5604823383376681e-1;
  v = 0.1968109917696070e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1638062693383378;
  b = 0.8968568601900765e-1;
  v = 0.2236754342249974e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2035586203373176;
  b = 0.1254086651976279;
  v = 0.2453186687017181e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2436798975293774;
  b = 0.1624780150162012;
  v = 0.2627551791580541e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2838207507773806;
  b = 0.2003422342683208;
  v = 0.2767654860152220e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3236787502217692;
  b = 0.2385628026255263;
  v = 0.2879467027765895e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3629849554840691;
  b = 0.2767731148783578;
  v = 0.2967639918918702e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4014948081992087;
  b = 0.3146542308245309;
  v = 0.3035900684660351e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4389818379260225;
  b = 0.3519196415895088;
  v = 0.3087338237298308e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4752331143674377;
  b = 0.3883050984023654;
  v = 0.3124608838860167e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5100457318374018;
  b = 0.4235613423908649;
  v = 0.3150084294226743e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5432238388954868;
  b = 0.4574484717196220;
  v = 0.3165958398598402e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5745758685072442;
  b = 0.4897311639255524;
  v = 0.3174320440957372e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1723981437592809;
  b = 0.3010630597881105e-1;
  v = 0.2182188909812599e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2149553257844597;
  b = 0.6326031554204694e-1;
  v = 0.2399727933921445e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2573256081247422;
  b = 0.9848566980258631e-1;
  v = 0.2579796133514652e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2993163751238106;
  b = 0.1350835952384266;
  v = 0.2727114052623535e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3407238005148000;
  b = 0.1725184055442181;
  v = 0.2846327656281355e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3813454978483264;
  b = 0.2103559279730725;
  v = 0.2941491102051334e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4209848104423343;
  b = 0.2482278774554860;
  v = 0.3016049492136107e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4594519699996300;
  b = 0.2858099509982883;
  v = 0.3072949726175648e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4965640166185930;
  b = 0.3228075659915428;
  v = 0.3114768142886460e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5321441655571562;
  b = 0.3589459907204151;
  v = 0.3143823673666223e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5660208438582166;
  b = 0.3939630088864310;
  v = 0.3162269764661535e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5980264315964364;
  b = 0.4276029922949089;
  v = 0.3172164663759821e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2644215852350733;
  b = 0.3300939429072552e-1;
  v = 0.2554575398967435e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3090113743443063;
  b = 0.6803887650078501e-1;
  v = 0.2701704069135677e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3525871079197808;
  b = 0.1044326136206709;
  v = 0.2823693413468940e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3950418005354029;
  b = 0.1416751597517679;
  v = 0.2922898463214289e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4362475663430163;
  b = 0.1793408610504821;
  v = 0.3001829062162428e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4760661812145854;
  b = 0.2170630750175722;
  v = 0.3062890864542953e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5143551042512103;
  b = 0.2545145157815807;
  v = 0.3108328279264746e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5509709026935597;
  b = 0.2913940101706601;
  v = 0.3140243146201245e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5857711030329428;
  b = 0.3274169910910705;
  v = 0.3160638030977130e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6186149917404392;
  b = 0.3623081329317265;
  v = 0.3171462882206275e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3586894569557064;
  b = 0.3497354386450040e-1;
  v = 0.2812388416031796e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4035266610019441;
  b = 0.7129736739757095e-1;
  v = 0.2912137500288045e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4467775312332510;
  b = 0.1084758620193165;
  v = 0.2993241256502206e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4883638346608543;
  b = 0.1460915689241772;
  v = 0.3057101738983822e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5281908348434601;
  b = 0.1837790832369980;
  v = 0.3105319326251432e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5661542687149311;
  b = 0.2212075390874021;
  v = 0.3139565514428167e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6021450102031452;
  b = 0.2580682841160985;
  v = 0.3161543006806366e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6360520783610050;
  b = 0.2940656362094121;
  v = 0.3172985960613294e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4521611065087196;
  b = 0.3631055365867002e-1;
  v = 0.2989400336901431e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4959365651560963;
  b = 0.7348318468484350e-1;
  v = 0.3054555883947677e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5376815804038283;
  b = 0.1111087643812648;
  v = 0.3104764960807702e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5773314480243768;
  b = 0.1488226085145408;
  v = 0.3141015825977616e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6148113245575056;
  b = 0.1862892274135151;
  v = 0.3164520621159896e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6500407462842380;
  b = 0.2231909701714456;
  v = 0.3176652305912204e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5425151448707213;
  b = 0.3718201306118944e-1;
  v = 0.3105097161023939e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5841860556907931;
  b = 0.7483616335067346e-1;
  v = 0.3143014117890550e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6234632186851500;
  b = 0.1125990834266120;
  v = 0.3168172866287200e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6602934551848843;
  b = 0.1501303813157619;
  v = 0.3181401865570968e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6278573968375105;
  b = 0.3767559930245720e-1;
  v = 0.3170663659156037e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6665611711264577;
  b = 0.7548443301360158e-1;
  v = 0.3185447944625510e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld3890(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD3890 computes the 3890 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.1807395252196920e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.2848008782238827e-3;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.2836065837530581e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1587876419858352e-1;
  v = 0.7013149266673816e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4069193593751206e-1;
  v = 0.1162798021956766e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7025888115257997e-1;
  v = 0.1518728583972105e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1027495450028704;
  v = 0.1798796108216934e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1371457730893426;
  v = 0.2022593385972785e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1727758532671953;
  v = 0.2203093105575464e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2091492038929037;
  v = 0.2349294234299855e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2458813281751915;
  v = 0.2467682058747003e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2826545859450066;
  v = 0.2563092683572224e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3191957291799622;
  v = 0.2639253896763318e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3552621469299578;
  v = 0.2699137479265108e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3906329503406230;
  v = 0.2745196420166739e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4251028614093031;
  v = 0.2779529197397593e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4584777520111870;
  v = 0.2803996086684265e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4905711358710193;
  v = 0.2820302356715842e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5212011669847385;
  v = 0.2830056747491068e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5501878488737995;
  v = 0.2834808950776839e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6025037877479342;
  v = 0.2835282339078929e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6254572689549016;
  v = 0.2833819267065800e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6460107179528248;
  v = 0.2832858336906784e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6639541138154251;
  v = 0.2833268235451244e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6790688515667495;
  v = 0.2835432677029253e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6911338580371512;
  v = 0.2839091722743049e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6999385956126490;
  v = 0.2843308178875841e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7053037748656896;
  v = 0.2846703550533846e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4732224387180115e-1;
  v = 0.1051193406971900e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1202100529326803;
  v = 0.1657871838796974e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2034304820664855;
  v = 0.2064648113714232e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2912285643573002;
  v = 0.2347942745819741e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3802361792726768;
  v = 0.2547775326597726e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4680598511056146;
  v = 0.2686876684847025e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5528151052155599;
  v = 0.2778665755515867e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6329386307803041;
  v = 0.2830996616782929e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8056516651369069e-1;
  b = 0.2363454684003124e-1;
  v = 0.1403063340168372e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1156476077139389;
  b = 0.5191291632545936e-1;
  v = 0.1696504125939477e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1520473382760421;
  b = 0.8322715736994519e-1;
  v = 0.1935787242745390e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1892986699745931;
  b = 0.1165855667993712;
  v = 0.2130614510521968e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2270194446777792;
  b = 0.1513077167409504;
  v = 0.2289381265931048e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2648908185093273;
  b = 0.1868882025807859;
  v = 0.2418630292816186e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3026389259574136;
  b = 0.2229277629776224;
  v = 0.2523400495631193e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3400220296151384;
  b = 0.2590951840746235;
  v = 0.2607623973449605e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3768217953335510;
  b = 0.2951047291750847;
  v = 0.2674441032689209e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4128372900921884;
  b = 0.3307019714169930;
  v = 0.2726432360343356e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4478807131815630;
  b = 0.3656544101087634;
  v = 0.2765787685924545e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4817742034089257;
  b = 0.3997448951939695;
  v = 0.2794428690642224e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5143472814653344;
  b = 0.4327667110812024;
  v = 0.2814099002062895e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5454346213905650;
  b = 0.4645196123532293;
  v = 0.2826429531578994e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5748739313170252;
  b = 0.4948063555703345;
  v = 0.2832983542550884e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1599598738286342;
  b = 0.2792357590048985e-1;
  v = 0.1886695565284976e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1998097412500951;
  b = 0.5877141038139065e-1;
  v = 0.2081867882748234e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2396228952566202;
  b = 0.9164573914691377e-1;
  v = 0.2245148680600796e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2792228341097746;
  b = 0.1259049641962687;
  v = 0.2380370491511872e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3184251107546741;
  b = 0.1610594823400863;
  v = 0.2491398041852455e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3570481164426244;
  b = 0.1967151653460898;
  v = 0.2581632405881230e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3949164710492144;
  b = 0.2325404606175168;
  v = 0.2653965506227417e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4318617293970503;
  b = 0.2682461141151439;
  v = 0.2710857216747087e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4677221009931678;
  b = 0.3035720116011973;
  v = 0.2754434093903659e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5023417939270955;
  b = 0.3382781859197439;
  v = 0.2786579932519380e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5355701836636128;
  b = 0.3721383065625942;
  v = 0.2809011080679474e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5672608451328771;
  b = 0.4049346360466055;
  v = 0.2823336184560987e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5972704202540162;
  b = 0.4364538098633802;
  v = 0.2831101175806309e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2461687022333596;
  b = 0.3070423166833368e-1;
  v = 0.2221679970354546e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2881774566286831;
  b = 0.6338034669281885e-1;
  v = 0.2356185734270703e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3293963604116978;
  b = 0.9742862487067941e-1;
  v = 0.2469228344805590e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3697303822241377;
  b = 0.1323799532282290;
  v = 0.2562726348642046e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4090663023135127;
  b = 0.1678497018129336;
  v = 0.2638756726753028e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4472819355411712;
  b = 0.2035095105326114;
  v = 0.2699311157390862e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4842513377231437;
  b = 0.2390692566672091;
  v = 0.2746233268403837e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5198477629962928;
  b = 0.2742649818076149;
  v = 0.2781225674454771e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5539453011883145;
  b = 0.3088503806580094;
  v = 0.2805881254045684e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5864196762401251;
  b = 0.3425904245906614;
  v = 0.2821719877004913e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6171484466668390;
  b = 0.3752562294789468;
  v = 0.2830222502333124e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3350337830565727;
  b = 0.3261589934634747e-1;
  v = 0.2457995956744870e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3775773224758284;
  b = 0.6658438928081572e-1;
  v = 0.2551474407503706e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4188155229848973;
  b = 0.1014565797157954;
  v = 0.2629065335195311e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4586805892009344;
  b = 0.1368573320843822;
  v = 0.2691900449925075e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4970895714224235;
  b = 0.1724614851951608;
  v = 0.2741275485754276e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5339505133960747;
  b = 0.2079779381416412;
  v = 0.2778530970122595e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5691665792531440;
  b = 0.2431385788322288;
  v = 0.2805010567646741e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6026387682680377;
  b = 0.2776901883049853;
  v = 0.2822055834031040e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6342676150163307;
  b = 0.3113881356386632;
  v = 0.2831016901243473e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4237951119537067;
  b = 0.3394877848664351e-1;
  v = 0.2624474901131803e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4656918683234929;
  b = 0.6880219556291447e-1;
  v = 0.2688034163039377e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5058857069185980;
  b = 0.1041946859721635;
  v = 0.2738932751287636e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5443204666713996;
  b = 0.1398039738736393;
  v = 0.2777944791242523e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5809298813759742;
  b = 0.1753373381196155;
  v = 0.2806011661660987e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6156416039447128;
  b = 0.2105215793514010;
  v = 0.2824181456597460e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6483801351066604;
  b = 0.2450953312157051;
  v = 0.2833585216577828e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5103616577251688;
  b = 0.3485560643800719e-1;
  v = 0.2738165236962878e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5506738792580681;
  b = 0.7026308631512033e-1;
  v = 0.2778365208203180e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5889573040995292;
  b = 0.1059035061296403;
  v = 0.2807852940418966e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6251641589516930;
  b = 0.1414823925236026;
  v = 0.2827245949674705e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6592414921570178;
  b = 0.1767207908214530;
  v = 0.2837342344829828e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5930314017533384;
  b = 0.3542189339561672e-1;
  v = 0.2809233907610981e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6309812253390175;
  b = 0.7109574040369549e-1;
  v = 0.2829930809742694e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6666296011353230;
  b = 0.1067259792282730;
  v = 0.2841097874111479e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6703715271049922;
  b = 0.3569455268820809e-1;
  v = 0.2843455206008783e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld4334(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD4334 computes the 4334 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.1449063022537883e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.2546377329828424e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1462896151831013e-1;
  v = 0.6018432961087496e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3769840812493139e-1;
  v = 0.1002286583263673e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6524701904096891e-1;
  v = 0.1315222931028093e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9560543416134648e-1;
  v = 0.1564213746876724e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1278335898929198;
  v = 0.1765118841507736e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1613096104466031;
  v = 0.1928737099311080e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1955806225745371;
  v = 0.2062658534263270e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2302935218498028;
  v = 0.2172395445953787e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2651584344113027;
  v = 0.2262076188876047e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2999276825183209;
  v = 0.2334885699462397e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3343828669718798;
  v = 0.2393355273179203e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3683265013750518;
  v = 0.2439559200468863e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4015763206518108;
  v = 0.2475251866060002e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4339612026399770;
  v = 0.2501965558158773e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4653180651114582;
  v = 0.2521081407925925e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4954893331080803;
  v = 0.2533881002388081e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5243207068924930;
  v = 0.2541582900848261e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5516590479041704;
  v = 0.2545365737525860e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6012371927804176;
  v = 0.2545726993066799e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6231574466449819;
  v = 0.2544456197465555e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6429416514181271;
  v = 0.2543481596881064e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6604124272943595;
  v = 0.2543506451429194e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6753851470408250;
  v = 0.2544905675493763e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6876717970626160;
  v = 0.2547611407344429e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6970895061319234;
  v = 0.2551060375448869e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7034746912553310;
  v = 0.2554291933816039e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7067017217542295;
  v = 0.2556255710686343e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4382223501131123e-1;
  v = 0.9041339695118195e-4;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1117474077400006;
  v = 0.1438426330079022e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1897153252911440;
  v = 0.1802523089820518e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2724023009910331;
  v = 0.2060052290565496e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3567163308709902;
  v = 0.2245002248967466e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4404784483028087;
  v = 0.2377059847731150e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5219833154161411;
  v = 0.2468118955882525e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5998179868977553;
  v = 0.2525410872966528e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6727803154548222;
  v = 0.2553101409933397e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7476563943166086e-1;
  b = 0.2193168509461185e-1;
  v = 0.1212879733668632e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1075341482001416;
  b = 0.4826419281533887e-1;
  v = 0.1472872881270931e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1416344885203259;
  b = 0.7751191883575742e-1;
  v = 0.1686846601010828e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1766325315388586;
  b = 0.1087558139247680;
  v = 0.1862698414660208e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2121744174481514;
  b = 0.1413661374253096;
  v = 0.2007430956991861e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2479669443408145;
  b = 0.1748768214258880;
  v = 0.2126568125394796e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2837600452294113;
  b = 0.2089216406612073;
  v = 0.2224394603372113e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3193344933193984;
  b = 0.2431987685545972;
  v = 0.2304264522673135e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3544935442438745;
  b = 0.2774497054377770;
  v = 0.2368854288424087e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3890571932288154;
  b = 0.3114460356156915;
  v = 0.2420352089461772e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4228581214259090;
  b = 0.3449806851913012;
  v = 0.2460597113081295e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4557387211304052;
  b = 0.3778618641248256;
  v = 0.2491181912257687e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4875487950541643;
  b = 0.4099086391698978;
  v = 0.2513528194205857e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5181436529962997;
  b = 0.4409474925853973;
  v = 0.2528943096693220e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5473824095600661;
  b = 0.4708094517711291;
  v = 0.2538660368488136e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5751263398976174;
  b = 0.4993275140354637;
  v = 0.2543868648299022e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1489515746840028;
  b = 0.2599381993267017e-1;
  v = 0.1642595537825183e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1863656444351767;
  b = 0.5479286532462190e-1;
  v = 0.1818246659849308e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2238602880356348;
  b = 0.8556763251425254e-1;
  v = 0.1966565649492420e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2612723375728160;
  b = 0.1177257802267011;
  v = 0.2090677905657991e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2984332990206190;
  b = 0.1508168456192700;
  v = 0.2193820409510504e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3351786584663333;
  b = 0.1844801892177727;
  v = 0.2278870827661928e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3713505522209120;
  b = 0.2184145236087598;
  v = 0.2348283192282090e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4067981098954663;
  b = 0.2523590641486229;
  v = 0.2404139755581477e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4413769993687534;
  b = 0.2860812976901373;
  v = 0.2448227407760734e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4749487182516394;
  b = 0.3193686757808996;
  v = 0.2482110455592573e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5073798105075426;
  b = 0.3520226949547602;
  v = 0.2507192397774103e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5385410448878654;
  b = 0.3838544395667890;
  v = 0.2524765968534880e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5683065353670530;
  b = 0.4146810037640963;
  v = 0.2536052388539425e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5965527620663510;
  b = 0.4443224094681121;
  v = 0.2542230588033068e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2299227700856157;
  b = 0.2865757664057584e-1;
  v = 0.1944817013047896e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2695752998553267;
  b = 0.5923421684485993e-1;
  v = 0.2067862362746635e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3086178716611389;
  b = 0.9117817776057715e-1;
  v = 0.2172440734649114e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3469649871659077;
  b = 0.1240593814082605;
  v = 0.2260125991723423e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3845153566319655;
  b = 0.1575272058259175;
  v = 0.2332655008689523e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4211600033403215;
  b = 0.1912845163525413;
  v = 0.2391699681532458e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4567867834329882;
  b = 0.2250710177858171;
  v = 0.2438801528273928e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4912829319232061;
  b = 0.2586521303440910;
  v = 0.2475370504260665e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5245364793303812;
  b = 0.2918112242865407;
  v = 0.2502707235640574e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5564369788915756;
  b = 0.3243439239067890;
  v = 0.2522031701054241e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5868757697775287;
  b = 0.3560536787835351;
  v = 0.2534511269978784e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6157458853519617;
  b = 0.3867480821242581;
  v = 0.2541284914955151e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3138461110672113;
  b = 0.3051374637507278e-1;
  v = 0.2161509250688394e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3542495872050569;
  b = 0.6237111233730755e-1;
  v = 0.2248778513437852e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3935751553120181;
  b = 0.9516223952401907e-1;
  v = 0.2322388803404617e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4317634668111147;
  b = 0.1285467341508517;
  v = 0.2383265471001355e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4687413842250821;
  b = 0.1622318931656033;
  v = 0.2432476675019525e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5044274237060283;
  b = 0.1959581153836453;
  v = 0.2471122223750674e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5387354077925727;
  b = 0.2294888081183837;
  v = 0.2500291752486870e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5715768898356105;
  b = 0.2626031152713945;
  v = 0.2521055942764682e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6028627200136111;
  b = 0.2950904075286713;
  v = 0.2534472785575503e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6325039812653463;
  b = 0.3267458451113286;
  v = 0.2541599713080121e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3981986708423407;
  b = 0.3183291458749821e-1;
  v = 0.2317380975862936e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4382791182133300;
  b = 0.6459548193880908e-1;
  v = 0.2378550733719775e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4769233057218166;
  b = 0.9795757037087952e-1;
  v = 0.2428884456739118e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5140823911194238;
  b = 0.1316307235126655;
  v = 0.2469002655757292e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5496977833862983;
  b = 0.1653556486358704;
  v = 0.2499657574265851e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5837047306512727;
  b = 0.1988931724126510;
  v = 0.2521676168486082e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6160349566926879;
  b = 0.2320174581438950;
  v = 0.2535935662645334e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6466185353209440;
  b = 0.2645106562168662;
  v = 0.2543356743363214e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4810835158795404;
  b = 0.3275917807743992e-1;
  v = 0.2427353285201535e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5199925041324341;
  b = 0.6612546183967181e-1;
  v = 0.2468258039744386e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5571717692207494;
  b = 0.9981498331474143e-1;
  v = 0.2500060956440310e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5925789250836378;
  b = 0.1335687001410374;
  v = 0.2523238365420979e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6261658523859670;
  b = 0.1671444402896463;
  v = 0.2538399260252846e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6578811126669331;
  b = 0.2003106382156076;
  v = 0.2546255927268069e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5609624612998100;
  b = 0.3337500940231335e-1;
  v = 0.2500583360048449e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5979959659984670;
  b = 0.6708750335901803e-1;
  v = 0.2524777638260203e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6330523711054002;
  b = 0.1008792126424850;
  v = 0.2540951193860656e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6660960998103972;
  b = 0.1345050343171794;
  v = 0.2549524085027472e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6365384364585819;
  b = 0.3372799460737052e-1;
  v = 0.2542569507009158e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6710994302899275;
  b = 0.6755249309678028e-1;
  v = 0.2552114127580376e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld4802(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD4802 computes the 4802 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.9687521879420705e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.2307897895367918e-3;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.2297310852498558e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2335728608887064e-1;
  v = 0.7386265944001919e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4352987836550653e-1;
  v = 0.8257977698542210e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6439200521088801e-1;
  v = 0.9706044762057630e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9003943631993181e-1;
  v = 0.1302393847117003e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1196706615548473;
  v = 0.1541957004600968e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1511715412838134;
  v = 0.1704459770092199e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1835982828503801;
  v = 0.1827374890942906e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2165081259155405;
  v = 0.1926360817436107e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2496208720417563;
  v = 0.2008010239494833e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2827200673567900;
  v = 0.2075635983209175e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3156190823994346;
  v = 0.2131306638690909e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3481476793749115;
  v = 0.2176562329937335e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3801466086947226;
  v = 0.2212682262991018e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4114652119634011;
  v = 0.2240799515668565e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4419598786519751;
  v = 0.2261959816187525e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4714925949329543;
  v = 0.2277156368808855e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4999293972879466;
  v = 0.2287351772128336e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5271387221431248;
  v = 0.2293490814084085e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5529896780837761;
  v = 0.2296505312376273e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6000856099481712;
  v = 0.2296793832318756e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6210562192785175;
  v = 0.2295785443842974e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6401165879934240;
  v = 0.2295017931529102e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6571144029244334;
  v = 0.2295059638184868e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6718910821718863;
  v = 0.2296232343237362e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6842845591099010;
  v = 0.2298530178740771e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6941353476269816;
  v = 0.2301579790280501e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7012965242212991;
  v = 0.2304690404996513e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7056471428242644;
  v = 0.2307027995907102e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4595557643585895e-1;
  v = 0.9312274696671092e-4;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1049316742435023;
  v = 0.1199919385876926e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1773548879549274;
  v = 0.1598039138877690e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2559071411236127;
  v = 0.1822253763574900e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3358156837985898;
  v = 0.1988579593655040e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4155835743763893;
  v = 0.2112620102533307e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4937894296167472;
  v = 0.2201594887699007e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5691569694793316;
  v = 0.2261622590895036e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6405840854894251;
  v = 0.2296458453435705e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7345133894143348e-1;
  b = 0.2177844081486067e-1;
  v = 0.1006006990267000e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1009859834044931;
  b = 0.4590362185775188e-1;
  v = 0.1227676689635876e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1324289619748758;
  b = 0.7255063095690877e-1;
  v = 0.1467864280270117e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1654272109607127;
  b = 0.1017825451960684;
  v = 0.1644178912101232e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1990767186776461;
  b = 0.1325652320980364;
  v = 0.1777664890718961e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2330125945523278;
  b = 0.1642765374496765;
  v = 0.1884825664516690e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2670080611108287;
  b = 0.1965360374337889;
  v = 0.1973269246453848e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3008753376294316;
  b = 0.2290726770542238;
  v = 0.2046767775855328e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3344475596167860;
  b = 0.2616645495370823;
  v = 0.2107600125918040e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3675709724070786;
  b = 0.2941150728843141;
  v = 0.2157416362266829e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4001000887587812;
  b = 0.3262440400919066;
  v = 0.2197557816920721e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4318956350436028;
  b = 0.3578835350611916;
  v = 0.2229192611835437e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4628239056795531;
  b = 0.3888751854043678;
  v = 0.2253385110212775e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4927563229773636;
  b = 0.4190678003222840;
  v = 0.2271137107548774e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5215687136707969;
  b = 0.4483151836883852;
  v = 0.2283414092917525e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5491402346984905;
  b = 0.4764740676087880;
  v = 0.2291161673130077e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5753520160126075;
  b = 0.5034021310998277;
  v = 0.2295313908576598e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1388326356417754;
  b = 0.2435436510372806e-1;
  v = 0.1438204721359031e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1743686900537244;
  b = 0.5118897057342652e-1;
  v = 0.1607738025495257e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2099737037950268;
  b = 0.8014695048539634e-1;
  v = 0.1741483853528379e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2454492590908548;
  b = 0.1105117874155699;
  v = 0.1851918467519151e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2807219257864278;
  b = 0.1417950531570966;
  v = 0.1944628638070613e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3156842271975842;
  b = 0.1736604945719597;
  v = 0.2022495446275152e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3502090945177752;
  b = 0.2058466324693981;
  v = 0.2087462382438514e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3841684849519686;
  b = 0.2381284261195919;
  v = 0.2141074754818308e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4174372367906016;
  b = 0.2703031270422569;
  v = 0.2184640913748162e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4498926465011892;
  b = 0.3021845683091309;
  v = 0.2219309165220329e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4814146229807701;
  b = 0.3335993355165720;
  v = 0.2246123118340624e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5118863625734701;
  b = 0.3643833735518232;
  v = 0.2266062766915125e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5411947455119144;
  b = 0.3943789541958179;
  v = 0.2280072952230796e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5692301500357246;
  b = 0.4234320144403542;
  v = 0.2289082025202583e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5958857204139576;
  b = 0.4513897947419260;
  v = 0.2294012695120025e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2156270284785766;
  b = 0.2681225755444491e-1;
  v = 0.1722434488736947e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2532385054909710;
  b = 0.5557495747805614e-1;
  v = 0.1830237421455091e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2902564617771537;
  b = 0.8569368062950249e-1;
  v = 0.1923855349997633e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3266979823143256;
  b = 0.1167367450324135;
  v = 0.2004067861936271e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3625039627493614;
  b = 0.1483861994003304;
  v = 0.2071817297354263e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3975838937548699;
  b = 0.1803821503011405;
  v = 0.2128250834102103e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4318396099009774;
  b = 0.2124962965666424;
  v = 0.2174513719440102e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4651706555732742;
  b = 0.2445221837805913;
  v = 0.2211661839150214e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4974752649620969;
  b = 0.2762701224322987;
  v = 0.2240665257813102e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5286517579627517;
  b = 0.3075627775211328;
  v = 0.2262439516632620e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5586001195731895;
  b = 0.3382311089826877;
  v = 0.2277874557231869e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5872229902021319;
  b = 0.3681108834741399;
  v = 0.2287854314454994e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6144258616235123;
  b = 0.3970397446872839;
  v = 0.2293268499615575e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2951676508064861;
  b = 0.2867499538750441e-1;
  v = 0.1912628201529828e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3335085485472725;
  b = 0.5867879341903510e-1;
  v = 0.1992499672238701e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3709561760636381;
  b = 0.8961099205022284e-1;
  v = 0.2061275533454027e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4074722861667498;
  b = 0.1211627927626297;
  v = 0.2119318215968572e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4429923648839117;
  b = 0.1530748903554898;
  v = 0.2167416581882652e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4774428052721736;
  b = 0.1851176436721877;
  v = 0.2206430730516600e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5107446539535904;
  b = 0.2170829107658179;
  v = 0.2237186938699523e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5428151370542935;
  b = 0.2487786689026271;
  v = 0.2260480075032884e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5735699292556964;
  b = 0.2800239952795016;
  v = 0.2277098884558542e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6029253794562866;
  b = 0.3106445702878119;
  v = 0.2287845715109671e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6307998987073145;
  b = 0.3404689500841194;
  v = 0.2293547268236294e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3752652273692719;
  b = 0.2997145098184479e-1;
  v = 0.2056073839852528e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4135383879344028;
  b = 0.6086725898678011e-1;
  v = 0.2114235865831876e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4506113885153907;
  b = 0.9238849548435643e-1;
  v = 0.2163175629770551e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4864401554606072;
  b = 0.1242786603851851;
  v = 0.2203392158111650e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5209708076611709;
  b = 0.1563086731483386;
  v = 0.2235473176847839e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5541422135830122;
  b = 0.1882696509388506;
  v = 0.2260024141501235e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5858880915113817;
  b = 0.2199672979126059;
  v = 0.2277675929329182e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6161399390603444;
  b = 0.2512165482924867;
  v = 0.2289102112284834e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6448296482255090;
  b = 0.2818368701871888;
  v = 0.2295027954625118e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4544796274917948;
  b = 0.3088970405060312e-1;
  v = 0.2161281589879992e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4919389072146628;
  b = 0.6240947677636835e-1;
  v = 0.2201980477395102e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5279313026985183;
  b = 0.9430706144280313e-1;
  v = 0.2234952066593166e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5624169925571135;
  b = 0.1263547818770374;
  v = 0.2260540098520838e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5953484627093287;
  b = 0.1583430788822594;
  v = 0.2279157981899988e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6266730715339185;
  b = 0.1900748462555988;
  v = 0.2291296918565571e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6563363204278871;
  b = 0.2213599519592567;
  v = 0.2297533752536649e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5314574716585696;
  b = 0.3152508811515374e-1;
  v = 0.2234927356465995e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5674614932298185;
  b = 0.6343865291465561e-1;
  v = 0.2261288012985219e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6017706004970264;
  b = 0.9551503504223951e-1;
  v = 0.2280818160923688e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6343471270264178;
  b = 0.1275440099801196;
  v = 0.2293773295180159e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6651494599127802;
  b = 0.1593252037671960;
  v = 0.2300528767338634e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6050184986005704;
  b = 0.3192538338496105e-1;
  v = 0.2281893855065666e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6390163550880400;
  b = 0.6402824353962306e-1;
  v = 0.2295720444840727e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6711199107088448;
  b = 0.9609805077002909e-1;
  v = 0.2303227649026753e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6741354429572275;
  b = 0.3211853196273233e-1;
  v = 0.2304831913227114e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld5294(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD5294 computes the 5294 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.9080510764308163e-4;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.2084824361987793e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2303261686261450e-1;
  v = 0.5011105657239616e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3757208620162394e-1;
  v = 0.5942520409683854e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5821912033821852e-1;
  v = 0.9564394826109721e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8403127529194872e-1;
  v = 0.1185530657126338e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1122927798060578;
  v = 0.1364510114230331e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1420125319192987;
  v = 0.1505828825605415e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1726396437341978;
  v = 0.1619298749867023e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2038170058115696;
  v = 0.1712450504267789e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2352849892876508;
  v = 0.1789891098164999e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2668363354312461;
  v = 0.1854474955629795e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2982941279900452;
  v = 0.1908148636673661e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3295002922087076;
  v = 0.1952377405281833e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3603094918363593;
  v = 0.1988349254282232e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3905857895173920;
  v = 0.2017079807160050e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4202005758160837;
  v = 0.2039473082709094e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4490310061597227;
  v = 0.2056360279288953e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4769586160311491;
  v = 0.2068525823066865e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5038679887049750;
  v = 0.2076724877534488e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5296454286519961;
  v = 0.2081694278237885e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5541776207164850;
  v = 0.2084157631219326e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5990467321921213;
  v = 0.2084381531128593e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6191467096294587;
  v = 0.2083476277129307e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6375251212901849;
  v = 0.2082686194459732e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6540514381131168;
  v = 0.2082475686112415e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6685899064391510;
  v = 0.2083139860289915e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6810013009681648;
  v = 0.2084745561831237e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6911469578730340;
  v = 0.2087091313375890e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6988956915141736;
  v = 0.2089718413297697e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7041335794868720;
  v = 0.2092003303479793e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7067754398018567;
  v = 0.2093336148263241e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3840368707853623e-1;
  v = 0.7591708117365267e-4;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9835485954117399e-1;
  v = 0.1083383968169186e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1665774947612998;
  v = 0.1403019395292510e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2405702335362910;
  v = 0.1615970179286436e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3165270770189046;
  v = 0.1771144187504911e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3927386145645443;
  v = 0.1887760022988168e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4678825918374656;
  v = 0.1973474670768214e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5408022024266935;
  v = 0.2033787661234659e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6104967445752438;
  v = 0.2072343626517331e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6760910702685738;
  v = 0.2091177834226918e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6655644120217392e-1;
  b = 0.1936508874588424e-1;
  v = 0.9316684484675566e-4;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9446246161270182e-1;
  b = 0.4252442002115869e-1;
  v = 0.1116193688682976e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1242651925452509;
  b = 0.6806529315354374e-1;
  v = 0.1298623551559414e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1553438064846751;
  b = 0.9560957491205369e-1;
  v = 0.1450236832456426e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1871137110542670;
  b = 0.1245931657452888;
  v = 0.1572719958149914e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2192612628836257;
  b = 0.1545385828778978;
  v = 0.1673234785867195e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2515682807206955;
  b = 0.1851004249723368;
  v = 0.1756860118725188e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2838535866287290;
  b = 0.2160182608272384;
  v = 0.1826776290439367e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3159578817528521;
  b = 0.2470799012277111;
  v = 0.1885116347992865e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3477370882791392;
  b = 0.2781014208986402;
  v = 0.1933457860170574e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3790576960890540;
  b = 0.3089172523515731;
  v = 0.1973060671902064e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4097938317810200;
  b = 0.3393750055472244;
  v = 0.2004987099616311e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4398256572859637;
  b = 0.3693322470987730;
  v = 0.2030170909281499e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4690384114718480;
  b = 0.3986541005609877;
  v = 0.2049461460119080e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4973216048301053;
  b = 0.4272112491408562;
  v = 0.2063653565200186e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5245681526132446;
  b = 0.4548781735309936;
  v = 0.2073507927381027e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5506733911803888;
  b = 0.4815315355023251;
  v = 0.2079764593256122e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5755339829522475;
  b = 0.5070486445801855;
  v = 0.2083150534968778e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1305472386056362;
  b = 0.2284970375722366e-1;
  v = 0.1262715121590664e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1637327908216477;
  b = 0.4812254338288384e-1;
  v = 0.1414386128545972e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1972734634149637;
  b = 0.7531734457511935e-1;
  v = 0.1538740401313898e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2308694653110130;
  b = 0.1039043639882017;
  v = 0.1642434942331432e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2643899218338160;
  b = 0.1334526587117626;
  v = 0.1729790609237496e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2977171599622171;
  b = 0.1636414868936382;
  v = 0.1803505190260828e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3307293903032310;
  b = 0.1942195406166568;
  v = 0.1865475350079657e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3633069198219073;
  b = 0.2249752879943753;
  v = 0.1917182669679069e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3953346955922727;
  b = 0.2557218821820032;
  v = 0.1959851709034382e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4267018394184914;
  b = 0.2862897925213193;
  v = 0.1994529548117882e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4573009622571704;
  b = 0.3165224536636518;
  v = 0.2022138911146548e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4870279559856109;
  b = 0.3462730221636496;
  v = 0.2043518024208592e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5157819581450322;
  b = 0.3754016870282835;
  v = 0.2059450313018110e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5434651666465393;
  b = 0.4037733784993613;
  v = 0.2070685715318472e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5699823887764627;
  b = 0.4312557784139123;
  v = 0.2077955310694373e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5952403350947741;
  b = 0.4577175367122110;
  v = 0.2081980387824712e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2025152599210369;
  b = 0.2520253617719557e-1;
  v = 0.1521318610377956e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2381066653274425;
  b = 0.5223254506119000e-1;
  v = 0.1622772720185755e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2732823383651612;
  b = 0.8060669688588620e-1;
  v = 0.1710498139420709e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3080137692611118;
  b = 0.1099335754081255;
  v = 0.1785911149448736e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3422405614587601;
  b = 0.1399120955959857;
  v = 0.1850125313687736e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3758808773890420;
  b = 0.1702977801651705;
  v = 0.1904229703933298e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4088458383438932;
  b = 0.2008799256601680;
  v = 0.1949259956121987e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4410450550841152;
  b = 0.2314703052180836;
  v = 0.1986161545363960e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4723879420561312;
  b = 0.2618972111375892;
  v = 0.2015790585641370e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5027843561874343;
  b = 0.2920013195600270;
  v = 0.2038934198707418e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5321453674452458;
  b = 0.3216322555190551;
  v = 0.2056334060538251e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5603839113834030;
  b = 0.3506456615934198;
  v = 0.2068705959462289e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5874150706875146;
  b = 0.3789007181306267;
  v = 0.2076753906106002e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6131559381660038;
  b = 0.4062580170572782;
  v = 0.2081179391734803e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2778497016394506;
  b = 0.2696271276876226e-1;
  v = 0.1700345216228943e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3143733562261912;
  b = 0.5523469316960465e-1;
  v = 0.1774906779990410e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3501485810261827;
  b = 0.8445193201626464e-1;
  v = 0.1839659377002642e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3851430322303653;
  b = 0.1143263119336083;
  v = 0.1894987462975169e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4193013979470415;
  b = 0.1446177898344475;
  v = 0.1941548809452595e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4525585960458567;
  b = 0.1751165438438091;
  v = 0.1980078427252384e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4848447779622947;
  b = 0.2056338306745660;
  v = 0.2011296284744488e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5160871208276894;
  b = 0.2359965487229226;
  v = 0.2035888456966776e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5462112185696926;
  b = 0.2660430223139146;
  v = 0.2054516325352142e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5751425068101757;
  b = 0.2956193664498032;
  v = 0.2067831033092635e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6028073872853596;
  b = 0.3245763905312779;
  v = 0.2076485320284876e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6291338275278409;
  b = 0.3527670026206972;
  v = 0.2081141439525255e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3541797528439391;
  b = 0.2823853479435550e-1;
  v = 0.1834383015469222e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3908234972074657;
  b = 0.5741296374713106e-1;
  v = 0.1889540591777677e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4264408450107590;
  b = 0.8724646633650199e-1;
  v = 0.1936677023597375e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4609949666553286;
  b = 0.1175034422915616;
  v = 0.1976176495066504e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4944389496536006;
  b = 0.1479755652628428;
  v = 0.2008536004560983e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5267194884346086;
  b = 0.1784740659484352;
  v = 0.2034280351712291e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5577787810220990;
  b = 0.2088245700431244;
  v = 0.2053944466027758e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5875563763536670;
  b = 0.2388628136570763;
  v = 0.2068077642882360e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6159910016391269;
  b = 0.2684308928769185;
  v = 0.2077250949661599e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6430219602956268;
  b = 0.2973740761960252;
  v = 0.2082062440705320e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4300647036213646;
  b = 0.2916399920493977e-1;
  v = 0.1934374486546626e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4661486308935531;
  b = 0.5898803024755659e-1;
  v = 0.1974107010484300e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5009658555287261;
  b = 0.8924162698525409e-1;
  v = 0.2007129290388658e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5344824270447704;
  b = 0.1197185199637321;
  v = 0.2033736947471293e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5666575997416371;
  b = 0.1502300756161382;
  v = 0.2054287125902493e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5974457471404752;
  b = 0.1806004191913564;
  v = 0.2069184936818894e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6267984444116886;
  b = 0.2106621764786252;
  v = 0.2078883689808782e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6546664713575417;
  b = 0.2402526932671914;
  v = 0.2083886366116359e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5042711004437253;
  b = 0.2982529203607657e-1;
  v = 0.2006593275470817e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5392127456774380;
  b = 0.6008728062339922e-1;
  v = 0.2033728426135397e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5726819437668618;
  b = 0.9058227674571398e-1;
  v = 0.2055008781377608e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6046469254207278;
  b = 0.1211219235803400;
  v = 0.2070651783518502e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6350716157434952;
  b = 0.1515286404791580;
  v = 0.2080953335094320e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6639177679185454;
  b = 0.1816314681255552;
  v = 0.2086284998988521e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5757276040972253;
  b = 0.3026991752575440e-1;
  v = 0.2055549387644668e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6090265823139755;
  b = 0.6078402297870770e-1;
  v = 0.2071871850267654e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6406735344387661;
  b = 0.9135459984176636e-1;
  v = 0.2082856600431965e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6706397927793709;
  b = 0.1218024155966590;
  v = 0.2088705858819358e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6435019674426665;
  b = 0.3052608357660639e-1;
  v = 0.2083995867536322e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6747218676375681;
  b = 0.6112185773983089e-1;
  v = 0.2090509712889637e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int ld5810(double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD5810 computes the 5810 point Lebedev angular grid.
//
//  Modified:
//
//    12 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Output, double X[N], Y[N], Z[N], W[N], the coordinates
//    and weights of the points.
//
{
  double a = 0.0;
  double b = 0.0;
  double v;
  int n = 0;

  v = 0.9735347946175486e-5;
  n = n + gen_oh(1, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.1907581241803167e-3;
  n = n + gen_oh(2, a, b, v, x + n, y + n, z + n, w + n);
  v = 0.1901059546737578e-3;
  n = n + gen_oh(3, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1182361662400277e-1;
  v = 0.3926424538919212e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3062145009138958e-1;
  v = 0.6667905467294382e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5329794036834243e-1;
  v = 0.8868891315019135e-4;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7848165532862220e-1;
  v = 0.1066306000958872e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1054038157636201;
  v = 0.1214506743336128e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1335577797766211;
  v = 0.1338054681640871e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1625769955502252;
  v = 0.1441677023628504e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1921787193412792;
  v = 0.1528880200826557e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2221340534690548;
  v = 0.1602330623773609e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2522504912791132;
  v = 0.1664102653445244e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2823610860679697;
  v = 0.1715845854011323e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3123173966267560;
  v = 0.1758901000133069e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3419847036953789;
  v = 0.1794382485256736e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3712386456999758;
  v = 0.1823238106757407e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3999627649876828;
  v = 0.1846293252959976e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4280466458648093;
  v = 0.1864284079323098e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4553844360185711;
  v = 0.1877882694626914e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4818736094437834;
  v = 0.1887716321852025e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5074138709260629;
  v = 0.1894381638175673e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5319061304570707;
  v = 0.1898454899533629e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5552514978677286;
  v = 0.1900497929577815e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5981009025246183;
  v = 0.1900671501924092e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6173990192228116;
  v = 0.1899837555533510e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6351365239411131;
  v = 0.1899014113156229e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6512010228227200;
  v = 0.1898581257705106e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6654758363948120;
  v = 0.1898804756095753e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6778410414853370;
  v = 0.1899793610426402e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6881760887484110;
  v = 0.1901464554844117e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6963645267094598;
  v = 0.1903533246259542e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7023010617153579;
  v = 0.1905556158463228e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.7059004636628753;
  v = 0.1907037155663528e-3;
  n = n + gen_oh(4, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3552470312472575e-1;
  v = 0.5992997844249967e-4;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.9151176620841283e-1;
  v = 0.9749059382456978e-4;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1566197930068980;
  v = 0.1241680804599158e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2265467599271907;
  v = 0.1437626154299360e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2988242318581361;
  v = 0.1584200054793902e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3717482419703886;
  v = 0.1694436550982744e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4440094491758889;
  v = 0.1776617014018108e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5145337096756642;
  v = 0.1836132434440077e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5824053672860230;
  v = 0.1876494727075983e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6468283961043370;
  v = 0.1899906535336482e-3;
  n = n + gen_oh(5, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6095964259104373e-1;
  b = 0.1787828275342931e-1;
  v = 0.8143252820767350e-4;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.8811962270959388e-1;
  b = 0.3953888740792096e-1;
  v = 0.9998859890887728e-4;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1165936722428831;
  b = 0.6378121797722990e-1;
  v = 0.1156199403068359e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1460232857031785;
  b = 0.8985890813745037e-1;
  v = 0.1287632092635513e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1761197110181755;
  b = 0.1172606510576162;
  v = 0.1398378643365139e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2066471190463718;
  b = 0.1456102876970995;
  v = 0.1491876468417391e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2374076026328152;
  b = 0.1746153823011775;
  v = 0.1570855679175456e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2682305474337051;
  b = 0.2040383070295584;
  v = 0.1637483948103775e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2989653312142369;
  b = 0.2336788634003698;
  v = 0.1693500566632843e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3294762752772209;
  b = 0.2633632752654219;
  v = 0.1740322769393633e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3596390887276086;
  b = 0.2929369098051601;
  v = 0.1779126637278296e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3893383046398812;
  b = 0.3222592785275512;
  v = 0.1810908108835412e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4184653789358347;
  b = 0.3512004791195743;
  v = 0.1836529132600190e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4469172319076166;
  b = 0.3796385677684537;
  v = 0.1856752841777379e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4745950813276976;
  b = 0.4074575378263879;
  v = 0.1872270566606832e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5014034601410262;
  b = 0.4345456906027828;
  v = 0.1883722645591307e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5272493404551239;
  b = 0.4607942515205134;
  v = 0.1891714324525297e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5520413051846366;
  b = 0.4860961284181720;
  v = 0.1896827480450146e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5756887237503077;
  b = 0.5103447395342790;
  v = 0.1899628417059528e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1225039430588352;
  b = 0.2136455922655793e-1;
  v = 0.1123301829001669e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1539113217321372;
  b = 0.4520926166137188e-1;
  v = 0.1253698826711277e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1856213098637712;
  b = 0.7086468177864818e-1;
  v = 0.1366266117678531e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2174998728035131;
  b = 0.9785239488772918e-1;
  v = 0.1462736856106918e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2494128336938330;
  b = 0.1258106396267210;
  v = 0.1545076466685412e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2812321562143480;
  b = 0.1544529125047001;
  v = 0.1615096280814007e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3128372276456111;
  b = 0.1835433512202753;
  v = 0.1674366639741759e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3441145160177973;
  b = 0.2128813258619585;
  v = 0.1724225002437900e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3749567714853510;
  b = 0.2422913734880829;
  v = 0.1765810822987288e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4052621732015610;
  b = 0.2716163748391453;
  v = 0.1800104126010751e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4349335453522385;
  b = 0.3007127671240280;
  v = 0.1827960437331284e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4638776641524965;
  b = 0.3294470677216479;
  v = 0.1850140300716308e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4920046410462687;
  b = 0.3576932543699155;
  v = 0.1867333507394938e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5192273554861704;
  b = 0.3853307059757764;
  v = 0.1880178688638289e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5454609081136522;
  b = 0.4122425044452694;
  v = 0.1889278925654758e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5706220661424140;
  b = 0.4383139587781027;
  v = 0.1895213832507346e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5946286755181518;
  b = 0.4634312536300553;
  v = 0.1898548277397420e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.1905370790924295;
  b = 0.2371311537781979e-1;
  v = 0.1349105935937341e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2242518717748009;
  b = 0.4917878059254806e-1;
  v = 0.1444060068369326e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2577190808025936;
  b = 0.7595498960495142e-1;
  v = 0.1526797390930008e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2908724534927187;
  b = 0.1036991083191100;
  v = 0.1598208771406474e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3236354020056219;
  b = 0.1321348584450234;
  v = 0.1659354368615331e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3559267359304543;
  b = 0.1610316571314789;
  v = 0.1711279910946440e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3876637123676956;
  b = 0.1901912080395707;
  v = 0.1754952725601440e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4187636705218842;
  b = 0.2194384950137950;
  v = 0.1791247850802529e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4491449019883107;
  b = 0.2486155334763858;
  v = 0.1820954300877716e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4787270932425445;
  b = 0.2775768931812335;
  v = 0.1844788524548449e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5074315153055574;
  b = 0.3061863786591120;
  v = 0.1863409481706220e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5351810507738336;
  b = 0.3343144718152556;
  v = 0.1877433008795068e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5619001025975381;
  b = 0.3618362729028427;
  v = 0.1887444543705232e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5875144035268046;
  b = 0.3886297583620408;
  v = 0.1894009829375006e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6119507308734495;
  b = 0.4145742277792031;
  v = 0.1897683345035198e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2619733870119463;
  b = 0.2540047186389353e-1;
  v = 0.1517327037467653e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.2968149743237949;
  b = 0.5208107018543989e-1;
  v = 0.1587740557483543e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3310451504860488;
  b = 0.7971828470885599e-1;
  v = 0.1649093382274097e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3646215567376676;
  b = 0.1080465999177927;
  v = 0.1701915216193265e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3974916785279360;
  b = 0.1368413849366629;
  v = 0.1746847753144065e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4295967403772029;
  b = 0.1659073184763559;
  v = 0.1784555512007570e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4608742854473447;
  b = 0.1950703730454614;
  v = 0.1815687562112174e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4912598858949903;
  b = 0.2241721144376724;
  v = 0.1840864370663302e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5206882758945558;
  b = 0.2530655255406489;
  v = 0.1860676785390006e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5490940914019819;
  b = 0.2816118409731066;
  v = 0.1875690583743703e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5764123302025542;
  b = 0.3096780504593238;
  v = 0.1886453236347225e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6025786004213506;
  b = 0.3371348366394987;
  v = 0.1893501123329645e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6275291964794956;
  b = 0.3638547827694396;
  v = 0.1897366184519868e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3348189479861771;
  b = 0.2664841935537443e-1;
  v = 0.1643908815152736e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.3699515545855295;
  b = 0.5424000066843495e-1;
  v = 0.1696300350907768e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4042003071474669;
  b = 0.8251992715430854e-1;
  v = 0.1741553103844483e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4375320100182624;
  b = 0.1112695182483710;
  v = 0.1780015282386092e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4699054490335947;
  b = 0.1402964116467816;
  v = 0.1812116787077125e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5012739879431952;
  b = 0.1694275117584291;
  v = 0.1838323158085421e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5315874883754966;
  b = 0.1985038235312689;
  v = 0.1859113119837737e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5607937109622117;
  b = 0.2273765660020893;
  v = 0.1874969220221698e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5888393223495521;
  b = 0.2559041492849764;
  v = 0.1886375612681076e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6156705979160163;
  b = 0.2839497251976899;
  v = 0.1893819575809276e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6412338809078123;
  b = 0.3113791060500690;
  v = 0.1897794748256767e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4076051259257167;
  b = 0.2757792290858463e-1;
  v = 0.1738963926584846e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4423788125791520;
  b = 0.5584136834984293e-1;
  v = 0.1777442359873466e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4760480917328258;
  b = 0.8457772087727143e-1;
  v = 0.1810010815068719e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5085838725946297;
  b = 0.1135975846359248;
  v = 0.1836920318248129e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5399513637391218;
  b = 0.1427286904765053;
  v = 0.1858489473214328e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5701118433636380;
  b = 0.1718112740057635;
  v = 0.1875079342496592e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5990240530606021;
  b = 0.2006944855985351;
  v = 0.1887080239102310e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6266452685139695;
  b = 0.2292335090598907;
  v = 0.1894905752176822e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6529320971415942;
  b = 0.2572871512353714;
  v = 0.1898991061200695e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.4791583834610126;
  b = 0.2826094197735932e-1;
  v = 0.1809065016458791e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5130373952796940;
  b = 0.5699871359683649e-1;
  v = 0.1836297121596799e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5456252429628476;
  b = 0.8602712528554394e-1;
  v = 0.1858426916241869e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5768956329682385;
  b = 0.1151748137221281;
  v = 0.1875654101134641e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6068186944699046;
  b = 0.1442811654136362;
  v = 0.1888240751833503e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6353622248024907;
  b = 0.1731930321657680;
  v = 0.1896497383866979e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6624927035731797;
  b = 0.2017619958756061;
  v = 0.1900775530219121e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5484933508028488;
  b = 0.2874219755907391e-1;
  v = 0.1858525041478814e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.5810207682142106;
  b = 0.5778312123713695e-1;
  v = 0.1876248690077947e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6120955197181352;
  b = 0.8695262371439526e-1;
  v = 0.1889404439064607e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6416944284294319;
  b = 0.1160893767057166;
  v = 0.1898168539265290e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6697926391731260;
  b = 0.1450378826743251;
  v = 0.1902779940661772e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6147594390585488;
  b = 0.2904957622341456e-1;
  v = 0.1890125641731815e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6455390026356783;
  b = 0.5823809152617197e-1;
  v = 0.1899434637795751e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6747258588365477;
  b = 0.8740384899884715e-1;
  v = 0.1904520856831751e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);
  a = 0.6772135750395347;
  b = 0.2919946135808105e-1;
  v = 0.1905534498734563e-3;
  n = n + gen_oh(6, a, b, v, x + n, y + n, z + n, w + n);

  return n;
}
//****************************************************************************80

int leb_order_routing(int order, double *x, double *y, double *z, double *w)

//****************************************************************************80
//
//  Purpose:
//
//    LD_ORDER_ROUTING returns a Lebedev angular grid given its order.
//
//  Discussion:
//
//    Only a certain set of such rules are available through this function.
//
//  Modified:
//
//    13 September 2010
//
//  Author:
//
//    Dmitri Laikov
//
//  Reference:
//
//    Vyacheslav Lebedev, Dmitri Laikov,
//    A quadrature formula for the sphere of the 131st
//    algebraic order of accuracy,
//    Russian Academy of Sciences Doklady Mathematics,
//    Volume 59, Number 3, 1999, pages 477-481.
//
//  Parameters:
//
//    Input, int ORDER, the order of the rule.
//
//    Output, double X[ORDER], Y[ORDER], Z[ORDER], W[ORDER], the coordinates
//    and weights of the points.
//
{
  int n = 0;

  if (order == 6) {
    n = ld0006(x, y, z, w);
  } else if (order == 14) {
    n = ld0014(x, y, z, w);
  } else if (order == 26) {
    n = ld0026(x, y, z, w);
  } else if (order == 38) {
    n = ld0038(x, y, z, w);
  } else if (order == 50) {
    n = ld0050(x, y, z, w);
  } else if (order == 74) {
    n = ld0074(x, y, z, w);
  } else if (order == 86) {
    n = ld0086(x, y, z, w);
  } else if (order == 110) {
    n = ld0110(x, y, z, w);
  } else if (order == 146) {
    n = ld0146(x, y, z, w);
  } else if (order == 170) {
    n = ld0170(x, y, z, w);
  } else if (order == 194) {
    n = ld0194(x, y, z, w);
  } else if (order == 230) {
    n = ld0230(x, y, z, w);
  } else if (order == 266) {
    n = ld0266(x, y, z, w);
  } else if (order == 302) {
    n = ld0302(x, y, z, w);
  } else if (order == 350) {
    n = ld0350(x, y, z, w);
  } else if (order == 434) {
    n = ld0434(x, y, z, w);
  } else if (order == 590) {
    n = ld0590(x, y, z, w);
  } else if (order == 770) {
    n = ld0770(x, y, z, w);
  } else if (order == 974) {
    n = ld0974(x, y, z, w);
  } else if (order == 1202) {
    n = ld1202(x, y, z, w);
  } else if (order == 1454) {
    n = ld1454(x, y, z, w);
  } else if (order == 1730) {
    n = ld1730(x, y, z, w);
  } else if (order == 2030) {
    n = ld2030(x, y, z, w);
  } else if (order == 2354) {
    n = ld2354(x, y, z, w);
  } else if (order == 2702) {
    n = ld2702(x, y, z, w);
  } else if (order == 3074) {
    n = ld3074(x, y, z, w);
  } else if (order == 3470) {
    n = ld3470(x, y, z, w);
  } else if (order == 3890) {
    n = ld3890(x, y, z, w);
  } else if (order == 4334) {
    n = ld4334(x, y, z, w);
  } else if (order == 4802) {
    n = ld4802(x, y, z, w);
  } else if (order == 5294) {
    n = ld5294(x, y, z, w);
  } else if (order == 5810) {
    n = ld5810(x, y, z, w);
  } else {
    fprintf(stderr,
            "\nLD_BY_ORDER - Fatal error!\n  Unexpected value of ORDER.\n");
    //return 1; //exit(1);
  }

  return n;
}
//****************************************************************************80
