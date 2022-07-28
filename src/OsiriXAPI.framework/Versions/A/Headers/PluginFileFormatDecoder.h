/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

/** \brief Plugin for adding file format */
@interface PluginFileFormatDecoder : NSObject {

	NSNumber *_height;
	NSNumber *_width;
	float *_fImage;
	NSNumber * _rowBytes;
	NSNumber *_windowWidth;
	NSNumber *_windowLevel;
	BOOL _isRGB;
	
	NSString *_patientName;
	NSString *_patientID;
	NSString *_studyID;
	NSString *_seriesID;
	NSString *_imageID;
	NSString *_studyDescription;
	NSString *_seriesDescription;
}
// not used currently
+ (float *)decodedDataAtPath:(NSString *)path;

/*
	This is the main method to get the fImage float pointer used by DCMPix to create an image.  
	If the data is RGB the pointe should be to unsigned char with the format ARGB
	Grayscale data is a float pointer
*/

- (float *)checkLoadAtPath:(NSString *)path;

//returns values needed by DCMPix
- (NSNumber *)height;
- (NSNumber *)width;
- (NSNumber *)rowBytes;
- (NSNumber *)windowWidth; //optional
- (NSNumber *)windowLevel; //optional
- (BOOL)isRGB; //default is YES

// Optional values for loading into the DB.
- (NSString *)patientName;
- (NSString *)patientID;
- (NSString *)studyID;
- (NSString *)seriesID;
- (NSString *)imageID;
- (NSString *)studyDescription;
- (NSString *)seriesDescription;


@end
