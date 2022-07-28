/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "HorizontalPanTouchBarItemView.h"

@protocol HorizontalPanTouchBarItemDelegate <NSObject>
@optional
- (void)horizontalPanTouchBarItemDidPanOfPercentage:(CGFloat)percentage;
@end

@interface HorizontalPanTouchBarItem : NSCustomTouchBarItem
@property (nonatomic, assign) id <HorizontalPanTouchBarItemDelegate> delegate;
@property CGFloat previousPanTranslation;
- (void)setTintColor:(NSColor*)tintColor;
- (void)setTitle:(NSString*)title;
@end
