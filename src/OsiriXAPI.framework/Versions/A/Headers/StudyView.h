/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>

/** \brief Study View for ViewerController */

@interface StudyView : NSView {
	int seriesRows;
	int seriesColumns;
	NSMutableArray *seriesViews;
}

- (id)initWithFrame:(NSRect)frame seriesRows:(int)rows  seriesColumns:(int)columns;
- (NSMutableArray *)seriesViews;
- (void)setSeriesViewMatrixForRows:(int)rows  columns:(int)columns;

@end
