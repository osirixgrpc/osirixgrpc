/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import "N2View.h"
@class N2Steps, N2Step, N2StepView, N2ColumnLayout;

@interface N2StepsView : N2View {
	IBOutlet N2Steps* _steps;
}

-(void)stepsDidAddStep:(NSNotification*)notification;
-(N2StepView*)stepViewForStep:(N2Step*)step;
-(void)layOut;

@end
