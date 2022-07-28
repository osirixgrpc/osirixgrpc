/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSManagedObject (N2)

+(NSString*)UidForXid:(NSString*)xid;
+(NSURL*)UrlForXid:(NSString*)xid;

-(NSString*)XID;
-(NSString*)XIDFilename;
@end
