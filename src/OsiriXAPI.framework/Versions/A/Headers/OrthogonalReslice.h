/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "DCMPix.h"

/** \brief Reslcie volume sagittally and Coronally */

@interface OrthogonalReslice : NSObject {
	NSMutableArray		*originalDCMPixList, *xReslicedDCMPixList, *yReslicedDCMPixList;
	NSMutableArray		*newPixListX, *newPixListY;
	short				thickSlab;
	float				sign;
	
	BOOL				useYcache;
	float				*Ycache;
	
	NSConditionLock		*resliceLock;
	
	long				minI, maxI, newX, newY, newTotal, currentAxe;
	DCMPix				*firstPix;
	
    NSOperationQueue    *yCacheQueue;
	NSLock				*processorsLock;
	volatile int		numberOfThreadsForCompute;
}

// init
- (id) initWithOriginalDCMPixList: (NSMutableArray*) pixList;
- (void) setOriginalDCMPixList: (NSMutableArray*) pixList;

// processors
- (void) reslice: (long) x : (long) y;
- (void) xReslice: (long) x;
- (void) yReslice: (long) y;

- (void) axeReslice: (short) axe : (long) sliceNumber;

// accessors
- (NSMutableArray*) originalDCMPixList;
- (NSMutableArray*) xReslicedDCMPixList;
- (NSMutableArray*) yReslicedDCMPixList;

// thickSlab
- (short) thickSlab;
- (void) setThickSlab : (short) newThickSlab;

- (void) flipVolume;
- (void)freeYCache;

- (BOOL)useYcache;
- (void)setUseYcache:(BOOL)boo;

@end
