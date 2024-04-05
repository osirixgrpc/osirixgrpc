#import "gRPCOsirixDelegate.h"

#import <OsiriXAPI/ViewerController.h>
#import <OsiriXAPI/VRController.h>
#import <OsiriXAPI/DicomImage.h>
#import <OsiriXAPI/DicomSeries.h>
#import <OsiriXAPI/DicomStudy.h>
#import <OsiriXAPI/ROI.h>
#import <OsiriXAPI/ROIVolume.h>
#import <OsiriXAPI/DCMPix.h>
#import <OsiriXAPI/browserController.h>

@implementation gRPCOsirixDelegate

+ (void) OsirixCurrentBrowser:(const osirixgrpc::Empty *) request :(osirixgrpc::OsirixCurrentBrowserResponse *) response :(gRPCCache *) cache
{
    BrowserController *bc = [BrowserController currentBrowser];
    
    if (!bc){
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No BrowserController active");
    }
    else
    {
        NSString *uid = nil;
        if ([cache doesContain:bc])
            uid = [cache uidForObject:bc];
        else
            uid = [cache addObject:bc];
        
        // Set relevant values
        response->mutable_status()->set_status(1);
        response->mutable_browser_controller()->set_osirixrpc_uid([uid UTF8String]);
    }
}

+ (void) OsirixFrontmostViewer:(const osirixgrpc::Empty *) request :(osirixgrpc::OsirixFrontmostViewerResponse *) response :(gRPCCache *) cache
{
    ViewerController *vc = [ViewerController frontMostDisplayed2DViewer];
    
    if (!vc)
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController active");
    }
    else
    {
        NSString *uid = nil;
        if ([cache doesContain:vc])
            uid = [cache uidForObject:vc];
        else
            uid = [cache addObject:vc];
        
        // Set relevant values
        response->mutable_status()->set_status(1);
        response->mutable_viewer_controller()->set_osirixrpc_uid([uid UTF8String]);
    }
}

+ (void) OsirixDisplayed2DViewers:(const osirixgrpc::Empty *) request :(osirixgrpc::OsirixDisplayed2DViewersResponse *) response :(gRPCCache *) cache
{
    NSArray *vcs = [ViewerController getDisplayed2DViewers];
        
    for (ViewerController *vc in vcs)
    {
        NSString *uid = nil;
        if ([cache doesContain:vc])
            uid = [cache uidForObject:vc];
        else
            uid = [cache addObject:vc];
        
        osirixgrpc::ViewerController *vc_ = response->mutable_viewer_controllers()->Add();
        vc_->set_osirixrpc_uid([uid UTF8String]);
    }
    
    response->mutable_status()->set_status(1);
}

+ (void) OsirixFrontmostVRController:(const osirixgrpc::Empty *) request :(osirixgrpc::OsirixFrontmostVRControllerResponse *) response :(gRPCCache *) cache;
{
    VRController *vrc = nil;
    for( NSWindow *win in [NSApp orderedWindows])
    {
        if (![win isVisible] && ![win isMiniaturized]) {
            continue;
        }
        NSWindowController *wc = [win windowController];
        if( [wc isKindOfClass:[VRController class]])
        {
            vrc = (VRController *)wc;
            break;
        }
    }
    
    if (!vrc){
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRController active");
    }
    else
    {
        NSString *uid = nil;
        if ([cache doesContain:vrc])
            uid = [cache uidForObject:vrc];
        else
            uid = [cache addObject:vrc];
        
        // Set relevant values
        response->mutable_status()->set_status(1);
        response->mutable_vr_controller()->set_osirixrpc_uid([uid UTF8String]);
    }
}

+ (void) OsirixDisplayedVRControllers:(const osirixgrpc::Empty *) request :(osirixgrpc::OsirixDisplayedVRControllersResponse *) response :(gRPCCache *) cache
{
    for( NSWindow *win in [NSApp orderedWindows])
    {
        if (![win isVisible] && ![win isMiniaturized]) {
            continue;
        }
        NSWindowController *wc = [win windowController];
        if( [wc isKindOfClass:[VRController class]])
        {
            NSString *uid = nil;
            if ([cache doesContain:wc])
                uid = [cache uidForObject:wc];
            else
                uid = [cache addObject:wc];
            
            osirixgrpc::VRController *vrc_ = response->mutable_vr_controllers()->Add();
            vrc_->set_osirixrpc_uid([uid UTF8String]);
        }
    }
    response->mutable_status()->set_status(1);
}

+ (void) OsirixVersion:(const osirixgrpc::Empty *)request :(osirixgrpc::OsirixVersionResponse *)response :(gRPCCache *)cache
{
    // Note this can be found in the Info.plist for OsiriX as "Bundle version string (short)".
    NSString *osirix_version = [NSMutableString stringWithString:[[[NSBundle bundleForClass:[BrowserController class]] infoDictionary] objectForKey:@"CFBundleShortVersionString"]];
    NSString *bundle_name = [NSMutableString stringWithString:[[[NSBundle bundleForClass:[BrowserController class]] infoDictionary] objectForKey:@"CFBundleName"]];
    response->mutable_status()->set_status(1);
    response->set_version([osirix_version UTF8String]);
    response->set_bundle_name([bundle_name UTF8String]);
}

+ (void) OsirixCacheUids:(const osirixgrpc::Empty *)request :(osirixgrpc::OsirixCacheUidsResponse *)response :(gRPCCache *)cache
{
    NSArray *uids = [cache uids];
    for (NSString *uid in uids) {
        response->mutable_uids()->Add([uid UTF8String]);
    }
    response->mutable_status()->set_status(1);
}

+ (void) OsirixCacheObjectForUid:(const osirixgrpc::OsirixCacheObjectForUidRequest *)request :(osirixgrpc::OsirixCacheObjectForUidResponse *)response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->uid());
    id obj = [cache objectForUID:uid];
    if (obj)
    {
        if ([obj isKindOfClass: [ViewerController class]]) {
            response->set_object_type("ViewerController");
        }
        else if ([obj isKindOfClass: [ROI class]]) {
            response->set_object_type("ROI");
        }
        else if ([obj isKindOfClass: [VRController class]]) {
            response->set_object_type("VRController");
        }
        else if ([obj isKindOfClass: [DicomImage class]]) {
            response->set_object_type("DicomImage");
        }
        else if ([obj isKindOfClass: [DicomSeries class]]) {
            response->set_object_type("DicomSeries");
        }
        else if ([obj isKindOfClass: [DicomStudy class]]) {
            response->set_object_type("DicomStudy");
        }
        else if ([obj isKindOfClass: [ROIVolume class]]) {
            response->set_object_type("ROIVolume");
        }
        else if ([obj isKindOfClass: [DCMPix class]]) {
            response->set_object_type("DCMPix");
        }
        else if ([obj isKindOfClass: [BrowserController class]]) {
            response->set_object_type("BrowserController");
        }
        else {
            response->set_object_type("unknown");
        }
    }
    else {
        response->set_object_type("no object");
    }
    response->mutable_status()->set_status(1);
}

@end
