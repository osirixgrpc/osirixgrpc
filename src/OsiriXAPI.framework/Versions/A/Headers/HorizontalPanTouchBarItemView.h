/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

@interface HorizontalPanTouchBarItemView : NSView

@property (nonatomic, retain) IBOutlet NSView *view;
@property (nonatomic, retain) IBOutlet NSTextField *textField;
@property (nonatomic, retain) IBOutlet NSImageView *chevronLeft1, *chevronLeft2, *chevronLeft3;
@property (nonatomic, retain) IBOutlet NSImageView *chevronRight1, *chevronRight2, *chevronRight3;

- (void)setTintColor:(NSColor*)tintColor;
- (void)setTitle:(NSString*)title;

@end
