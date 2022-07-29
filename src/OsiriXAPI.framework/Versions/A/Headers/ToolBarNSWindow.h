/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>

/** \brief Window with only a toolbar */
@interface ToolBarNSWindow : NSPanel
{
    BOOL alreadyDisplayedOnce;
    int recursiveOrderOut;
    int recursiveOrderBack;
}
@end
