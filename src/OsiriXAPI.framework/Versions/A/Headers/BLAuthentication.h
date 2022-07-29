//  ====================================================================== 	//
//  BLAuthentication.h														//
//  																		//
//  Last Modified on Tuesday April 24 2001									//
//  Copyright 2001 Ben Lachman												//
//																			//
//	Thanks to Brian R. Hill <http://personalpages.tds.net/~brian_hill/>		//
//  ====================================================================== 	//

#import <Cocoa/Cocoa.h>
#import <Security/Authorization.h>

/** \brief authentication and authorization */
@interface BLAuthentication : NSObject 
{
	AuthorizationRef authorizationRef; 
}
// returns a shared instance of the class
+ sharedInstance;
+(void) setDontAskPrivileges: (BOOL) p;
// checks if user is authentcated forCommands
- (BOOL)isAuthenticated:(NSArray *)forCommands;
// authenticates user forCommands
- (BOOL)authenticate:(NSArray *)forCommands;
// deauthenticates user
- (void)deauthenticate;
// gets the pid forProcess
- (int)getPID:(NSString *)forProcess;
// executes pathToCommand with privileges
- (BOOL)executeCommand:(NSString *)pathToCommand withArgs:(NSArray *)arguments;
- (BOOL)executeCommand:(NSString *)pathToCommand withArgs:(NSArray *)arguments wait: (BOOL) wait;
- (BOOL)executeCommand:(NSString *)pathToCommand withArgs:(NSArray *)arguments wait: (BOOL) wait pipe: (FILE**) pipe;
// kills the process specified by commandFromPS
- (BOOL)killProcess:(NSString *)commandFromPS;
@end




