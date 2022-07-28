/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "OSIVolumeWindow.h"

@class ViewerController;
@class DCMView;

@interface OSIVolumeWindow (Private)

- (id)initWithViewerController:(ViewerController *)viewerController;
- (void)viewerControllerDidClose;
- (void)viewerControllerWillChangeData;
- (void)viewerControllerDidChangeData;

- (void)drawInDCMView:(DCMView *)dcmView;
- (void)setNeedsDisplay;

@end




