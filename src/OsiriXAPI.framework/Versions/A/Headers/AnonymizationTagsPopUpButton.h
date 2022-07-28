/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@class DCMAttributeTag;
@class DICOMFieldMenu;

@interface AnonymizationTagsPopUpButton : NSButton {
	DCMAttributeTag* selectedTag;
    DICOMFieldMenu *DICOMField;
}

@property(retain,nonatomic) DCMAttributeTag* selectedTag;
@property (retain) DICOMFieldMenu *DICOMField;

@end
