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

NS_ASSUME_NONNULL_BEGIN

@interface LogEntry : NSManagedObject

- (NSString *) countryDestinationHostname;
- (NSString *) countryOriginHostname;
- (NSString *) countryOriginName;

@end

NS_ASSUME_NONNULL_END

#import "LogEntry+CoreDataProperties.h"
