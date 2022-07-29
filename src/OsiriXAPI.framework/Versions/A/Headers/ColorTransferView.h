/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <AppKit/AppKit.h>


@interface ColorTransferView : NSView {

	IBOutlet		NSColorWell *pick;
	IBOutlet		NSTextField *position;
	
	NSMutableArray  *colors;
	NSMutableArray  *points;
	
	NSInteger		curIndex;
}

-(void) selectPicker:(id) sender;
-(NSMutableArray*) getPoints;
-(NSMutableArray*) getColors;
-(void) ConvertCLUT:(unsigned char*) red : (unsigned char*) green : (unsigned char*) blue;
-(IBAction) renderButton:(id) sender;
@end
