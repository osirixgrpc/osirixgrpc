/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

@interface NSThread (N2)

+(NSThread*)performBlockInBackground:(void(^)())block;

extern NSString* const NSThreadNameKey;

extern NSString* const NSThreadUniqueIdKey;
-(NSString*)uniqueId;
-(void)setUniqueId:(NSString*)uniqueId;

extern NSString* const NSThreadIsCancelledKey;
//-(BOOL)isCancelled;
-(void)setIsCancelled:(BOOL)isCancelled;

-(void)enterOperation;
-(void)enterOperationIgnoringLowerLevels;
-(void)enterOperationWithRange:(CGFloat)rangeLoc :(CGFloat)rangeLen;
-(void)exitOperation;
-(void)enterSubthreadWithRange:(CGFloat)rangeLoc :(CGFloat)rangeLen __deprecated;
-(void)exitSubthread __deprecated;

-(void)enterIgnoreGUIChanges;
-(void)exitIgnoreGUIChanges;

extern NSString* const NSThreadSupportsCancelKey;
-(BOOL)supportsCancel;
-(void)setSupportsCancel:(BOOL)supportsCancel;

extern NSString* const NSThreadSupportsBackgroundingKey;
-(BOOL)supportsBackgrounding;
-(void)setSupportsBackgrounding:(BOOL)supportsBackgrounding;

extern NSString* const NSThreadStatusKey;
-(NSString*)status;
-(void)setStatus:(NSString*)status;

extern NSString* const NSThreadProgressKey;
-(CGFloat)progress;
-(void)setProgress:(CGFloat)progress;

extern NSString* const NSThreadProgressDetailsKey;
-(NSString*)progressDetails;
-(void)setProgressDetails:(NSString*)progressDetails;

extern NSString* const NSThreadSubthreadsAwareProgressKey;
-(CGFloat)subthreadsAwareProgress;

-(NSInteger)getThreadNum;
@end

