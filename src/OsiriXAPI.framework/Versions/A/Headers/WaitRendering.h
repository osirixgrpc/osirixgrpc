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

/** \brief Window Controller for Wait rendering */
@interface WaitRendering : NSWindowController <NSWindowDelegate>
{
    IBOutlet NSProgressIndicator *progress;
	IBOutlet NSButton		     *abort;
	IBOutlet NSTextField		 *message, *currentTimeText, *lastTimeText;
	
    NSRect                      windowFrameRect;
	NSString					*string;
	NSTimeInterval				lastDuration, lastTimeFrame;
	NSTimeInterval              startTime;
	
	BOOL						aborted, eventsClear;
	volatile BOOL				stop;
	BOOL						supportCancel;
	
	id							cancelDelegate;
	
	NSTimeInterval				displayedTime;
    
    IOPMAssertionID assertionID;
    
    BOOL closed, ticktack;
    
    NSModalSession session;
}

@property (retain, nonatomic) NSString *string;

+(id) showWithString:(NSString*) str cancel:(BOOL) cancel;
+(id) showWithString:(NSString*) str;

- (id) init:(NSString*) s;
- (id) initWithString:(NSString*) str;
- (BOOL) run;
- (void) start __deprecated;
- (BOOL) started;
- (void) end;
- (IBAction) abort:(id) sender;
- (void) setCancel :(BOOL) val;
- (BOOL) aborted;
- (void) setCancelDelegate:(id) object;
- (void) resetLastDuration;
@end
