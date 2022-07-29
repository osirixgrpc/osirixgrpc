/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>
#import "MyPoint.h"

#import <OpenGL/CGLMacro.h>

#ifdef __cplusplus
extern "C"
{
#endif
extern int spline( NSPoint *Pt, int tot, NSPoint **newPt, long **correspondingSegmentPt, double scale);
#ifdef __cplusplus
}
#endif

typedef enum ROI_mode_
{
	ROI_sleep = 0,
	ROI_drawing = 1,
	ROI_selected = 2,
	ROI_selectedModify = 3
} ROI_mode;

typedef enum regionCode_
{
    regionCode_None = 0,
    regionCode_percentage,
    regionCode_dB,
    regionCode_cm,
    regionCode_second,
    regionCode_herz,
    regionCode_dbsec,
    regionCode_cmsec,
    regionCode_cm2,
    regionCode_cm2sec,
    regionCode_cm3,
    regionCode_cm3dsec
} regionCode;

// WARNING: If you add or modify this list, check ViewerController.m, DCMView.h and HotKey Pref Pane

typedef enum ToolMode_
{
    tIdle                       =   -1,
    tWL							=	0,
    tTranslate,					//	1
    tZoom,						//	2
    tRotate,					//	3
    tNext,						//	4
    tMesure,					//	5
    tROI,						//	6
	t3DRotate,					//	7
	tCross,						//	8
	tOval,						//	9
	tOPolygon,					//	10
	tCPolygon,					//	11
	tAngle ,					//	12
	tText,						//	13
	tArrow,						//	14
	tPencil,					//	15
	t3Dpoint,					//	16
	t3DCut,						//	17
	tCamera3D,					//	18
	t2DPoint,					//	19
	tPlain,						//	20
	tBonesRemoval,				//	21
	tWLBlended,					//  22
	tRepulsor,					//  23
	tLayerROI,					//	24
	tROISelector,				//	25
	tAxis,						//	26
	tDynAngle,					//	27
	tCurvedROI,					//	28
    tTAGT,                      //  29
    tBall,                      //  30
    tOvalAngle,                 //  31
    tAutoCurvedROI,             //  32
    t3DPosition,                //  33
    tMagicFill                  //  34
} ToolMode;

struct RGBAColor {
    float red;
    float green;
    float blue;
    float alpha;
};
typedef struct RGBAColor RGBAColor;

@class DCMView;
@class DCMPix;
@class StringTexture;
@class DCMObject;
@class DCMUSRegion;

/** \brief Region of Interest
* 
* Region of Interest on a 2D Image:\n
* Types\n
*	tMesure  = line\n
*	tROI = Rectangle\n
*	tOval = Oval\n
*	tOPolygon = Open Polygon\n
*	tCPolygon = Closed Polygon\n
*	tAngle = Angle\n
*	tText = Text\n
*	tArrow = Arrow\n
*	tPencil = Pencil\n
*	t3Dpoint= 3D Point\n
*	t2DPoint = 2D Point\n
*	tPlain = Brush ROI\n
*	tLayerROI = Layer Overlay\n
*	tAxis = Axis\n					
*	tDynAngle = Dynamic Angle\n
*   tTAGT = 2 paralles lines and 1 perpendicular line
*   tBall = 3D Ball
*/

@interface ROI : NSObject <NSCoding, NSCopying>
{
	NSRecursiveLock *roiLock;
	
	int				textureWidth, textureHeight;

	unsigned char   *textureBuffer, *textureBufferSelected;
    
	NSMutableArray *ctxArray;	//All contexts where this texture is used
	NSMutableArray *textArray;	//All texture id

	int				textureUpLeftCornerX,textureUpLeftCornerY,textureDownRightCornerX,textureDownRightCornerY;
	int				textureFirstPoint;
	
	NSMutableArray  *points;
	NSMutableArray  *zPositions;
	NSRect			rect;
    float           zLocation;
	BOOL			_hasIsSpline, _isSpline;
	
	ToolMode		type;
	ROI_mode		mode, previousMode;
	BOOL			needQuartz;
	
	float			thickness;
	
	BOOL			fill;
	float			opacity;
	RGBColor		color;
	
	BOOL			closed,clickInTextBox;
	
	NSString		*name;
	NSString		*comments;
	
	double			pixelSpacingX, pixelSpacingY;
	NSPoint			imageOrigin;
	
	// **** **** **** **** **** **** **** **** **** **** TRACKING
	
    BOOL            mouseOverROI;
	int				PointUnderMouse;
	long			selectedModifyPoint;
	NSPoint			clickPoint, previousPoint, originAnchor;
	
	DCMView			*curView;
	DCMPix			*_pix, *_previousDrawingPix;
	
    NSPoint         cacheSmallDiameter[ 2], cacheLargeDiameter[ 2];
    NSPoint         *cachedNSPoint, cacheVisualCenter;
    long            cachedNSPointSize;
    NSMutableArray  *cachedSplinePoints, *cachedSplinePointsWithoutScale;
    float           previousScaleForSplinePoints;
    
    DCMUSRegion     *rUSRegion;
	float			rmean, rmedian, rmax, rmin, rdev, rtotal, rskewness, rkurtosis, rLength, rLengthPix, rArea, rAreaPix;
	
    NSMutableDictionary *peakValue, *isoContour;
    
	float			mousePosMeasure;
	
	StringTexture	*stringTex;
	NSMutableDictionary	*stanStringAttrib;
	NSCache         *stringTextureCache;
    
	ROI*			parentROI;
	
	NSRect			drawRect;
	
	float			offsetTextBox_x, offsetTextBox_y;
	
	NSString		*textualBoxLine1, *textualBoxLine2, *textualBoxLine3, *textualBoxLine4, *textualBoxLine5, *textualBoxLine6, *textualBoxLine7, *textualBoxLine8, *textualBoxLine9, *textualBoxLine10;
	
	BOOL			_displayCalciumScoring;
	int				_calciumThreshold;
	double			_sliceThickness;
	int				_calciumCofactor;
	
	NSString		*layerReferenceFilePath;
	NSImage			*layerImage;//, *layerImageWhenSelected;
	NSData			*layerImageJPEG;//, *layerImageWhenSelectedJPEG;
	float			layerPixelSpacingX, layerPixelSpacingY;
    NSSize          layerImageTextureSize;
	BOOL			isLayerOpacityConstant;
	BOOL			canColorizeLayer, canResizeLayer;
	NSColor			*layerColor;
	
    NSString        *UUID;           // saved
	NSNumber		*uniqueID;		// <- not saved, only valid during the 'life' of a ROI
	NSTimeInterval	groupID;		// timestamp of a ROI group. Grouped ROI will be selected/deleted together.
	
	BOOL			displayTextualData;
	BOOL			displayCMOrPixels;
	
	BOOL			locked;
	BOOL			selectable;
	BOOL			isAliased;
	int				originalIndexForAlias;
    
    BOOL            hidden;
    
	StringTexture   *stringTexA, *stringTexB, *stringTexC;
    
    NSString        *savedStudyInstanceUID;
    
    BOOL            is3DROI;
    
    float           ovalAngle1, ovalAngle2;
    float           roiRotation;
    
    float           localFontHeight, localFontSize;
    NSString        *localFontName;
    
    NSPoint         arh1, arh2, arh3;
    
    NSMutableArray  *stringTags; // An array containing a list of NSStrings : store private strings in this array
    BOOL            dontDisplayInKeyImagesWindow;
    
    float           preferredWL, preferredWW;
    BOOL            dontSavePreferredWLWW;
    
    NSTimeInterval           creationTimeStamp;
    BOOL observersAdded;
    BOOL is3DMeasure;
    
    NSDate *creationDate;
    NSDate *modificationDate;
    NSString *username;
    
    BOOL textNameOnly;
    
    NSMutableArray *texturesToDeleteAfterFlush;
    
    NSPoint magicFillPt1, magicFillPt2;
}

@property(retain,nonatomic) NSDate *creationDate, *modificationDate;
@property float roiRotation;
@property NSPoint imageOrigin;
@property(readonly) NSMutableArray *texturesToDeleteAfterFlush;
@property(readonly) int textureWidth, textureHeight;
@property(readonly) NSTimeInterval creationTimeStamp;
@property(readonly) int textureDownRightCornerX,textureDownRightCornerY, textureUpLeftCornerX, textureUpLeftCornerY;
@property(readonly) unsigned char *textureBuffer;
@property(nonatomic) float opacity, zLocation;
@property(nonatomic) int originalIndexForAlias;
@property(nonatomic) BOOL hidden, locked, selectable, is3DROI;
@property BOOL isAliased, displayCMOrPixels, mouseOverROI, dontDisplayInKeyImagesWindow, fill, is3DMeasure, textNameOnly;
@property(nonatomic, copy) NSString *name, *localFontName;
@property(retain,nonatomic) NSString *comments, *UUID, *username;
@property(retain) NSNumber *uniqueID;
@property ToolMode type;
@property(nonatomic, setter=setROIMode:) ROI_mode ROImode;
@property(readonly) NSMutableArray *zPositions, *stringTags;
@property BOOL clickInTextBox;
@property(nonatomic, setter=setROIRect:) NSRect rect; // To create a Rectangular ROI (tROI) or an Oval ROI (tOval) or a 2DPoint
@property(nonatomic, retain) DCMPix *pix; // The DCMPix associated to this ROI
@property(assign, nonatomic) DCMView *curView;  // The DCMView associated to this ROI
@property float mousePosMeasure;
@property(readonly) NSData *data;
@property(readonly) NSString *savedStudyInstanceUID;
@property(nonatomic, setter=setColor:) RGBColor rgbcolor;
@property(nonatomic) float thickness;
@property(retain) ROI *parentROI;
@property double sliceThickness, pixelSpacingX, pixelSpacingY;
@property (nonatomic) float min, max, mean, median, dev, skewness, kurtosis, total, length, area, lengthPix, areaPix;
@property(assign) NSColor* NSColor;
@property(assign) BOOL isSpline;
@property(readonly) NSMutableDictionary *peakValue, *isoContour;
@property float offsetTextBox_x, offsetTextBox_y, localFontHeight, localFontSize, preferredWL, preferredWW;
@property BOOL dontSavePreferredWLWW;
@property(retain) ROI *magicROI;

+ (id) unarchiveObjectWithData: (NSData*) d;
+ (id) unarchiveObjectWithFile: (NSString*) d;

+ (NSNumberFormatter*) fmt3d;
+ (NSNumberFormatter*) fmt2d;
+ (NSNumberFormatter*) fmt1d;

- (void) setNSColor:(NSColor*)color globally:(BOOL)g;
- (void) setColor:(RGBColor) a globally: (BOOL) g;
- (void) setThickness:(float) a globally: (BOOL) g;
- (void) setOpacity:(float)newOpacity globally: (BOOL) g;
- (void) addPointUnderMouse: (NSPoint) pt scale:(float) scale;

- (BOOL) isEqualToROI: (ROI*) r;

/** Set default ROI name (if not set, then default name is the currentTool) */
+ (void) setDefaultName:(NSString*) n;
/** Return the default name */
+ (NSString*) defaultName;
+ (void) setFontHeight: (float) f;
+ (float) fontHeight;

+ (NSPoint) segmentDistToPoint: (NSPoint) segA :(NSPoint) segB :(NSPoint) p;
+ (BOOL) isBetween: (NSPoint) a :(NSPoint) b :(NSPoint) c;

- (void) newUID;
- (void) setDefaultName:(NSString*) n;
- (NSString*) defaultName;
- (BOOL) isValidForVolume;
- (void) updateLabelFont;
- (void) prepareForRelease;
- (void) resetCache;
- (NSMutableArray *) roiList;
- (BOOL) invertBrushROI;
+ (BOOL) splineForROI;
- (NSRect) boundRect;
- (void) setPoints: (NSArray*) pts;
- (NSMutableArray*) points;
- (NSArray*) pointsIn3DCoordinates;

/** Load User Defaults */
+(void) loadDefaultSettings;

/** Save User Defaults */
+(void) saveDefaultSettings;

/** Create a new ROI, needs the current pixel resolution and image origin
* @param itype ROI Type
* @param ipixelSpacing  Assumes pixel size is same in both x and y
* @param iimageOrigin  Origin on image
*/
- (id) initWithType: (long) itype :(float) ipixelSpacing :(NSPoint) iimageOrigin;
- (id) initWithType: (long) itype inView: (DCMView*) v;
+ (id) roiWithType: (long) itype inView: (DCMView*) v;
+ (id) roiWithTexture: (unsigned char*)tBuff rect:(NSRect) rect inView:(DCMView *)v;

/** Create a new ROI, needs the current pixel resolution  x and y and image origin* @param itype ROI Type
* @param ipixelSpacingx  Pixel width
* @param ipixelSpacingy  Pixel height
* @param iimageOrigin  Origin on image
* @param dcmPix  associated DCMPix
* @param dcmView  associated DCMView
*/
- (id) initWithType: (long) itype :(float) ipixelSpacingx :(float) ipixelSpacingy :(NSPoint) iimageOrigin;
- (id) initWithType: (long) itype pixelSpacingX:(float) ipixelSpacingx pixelSpacingY:(float) ipixelSpacingy origin:(NSPoint) iimageOrigin dcmPix: (DCMPix*) p dcmView: (DCMView*) v;

/** arg: specific methods for tPlain roi 
* @param tBuff  Pointer to the texture buffer
* @param tWidth Texture width
* @param tHeight Texture height
* @param tName ROI Name
* @param posX Origin.x of texture upper left corner
* @param posY Origin.y of texture upper left corner
* @param ipixelSpacingx  Pixel width
* @param ipixelSpacingy  Pixel height 
* @param iimageOrigin  Origin on image
*/
- (id) initWithTexture: (unsigned char*)tBuff  textWidth:(int)tWidth textHeight:(int)tHeight textName:(NSString*)tName
			 positionX:(int)posX positionY:(int)posY
			  spacingX:(float) ipixelSpacingx spacingY:(float) ipixelSpacingy imageOrigin:(NSPoint) iimageOrigin;



/** Set offset for text box */
- (void) setTextBoxOffset:(NSPoint) o;


/** Prints info about texture to output */
- (void)displayTexture;

/** Set resolution and origin associated to the ROI */
- (void) setOriginAndSpacing :(float) ipixelSpacing :(NSPoint) iimageOrigin;

/** Set resolution and origin associated to the ROI */
- (void) setOriginAndSpacing :(float) ipixelSpacingx :(float) ipixelSpacingy :(NSPoint) iimageOrigin;

/** Set resolution and origin associated to the ROI */
- (void) setOriginAndSpacing :(float) ipixelSpacingx :(float) ipixelSpacingy :(NSPoint) iimageOrigin :(BOOL) sendNotification;

/** Set resolution and origin associated to the ROI */
- (void) setOriginAndSpacing :(float) ipixelSpacingx :(float) ipixelSpacingy :(NSPoint) iimageOrigin :(BOOL) sendNotification :(BOOL) inImageCheck;

/** Compute the geometric centroid in pixel space */
- (NSPoint) centroid;

/**  Compute the length for between two points in cm */
-(float) LengthInCm:(NSPoint) ptA to:(NSPoint) ptB;
+(float) LengthInCmFrom:(NSPoint) ptA to:(NSPoint) ptB spacingX: (double) px spacingY: (double) py;
+(float) LengthInPixelsFrom:(NSPoint) ptA to:(NSPoint) ptB;
+(float) LengthFrom:(NSPoint) ptA to:(NSPoint) ptB spacingX: (double) px spacingY: (double) py;

/** Deprecated functions **/
-(float) MesureLength:(float*) pixels pointA: (NSPoint) a pointB: (NSPoint) b __deprecated;
-(float) MesureLength:(float*) pixels __deprecated;
-(float) Length:(NSPoint) mesureA :(NSPoint) mesureB __deprecated;
-(float) LengthFrom:(NSPoint) mesureA to:(NSPoint) mesureB inPixel: (BOOL) inPixel __deprecated;

/** Compute an angle between 2 lines */
- (float) Angle:(NSPoint) p2 :(NSPoint) p1 :(NSPoint) p3;

- (float*) dataValuesAsFloatPointer :(long*) no;
- (NSMutableArray*) dataValues;
- (void) computeROIIfNedeed;

-(NSPoint)pointAtIndex:(NSUInteger)index;
-(void)setPoint:(NSPoint)point atIndex:(NSUInteger)index;
-(void)addPoint:(NSPoint)point;

- (NSDictionary*) representationIn3D;
- (id) initWith3DRepresentation:(NSDictionary*) d inView: (DCMView*) v;

/** Find a point between two points 
*  @param a First point
*  @param b Second point
*  @param r Weighting bewtween the two points
*/
+ (NSPoint) pointBetweenPoint:(NSPoint) a and:(NSPoint) b ratio: (float) r;

+ (NSMutableArray*)resamplePoints:(NSArray*)points number:(int)no;
+ (NSMutableArray*)resamplePoints:(NSArray*)points number:(int)no closeROI:(BOOL)closeROI;

+ (NSString*) formattedLengthForCM: (float) lCm;

/** Update ROI on mouse down. For most rois this will be the origin of the ROI */
- (BOOL)mouseRoiDown:(NSPoint)pt :(int)slice :(float)scale;

/** Update ROI on mouse down in the current image. For most rois this will be the origin of the ROI */
- (BOOL) mouseRoiDown:(NSPoint) pt :(float) scale;

/** Move the ROI */
- (void) roiMove:(NSPoint) offset;

/** Move the ROI */
- (void) roiMove:(NSPoint) offset :(BOOL) sendNotification;

/** Modify roi as mouse is dragged */
- (BOOL) mouseRoiDragged:(NSPoint) pt :(unsigned int) modifier :(float) scale;

/** Modify roi on mouse up */
- (BOOL) mouseRoiUp:(NSPoint) pt;
- (BOOL) mouseRoiUp:(NSPoint) pt scaleValue: (float) scaleValue;

/** Returns YES if roi is valid */
- (BOOL) valid; // YES, if drawing
- (BOOL) isValid;

+ (void) deleteROIs: (NSArray*) array postNotification: (BOOL) postNotification;
+ (void) deleteROIs: (NSArray*) array;
+ (void) deleteROI: (ROI*) r;

- (BOOL) writeToFile:(NSString*) file;
+ (ROI*) readFromFile:(NSString*) file;

/** Draw the ROI */
- (void) drawROI :(float) scaleValue :(float) offsetx :(float) offsety :(float) spacingx :(float) spacingy;
- (void) drawROIWithScaleValue:(float)scaleValue offsetX:(float)offsetx offsetY:(float)offsety pixelSpacingX:(float)spacingX pixelSpacingY:(float)spacingY highlightIfSelected:(BOOL)highlightIfSelected thickness:(float)thick prepareTextualData:(BOOL) prepareTextualData;

/** Always returns NO */
- (BOOL) needQuartz;

/** Delete the current selected point */
- (BOOL) deleteSelectedPoint;

/** The info displayed in the text box */
- (NSMutableDictionary*) dataString;

/** Set the associated view */
- (void) setRoiView:(DCMView*) v __deprecated;

/** Draw a NSString in OpenGL */
- (void) glStr: (NSString*) str :(float) x :(float) y :(float) line;

/** Recompute */
- (void) recompute;

/** Rotate the ROI */
- (void) rotate: (float) angle :(NSPoint) center;

/** Flip the ROI vertically or horizontally */
- (void) flipVertically: (BOOL) vertically;

/** Test to see if ROI can be resized */
- (BOOL)canResize;

/** Resize ROI */
- (void) resize: (float) factor :(NSPoint) center;

/** Test to see if texture can be reduced */
- (BOOL) reduceTextureIfPossible;

/** Merge two brush ROI together */
- (void) mergeWithTexture: (ROI*) r;

/** Add a margin to the buffer */
- (void) addMarginToBuffer: (int) margin;

/** Draw text box for ROI */
- (void) drawTextualData;

/** is Spline rendered ? */
- (BOOL)isSpline;

/** area in mm2, deprecated: prefer property area */
- (float) roiArea __deprecated;

/** Description of elements contained in <-(NSString*) description>, separated by \t (tab) */
+ (NSString*) descriptionHeader;
+ (NSString*) stringTypeForROI: (int) i;
- (NSString*) niceDescription;
- (NSString*) textualForLens;

- (void) purgeTexturesAfterFlush;
- (void) applySettingsToParent;
- (void) applySettingsFromParent;
- (BOOL) isPointInside: (NSPoint) pixelCoordinates;
- (BOOL) isInside: (int*) pixelCoordinates;
- (BOOL) isInside: (int*) pixelCoordinates :(float) sliceInterval;
- (BOOL) containBallROI: (DCMView*) view pixelCoordinates: (double*) pixelCoordinates radius: (double*) radius;
- (BOOL) containBallROIInPix: (DCMPix*) inPix pixelCoordinates: (double*) pixelCoordinates radius: (double*) radius;
- (ROI*) ovalROIFromBallAtPix: (DCMPix*) p;
- (unsigned char*) getMapSize:(NSSize*) size origin:(NSPoint*) ROIorigin;
- (ROI*) getBrushROI;
- (ROI*) getBrushROIwithMinimum: (float) minimum maximum : (float) maximum dcmPix: (DCMPix*) inPix;
- (void) computeAndDrawDiameterAgainst: (ROI*) otherROI scaleValue: (float) scaleValue offsetX: (float) offsetx offsetY: (float) offsety;

/** Test to see if point is in text box or ROI and returns the mode. 
* Can be ROI_Selected or ROI_selectedModify if hit test is YES 
*/
- (long) clickInROI:(NSPoint) pt :(float) offsetx :(float) offsety :(float) scale :(BOOL) testDrawRect;
- (long) clickInROI:(NSPoint) pt :(float) offsetx :(float) offsety :(float) scale :(BOOL) testDrawRect radius: (float) NEIGHBORHOODRADIUS;
- (NSPoint) ProjectionPointLine: (NSPoint) Point :(NSPoint) startPoint :(NSPoint) endPoint;

/** Delete texture */
- (void) deleteTexture:(NSOpenGLContext*) c;
- (void) textureBufferHasChanged;

/** Set cab resize layer */
- (void) setCanResizeLayer:(BOOL)boo;
// Calcium Scoring
/** Cofactor for Calcium Score 
*	Cofactor values used by Agaston.  
*	Using a threshold of 90 rather than 130. Assuming
*	multislice CT rather than electron beam.
*	We could have a flag for Electron beam rather than multichannel CT
*	and use 130 as a cutoff
*   Based on Hounsfield density of Calcium
*/
- (int)calciumScoreCofactor;
/** Calcium score 
* roi Area * cofactor;  area is is mm2.
*plainArea is number of pixels 
*/
- (float)calciumScore;

/** Calcium volume 
* area * thickness
*/
- (float)calciumVolume;

/** Calcium mass
* Volume * mean CT Density / 250 
 */
- (float)calciumMass;

@property BOOL displayCalciumScoring;
@property int calciumThreshold;

@property(retain) NSString *layerReferenceFilePath;
@property(nonatomic, retain) NSImage *layerImage;
@property float layerPixelSpacingX, layerPixelSpacingY;

- (GLuint)loadLayerImageTexture;
- (void)generateEncodedLayerImage;
- (BOOL)isPoint:(NSPoint)point inRectDefinedByPointA:(NSPoint)pointA pointB:(NSPoint)pointB pointC:(NSPoint)pointC pointD:(NSPoint)pointD;
- (NSPoint)rotatePoint:(NSPoint)point withAngle:(float)alpha aroundCenter:(NSPoint)center;
- (void) displayPointUnderMouse:(NSPoint) pt :(float) offsetx :(float) offsety :(float) scale;

@property(retain) NSString *textualBoxLine1, *textualBoxLine2, *textualBoxLine3, *textualBoxLine4, *textualBoxLine5, *textualBoxLine6, *textualBoxLine7, *textualBoxLine8, *textualBoxLine9, *textualBoxLine10;
- (NSArray*) textualBoxLines;

@property NSTimeInterval groupID;


/** Lower right point of ROI */
- (NSPoint) lowerRightPoint;

@property(nonatomic) BOOL isLayerOpacityConstant;
@property(nonatomic) BOOL canColorizeLayer;
@property BOOL displayTextualData;
@property(readonly) NSPoint clickPoint;

-(NSMutableArray*) splinePoints;
-(NSMutableArray*) splinePoints:(float) scale;
-(NSMutableArray*) splinePoints:(float) scale correspondingSegmentArray: (NSMutableArray**) correspondingSegmentArray;
-(NSMutableArray*) splineZPositions;

- (void) setTexture: (unsigned char*) t width: (int) w height:(int) h;
@end
