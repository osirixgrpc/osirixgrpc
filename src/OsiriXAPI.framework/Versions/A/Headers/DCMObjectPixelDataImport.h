/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>
#import <OsiriX/DCMObject.h>


@interface DCMObjectPixelDataImport : DCMObject {

}

+ (id)objectWithContentsOfFile:(NSString *)file decodingPixelData:(BOOL)decodePixelData	;

@end
