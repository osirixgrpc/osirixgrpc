/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

#import "Audit.h"

@interface AuditDataView : NSView {
    int year;
    Audit *audit;
    
    int mouseStartDay, mouseStartMonth;
    int mouseEndDay, mouseEndMonth;
    
    NSDictionary *stat;
    NSSet *availablePeriods;
    
    BOOL tooltipsCreated;
    NSMutableArray *tooltipsRetained;
}
@property (nonatomic) int year;
@property (nonatomic, retain) Audit *audit;
@property (retain) NSDictionary *stat;
@property (retain) NSSet *availablePeriods;
@property BOOL tooltipsCreated;

@property int mouseStartDay, mouseStartMonth, mouseEndDay, mouseEndMonth;

- (void) computeStat;

@end
