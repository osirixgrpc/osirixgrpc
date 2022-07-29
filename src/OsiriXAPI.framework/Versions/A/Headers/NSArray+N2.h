/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSArray (N2)
- (NSArray*)splitArrayIntoArraysOfMinSize:(NSUInteger)chunkSize maxArrays:(NSUInteger)maxArrays;
- (NSArray*)splitArrayIntoChunksOfMinSize:(NSUInteger)chunkSize maxChunks:(NSUInteger)maxChunks;
- (id) deepMutableCopy;
- (NSArray *)arrayByRemovingObject:(id)obj;
- (NSArray *)arrayByRemovingObjectFirstOccurenceOf:(id)obj;
- (NSArray *)arrayByRemovingObjectAtIndex:(NSUInteger)index;
- (NSArray *)arrayByRemovingObjectsFromArray:(NSArray*)objs;
- (NSArray *)arrayByRemovingDuplicates;
- (NSArray *)reversedArray;
- (NSArray*)divideArraySizeBy:(int) d;
- (id) randomObject;
- (BOOL)intersectArray:(NSArray*) a;
- (NSArray*)intersectionArray:(NSArray*) a;

- (NSString*)arrayAsJSONwithOptions: (NSJSONWritingOptions) o;
+ (NSArray*)arrayFromJSON:(NSString*) s withOptions: (NSJSONReadingOptions) o;
- (NSString*)arrayAsString;
+ (NSArray*)arrayFromString: (NSString*) s;
- (NSArray*)randomizedArray;
@end


@interface NSMutableArray (N2)

-(void)addUniqueObjectsFromArray:(NSArray*)array;
-(void) replaceLasObjectWith: (id) object;
-(void) addObjectIfNotNil: (id) object;
@end
