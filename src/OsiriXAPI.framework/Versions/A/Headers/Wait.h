/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import <IOKit/pwr_mgt/IOPMLib.h>


@class SendController;

/** \brief Window Controller for the Wait Panel */
@interface Wait : NSWindowController <NSWindowDelegate>
{
    IBOutlet NSProgressIndicator *progress;
	IBOutlet NSTextField		 *text, *elapsed;
	IBOutlet NSButton			 *abort;
	
	NSTimeInterval startTime;
	BOOL	cancel, aborted;
	NSTimeInterval lastTimeFrame, lastTimeFrameUpdate, firstTime, displayedTime;
    IOPMAssertionID assertionID;
    
    NSRect windowFrameRect;
    BOOL closed, ticktack;
    
    NSModalSession session;
}
+ (Wait*) showWithString: (NSString*) str;
+ (Wait*) showWithString: (NSString*) str maxProgress: (int) maxValue showCancel: (BOOL) showCancel;

- (void)setProgressValue:(double)v;
- (void)incrementBy:(double)delta;
- (void)increment;
- (NSProgressIndicator*) progress;
- (id) initWithString:(NSString*) str;
- (BOOL) aborted;
- (IBAction) abortButton: (id) sender;
- (void) setCancel :(BOOL) val;
- (void) setElapsedString :(NSString*) str;
@end
