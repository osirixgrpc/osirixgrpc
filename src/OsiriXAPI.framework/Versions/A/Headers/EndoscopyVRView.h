/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>

#import "VRView.h"

/** \brief   VRview for Endoscopy
*/
@interface EndoscopyVRView : VRView {

}

- (void) setShadingValues:(float) ambient :(float) diffuse :(float) specular :(float) specularpower;
-(unsigned char*) superGetRawPixels:(long*) width :(long*) height :(long*) spp :(long*) bpp :(BOOL) screenCapture :(BOOL) force8bits;
@end
