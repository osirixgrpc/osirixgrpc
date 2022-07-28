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

/** \brief  Shares DB with Bonjour */

@class N2ConnectionListener;

@interface BonjourPublisher : NSObject <NSNetServiceDelegate>
{
    N2ConnectionListener* _listener;
	
    NSNetService* _bonjour;
    BOOL published;
    
	NSLock* dicomSendLock;
}

//@property(retain) NSString* serviceName;
//@property(retain, readonly) NSNetService* netService;

- (void)toggleSharing:(BOOL)activate;

// for now, we will only share the name of the shared database
//- (void)connectionReceived:(NSNotification *)aNotification;

// work as a delegate of the NSNetService
//- (void)netServiceWillPublish:(NSNetService *)sender;
//- (void)netService:(NSNetService *)sender didNotPublish:(NSDictionary *)errorDict;
//- (void)netServiceDidStop:(NSNetService *)sender;

- (NSNetService*)netService __deprecated;

//- (void)setServiceName:(NSString *) newName;
//- (NSString *) serviceName;
- (int) OsiriXDBCurrentPort __deprecated; // use -[[[AppController sharedAppController] bonjourPublisher] port]
+ (BonjourPublisher*) currentPublisher __deprecated; // use -[[AppController sharedAppController] bonjourPublisher]

+ (NSDictionary*)dictionaryFromXTRecordData:(NSData*)data;

@end
