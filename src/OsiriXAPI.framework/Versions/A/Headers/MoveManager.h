/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

/** \brief move manager */
@interface MoveManager : NSObject {
	NSMutableSet *_set;
}

+ (id)sharedManager;
- (void)addMove:(id)move;
- (void)removeMove:(id)move;
- (BOOL)containsMove:(id)move;

@end
