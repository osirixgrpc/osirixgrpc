/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>


@interface ThreadsManager : NSObject {
	@private 
	NSArrayController* _threadsController;
    NSTimer* _timer;
}

@property(readonly) NSArrayController* threadsController;

+(ThreadsManager*)defaultManager;

-(NSArray*)threads;
-(NSUInteger)threadsCount;
-(NSThread*)threadAtIndex:(NSUInteger)index;
-(void)addThreadAndStart:(NSThread*)thread;
-(void)removeThread:(NSThread*)thread;

@end
