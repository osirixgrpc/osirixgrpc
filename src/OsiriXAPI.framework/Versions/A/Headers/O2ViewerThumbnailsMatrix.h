/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@interface O2ViewerThumbnailsMatrix : NSMatrix {
    NSPoint draggingStartingPoint;
    NSTimeInterval doubleClick;
    NSCell *doubleClickCell;
    BOOL recomputeCells;
    NSRect *rectsCache;
}

- (void) resetCacheCells;
+ (BOOL)draggingThumbnailCell;
@end

@interface O2ViewerThumbnailsMatrixRepresentedObject : NSObject {
    id _object;
    NSArray* _children;
    int curStudyIndexAll;
}

@property(retain) id object;
@property(retain) NSArray* children;
@property int curStudyIndexAll;
@property BOOL isOpenedStudy;

+ (id)object:(id)object __deprecated;
+ (id)object:(id)object children:(NSArray*)children studyIndex: (int) sI;

@end
