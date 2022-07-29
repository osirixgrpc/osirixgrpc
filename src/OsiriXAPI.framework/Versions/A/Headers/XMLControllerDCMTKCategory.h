/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "XMLController.h"

/** \brief DCMTK calls for xml */

@interface XMLController (XMLControllerDCMTKCategory)


+ (NSString*) dcmFindNameOfUID: (NSString*) string;
+ (int) modifyDicom:(NSArray*) params encoding: (NSStringEncoding) encoding;
+ (int) modifyDicom:(NSArray*) params files: (NSArray*) files encoding: (NSStringEncoding) encoding;
//+ (NSString*) stringForElement: (int) element group: (int) group vr: (NSString*) vrString string: (NSString*) string encoding: (NSStringEncoding) encoding;
- (void) prepareDictionaryArray;
- (int) getGroupAndElementForName:(NSString*) name group:(int*) gp element:(int*) el;

@end
