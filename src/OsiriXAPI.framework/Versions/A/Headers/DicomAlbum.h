/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

@class DicomStudy;

/** \brief  Core Data Entity for an Album */

@interface DicomAlbum : NSManagedObject {
    int numberOfStudies;
}

@property(nonatomic, retain) NSNumber* modifiedTimeStamp;
@property(nonatomic, retain) NSNumber* index;
@property(nonatomic, retain) NSString* name;
@property(nonatomic, retain) NSString* uid;
@property(nonatomic, retain) NSString* predicateString;
@property(nonatomic, retain) NSNumber* smartAlbum;
@property(nonatomic, retain) NSSet* studies;
@property(nonatomic, retain) NSNumber* cloud_downloaded;
@property(nonatomic, retain) NSNumber* cloud_set;
@property int numberOfStudies;

@end

@interface DicomAlbum (CoreDataGeneratedAccessors)

- (void)addStudiesObject:(DicomStudy *)value;
- (void)removeStudiesObject:(DicomStudy *)value;
- (void)addStudies:(NSSet *)value;
- (void)removeStudies:(NSSet *)value;

+ (NSPredicate*) smartAlbumPredicateString:(NSString*) string;
- (NSPredicate*)smartAlbumPredicate;

@end

