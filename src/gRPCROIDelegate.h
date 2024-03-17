#import "gRPCDelegate.h"
#import "roi.pb.h"

@interface gRPCROIDelegate : NSObject

delegateDeclaration(ROIDelete, ROI, Response)
delegateDeclaration(ROIFlipHorizontally, ROI, Response)
delegateDeclaration(ROIFlipVertically, ROI, Response)
delegateDeclaration(ROIArea, ROI, ROIAreaResponse)
delegateDeclaration(ROICentroid, ROI, ROICentroidResponse)
delegateDeclaration(ROIRotate, ROIRotateRequest, Response)
delegateDeclaration(ROIMove, ROIMoveRequest, Response)
delegateDeclaration(ROIPix, ROI, ROIPixResponse)
delegateDeclaration(ROIIType, ROI, ROIITypeResponse)
delegateDeclaration(ROIName, ROI, ROINameResponse)
delegateDeclaration(ROISetName, ROISetNameRequest, Response)
delegateDeclaration(ROIColor, ROI, ROIColorResponse)
delegateDeclaration(ROISetColor, ROISetColorRequest, Response)
delegateDeclaration(ROIOpacity, ROI, ROIOpacityResponse)
delegateDeclaration(ROISetOpacity, ROISetOpacityRequest, Response)
delegateDeclaration(ROIThickness, ROI, ROIThicknessResponse)
delegateDeclaration(ROISetThickness, ROISetThicknessRequest, Response)
delegateDeclaration(ROIPoints, ROI, ROIPointsResponse)
delegateDeclaration(ROISetPoints, ROISetPointsRequest, Response)

@end
