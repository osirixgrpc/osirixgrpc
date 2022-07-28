/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "BrowserController.h"
#import "WaitRendering.h"

/** \brief  Searches and retrieves Bonjour shared databases */

@interface BonjourBrowser : NSObject <NSNetServiceDelegate, NSNetServiceBrowserDelegate>
{
    NSNetServiceBrowser* browser;
	NSMutableArray* services;
	BrowserController* interfaceOsiriX;
}

+ (BonjourBrowser*) currentBrowser;

- (id) initWithBrowserController: (BrowserController*) bC;

- (NSArray*) services;

- (void) buildFixedIPList;
- (void) buildLocalPathsList;
- (void) buildDICOMDestinationsList;
- (void) arrangeServices;

@end
