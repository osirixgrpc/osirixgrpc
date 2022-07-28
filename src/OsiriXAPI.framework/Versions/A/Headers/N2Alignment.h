/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

typedef uint8_t N2Alignment;

#ifdef  __cplusplus
extern "C" {
#endif
    
extern const N2Alignment N2Top;
extern const N2Alignment N2Bottom;
extern const N2Alignment N2Left;
extern const N2Alignment N2Right;

extern NSRect NSRectCenteredInRect(NSRect r, NSRect r2);
extern NSRect NSRectCenteredAndScaledInRect(NSRect smallRect, NSRect bigRect);

extern NSPoint centerOfRect( NSRect rect);
extern double distanceBetweenPoints( NSPoint p1, NSPoint p2);
extern NSPoint upperLeft( NSRect r);
extern NSPoint upperRight( NSRect r);
extern NSPoint lowerLeft( NSRect r);
NSPoint lowerRight( NSRect r);

#ifdef  __cplusplus
}
#endif
