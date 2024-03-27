#import "gRPCDelegate.h"
#import "osirix.pb.h"
#import "osirix.grpc.pb.h"

@interface gRPCOsirixDelegate : NSObject

delegateDeclaration(OsirixCurrentBrowser, Empty, OsirixCurrentBrowserResponse)
delegateDeclaration(OsirixFrontmostViewer, Empty, OsirixFrontmostViewerResponse)
delegateDeclaration(OsirixDisplayed2DViewers, Empty, OsirixDisplayed2DViewersResponse)
delegateDeclaration(OsirixFrontmostVRController, Empty, OsirixFrontmostVRControllerResponse)
delegateDeclaration(OsirixDisplayedVRControllers, Empty, OsirixDisplayedVRControllersResponse)
delegateDeclaration(OsirixVersion, Empty, OsirixVersionResponse)

delegateDeclaration(OsirixCacheUids, Empty, OsirixCacheUidsResponse)
delegateDeclaration(OsirixCacheObjectForUid, OsirixCacheObjectForUidRequest, OsirixCacheObjectForUidResponse)


@end
