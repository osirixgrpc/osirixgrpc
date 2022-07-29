/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>


@class ThreadsManager;

@interface ThreadCell : NSTextFieldCell {
	NSProgressIndicator* _progressIndicator;
	ThreadsManager* _manager;
	NSButton* _cancelButton;
	NSThread* _thread;
    id _retainedThreadDictionary;
	NSTableView* _view;
    NSTimeInterval lastStatusUpdate, lastCancelUpdate, lastProgressUpdate;
    BOOL KVOObserving;
}

@property(retain) NSProgressIndicator* progressIndicator;
@property(retain) NSButton* cancelButton;
@property(nonatomic, retain) NSThread* thread;
@property(assign, readonly) ThreadsManager* manager;
@property(assign, readonly) NSTableView* view;

-(id)initWithThread:(NSThread*)thread manager:(ThreadsManager*)manager view:(NSTableView*)view;

-(void)cleanup;

@end
