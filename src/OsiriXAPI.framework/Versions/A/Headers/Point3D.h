/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>
#import "N3Geometry.h"

/** \brief  Represents a 3D Point
*
*  Represents a 3D Point
*  Has x, y, and z positions as double
*/


@interface Point3D : NSObject <NSCoding> {
	double x, y, z;
}

@property double x;
@property double y;
@property double z;

+ (id) point;
+ (id) pointWithX:(double)x1 y:(double)y1 z:(double)z1;
+ (id) pointWithDictionary: (NSDictionary*) d;
+ (id) pointWithArray:(double*)a;

-(id) init; // initiatize to origin
-(id) initWithValues:(double)x :(double)y :(double)z;
-(id) initWithPoint3D: (Point3D*)p;
-(id) initWithX:(double)x  y:(double)y  z:(double)z;
- (id)copyWithZone:(NSZone *)zone;

-(void) setPoint3D: (Point3D*)p;

-(void) add: (Point3D*)p;
-(void) subtract: (Point3D*)p;
-(void) multiply: (double)a;

-(NSMutableDictionary*) exportToXML;
-(id) initWithDictionary: (NSDictionary*)xml;

@end

@interface Point3D (N3GeometryAdditions)

+ (id)pointWithN3Vector:(N3Vector)vector;
- (id)initWithN3Vector:(N3Vector)vector;
- (N3Vector)N3VectorValue;

@end
