/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSBitmapImageRep (N2)

-(void)setColor:(NSColor*)color __deprecated; // buggy in Retina...
-(NSImage*)image;
-(NSBitmapImageRep*)repUsingColorSpaceName:(NSString*)colorSpaceName;

-(void)ATMask:(float)level DEPRECATED_ATTRIBUTE;
-(NSBitmapImageRep*)smoothen:(NSUInteger)margin;
//-(NSBitmapImageRep*)convolveWithFilter:(const boost::numeric::ublas::matrix<float>&)filter fillPixel:(NSUInteger[])fillPixel;
//-(NSBitmapImageRep*)fftConvolveWithFilter:(const boost::numeric::ublas::matrix<float>&)filter fillPixel:(NSUInteger[])fillPixel;

@end
