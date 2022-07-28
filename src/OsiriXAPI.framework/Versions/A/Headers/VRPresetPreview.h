/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>
#import "VRView.h"
#import "SelectionView.h"

@interface VRPresetPreview : VRView {
	BOOL isEmpty, isSelected;
	IBOutlet SelectionView	*selectionView;
	
	IBOutlet VRController	*presetController;
	int presetIndex;
}

- (void)setIsEmpty:(BOOL)empty;
- (BOOL)isEmpty;
- (void)setSelected;
- (void)setIndex:(int)index;
- (int)index;

@end
