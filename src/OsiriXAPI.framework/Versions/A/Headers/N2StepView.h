/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "N2DisclosureBox.h"
@class N2Step;

@interface N2StepView : N2DisclosureBox {
	N2Step* _step;
}

@property(readonly) N2Step* step;

-(id)initWithStep:(N2Step*)step;

@end
