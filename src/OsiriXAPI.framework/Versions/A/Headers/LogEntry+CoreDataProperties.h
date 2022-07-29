/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "LogEntry.h"

NS_ASSUME_NONNULL_BEGIN

@interface LogEntry (CoreDataProperties)

@property (nullable, nonatomic, retain) NSString *destinationName;
@property (nullable, nonatomic, retain) NSString *destinationPort;
@property (nullable, nonatomic, retain) NSString *message;
@property (nullable, nonatomic, retain) NSString *destinationHostname;
@property (nullable, nonatomic, retain) NSString *originName;
@property (nullable, nonatomic, retain) NSString *originHostname;
@property (nullable, nonatomic, retain) NSString *type;
@property (nullable, nonatomic, retain) NSString *studyName;
@property (nullable, nonatomic, retain) NSDate *studyDate;
@property (nullable, nonatomic, retain) NSString *studyUID;
@property (nullable, nonatomic, retain) NSString *studyAccessionNumber;
@property (nullable, nonatomic, retain) NSNumber *numberError;
@property (nullable, nonatomic, retain) NSString *patientName;
@property (nullable, nonatomic, retain) NSString *patientID;
@property (nullable, nonatomic, retain) NSNumber *numberPending;
@property (nullable, nonatomic, retain) NSDate *endTime;
@property (nullable, nonatomic, retain) NSNumber *numberImages;
@property (nullable, nonatomic, retain) NSNumber *numberSent;
@property (nullable, nonatomic, retain) NSDate *startTime;
@property (nullable, nonatomic, retain) NSString *originPort;
@property (nullable, nonatomic, retain) NSString *status;
@property (nullable, nonatomic, retain) NSString *username;

@end

NS_ASSUME_NONNULL_END
