/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@interface LoginWindow : NSWindowController
{
    NSString *username, *password, *reason;
    BOOL autoSignIn;
    NSArray *keychainAccounts;
}
@property (retain, nonatomic) NSString *username, *password, *reason;
@property (retain) NSArray *keychainAccounts;

+ (id) instantiate;
+ (id) instantiateWithUsername:(NSString*) username;
+ (id) instantiateWithUsername:(NSString*) username reason:(NSString*) reason;
+ (id) instantiateWithReason:(NSString*) reason;

- (BOOL) runModal;

@end
