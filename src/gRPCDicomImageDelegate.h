#import "gRPCDelegate.h"
#import "dicomimage.pb.h"

@interface gRPCDicomImageDelegate : NSObject

delegateDeclaration(DicomImageWidth, DicomImage, DicomImageWidthResponse)
delegateDeclaration(DicomImageHeight, DicomImage, DicomImageHeightResponse)
delegateDeclaration(DicomImageSOPInstanceUID, DicomImage, DicomImageSOPInstanceUIDResponse)
delegateDeclaration(DicomImageCompletePath, DicomImage, DicomImageCompletePathResponse)
delegateDeclaration(DicomImageDate, DicomImage, DicomImageDateResponse)
delegateDeclaration(DicomImageNumberOfFrames, DicomImage, DicomImageNumberOfFramesResponse)
delegateDeclaration(DicomImageModality, DicomImage, DicomImageModalityResponse)
delegateDeclaration(DicomImageSeries, DicomImage, DicomImageSeriesResponse)
delegateDeclaration(DicomImageSliceLocation, DicomImage, DicomImageSliceLocationResponse)
delegateDeclaration(DicomImageInstanceNumber, DicomImage, DicomImageInstanceNumberResponse)

@end
