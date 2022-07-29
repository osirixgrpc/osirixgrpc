/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/




#import <Cocoa/Cocoa.h>

/** \brief  Cursors */
@interface NSCursor(DCMCursor) 

+(NSCursor*)zoomCursor;
+(NSCursor*)rotateCursor;
+(NSCursor*)stackCursor;
+(NSCursor*)contrastCursor;
+(NSCursor*)rotate3DCursor;
+(NSCursor*)rotate3DCameraCursor;
+(NSCursor*)bonesRemovalCursor;
+(NSCursor*)crossCursor;
+(NSCursor*)rotateAxisCursor;

@end
