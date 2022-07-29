/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "AuditStudy.h"


NS_ASSUME_NONNULL_BEGIN

@interface AuditStudy (CoreDataProperties)

+ (NSFetchRequest<AuditStudy *> *)fetchRequest;

@property (nullable, nonatomic, copy) NSString *bodyPartExamined;
@property (nullable, nonatomic, copy) NSString *server;
@property (nullable, nonatomic, copy) NSNumber *duration;
@property (nullable, nonatomic, copy) NSNumber *dayOfWeek;
@property (nullable, nonatomic, copy) NSNumber *month;
@property (nullable, nonatomic, copy) NSString *sex;
@property (nullable, nonatomic, copy) NSString *manufacturerModelName;
@property (nullable, nonatomic, copy) NSString *momentOfDay;
@property (nullable, nonatomic, copy) NSNumber *numberOfStudyRelatedInstances;
@property (nullable, nonatomic, copy) NSString *modality;
@property (nullable, nonatomic, copy) NSString *momentOfWeek;
@property (nullable, nonatomic, copy) NSString *performingPhysician;
@property (nullable, nonatomic, copy) NSNumber *year;
@property (nullable, nonatomic, copy) NSNumber *day;
@property (nullable, nonatomic, copy) NSNumber *hourOfDay;
@property (nullable, nonatomic, copy) NSString *name;
@property (nullable, nonatomic, copy) NSDate *date;
@property (nullable, nonatomic, copy) NSString *dateFormatted;
@property (nullable, nonatomic, copy) NSString *studyInstanceUID;
@property (nullable, nonatomic, copy) NSNumber *age;
@property (nullable, nonatomic, copy) NSString *referringPhysician;
@property (nullable, nonatomic, retain) Audit *audit;

@end

NS_ASSUME_NONNULL_END
