/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


/** \brief Cell that can contain text and and image */

#import <Cocoa/Cocoa.h>

@interface ImageAndTextCell : NSTextFieldCell {
@private
    NSImage	*image, *lastImage, *lastImageAlternate;
	BOOL clickedInLastImage;
    BOOL rescaleImageToFit;
    
    NSArray *imagesNames;
    int clickedImageIndex;
    
    id delegate;
}

@property BOOL rescaleImageToFit;
@property int clickedImageIndex;
@property (retain) NSArray *imagesNames;
@property (retain) id delegate;

- (void)setImage:(NSImage *)anImage;
- (void)setLastImage:(NSImage *)anImage;
- (void)setLastImageAlternate:(NSImage *)anImage;
- (NSImage *)image;

- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (NSSize)cellSize;
- (BOOL) clickedInLastImage;

@end
