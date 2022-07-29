/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>
/** \brief  Category to shuffle arrays */
@interface NSArray (ArrayCategory)

- (NSArray*)shuffledArray;

@end

/** \brief  Category to shuffle mutableArrays */
@interface NSMutableArray (MutableArrayCategory)

//appends array to self except when the object is already in the array as determined by isEqual:
- (void) mergeWithArray:(NSArray*)array;
- (BOOL) containsString:(NSString *)string __deprecated; // Deprecated: why use this instead of containsObject: ?
- (BOOL) removeDuplicatedStrings __deprecated;
- (BOOL) removeDuplicatedStringsInSyncWithThisArray: (NSMutableArray*) otherArray __deprecated;
- (BOOL) removeDuplicatedObjects;
- (void) addString:(NSString*) str;
//randomizes the array
- (void)shuffle;

@end
