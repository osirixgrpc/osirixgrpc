/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@interface DiscMountedAskTheUserDialogController : NSWindowController {
    NSString* _mountedPath;
    NSInteger _filesCount;
    NSInteger _choice;
    // Outlets
    NSTextField* _label;
}

@property(assign) IBOutlet NSTextField* label;
@property(readonly) NSInteger choice;

-(id)initWithMountedPath:(NSString*)path dicomFilesCount:(NSInteger)count;

-(IBAction)buttonAction:(NSButton*)sender;

@end
