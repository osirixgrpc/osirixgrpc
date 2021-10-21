#import "gRPCDelegate.h"
#import "vrcontroller.pb.h"

@interface gRPCVRControllerDelegate : NSObject

delegateDeclaration(VRControllerViewer2D, VRController, VRControllerViewer2DResponse)
delegateDeclaration(VRControllerBlendingController, VRController, VRControllerBlendingControllerResponse)
delegateDeclaration(VRControllerStyle, VRController, VRControllerStyleResponse)
delegateDeclaration(VRControllerTitle, VRController, VRControllerTitleResponse)
delegateDeclaration(VRControllerROIVolumes, VRController, VRControllerROIVolumesResponse)
delegateDeclaration(VRControllerRenderingMode, VRController, VRControllerRenderingModeResponse)
delegateDeclaration(VRControllerSetRenderingMode, VRControllerSetRenderingModeRequest, Response)
delegateDeclaration(VRControllerWLWW, VRController, VRControllerWLWWResponse)
delegateDeclaration(VRControllerSetWLWW, VRControllerSetWLWWRequest, Response)

@end