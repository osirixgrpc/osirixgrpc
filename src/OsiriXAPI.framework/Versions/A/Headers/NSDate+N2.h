/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSDate (N2)

+(id)dateWithString:(NSString *)str calendarFormat:(NSString*)format;
- (NSString*) dateAsStringWithCalendarFormat: (NSString*)format;

+(id)dateWithString:(NSString *)str calendarFormat:(NSString*)format error:(BOOL*) failed;
+(id)dateWithYYYYMMDD:(NSString*)datestr HHMMss:(NSString*)timestr;

-(NSDateComponents*) differenceWithDate: (NSDate*) endDate;
-(NSCalendarDate*) endOfDay;
-(NSCalendarDate*) startOfDay;
@end
