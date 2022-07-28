/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "OrthogonalMPRView.h"

/** \brief OrthogonalMPRView for PET-CT fusion */

@interface OrthogonalMPRPETCTView : OrthogonalMPRView {
}
- (void) superSetBlendingFactor:(float) f;
- (void) superFlipVertical:(id) sender;
- (void) superFlipHorizontal:(id) sender;

@end
