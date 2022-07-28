/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>
#import "OrthogonalMPRController.h"
#import "OrthogonalMPRView.h"

/** \brief   MPR views for endoscopy
*/

@interface EndoscopyMPRView : OrthogonalMPRView {
	NSPoint	cameraPosition, cameraFocalPoint;
	float	cameraAngle;
	long	focalPointX, focalPointY, focalShiftX, focalShiftY, near, maxFocalLength;
	long	viewUpX, viewUpY;
	NSArray* flyThroughPath;
}

@property  (retain) NSArray* flyThroughPath;


- (void) setCameraPosition: (float) x : (float) y;
- (NSPoint) cameraPosition;
- (void) setCameraFocalPoint: (float) x : (float) y;
- (NSPoint) cameraFocalPoint;
- (void) setCameraAngle: (float) alpha;
- (float) cameraAngle;

- (void) setFocalPointX: (long) x;
- (void) setFocalPointY: (long) y;
- (long) focalPointX;
- (long) focalPointY;
- (void) setFocalShiftX: (long) x;
- (void) setFocalShiftY: (long) y;
- (long) focalShiftX;
- (long) focalShiftY;

- (void) setViewUpX: (long) x;
- (void) setViewUpY: (long) y;
- (long) viewUpX;
- (long) viewUpY;

-(unsigned char*) superGetRawPixels:(long*) width :(long*) height :(long*) spp :(long*) bpp :(BOOL) screenCapture :(BOOL) force8bits :(BOOL) removeGraphical;

@end
