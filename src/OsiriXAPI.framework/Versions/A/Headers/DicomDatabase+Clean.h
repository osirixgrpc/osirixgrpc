/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "DicomDatabase.h"


@interface DicomDatabase (Clean)

-(void) initClean;
-(void) deallocClean;
-(void) initiateCleanUnlessAlreadyCleaning;
-(void) cleanOldStuff;
-(void) cleanForFreeSpace;
-(void) cleanForFreeSpaceMB:(NSInteger)freeMemoryRequested; // so we can allow timed "deep clean"
-(BOOL) freeSpaceLimitSoonReachedForPath: (NSString*) path;
@end
