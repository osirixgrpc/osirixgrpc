/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@interface NSImage (N2)

+ (NSSize)badgeSizeForString:(NSString*)string;
+ (void)drawBadgeImageWithText:(NSString*)text atPoint:(NSPoint)point;

-(NSImage *)rotateBy:(float) rotation;
-(NSImage *)flipImageX:(BOOL) xFlip Y:(BOOL) yFlip;
-(NSRect)boundingBoxSkippingColor:(NSColor*)color inRect:(NSRect)box;
-(NSRect)boundingBoxSkippingColor:(NSColor*)color;

-(NSImage*)shadowImage;
-(NSImage*)imageWithHue:(CGFloat)hue;
-(NSImage*)imageInverted;

-(NSSize)sizeByScalingProportionallyToSize:(NSSize)targetSize;
-(NSSize)sizeByScalingDownProportionallyToSize:(NSSize)targetSize;
-(NSImage*)imageByScalingProportionallyToSize:(NSSize)targetSize;
-(NSImage*)imageByScalingProportionallyToSizeUsingNSImage:(NSSize)targetSize;
-(NSImage*)imageByScalingProportionallyToSize:(NSSize)targetSize retinaSupport: (BOOL) retinaSupport;
-(NSImage*)imageByScalingToSize:(NSSize)targetSize retinaSupport: (BOOL) retinaSupport proportionally: (BOOL) proportionally;
-(NSImage*)imageByScalingProportionallyUsingNSImage:(float)ratio;
-(NSData*)getDataOfType:(NSBitmapImageFileType)type compressionFactor:(float)factor;
-(NSBitmapImageRep *)bitmapImageRepresentation;
-(NSBitmapImageRep *)bitmapImageRepresentationWithBitsPerSample: (int) bps andBitsPerPixel: (int) bpp;
-(NSBitmapImageRep *)bitmapImageRepresentationWithBitsPerSample: (int) bps andBitsPerPixel: (int) bpp scalingFactor: (float) s;
+ (float) backingScaleNSImage;
+ (NSImage *)imageWithPreviewOfFileAtPath:(NSString *)path ofSize:(NSSize)size;

@end

@interface N2Image : NSImage {
	NSRect _portion;
	NSSize _inchSize;
}

@property NSSize inchSize;
@property NSRect portion;

-(id)initWithSize:(NSSize)size inches:(NSSize)inches;
-(id)initWithSize:(NSSize)size inches:(NSSize)inches portion:(NSRect)portion;
-(N2Image*)crop:(NSRect)rect;
-(NSPoint)convertPointFromPageInches:(NSPoint)p;
-(NSSize)originalInchSize;
-(float)resolution;

@end
