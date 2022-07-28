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

@class SRController;

/** \brief FlyThruAdapter for Surface Rendering
*
* Surface Rendering FlyThruAdapter
*/

@interface SRFlyThruAdapter : FlyThruAdapter {

}

- (id) initWithSRController: (SRController*) aSRController;

@end
