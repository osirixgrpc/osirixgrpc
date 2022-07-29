/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


@class ThreadsManagerThreadInfo;

@interface ThreadModalForWindowController : NSWindowController {
	NSThread* _thread;
    id _retainedThreadDictionary;
	NSWindow* _docWindow;
	NSProgressIndicator* _progressIndicator;
	NSButton* _cancelButton;
	NSButton* _backgroundButton;
	NSTextField* _titleField;
	NSTextView* _statusField;
    NSScrollView* _statusFieldScroll;
	NSTextField* _progressDetailsField;
    BOOL _isValid;

    CGFloat _lastDisplayedProgress;
    NSString* _lastPositionedStatus;
    
    NSTimeInterval lastGUIUpdate;
    
    int protectRecusive;
}

@property(retain, readonly) NSThread* thread;
@property(retain, readonly) NSWindow* docWindow;
@property(retain) IBOutlet NSProgressIndicator* progressIndicator;
@property(retain) IBOutlet NSButton* cancelButton;
@property(retain) IBOutlet NSButton* backgroundButton;
@property(retain) IBOutlet NSTextField* titleField;
@property(retain) IBOutlet NSTextView* statusField;
@property(retain) IBOutlet NSScrollView* statusFieldScroll;
@property(retain) IBOutlet NSTextField* progressDetailsField;

-(id)initWithThread:(NSThread*)thread window:(NSWindow*)window;

-(IBAction)cancelAction:(id)source;
-(IBAction)backgroundAction:(id)source;

-(void)invalidate;

@end


@interface NSThread (ModalForWindow)

extern NSString* const NSThreadModalForWindowControllerKey;

-(ThreadModalForWindowController*)startModalForWindow:(NSWindow*)window; // returns nil if not called on main thread
-(ThreadModalForWindowController*)modalForWindowController;

@end;
