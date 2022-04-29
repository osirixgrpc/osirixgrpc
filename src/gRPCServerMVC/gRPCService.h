#include "osirix.grpc.pb.h"
#include "osirix.pb.h"
#include "roi.pb.h"
#include "roivolume.pb.h"
#include "dcmpix.pb.h"
#include "vrcontroller.pb.h"
#include "viewercontroller.pb.h"
#include "browsercontroller.pb.h"
#include "dicomimage.pb.h"
#include "dicomseries.pb.h"
#include "dicomstudy.pb.h"
#include "utilities.pb.h"
#include "types.pb.h"

#import "gRPCViewerControllerDelegate.h"
#import "gRPCVRControllerDelegate.h"
#import "gRPCDCMPixDelegate.h"
#import "gRPCOsirixDelegate.h"
#import "gRPCROIDelegate.h"
#import "gRPCROIVolumeDelegate.h"
#import "gRPCBrowserControllerDelegate.h"
#import "gRPCDicomImageDelegate.h"
#import "gRPCDicomSeriesDelegate.h"
#import "gRPCDicomStudyDelegate.h"

#import "gRPCCache.h"

#define gRPCServiceMessageDeclaration(name, requestType, responseType) \
    grpc::Status name(grpc::ServerContext *context,\
                      const osirixgrpc::requestType *request,\
                      osirixgrpc:: responseType *response ) override;

class gRPCService final : public osirixgrpc::OsiriXService::Service {
    
public:
    gRPCService(gRPCCache *cache); // Constructor
    
private:
    gRPCCache *_cache;
    
    // OsiriX messages
    gRPCServiceMessageDeclaration(OsirixCurrentBrowser, Empty, OsirixCurrentBrowserResponse)
    gRPCServiceMessageDeclaration(OsirixFrontmostViewer, Empty, OsirixFrontmostViewerResponse)
    gRPCServiceMessageDeclaration(OsirixDisplayed2DViewers, Empty, OsirixDisplayed2DViewersResponse)
    gRPCServiceMessageDeclaration(OsirixFrontmostVRController, Empty, OsirixFrontmostVRControllerResponse)
    gRPCServiceMessageDeclaration(OsirixDisplayedVRControllers, Empty, OsirixDisplayedVRControllersResponse)

    // ViewerController messages
    gRPCServiceMessageDeclaration(ViewerControllerCloseViewer, ViewerController, Response)
    gRPCServiceMessageDeclaration(ViewerControllerPixList, ViewerControllerPixListRequest, ViewerControllerPixListResponse)
    gRPCServiceMessageDeclaration(ViewerControllerNeedsDisplayUpdate, ViewerController, Response)
    gRPCServiceMessageDeclaration(ViewerControllerROIList, ViewerControllerROIListRequest, ViewerControllerROIListResponse)
    gRPCServiceMessageDeclaration(ViewerControllerNewROI, ViewerControllerNewROIRequest, ViewerControllerNewROIResponse)
    gRPCServiceMessageDeclaration(ViewerControllerCurDCM, ViewerController, ViewerControllerCurDCMResponse)
    gRPCServiceMessageDeclaration(ViewerControllerROIsWithName, ViewerControllerROIsWithNameRequest, ViewerControllerROIsWithNameResponse)
    gRPCServiceMessageDeclaration(ViewerControllerSelectedROIs, ViewerController, ViewerControllerSelectedROIsResponse)
    gRPCServiceMessageDeclaration(ViewerControllerIsDataVolumic, ViewerControllerIsDataVolumicRequest, ViewerControllerIsDataVolumicResponse)
    gRPCServiceMessageDeclaration(ViewerControllerCopyViewerWindow, ViewerControllerCopyViewerWindowRequest, Response)
    gRPCServiceMessageDeclaration(ViewerControllerResampleViewerController, ViewerControllerResampleViewerControllerRequest, Response)
    gRPCServiceMessageDeclaration(ViewerControllerBlendingController, ViewerController, ViewerControllerBlendingControllerResponse)
    gRPCServiceMessageDeclaration(ViewerControllerVRControllers, ViewerController, ViewerControllerVRControllersResponse)
    gRPCServiceMessageDeclaration(ViewerControllerTitle, ViewerController, ViewerControllerTitleResponse)
    gRPCServiceMessageDeclaration(ViewerControllerModality, ViewerController, ViewerControllerModalityResponse)
    gRPCServiceMessageDeclaration(ViewerControllerMovieIdx, ViewerController, ViewerControllerMovieIdxResponse)
    gRPCServiceMessageDeclaration(ViewerControllerSetMovieIdx, ViewerControllerSetMovieIdxRequest, Response)
    gRPCServiceMessageDeclaration(ViewerControllerMaxMovieIdx, ViewerController, ViewerControllerMaxMovieIdxResponse)
    gRPCServiceMessageDeclaration(ViewerControllerIdx, ViewerController, ViewerControllerIdxResponse)
    gRPCServiceMessageDeclaration(ViewerControllerSetIdx, ViewerControllerSetIdxRequest, Response)
    gRPCServiceMessageDeclaration(ViewerControllerWLWW, ViewerController, ViewerControllerWLWWResponse)
    gRPCServiceMessageDeclaration(ViewerControllerSetWLWW, ViewerControllerSetWLWWRequest, Response)
    gRPCServiceMessageDeclaration(ViewerControllerOpenVRViewerForMode, ViewerControllerOpenVRViewerForModeRequest, ViewerControllerOpenVRViewerForModeResponse)
    
    // DCMPix messages
    gRPCServiceMessageDeclaration(DCMPixConvertToRGB, DCMPixConvertToRGBRequest, Response)
    gRPCServiceMessageDeclaration(DCMPixConvertToBW, DCMPixConvertToBWRequest, Response)
    gRPCServiceMessageDeclaration(DCMPixIsRGB, DCMPix, DCMPixIsRGBResponse)
    gRPCServiceMessageDeclaration(DCMPixComputeROI, DCMPixComputeROIRequest, DCMPixComputeROIResponse)
    gRPCServiceMessageDeclaration(DCMPixROIValues, DCMPixROIValuesRequest, DCMPixROIValuesResponse)
    gRPCServiceMessageDeclaration(DCMPixShape, DCMPix, DCMPixShapeResponse)
    gRPCServiceMessageDeclaration(DCMPixSpacing, DCMPix, DCMPixSpacingResponse)
    gRPCServiceMessageDeclaration(DCMPixOrigin, DCMPix, DCMPixOriginResponse)
    gRPCServiceMessageDeclaration(DCMPixOrientation, DCMPix, DCMPixOrientationResponse)
    gRPCServiceMessageDeclaration(DCMPixSliceLocation, DCMPix, DCMPixSliceLocationResponse)
    gRPCServiceMessageDeclaration(DCMPixSourceFile, DCMPix, DCMPixSourceFileResponse)
    gRPCServiceMessageDeclaration(DCMPixImage, DCMPix, DCMPixImageResponse)
    gRPCServiceMessageDeclaration(DCMPixSetImage, DCMPixSetImageRequest, Response)
    gRPCServiceMessageDeclaration(DCMPixGetMapFromROI, DCMPixGetMapFromROIRequest, DCMPixGetMapFromROIResponse)
    gRPCServiceMessageDeclaration(DCMPixDicomImage, DCMPix, DCMPixDicomImageResponse)
    gRPCServiceMessageDeclaration(DCMPixDicomSeries, DCMPix, DCMPixDicomSeriesResponse)
    gRPCServiceMessageDeclaration(DCMPixDicomStudy, DCMPix, DCMPixDicomStudyResponse)
    
    // ROI messages
    gRPCServiceMessageDeclaration(ROIFlipHorizontally, ROI, Response)
    gRPCServiceMessageDeclaration(ROIFlipVertically, ROI, Response)
    gRPCServiceMessageDeclaration(ROIArea, ROI, ROIAreaResponse)
    gRPCServiceMessageDeclaration(ROICentroid, ROI, ROICentroidResponse)
    gRPCServiceMessageDeclaration(ROIRotate, ROIRotateRequest, Response)
    gRPCServiceMessageDeclaration(ROIMove, ROIMoveRequest, Response)
    gRPCServiceMessageDeclaration(ROIPix, ROI, ROIPixResponse)
    gRPCServiceMessageDeclaration(ROIIType, ROI, ROIITypeResponse)
    gRPCServiceMessageDeclaration(ROIName, ROI, ROINameResponse)
    gRPCServiceMessageDeclaration(ROISetName, ROISetNameRequest, Response)
    gRPCServiceMessageDeclaration(ROIColor, ROI, ROIColorResponse)
    gRPCServiceMessageDeclaration(ROISetColor, ROISetColorRequest, Response)
    gRPCServiceMessageDeclaration(ROIOpacity, ROI, ROIOpacityResponse)
    gRPCServiceMessageDeclaration(ROISetOpacity, ROISetOpacityRequest, Response)
    gRPCServiceMessageDeclaration(ROIThickness, ROI, ROIThicknessResponse)
    gRPCServiceMessageDeclaration(ROISetThickness, ROISetThicknessRequest, Response)
    gRPCServiceMessageDeclaration(ROIPoints, ROI, ROIPointsResponse)
    gRPCServiceMessageDeclaration(ROISetPoints, ROISetPointsRequest, Response)
    
    // VRController messages
    gRPCServiceMessageDeclaration(VRControllerViewer2D, VRController, VRControllerViewer2DResponse)
    gRPCServiceMessageDeclaration(VRControllerBlendingController, VRController, VRControllerBlendingControllerResponse)
    gRPCServiceMessageDeclaration(VRControllerStyle, VRController, VRControllerStyleResponse)
    gRPCServiceMessageDeclaration(VRControllerTitle, VRController, VRControllerTitleResponse)
    gRPCServiceMessageDeclaration(VRControllerROIVolumes, VRController, VRControllerROIVolumesResponse)
    gRPCServiceMessageDeclaration(VRControllerRenderingMode, VRController, VRControllerRenderingModeResponse)
    gRPCServiceMessageDeclaration(VRControllerSetRenderingMode, VRControllerSetRenderingModeRequest, Response)
    gRPCServiceMessageDeclaration(VRControllerWLWW, VRController, VRControllerWLWWResponse)
    gRPCServiceMessageDeclaration(VRControllerSetWLWW, VRControllerSetWLWWRequest, Response)
    
    // ROIVolume messages
    gRPCServiceMessageDeclaration(ROIVolumeTexture, ROIVolume, ROIVolumeTextureResponse)
    gRPCServiceMessageDeclaration(ROIVolumeSetTexture, ROIVolumeSetTextureRequest, Response)
    gRPCServiceMessageDeclaration(ROIVolumeVolume, ROIVolume, ROIVolumeVolumeResponse)
    gRPCServiceMessageDeclaration(ROIVolumeColor, ROIVolume, ROIVolumeColorResponse)
    gRPCServiceMessageDeclaration(ROIVolumeSetColor, ROIVolumeSetColorRequest, Response)
    gRPCServiceMessageDeclaration(ROIVolumeOpacity, ROIVolume, ROIVolumeOpacityResponse)
    gRPCServiceMessageDeclaration(ROIVolumeSetOpacity, ROIVolumeSetOpacityRequest, Response)
    gRPCServiceMessageDeclaration(ROIVolumeFactor, ROIVolume, ROIVolumeFactorResponse)
    gRPCServiceMessageDeclaration(ROIVolumeSetFactor, ROIVolumeSetFactorRequest, Response)
    gRPCServiceMessageDeclaration(ROIVolumeVisible, ROIVolume, ROIVolumeVisibleResponse)
    gRPCServiceMessageDeclaration(ROIVolumeSetVisible, ROIVolumeSetVisibleRequest, Response)
    gRPCServiceMessageDeclaration(ROIVolumeName, ROIVolume, ROIVolumeNameResponse)
    
    // BrowserController messages
    gRPCServiceMessageDeclaration(BrowserControllerDatabaseSelection, BrowserController, BrowserControllerDatabaseSelectionResponse)
    gRPCServiceMessageDeclaration(BrowserControllerCopyFilesIfNeeded, BrowserControllerCopyFilesIfNeededRequest, Response)
    
    // DicomImage messages
    gRPCServiceMessageDeclaration(DicomImageWidth, DicomImage, DicomImageWidthResponse)
    gRPCServiceMessageDeclaration(DicomImageHeight, DicomImage, DicomImageHeightResponse)
    gRPCServiceMessageDeclaration(DicomImageSOPInstanceUID, DicomImage, DicomImageSOPInstanceUIDResponse)
    gRPCServiceMessageDeclaration(DicomImageCompletePath, DicomImage, DicomImageCompletePathResponse)
    gRPCServiceMessageDeclaration(DicomImageDate, DicomImage, DicomImageDateResponse)
    gRPCServiceMessageDeclaration(DicomImageNumberOfFrames, DicomImage, DicomImageNumberOfFramesResponse)
    gRPCServiceMessageDeclaration(DicomImageModality, DicomImage, DicomImageModalityResponse)
    gRPCServiceMessageDeclaration(DicomImageSeries, DicomImage, DicomImageSeriesResponse)
    gRPCServiceMessageDeclaration(DicomImageSliceLocation, DicomImage, DicomImageSliceLocationResponse)
    gRPCServiceMessageDeclaration(DicomImageInstanceNumber, DicomImage, DicomImageInstanceNumberResponse)
    
    // DicomSeries messages
    gRPCServiceMessageDeclaration(DicomSeriesPaths, DicomSeries, DicomSeriesPathsResponse)
    gRPCServiceMessageDeclaration(DicomSeriesPreviousSeries, DicomSeries, DicomSeriesPreviousSeriesResponse)
    gRPCServiceMessageDeclaration(DicomSeriesNextSeries, DicomSeries, DicomSeriesNextSeriesResponse)
    gRPCServiceMessageDeclaration(DicomSeriesSortedImages, DicomSeries, DicomSeriesSortedImagesResponse)
    gRPCServiceMessageDeclaration(DicomSeriesStudy, DicomSeries, DicomSeriesStudyResponse)
    gRPCServiceMessageDeclaration(DicomSeriesImages, DicomSeries, DicomSeriesImagesResponse)
    gRPCServiceMessageDeclaration(DicomSeriesSeriesInstanceUID, DicomSeries, DicomSeriesSeriesInstanceUIDResponse)
    gRPCServiceMessageDeclaration(DicomSeriesSeriesSOPClassUID, DicomSeries, DicomSeriesSeriesSOPClassUIDResponse)
    gRPCServiceMessageDeclaration(DicomSeriesSeriesDescription, DicomSeries, DicomSeriesSeriesDescriptionResponse)
    gRPCServiceMessageDeclaration(DicomSeriesModality, DicomSeries, DicomSeriesModalityResponse)
    gRPCServiceMessageDeclaration(DicomSeriesName, DicomSeries, DicomSeriesNameResponse)
    gRPCServiceMessageDeclaration(DicomSeriesDate, DicomSeries, DicomSeriesDateResponse)
    
    // DicomStudy messages
    gRPCServiceMessageDeclaration(DicomStudyPaths, DicomStudy, DicomStudyPathsResponse)
    gRPCServiceMessageDeclaration(DicomStudyImages, DicomStudy, DicomStudyImagesResponse)
    gRPCServiceMessageDeclaration(DicomStudyModalities, DicomStudy, DicomStudyModalitiesResponse)
    gRPCServiceMessageDeclaration(DicomStudyNoFiles, DicomStudy, DicomStudyNoFilesResponse)
    gRPCServiceMessageDeclaration(DicomStudyRawNoFiles, DicomStudy, DicomStudyRawNoFilesResponse)
    gRPCServiceMessageDeclaration(DicomStudyNoFilesExcludingMultiFrames, DicomStudy, DicomStudyNoFilesExcludingMultiFramesResponse)
    gRPCServiceMessageDeclaration(DicomStudyNumberOfImages, DicomStudy, DicomStudyNumberOfImagesResponse)
    gRPCServiceMessageDeclaration(DicomStudySeries, DicomStudy, DicomStudySeriesResponse)
    gRPCServiceMessageDeclaration(DicomStudyName, DicomStudy, DicomStudyNameResponse)
    gRPCServiceMessageDeclaration(DicomStudyDate, DicomStudy, DicomStudyDateResponse)
    gRPCServiceMessageDeclaration(DicomStudyDateAdded, DicomStudy, DicomStudyDateAddedResponse)
    gRPCServiceMessageDeclaration(DicomStudyDateOfBirth, DicomStudy, DicomStudyDateOfBirthResponse)
    gRPCServiceMessageDeclaration(DicomStudyInstitutionName, DicomStudy, DicomStudyInstitutionNameResponse)
    gRPCServiceMessageDeclaration(DicomStudyModality, DicomStudy, DicomStudyModalityResponse)
    gRPCServiceMessageDeclaration(DicomStudyPatientID, DicomStudy, DicomStudyPatientIDResponse)
    gRPCServiceMessageDeclaration(DicomStudyPatientUID, DicomStudy, DicomStudyPatientUIDResponse)
    gRPCServiceMessageDeclaration(DicomStudyPatientSex, DicomStudy, DicomStudyPatientSexResponse)
    gRPCServiceMessageDeclaration(DicomStudyPerformingPhysician, DicomStudy, DicomStudyPerformingPhysicianResponse)
    gRPCServiceMessageDeclaration(DicomStudyReferringPhysician, DicomStudy, DicomStudyReferringPhysicianResponse)
    gRPCServiceMessageDeclaration(DicomStudyStudyInstanceUID, DicomStudy, DicomStudyStudyInstanceUIDResponse)
    gRPCServiceMessageDeclaration(DicomStudyStudyName, DicomStudy, DicomStudyStudyNameResponse)
};
