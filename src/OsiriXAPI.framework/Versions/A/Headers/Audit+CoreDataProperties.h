/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "Audit.h"


NS_ASSUME_NONNULL_BEGIN

@interface Audit (CoreDataProperties)

+ (NSFetchRequest<Audit *> *)fetchRequest;

@property (nullable, nonatomic, copy) NSDate *creationDate;
@property (nullable, nonatomic, copy) NSDate *modificationDate;
@property (nullable, nonatomic, copy) NSString *name;
@property (nullable, nonatomic, retain) NSData *sources;
@property (nullable, nonatomic, retain) NSData *retrievedPeriods;
@property (nullable, nonatomic, copy) NSString *uid;
@property (nullable, nonatomic, retain) NSSet<AuditStudy *> *studies;

@end

@interface Audit (CoreDataGeneratedAccessors)

- (void)addStudiesObject:(AuditStudy *)value;
- (void)removeStudiesObject:(AuditStudy *)value;
- (void)addStudies:(NSSet<AuditStudy *> *)values;
- (void)removeStudies:(NSSet<AuditStudy *> *)values;

@end

NS_ASSUME_NONNULL_END
