/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>
#import "OSIROIMask.h"

@interface OSIROIMaskRunStack : NSObject
{
    NSData *_maskRunData;
    NSUInteger maskRunCount;
    NSUInteger _maskRunIndex;
    
    NSMutableArray *_maskRunArray;
}

- (id)initWithMaskRunData:(NSData *)maskRunData;

- (OSIROIMaskRun)currentMaskRun;
- (void)pushMaskRun:(OSIROIMaskRun)maskRun;
- (OSIROIMaskRun)popMaskRun;

- (NSUInteger)count;

@end
