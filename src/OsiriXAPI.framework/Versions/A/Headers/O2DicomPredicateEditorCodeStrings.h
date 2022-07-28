/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>

@class DCMAttributeTag;

@interface O2DicomPredicateEditorCodeStrings : NSObject

+ (NSDictionary*)codeStringsForTag:(DCMAttributeTag*)tag;

@end

