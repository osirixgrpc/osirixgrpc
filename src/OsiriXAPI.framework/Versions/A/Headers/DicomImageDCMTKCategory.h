/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "DicomImage.h"

/** \brief  DCMTK calls for Dicom Image */ 
@interface DicomImage (DicomImageDCMTKCategory)

- (NSString *)keyObjectType;
- (NSArray *)referencedObjects;
@end
