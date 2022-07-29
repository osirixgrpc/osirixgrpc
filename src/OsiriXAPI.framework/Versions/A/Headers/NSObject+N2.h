/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@interface NSObject (N2)

- (void)OsiriXPerformSelectorOnMainThread:(SEL)aSelector withObject:(id)arg waitUntilDone:(BOOL)wait;
- (void)OsiriXPerformSelectorOnMainThread:(SEL)aSelector withObject:(id)arg afterDelay:(float)delay;

- (void)OsiriXPerformSelectorOnMainThread:(SEL)aSelector withObject:(id)arg rootCallStack:(BOOL)rootCallStack;
- (void)OsiriXPerformSelectorOnMainThread:(SEL)aSelector withObject:(id)arg rootCallStack:(BOOL)rootCallStack afterDelay:(float)delay;
@end

