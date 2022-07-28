/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "DCMView.h"
#import "CPRMPRDCMView.h"

enum _CPRTransverseViewReformationDisplayStyle { 
    CPRTransverseViewStraightenedReformationDisplayStyle = 0,
    CPRTransverseViewStretchedReformationDisplayStyle = 1,
};
typedef NSInteger CPRTransverseViewReformationDisplayStyle;

// horrible name! rename me!
enum _CPRTransverseViewSectionType { 
    CPRTransverseViewNoneSectionType = -1,
    CPRTransverseViewCenterSectionType = 0,
    CPRTransverseViewLeftSectionType,
    CPRTransverseViewRightSectionType
};
typedef NSInteger CPRTransverseViewSection;

@class CPRCurvedPath;
@class CPRDisplayInfo;
@class CPRVolumeData;
@class CPRObliqueSliceGeneratorRequest;
@class StringTexture;

@interface CPRTransverseView : DCMView {
    id<CPRViewDelegate> _delegate;

    CPRCurvedPath *_curvedPath;
    CPRDisplayInfo *_displayInfo;
    CPRTransverseViewSection _sectionType;
    CGFloat _sectionWidth;
    
    CPRVolumeData *_volumeData;
    CPRVolumeData *_generatedVolumeData;
    
    CPRObliqueSliceGeneratorRequest *_lastRequest;
    BOOL _processingRequest;
    BOOL _needsNewRequest;
	
	BOOL displayCrossLines;
	CPRTransverseViewReformationDisplayStyle _reformationDisplayStyle;
    
	CGFloat _renderingScale;
	
	float previousScale;
	
	NSMutableDictionary *stanStringAttrib;
	StringTexture *stringTex;
}

@property (nonatomic, readwrite, assign) id<CPRViewDelegate> delegate;
@property (nonatomic, readwrite, copy) CPRCurvedPath* curvedPath;
@property (nonatomic, readwrite, copy) CPRDisplayInfo *displayInfo;
@property (nonatomic, readwrite, assign) CPRTransverseViewSection sectionType;
@property (nonatomic, readwrite, assign) CGFloat sectionWidth; // the width to be displayed in mm
@property (nonatomic, readwrite, retain) CPRVolumeData *volumeData;
@property (nonatomic, readwrite, assign) CGFloat renderingScale;
@property (nonatomic, readwrite, assign) BOOL displayCrossLines;

@property (nonatomic, readwrite, assign) CPRTransverseViewReformationDisplayStyle reformationDisplayStyle;

- (float) pixelsPerMm;

@end
