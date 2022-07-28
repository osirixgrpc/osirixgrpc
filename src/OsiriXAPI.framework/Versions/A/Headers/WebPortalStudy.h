/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@class DicomStudy, WebPortalUser;

@interface WebPortalStudy : NSManagedObject

-(DicomStudy*)study;

@property (nonatomic, retain) NSDate * dateAdded;
@property (nonatomic, retain) NSString * patientUID;
@property (nonatomic, retain) NSString * studyInstanceUID;
@property (nonatomic, retain) WebPortalUser * user;

@property (readonly) DicomStudy* study;

@end
