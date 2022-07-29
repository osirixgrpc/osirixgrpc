/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

/** \brief add exif to JPEG */
@interface JPEGExif : NSObject {

}

+ (void) addExif:(NSURL*) url properties:(NSDictionary*) exifDict format: (NSString*) format;

@end
