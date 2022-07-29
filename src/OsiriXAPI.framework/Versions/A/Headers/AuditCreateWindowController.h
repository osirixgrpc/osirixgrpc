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
#import "sourcesTableView.h"

@interface AuditCreateWindowController : OSIWindowController
{
    NSString *auditName;
    
    NSMutableArray *sourcesArray;
    IBOutlet sourcesTableView *sourcesTable;
    
    NSMutableArray *sourcesDatabasesArray;
    IBOutlet sourcesTableView *sourcesDatabasesTable;
}
@property(retain) NSString *auditName;

+ (id) showWindow;
@end
