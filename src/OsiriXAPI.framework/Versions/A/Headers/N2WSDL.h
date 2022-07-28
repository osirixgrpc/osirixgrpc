/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface N2WSDL : NSObject {
	NSMutableArray* _types;
	NSMutableArray* _messages;
	NSMutableArray* _operations;
	NSMutableArray* _portTypes;
	NSMutableArray* _bindings;
	NSMutableArray* _ports;
	NSMutableArray* _services;
}

-(id)initWithContentsOfURL:(NSURL*)url;

@end
