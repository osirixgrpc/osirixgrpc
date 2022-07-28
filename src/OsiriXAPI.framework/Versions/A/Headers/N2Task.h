/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#include <sys/event.h>

@interface N2Task : NSTask {
	NSString* _launchPath;
	NSArray* _arguments;
	pid_t _pid;
	uid_t _uid;
	NSTimeInterval _launchTime;
	NSDictionary* _environment;
	NSString* _currentDirectoryPath;
	id _standardError, _standardInput, _standardOutput;
}

@property(copy) NSArray* arguments;
@property(copy) NSString* currentDirectoryPath;
@property(copy) NSDictionary* environment;
@property(copy) NSString* launchPath;
@property(retain) id standardError;
@property(retain) id standardInput;
@property(retain) id standardOutput;

@property(readonly) NSTimeInterval launchTime;
@property(assign) uid_t uid;


//-(void)setEnv:(NSString*)name to:(NSString*)value;

@end
