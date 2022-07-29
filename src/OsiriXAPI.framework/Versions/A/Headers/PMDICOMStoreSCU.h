/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/





#import <Foundation/Foundation.h>


@interface PMDICOMStoreSCU : NSObject {

}


//-(id)initWithCalledAET:(NSString *) callingAET:(NSString *)  hostName:(NSString *) port:(int);
-(BOOL)sendFile:(NSString *)fileName :(int)compressionLevel;
@end
