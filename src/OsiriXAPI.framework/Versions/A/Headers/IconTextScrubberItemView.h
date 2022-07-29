/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

@interface IconTextScrubberItemView : NSScrubberItemView

@property (retain) NSImageView *imageView;
@property (retain) NSTextField *textField;

+ (int)horizontalMargin;

@end
