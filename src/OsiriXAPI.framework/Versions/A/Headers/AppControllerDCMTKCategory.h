/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>
#import "AppController.h"


/** \brief  AppController category containing DCMTK call
*
* Certain C++ headers from DCMTK conflict with Objective C.
* Putting c++ calls in a category prevents build errors
 */

@interface AppController (AppControllerDCMTKCategory)

- (void)initDCMTK;  /**< Global registration of DCMTK toolkit*/
- (void)destroyDCMTK; /**< Degegister DCMTK*/

@end
