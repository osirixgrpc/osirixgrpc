/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>

@class QueryLogController;

/** \brief  Window Controller for network logs */
@interface LogWindowController : NSWindowController <NSTableViewDelegate, NSWindowDelegate>
{
	IBOutlet QueryLogController *receive, *move, *send, *web;
    IBOutlet NSTableView *webTableView;
}

- (IBAction) export:(id) sender;

@end
