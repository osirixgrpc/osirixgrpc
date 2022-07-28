/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>
#import "OSIWindowController.h"
#import "Audit.h"
#import "AuditDataView.h"

@interface AuditRetrieveWindowController : OSIWindowController
{
    Audit *currentAudit;
    
    IBOutlet NSArrayController *audits;
    IBOutlet AuditDataView *yearView;
    
    NSString *sourcesTitle, *oldestDate, *mostRecentDate, *numberOfDays;
    IBOutlet NSDatePicker *fromDate;
    IBOutlet NSDatePicker *toDate;
    
    NSThread* retrieveThread;
    BOOL retrieving;
    
    int displayedYear;
    int dateRangeMaxValue, dateRangeMinValue;
}
@property(retain) Audit *currentAudit;
@property(retain) NSString *sourcesTitle, *oldestDate, *mostRecentDate, *numberOfDays;
@property(retain) NSThread* retrieveThread;
@property BOOL retrieving;
@property(nonatomic) int displayedYear, dateRangeMaxValue, dateRangeMinValue;

+ (id) showWindow;
+ (id) showWindowWithUID:(NSString*) uid;
@end
