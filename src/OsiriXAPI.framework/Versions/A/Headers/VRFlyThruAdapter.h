/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/




#import <Cocoa/Cocoa.h>
#import "FlyThruAdapter.h"

@class VRController;

/** \brief FlyThruAdapter for Volume Rendering
*
* Volume Rendering FlyThruAdapter
*/

@interface VRFlyThruAdapter : FlyThruAdapter {
}

- (id) initWithVRController: (VRController*) aVRController;
- (NSImage*) getCurrentCameraImage: (BOOL) highQuality;

@end
