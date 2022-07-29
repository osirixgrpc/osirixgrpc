/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class AuditStudy;

NS_ASSUME_NONNULL_BEGIN

@interface Audit : NSManagedObject {
    NSSet *retrievedPeriodCache;
}
- (NSDate*) oldestPeriodDate;
- (NSDate*) latestPeriodDate;
- (NSSet*) formattedPeriodsForYear: (int) year;
- (NSSet*) retrievedPeriodsSet;
@end

NS_ASSUME_NONNULL_END

#import "Audit+CoreDataProperties.h"
