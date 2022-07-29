/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

extern NSString* N2ConnectionListenerOpenedConnectionNotification;
extern NSString* N2ConnectionListenerOpenedConnection;

@class N2Connection;

@interface N2ConnectionListener : NSObject  {
	Class _class;
    CFSocketRef ipv4socket;
    CFSocketRef ipv6socket;	
	NSMutableArray* _clients;
    BOOL _threadPerConnection;
    BOOL _tlsFlag;
}

@property BOOL threadPerConnection;

- (id)initWithPort:(NSInteger)port connectionClass:(Class)classs;
- (id)initWithPort:(NSInteger)port tls:(BOOL) tls connectionClass:(Class)classs;

- (id)initWithPath:(NSString*)path connectionClass:(Class)classs;

- (in_port_t)port;

@end
