#import "gRPCDelegate.h"
#import "roivolume.pb.h"

@interface gRPCROIVolumeDelegate : NSObject

delegateDeclaration(ROIVolumeTexture, ROIVolume, ROIVolumeTextureResponse)
delegateDeclaration(ROIVolumeSetTexture, ROIVolumeSetTextureRequest, Response)
delegateDeclaration(ROIVolumeVolume, ROIVolume, ROIVolumeVolumeResponse)
delegateDeclaration(ROIVolumeColor, ROIVolume, ROIVolumeColorResponse)
delegateDeclaration(ROIVolumeSetColor, ROIVolumeSetColorRequest, Response)
delegateDeclaration(ROIVolumeOpacity, ROIVolume, ROIVolumeOpacityResponse)
delegateDeclaration(ROIVolumeSetOpacity, ROIVolumeSetOpacityRequest, Response)
delegateDeclaration(ROIVolumeFactor, ROIVolume, ROIVolumeFactorResponse)
delegateDeclaration(ROIVolumeSetFactor, ROIVolumeSetFactorRequest, Response)
delegateDeclaration(ROIVolumeVisible, ROIVolume, ROIVolumeVisibleResponse)
delegateDeclaration(ROIVolumeName, ROIVolume, ROIVolumeNameResponse)

@end
