/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>
#import "ViewerController.h"


/** \brief View used for printing from ViewerController */
@interface printView : NSView
{
	id						viewer;
	NSDictionary			*settings;
	NSArray					*filesToPrint;
	int						columns;
	int						rows;
	int						ipp;
	float					headerHeight;
    NSManagedObjectID       *firstImageID;
}

- (id)initWithViewer:(id) v
			settings:(NSDictionary*) s
			   files:(NSArray*) f
		   printInfo:(NSPrintInfo*) pi;
- (int)columns;
- (int)rows;
- (int)ipp;

@end
