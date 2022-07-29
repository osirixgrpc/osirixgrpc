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

#ifndef OSIRIX_LIGHT
/** \brief Study level DCMTKQueryNode */
@interface DCMTKStudyQueryNode : DCMTKQueryNode {
    BOOL isHidden;
    
    NSString *_studyID;
    
    NSManagedObjectID *localStudyObjectID;
    NSTimeInterval localStudyObjectIDTime;
}

@property (retain) NSManagedObjectID *localStudyObjectID;

- (NSManagedObjectID*) localStudyObjectIDForContext: (NSManagedObjectContext *) context;
- (NSString*) patientUID;
- (NSNumber*) stateText;
- (NSString*) studyID;
- (NSString*) studyInstanceUID;// Match DicomStudy
- (NSString*) studyName;// Match DicomStudy
- (NSNumber*) numberOfImages;// Match DicomStudy
- (NSDate*) dateOfBirth; // Match DicomStudy
- (NSString*) dateOfBirthString; // Match DicomStudy
- (NSNumber*) noFiles; // Match DicomStudy
- (BOOL) isHidden;
- (void) setHidden: (BOOL) h;
- (void) queryChildrenAtIMAGELevel;
- (BOOL) isModalityFieldEmpty;
- (NSString*) modalities;

-(void) computeNumberOfImages;
-(void) computeModalitiesInStudy;

@end
#endif
