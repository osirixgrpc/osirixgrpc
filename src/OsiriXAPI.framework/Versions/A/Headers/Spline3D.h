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
#include <vtkCardinalSpline.h>
#else
typedef char* vtkCardinalSpline;
#endif


/** \brief Spline interpolation for FlyThru
*/


@interface Spline3D : Interpolation3D {
	vtkCardinalSpline	*xSpline, *ySpline, *zSpline;
	BOOL				computed;
}

- (id) init;
- (void) compute;

@end
