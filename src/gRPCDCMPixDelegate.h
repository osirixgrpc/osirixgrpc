#import "gRPCDelegate.h"
#import "dcmpix.pb.h"

@interface gRPCDCMPixDelegate : NSObject

delegateDeclaration(DCMPixConvertToRGB, DCMPixConvertToRGBRequest, Response)
delegateDeclaration(DCMPixConvertToBW, DCMPixConvertToBWRequest, Response)
delegateDeclaration(DCMPixIsRGB, DCMPix, DCMPixIsRGBResponse)
delegateDeclaration(DCMPixComputeROI, DCMPixComputeROIRequest, DCMPixComputeROIResponse)
delegateDeclaration(DCMPixROIValues, DCMPixROIValuesRequest, DCMPixROIValuesResponse)
delegateDeclaration(DCMPixShape, DCMPix, DCMPixShapeResponse)
delegateDeclaration(DCMPixSpacing, DCMPix, DCMPixSpacingResponse)
delegateDeclaration(DCMPixOrigin, DCMPix, DCMPixOriginResponse)
delegateDeclaration(DCMPixOrientation, DCMPix, DCMPixOrientationResponse)
delegateDeclaration(DCMPixSliceLocation, DCMPix, DCMPixSliceLocationResponse)
delegateDeclaration(DCMPixSourceFile, DCMPix, DCMPixSourceFileResponse)
delegateDeclaration(DCMPixImage, DCMPix, DCMPixImageResponse)
delegateDeclaration(DCMPixSetImage, DCMPixSetImageRequest, Response)
delegateDeclaration(DCMPixGetMapFromROI, DCMPixGetMapFromROIRequest, DCMPixGetMapFromROIResponse)
delegateDeclaration(DCMPixDicomImage, DCMPix, DCMPixDicomImageResponse)
delegateDeclaration(DCMPixDicomSeries, DCMPix, DCMPixDicomSeriesResponse)
delegateDeclaration(DCMPixDicomStudy, DCMPix, DCMPixDicomStudyResponse)

@end
