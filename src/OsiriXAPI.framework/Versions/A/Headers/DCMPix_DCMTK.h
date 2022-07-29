/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "DCMPix.h"

@interface DCMPix (DCMPix_DCMTK)

- (BOOL) isHologicTomosynthesis;
- (void*) readHologicTomosynthesis: (int) frame;
- (void*) readRawDataFromGroup: (int) group field: (int) field length: (unsigned long*) length;

@end
