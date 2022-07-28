/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

@class FlyThruController;


/** \brief  Manages the array of FlyThru steps
*
* A subclass of NSArrayController used to manage the steps of the flythru.
* Each step consists of a Camera -- See Camera.h
* Uses the usual NSArrayController methods.
*/


@interface FlyThruStepsArrayController : NSArrayController {
	IBOutlet FlyThruController *flyThruController;
	IBOutlet NSTableView	*tableview;
}

- (IBAction) flyThruButton:(id) sender;
- (void) flyThruTag:(int) x;
- (void) resetCameraIndexes;
- (IBAction)updateCamera:(id)sender;
- (IBAction)resetCameras:(id)sender;
- (void) keyDown:(NSEvent *)theEvent;

@end
