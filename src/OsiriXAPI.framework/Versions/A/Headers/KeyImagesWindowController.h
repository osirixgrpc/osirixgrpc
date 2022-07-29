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

@interface KeyImagesWindowController : NSWindowController
{
    IBOutlet NSScrollView *scrollView;
    IBOutlet NSMatrix *matrix;
    NSArray *previousThumbnails;
    ViewerController *viewer;
    int previousIndex;
    NSString *previousStudyInstanceUID;
    BOOL hidden;
}

@property (retain) ViewerController *viewer;
@property (retain) NSString *previousStudyInstanceUID;
@property (readonly) BOOL hidden;

- (id) initForViewer:(ViewerController*) v;
- (BOOL) buildThumbnailMatrix;
- (BOOL) isVisible;
- (IBAction) hideButton: (id) sender;
- (IBAction) showButton: (id) sender;
@end
