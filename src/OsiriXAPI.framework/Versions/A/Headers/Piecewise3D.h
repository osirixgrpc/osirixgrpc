/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/




#import <Cocoa/Cocoa.h>
#import "Interpolation3D.h"

#ifdef __cplusplus
#include <vtkPiecewiseFunction.h>
#else
typedef char* vtkPiecewiseFunction;
#endif


/** \brief Linear interpolation for FlyThru
*/


@interface Piecewise3D : Interpolation3D {
	vtkPiecewiseFunction	*xPiecewise, *yPiecewise, *zPiecewise;
}

@end
