/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>
#import "DCMTKQueryNode.h"

/** \brief Image level DCMTKQueryNode*/
@interface DCMTKImageQueryNode : DCMTKQueryNode <NSCopying>
{
	NSString *_studyInstanceUID, *_seriesInstanceUID;
}

- (NSString*) seriesInstanceUID;
- (NSString*) studyInstanceUID;
- (NSString*) sopInstanceUID;

@end
