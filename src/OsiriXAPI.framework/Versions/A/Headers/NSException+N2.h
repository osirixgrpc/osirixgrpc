/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


extern NSString* const N2ErrorDomain;


@interface NSException (N2)

-(NSString*)stackTrace;
-(NSString*)printStackTrace;

@end
