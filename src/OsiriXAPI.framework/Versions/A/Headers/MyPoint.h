/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>

/** \brief Wrapper for NSPoint */

@interface MyPoint : NSObject<NSCoding> {
	NSPoint pt;
}

@property(assign) NSPoint point;
@property(readonly) double x, y;

+(MyPoint*)point:(NSPoint)a;
+(MyPoint*)pointWithFloatArray:(float*)a;
+(MyPoint*)pointWithDoubleArray:(float*)a;

- (id)initWithPoint:(NSPoint)a;
- (CGPoint) CGPoint;
- (void)setPoint:(NSPoint)a;
- (void)move:(double)x :(double)y;
- (double) distanceWithPoint: (MyPoint*) p;
- (double) squareDistanceWithPoint: (MyPoint*) p;
- (double) squareDistanceWithNSPoint: (NSPoint) p;
- (BOOL)isEqualToMyPoint:(MyPoint*)a;
- (BOOL)isEqualToPoint:(NSPoint)a;
- (BOOL)isNearToPoint:(NSPoint)a :(double)scale :(double)ratio;

@end
