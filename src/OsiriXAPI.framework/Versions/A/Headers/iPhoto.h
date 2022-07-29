/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/




#import <Foundation/Foundation.h>
#import <Carbon/Carbon.h>

/** \brief Import into iPhoto*/
@interface iPhoto : NSObject
{
}

- (void)runScript:(NSString *)txt;
- (BOOL)importIniPhoto: (NSArray*) files;
@end
