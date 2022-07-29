/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <Accelerate/Accelerate.h>

#define ORIENTATION_SENSIBILITY 0.001
#define SLICEINTERVAL_SENSIBILITY 0.5

typedef struct {
   double x,y,z;
} XYZ;

struct NSPointInt
{
    long x;
    long y;
};
typedef struct NSPointInt NSPointInt;

#ifdef __cplusplus
extern "C"
{
#endif /*cplusplus*/
    extern XYZ ArbitraryRotate(XYZ p,double theta,XYZ r);
    extern void ras_FillPolygon( NSPointInt *p, long no, float *pix, long w, long h, long s, float min,float max,BOOL outside,float newVal,BOOL addition,BOOL RGB,BOOL compute,float *imax,float *imin,long *count,float *itotal,float *idev,float imean,long orientation,long stackNo,BOOL restore,float *values,float *locations);
    extern void CLIP_Polygon(NSPointInt *inPoly, long inCount, NSPointInt *outPoly, long *outCount, NSPoint clipMin, NSPoint clipMax);
#ifdef __cplusplus
}
#endif /*cplusplus*/


@class ROI;
@class ThickSlabController;
@class DCMObject;
@class Point3D;
@class DicomImage;
@class DicomSeries;
@class DicomStudy;
@class DCMWaveform;
@class DCMTKFileFormat;

/** \brief Represents an image for display */

@interface DCMPix: NSObject <NSCopying>
{
	NSString            *sourceFile, *URIRepresentationAbsoluteString, *imageType, *decryptedFile;
	BOOL				isBonjour, fileTypeHasPrefixDICOM, isSigned;
    int                 numberOfFrames;
    int                 originalPhotoInterpret;
    
	NSArray				*pixArray;
    NSManagedObjectID	*imageObjectID;	/**< Core data object ID for image */
	float				*fImage /**< float buffer of image Data */, *fExternalOwnedImage;  /**< float buffer of image Data - provided by another source, not owned by this object, not release by this object */
	
//DICOM TAGS

//	orientation
	BOOL				isOriginDefined, patientOrientationComputed;
	double				originX /**< x position of image origin */ , originY /**< y Position of image origin */ , originZ /**< Z position of image origin*/;
	double				orientation[ 9], patientOrientationVector[ 9];  /**< pointer to orientation vectors  */

//	pixel representation
	short				bitsAllocated, bitsStored, highBit;
    long                height, width;
    float               slope, offset;
    float               realWorldSlope, realWorldOffset;
    
//	window level & width
	float				savedWL, savedWW;
    NSMutableDictionary *savedWLWWDict;

//	planar configuration
	long				planarConf;
    double				pixelSpacingX, pixelSpacingY, pixelRatio, estimatedRadiographicMagnificationFactor;
	BOOL				pixelSpacingFromUltrasoundRegions, dontCorrectMagnification;

// RT DOSE
    double              doseGridScaling;
    NSString            *doseUnit, *doseType;
    
//	photointerpretation
	BOOL				isRGB, inverseVal;

//  US Regions
    NSMutableArray      *usRegions;
    
//  Waveform data
    DCMWaveform         *waveform;
    
//--------------------------------------

// DICOM params needed for SUV calculations
    NSString            *patientsSex;
	float				patientsWeight, patientsSize, repetitionTime, diffusionbvalue, echoTime, flipAngle;
	NSString			*laterality, *viewPosition, *patientPosition, *acquisitionDate, *SOPClassUID, *frameofReferenceUID, *rescaleType, *bodyPartExamined;
	BOOL				hasSUV, SUVConverted, SULConverted, displaySUVValue;
	NSString			*units, *decayCorrection;
	float				factorPET2SUV, radionuclideTotalDose, radionuclideTotalDoseCorrected;
	NSCalendarDate		*acquisitionTime, *radiopharmaceuticalStartTime;
	float				halflife, frameReferenceTime, philipsFactor;

#define MaxNumOfOverlays 10
// DICOM params for Overlays - 0x60XX group
	int					oRows[ MaxNumOfOverlays], oColumns[ MaxNumOfOverlays], oType[ MaxNumOfOverlays], oOrigin[ MaxNumOfOverlays][ 2], oBits[ MaxNumOfOverlays], oBitPosition[ MaxNumOfOverlays];
    int                 oImageFrameOrigin[ MaxNumOfOverlays], oNumberOfFramesInOverlay[ MaxNumOfOverlays];
	unsigned char		*oData[ MaxNumOfOverlays];
	
//	DSA-subtraction	
	float				*subtractedfImage;
	NSPoint				subPixOffset, subMinMax;
	float				subtractedfPercent, subtractedfZ, subtractedfZero, subtractedfGamma;
	GammaFunction		subGammaFunction;
	
	long				maskID;
	float				maskTime, fImageTime;
	
    BOOL                shutterEnabled;
    NSRect              shutterRect;
	NSPoint             shutterCircular;
	long				shutterCircular_radius;
	
	NSPoint	 			*shutterPolygonal;
	long				shutterPolygonalSize;

//-------------------------------------------------------	
	long				frameNo, serieNo, imID, imTot;
    char                *baseAddr;

//convolution	
	BOOL				convolution, updateToBeApplied;
	short				kernelsize;
	float				normalization, kernel[25];
    
	float				cineRate, nominalInterval, triggerTime;

//slice
    double				sliceInterval, sliceLocation, sliceThickness, spacingBetweenSlices;
	
//stack
	short				stack, stackMode, pixPos, stackDirection;
//thickslab
    BOOL				thickSlabVRActivated;
	ThickSlabController *thickSlab;
	
	float				countstackMean;
    float				ww, wl;
	float				fullww, fullwl;
	BOOL				fixed8bitsWLWW;	
    float               maxValueOfSeries, minValueOfSeries;
	
	BOOL				generated;
    NSString			*generatedName;
	NSRecursiveLock		*checking;
	
	BOOL				notAbleToLoadImage, VOILUTApplied;
    
    NSMutableArray      *VOILUT_tables;
	
	char				blackIndex;
	
	NSData				*transferFunction;
	float				*transferFunctionPtr;
	
/** custom annotations */
	NSMutableDictionary *annotationsDictionary, *annotationsDBFields;
    NSString            *yearOld, *yearOldAcquisition;
	
/** 12 bit monitors */
	BOOL				isLUT12Bit;
	unsigned char		*LUT12baseAddr;
	
	BOOL				needToCompute8bitRepresentation;

/** Papyrus Loading variables */	
	
	NSString			*modalityString, *studyInstanceUID, *patientOrientation;
	unsigned short      *shortRed, *shortGreen, *shortBlue;
	unsigned short		clutEntryR, clutEntryG, clutEntryB;
	unsigned short		clutDepthR, clutDepthG, clutDepthB;
	unsigned char		*clutRed, *clutGreen, *clutBlue;
	BOOL				fSetClut, fSetClut16;
	
	int					savedHeightInDB, savedWidthInDB;
	
	id					retainedCacheGroup;
    
    BOOL                isHologic;
    
    BOOL                sigmoidVOILUT;
    
// Ophtalmic fundus images
    
    NSString            *referencedSOPInstanceUID;
    float               referenceCoordinates[ 4];
    
    BOOL                RGBAlphaMaskComputed;
    
    NSRect              contentFrameRect; // computeCTFrameRect
    
    NSTimeInterval      studyDuration, seriesDuration;
}

@property BOOL inverseVal;
@property long frameNo;
@property NSRect contentFrameRect;
@property (setter=setID:) long ID;
@property (readonly) NSRecursiveLock *checking;
@property (nonatomic) float minValueOfSeries, maxValueOfSeries, factorPET2SUV;
@property (retain, nonatomic) NSString *modalityString, *studyInstanceUID, *patientOrientation, *decryptedFile;
@property (retain) NSString* imageType, *referencedSOPInstanceUID, *yearOld, *yearOldAcquisition, *bodyPartExamined;
@property NSTimeInterval studyDuration, seriesDuration;

// Dimensions in pixels
@property (nonatomic) long pwidth, pheight;

/** Is it an RGB image (ARGB) or float image?
Note setter is different to not break existing usage. :-( */
@property(nonatomic, setter=setRGB:) BOOL isRGB;  

/** Pointer to image data */
@property(setter=setfImage:) float* fImage;

/** WW & WL */
@property(readonly) short bitsAllocated;
@property(readonly) float ww, wl, fullww, fullwl;
@property(nonatomic) float slope, offset, realWorldSlope, realWorldOffset, savedWW, savedWL, *subtractedfImage;

@property(readonly) BOOL notAbleToLoadImage, VOILUTApplied;
@property(readonly) NSPoint *shutterPolygonal;

/**  X/Y ratio - non-square pixels */
@property(nonatomic) double pixelRatio;

/**  pixel size */
@property double pixelSpacingX, pixelSpacingY;

- (BOOL) identicalOrientationTo:(DCMPix*) c;

- (void)orientationDouble:(double*) c;
- (void)setOrientationDouble:(double*) c;
- (void)orientationFromPatientOrientation:(float*) o;

/** Slice location */
@property(readonly) double originX, originY, originZ;
@property(readonly) BOOL isOriginDefined;
@property(retain) NSString *frameofReferenceUID;

- (void)setOrigin :(float*) o;
- (void)setOriginDouble :(double*) o;
- (void)origin: (float*)o;
- (void)originDouble: (double*)o;

/**  Axial Location */
@property(nonatomic) double sliceLocation, sliceThickness, sliceInterval, spacingBetweenSlices;

/**  8-bit TransferFunction */
@property(nonatomic, retain) NSData *transferFunction; 

@property(nonatomic) NSPoint subPixOffset;

@property(nonatomic) BOOL shutterEnabled;
@property(nonatomic) NSRect shutterRect;

@property float repetitionTime, echoTime, diffusionbvalue, flipAngle;
@property(readonly) NSString *laterality, *viewPosition, *patientPosition;

@property char* baseAddr;
@property unsigned char* LUT12baseAddr;

@property(readonly) long serieNo;
@property(readonly) NSArray *pixArray;
@property(readonly) float *transferFunctionPtr;
@property short pixPos;
@property short stackDirection;
@property float countstackMean;

@property(getter=Tot, setter=setTot:) long Tot;

@property(readonly) short stack, stackMode;
@property BOOL generated;
@property(retain) NSString *generatedName;
@property(retain) NSString *sourceFile, *doseUnit, *doseType;
@property double doseGridScaling;

@property(readonly) NSArray *VOILUT_tables;

/** Database links */
@property(retain) NSManagedObjectID *imageObjectID;
@property(retain) NSString *SOPClassUID;
@property(retain) NSMutableDictionary *annotationsDictionary, *annotationsDBFields;

// Properties (aka accessors) needed for SUV calculations
@property(readonly) float philipsFactor;
@property float patientsWeight, patientsSize, halflife, radionuclideTotalDose, radionuclideTotalDoseCorrected;
@property(retain) NSCalendarDate *acquisitionTime;
@property(retain) NSString *acquisitionDate, *rescaleType, *patientsSex;
@property(retain) NSCalendarDate *radiopharmaceuticalStartTime;
@property BOOL SUVConverted, SULConverted, needToCompute8bitRepresentation;
@property(readonly) BOOL hasSUV;
@property(nonatomic)float nominalInterval, triggerTime;
@property(retain) NSString *units, *decayCorrection;
@property BOOL displaySUVValue;
@property BOOL isLUT12Bit;

// Waveform
@property(readonly,retain) DCMWaveform* waveform;

// US Regions
@property(readonly) NSMutableArray *usRegions;
-(BOOL) hasUSRegions;

- (float) appliedFactorPET2SUV;
- (void) copySUVfrom: (DCMPix*) from;  /**< Copy the SUV from another DCMPic */
- (float) getPixelValueX: (long) x Y:(long) y;  /**< Get the pixel for a point with x,y coordinates */

- (void) checkSUV; /**< Makes sure all the necessary values for SUV calculation are present */
+ (float) LBMSize:(float) sizeInCm weight:(float) weight sex:(NSString*) sex;
- (float) LBM; /**< lean body mass */
- (float) SULFactor;

+ (void) checkUserDefaults: (BOOL) update;  /**< Check User Default for needed setting */
+ (void) resetUserDefaults;  /**< Reset the defaults */
 /** Determine if a point is inside a polygon
 * @param x is the NSPoint to check. 
 * @param  poly is a pointer to an array of NSPoints. 
 * @param count is the number of 
 * points in the polygon.
*/
+ (BOOL) IsPoint:(NSPoint) x inPolygon:(NSPoint*) poly size:(int) count; 

- (void) compute8bitRepresentation;
- (void) changeWLWW:(float)newWL :(float)newWW;  /**< Change window level to window width to the new values */
- (void) computePixMinPixMax;  /**< Compute the min and max values in the image */

#ifdef OSIRIX_VIEWER

// Compute ROI data
/** Calculates the cofactor used Calcium scoring.
 * Depends on the threshold used for scoring
 * Threshold is usually 90 or 120 depending on whether the source is
 * Electron Beam or Multislice CT
 */
- (int)calciumCofactorForROI:(ROI *)roi threshold:(int)threshold;

/** returns calculated values for ROI:
*  mean, total, deviation, min, max
*/
- (void) computeROI:(ROI*) roi :(float *)mean :(float *)median :(float *)total :(float *)dev :(float *)min :(float *)max :(float *)skewness :(float*) kurtosis;
- (void) computeROI:(ROI*) roi :(float *)mean :(float *)total :(float *)dev :(float *)min :(float *)max :(float*) skewness :(float*) kurtosis;
- (void) computeROI:(ROI*) roi :(float *)mean :(float *)total :(float *)dev :(float *)min :(float *)max;

- (void) computeBallROI:(ROI*) roi :(float*) mean :(float *)total :(float *)dev :(float *)min :(float *)max :(float *)skewness :(float*) kurtosis;
- (void) computeBallROI:(ROI*) roi :(float*) mean :(float *)total :(float *)dev :(float *)min :(float *)max :(float *)skewness :(float*) kurtosis :(NSMutableDictionary*) peakValue :(NSMutableDictionary*) isoContour;
- (void) computeBallROI:(ROI*) roi :(float*) mean :(float*)median :(float *)total :(float *)dev :(float *)min :(float *)max :(float *)skewness :(float*) kurtosis :(NSMutableDictionary*) peakValue :(NSMutableDictionary*) isoContour;

/** Fill a ROI with a value
* @param roi  Selected ROI
* @param newVal  The replacement value
* @param minValue  Lower threshold
* @param maxValue Upper threshold
* @param outside  if YES replace outside the ROI
* @param orientationStack  
* @param stackNo  
* @param restore  
* @param addition  
*/
- (void) fillROI:(ROI*) roi newVal :(float) newVal outside :(BOOL) outside;
- (void) fillROI:(ROI*) roi newVal:(float) newVal minValue:(float) minValue maxValue:(float) maxValue outside:(BOOL) outside orientationStack:(long) orientationStack stackNo:(long) stackNo restore:(BOOL) restore addition:(BOOL) addition;
- (void) fillROI:(ROI*) roi newVal:(float) newVal minValue:(float) minValue maxValue:(float) maxValue outside:(BOOL) outside orientationStack:(long) orientationStack stackNo:(long) stackNo restore:(BOOL) restore addition:(BOOL) addition spline:(BOOL) spline;
- (void) fillROI:(ROI*) roi newVal :(float) newVal minValue :(float) minValue maxValue :(float) maxValue outside :(BOOL) outside orientationStack :(long) orientationStack stackNo :(long) stackNo restore :(BOOL) restore addition:(BOOL) addition spline:(BOOL) spline clipMin: (NSPoint) clipMin clipMax: (NSPoint) clipMax;

/** Fill a ROI with a value
* @param roi  Selected ROI
* @param newVal  The replacement value
* @param minValue  lower threshold
* @param maxValue  upper threshold
* @param outside  if YES replace outside the ROI
* @param orientationStack  ?
* @param  stackNo  
* @param  restore  
*/
- (void) fillROI:(ROI*) roi :(float) newVal :(float) minValue :(float) maxValue :(BOOL) outside :(long) orientationStack :(long) stackNo :(BOOL) restore;

/** Fill a ROI with a value
* @param roi  Selected ROI
* @param newVal  The replacement value
* @param minValue  lower threshold
* @param maxValue  upper threshold
* @param outside  if YES replace outside the ROI
* @param orientation  
* @param stackNo   
*/
- (void) fillROI:(ROI*) roi :(float) newVal :(float) minValue :(float) maxValue :(BOOL) outside :(long) orientation :(long) stackNo;

/** Fill a ROI with a value.
* @param roi Selected ROI
* @param newVal  The replacement value
* @param minValue  Lower threshold
* @param maxValue  Upper threshold
* @param outside  If YES replace outside the ROI
*/
- (void) fillROI:(ROI*) roi :(float) newVal :(float) minValue :(float) maxValue :(BOOL) outside;

- (unsigned char*) getMapFromPolygonROI:(ROI*) roi size:(NSSize*) size origin:(NSPoint*) origin  __deprecated; /**< Map from Polygon ROI */
+ (unsigned char*) getMapFromPolygonROI:(ROI*) roi size:(NSSize*) size origin:(NSPoint*) ROIorigin  __deprecated;

/** Is this Point (pt) in this ROI ? */
- (BOOL) isInROI:(ROI*) roi :(NSPoint) pt __deprecated;

/** Returns a pointer with all pixels values contained in the current ROI
* User must Free the pointer with the free() function
* Returns reference number of pixels in numberOfValues
* Returns a pointer to the pixel locations. Each point has the x position followed by the y position
* Locations is malloced but not freed
*/
- (float*) getROIValue :(long*) numberOfValues :(ROI*) roi :(float**) locations;

/** Returns a pointer with all pixels values contained in the current ROI
* User must Free the pointer with the free() function
* Returns reference number of pixels in numberOfValues
* Returns a pointer to the pixel locations. Each point has the x position followed by the y position
* Locations is malloced but not freed
*/
- (float*) getLineROIValue :(long*) numberOfValues :(ROI*) roi;
#endif

/** Utility methods to convert user supplied pixel coords to DICOM patient coords float d[3] (in mm)
* using current slice location and orientation
*/
- (void) convertPixX: (float) x pixY: (float) y toDICOMCoords: (float*) d;
- (void) convertPixX: (float) x pixY: (float) y toDICOMCoords: (float*) d pixelCenter: (BOOL) pixelCenter;

- (void) getSliceCenter3DCoords: (float*) center;

/** Utility methods to convert user supplied pixel coords to DICOM patient coords double d[3] (in mm)
* using current slice location and orientation
*/
- (void) convertPixDoubleX: (double) x pixY: (double) y toDICOMCoords: (double*) d;
- (void) convertPixDoubleX: (double) x pixY: (double) y toDICOMCoords: (double*) d pixelCenter: (BOOL) pixelCenter;
- (void) offsetPixDoubleX: (double) x pixY: (double) y toDICOMCoords: (double*) d;

/** convert DICOM coordinated to slice coordinates */
- (void) convertDICOMCoords: (float*) dc toSliceCoords: (float*) sc;
- (void) convertDICOMCoords: (float*) dc toSliceCoords: (float*) sc pixelCenter:(BOOL) pixelCenter;
- (NSPoint) convertDICOMCoords: (float*) dc;
- (NSPoint) convert3DPoint: (float*) dc;

/** convert DICOM coordinated to slice coordinates */
- (void) convertDICOMCoordsDouble: (double*) dc toSliceCoords: (double*) sc;
- (void) convertDICOMCoordsDouble: (double*) dc toSliceCoords: (double*) sc pixelCenter:(BOOL) pixelCenter;

/** Return index & sliceCoords */
+(int) nearestSliceInPixelList: (NSArray*)pixlist withDICOMCoords: (float*)dc sliceCoords: (float*) sc;  

- (DicomImage*) imageObj;
- (DicomSeries*) seriesObj;
- (DicomStudy*) studyObj;

- (BOOL) thickSlabVRActivated; /**< Activate Thick Slab VR */

/** convert to Black and White. 
* @param mode values: 0 Use Red Channel, 1 use Green Channel 2 use Blue Channel  3 Merge and use RGB
*/
- (void) ConvertToBW:(long) mode; 

/** convert to RGB. 
* @param mode values: 0 create Red Channel, 1 create Green Channel 2 create Blue Channel  3 create all channels
* @param  cwl  = window level to use
* @param cww = window width to use
*/
- (void) ConvertToRGB:(long) mode :(long) cwl :(long) cww;
- (BOOL) hasCLUT;
- (BOOL) getCLUTRed: (unsigned char*) r green: (unsigned char*) g blue: (unsigned char*) b;
- (void) setPixelX: (int) x Y:(int) y value:(float) v;
- (float) cineRate;  /**< Returns the Cine rate */
+ (int) maxProcessors;
- (BOOL) intersect: (DCMPix*) o;
// drag-drop subtraction-multiplication between series
- (void) imageArithmeticMultiplication:(DCMPix*) sub;
- (float*) multiplyImages :(float*) input :(float*) subfImage;
- (void) imageArithmeticSubtraction:(DCMPix*) sub;
- (void) imageArithmeticSubtraction:(DCMPix*) sub absolute:(BOOL) abs;
- (float*) arithmeticSubtractImages :(float*) input :(float*) subfImage;
-(float*) arithmeticSubtractImages :(float*) input :(float*) subfImage absolute:(BOOL) abs;
//DSA
- (void) setSubSlidersPercent: (float) p gamma: (float) g zero: (float) z;
- (void) setSubSlidersPercent: (float) p;
- (NSPoint) subMinMax:(float*)input :(float*)subfImage;
- (void) setSubtractedfImage:(float*)mask :(NSPoint)smm;
- (float*) subtractImages:(float*)input :(float*)subfImage;
- (void) fImageTime:(float)newTime;
- (float) fImageTime;
- (void) freefImageWhenDone:(BOOL) b;
- (void) maskID:(long)newID;
- (long) maskID;
- (void) maskTime:(float)newMaskTime;
- (float) maskTime;
- (double) minimumEncodedValue;
- (double) maximumEncodedValue;
- (void) convertExternalOwnedtoSelfOwned;
- (BOOL) hasOrientation;
- (void) getDataFromNSImage:(NSImage*) otherImage;
- (NSPoint) originDeltaWith:(DCMPix*) pix1;
- (NSPoint) originDeltaWith:(DCMPix*) pix1 angle: (float) angle;
- (NSPoint) originDeltaWith:(DCMPix*) pix1 angle: (float) angle originIsPixelCenter: (BOOL) originIsPixelCenter;
+ (NSPoint) originCorrectedAccordingToOrientation: (DCMPix*) pix1;
- (void) setBlackIndex:(int) i;
+ (NSImage*) resizeIfNecessary:(NSImage*) currentImage dcmPix: (DCMPix*) dcmPix;
- (void) computeTotalDoseCorrected;
- (void) setRGB : (BOOL) val;
- (void) setConvolutionKernel:(float*)val :(short) size :(float) norm;
- (void) applyConvolutionOnSourceImage;
- (void) setArrayPix :(NSArray*) array :(short) i;
- (BOOL) updateToApply;
- (id) myinitEmpty;  /**< Returns an Empty object */
- (float*) kernel;
- (void) applyShutter;
- (BOOL) is3DPlane;
- (void) orientationCorrected:(float*) correctedOrientation rotation:(float) rotation xFlipped: (BOOL) xFlipped yFlipped: (BOOL) yFlipped;
+ (NSPoint) rotatePoint:(NSPoint)pt aroundPoint:(NSPoint)c angle:(float)a;
- (void) computeCineRateFromNominalIntervalForCount: (float) numberOfImagesInSeries;
- (float) normalization;
- (short) kernelsize;
- (float) defaultWL; // = savedWL, or fullWL if not available
- (float) defaultWW;  // = savedWW, or fullWW if not available
- (void) resetFullWWAndWL;
- (void) computeAlphaMaskIfNeeded;
+ (void) clearDcmPixCache;
+ (NSString*) convertECGStorageToPDF: (NSString*) file sopInstanceUID: (NSString*) sopUID;
- (DCMPix*) renderWithScale:(float) scale;
- (DCMPix*) renderWithRotation:(float) r scale:(float) scale xFlipped:(BOOL) xF yFlipped: (BOOL) yF;
- (DCMPix*) renderWithRotation:(float) r scale:(float) scale xFlipped:(BOOL) xF yFlipped: (BOOL) yF backgroundOffset: (float) bgO;
- (NSRect) usefullRectWithRotation:(float) r scale:(float) scale xFlipped:(BOOL) xF yFlipped: (BOOL) yF;
- (NSRect) usefullRectWithRotation:(float) r scale:(float) scale xFlipped:(BOOL) xF yFlipped: (BOOL) yF useContentFrameRect:(BOOL)useContentFrameRect;
- (DCMPix*) mergeWithDCMPix:(DCMPix*) o offset:(NSPoint) oo;
- (DCMPix*) renderInRectSize:(NSSize) rectSize atPosition:(NSPoint) oo rotation:(float) r scale:(float) scale xFlipped:(BOOL) xF yFlipped: (BOOL) yF;
- (DCMPix*) renderInRectSize:(NSSize) rectSize atPosition:(NSPoint) oo rotation:(float) r scale:(float) scale xFlipped:(BOOL) xF yFlipped: (BOOL) yF smartCrop: (BOOL) smartCrop;
- (NSImage*) renderNSImageInRectSize:(NSSize) rectSize atPosition:(NSPoint) oo rotation:(float) r scale:(float) scale xFlipped:(BOOL) xF yFlipped: (BOOL) yF;
/**  calls 
* myinit:(NSString*) s :(long) pos :(long) tot :(float*) ptr :(long) f :(long) ss isBonjour:(BOOL) hello imageObj: (NSManagedObject*) iO
* with hello = NO and iO = nil
*/
- (id) myinit:(NSString*) s :(long) pos :(long) tot :(float*) ptr :(long) f :(long) ss;
- (id) initWithPath:(NSString*) s :(long) pos :(long) tot :(float*) ptr :(long) f :(long) ss;

/**  Initialize
* doesn't load pix data, only initializes instance variables
* @param s  filename
* @param pos  imageID  Position in array.
* @param tot  imTot  Total number of images. 
* @param ptr  pointer to volume
* @param f  frame number
* @param ss  series number
* @param hello  flag to indicate remote bonjour file
* @param iO  coreData image Entity for image
*/ 
- (id) myinit:(NSString*) s :(long) pos :(long) tot :(float*) ptr :(long) f :(long) ss isBonjour:(BOOL) hello imageObj: (DicomImage*) iO;
- (id) initWithPath:(NSString*) s :(long) pos :(long) tot :(float*) ptr :(long) f :(long) ss isBonjour:(BOOL) hello imageObj: (DicomImage*) iO;

/** init with data pointer
* @param im  pointer to image data
* @param pixelSize  pixelDepth in bits
* @param xDim  image width
* @param yDim =image height
* @param xSpace  pixel width
* @param ySpace  pxiel height
* @param oX x position of origin
* @param oY y position of origin
* @param oZ z position of origin
*/
- (id) initwithdata :(float*) im :(short) pixelSize :(long) xDim :(long) yDim :(float) xSpace :(float) ySpace :(float) oX :(float) oY :(float) oZ;
- (id) initWithData :(float*) im :(short) pixelSize :(long) xDim :(long) yDim :(float) xSpace :(float) ySpace :(float) oX :(float) oY :(float) oZ;

/** init with data pointer
* @param im = pointer to image data
* @param pixelSize = pixelDepth in bits
* @param xDim  image width
* @param yDim  image height
* @param xSpace  pixel width
* @param ySpace  pxiel height
* @param oX x position of origin
* @param oY y position of origin
* @param oZ z position of origin
* @param volSize ?
*/
- (id) initwithdata :(float*) im :(short) pixelSize :(long) xDim :(long) yDim :(float) xSpace :(float) ySpace :(float) oX :(float) oY :(float) oZ :(BOOL) volSize;
- (id) initWithData :(float*) im :(short) pixelSize :(long) xDim :(long) yDim :(float) xSpace :(float) ySpace :(float) oX :(float) oY :(float) oZ :(BOOL) volSize;

+ (id) dcmPixWithImageObj: (DicomImage*) image;
- (id) initWithImageObj: (DicomImage *) image;

- (id) initWithContentsOfFile: (NSString *)file; 
/** create an NSImage from the current pix
* @param newWW  window width to use
* @param newWL window level to use;
*/
- (NSImage*) generateThumbnailImageWithWW: (float)newWW WL: (float)newWL;
- (NSImage*) generateThumbnailImageWithWW: (float)newWW WL: (float)newWL xFlipped:(BOOL)xFlipped yFlipped:(BOOL)yFlipped rotation:(float) rotation;
- (void) allocate8bitRepresentation;

/** create an NSImage from the current pix using the current ww/wl. Full size*/
- (NSImage*) image;
- (NSImage*) imageXFlip:(BOOL) xFlip YFlip:(BOOL) yFlip rotation:(float) degrees;
- (NSImage*) imageXFlip:(BOOL) xFlip YFlip:(BOOL) yFlip rotation:(float) degrees minSize:(NSSize) minSize maxSize:(NSSize) maxSize;

/** reeturns the current image. returns nil if no image has be previously created */
// - (NSImage*) getImage;

/** A pointer to the orientation.  9 values in length. 3 for each axis. */
- (void) orientation:(float*) c;

/** Sets the orientation.  9 values in length. 3 for each axis. */
- (void) setOrientation:(float*) c;

/** Compute slicelocation according to pixelSpacing values, slice origin and slice orientation: the location is the center of the slice */
- (void) computeSliceLocation;

/** Releases the current NSImage */
- (void) kill8bitsImage;

- (void) checkImageAvailble:(float)newWW :(float)newWL;

/** Load the DICOM image using Papyrus.
* There should be no reason to call this. The class will call it when needed.
*/
- (BOOL) loadDICOMPapyrus;

/** Reset the Annotations */
- (void) reloadAnnotations;


/** Parses the file. Extracts necessary data. Load image data.
* This class will be called by the class when necessay. 
* There should be no need to call it externally
*/
- (void) CheckLoadIn;

/** Calls CheckLoadIn when needed */
- (void) CheckLoad;
- (BOOL) isLoaded;

/** Compute the float pointer for the image data */
- (float*) computefImage;

/** Sets fusion paramaters
* @param m  stack mode
* @param s stack
* @param direction stack direction
*/
- (void) setFusion:(short) m :(short) s :(short) direction;

/** Sets updateToBeApplied to YES. It is called whenver a setting has been changed.  
* Should be called by the class automatically when needed */
- (void) setUpdateToApply;


/** Releases the fImage and sets all values to nil. */
- (void) revert;
- (void) revert:(BOOL) reloadAnnotations;

/** Sets the ThickSlabController */
- (void) setThickSlabController:( ThickSlabController*) ts;
- (ThickSlabController*) thickSlabController;

/** Sets the fixed8bitsWLWW flag */
- (void) setFixed8bitsWLWW:(BOOL) f;

/** Creates a DCMPix with the original values and places it in the restore cache*/
- (void) prepareRestore;


/** Releases the restored DCMPix from the restoreCache */
- (void) freeRestore;

/** Sets flag for when OsiriX is running in protected mode */
+ (void) setRunOsiriXInProtectedMode:(BOOL) v;

/** Returns flag for protected mode */
+ (BOOL) isRunOsiriXInProtectedModeActivated;

/** Clears the papyrus group cache */
- (void) clearCachedPapyGroups;
+ (void) purgeCachedDictionaries;

+ (void) convertDICOMSR: (NSString*) sourceFile toHTML: (NSString*) htmlpath;
+ (void) convertDICOMSR: (NSString*) sourceFile toHTML: (NSString*) htmlpath extraArguments: (NSArray*) extra;
+ (NSString*) convertHTMLtoPDF: (NSString*) htmlpath;

/** Returns a pointer the the papyrus group
* @param group group
*/
- (void *) getPapyGroup: (int)group;

//+ (double) moment: (float *) x length:(long) length mean: (double) mean order: (int) order;
+ (double) skewness: (float*) data length: (long) length mean: (double) mean;
+ (double) kurtosis: (float*) data length: (long) length mean: (double) mean;
+ (float) median: (float*) data length: (long) length;

#ifndef OSIRIX_LIGHT
/** create ROIs from RTSTRUCT */
- (void)createROIsFromRTSTRUCT: (DCMObject*)dcmObject;
#endif

#ifdef OSIRIX_VIEWER
/** Custom Annotations */
- (void)loadCustomImageAnnotationsDBFields: (DicomImage*) imageObj;
#endif

@end
