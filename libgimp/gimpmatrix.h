/* gimpmatrix.h
 * Copyright (C) 1998 Jay Cox <jaycox@earthlink.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GIMPMATRIX_H__
#define __GIMPMATRIX_H__

typedef double  GimpMatrix[3][3];

void          gimp_matrix_transform_point (const GimpMatrix, double, double,
					   double *, double *);
void          gimp_matrix_mult            (const GimpMatrix, GimpMatrix);
void          gimp_matrix_identity        (GimpMatrix);
void          gimp_matrix_translate       (GimpMatrix, double, double);
void          gimp_matrix_scale           (GimpMatrix, double, double);
void          gimp_matrix_rotate          (GimpMatrix, double);
void          gimp_matrix_xshear          (GimpMatrix, double);
void          gimp_matrix_yshear          (GimpMatrix, double);
double        gimp_matrix_determinant     (const GimpMatrix);
void          gimp_matrix_invert          (const GimpMatrix m, GimpMatrix m_inv);


#endif  /*  __GIMPMATRIX_H__  */
