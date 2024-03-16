#import "gRPCOsirixDelegate.h"

#import <OsiriXAPI/ViewerController.h>
#import <OsiriXAPI/VRController.h>
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
    
    if ([vcs count] < 1)
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerControllers active");
    }
    else
    {
        response->mutable_status()->set_status(1);
    }
    
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
    
}

+ (void) OsirixFrontmostVRController:(const osirixgrpc::Empty *) request :(osirixgrpc::OsirixFrontmostVRControllerResponse *) response :(gRPCCache *) cache;
{
    VRController *vrc = nil;
    for( NSWindow *win in [NSApp orderedWindows])
    {
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
    NSMutableArray *vrcs = [NSMutableArray array];
    for( NSWindow *win in [NSApp orderedWindows])
    {
        NSWindowController *wc = [win windowController];
        if( [wc isKindOfClass:[VRController class]])
            [vrcs addObject:wc];
    }
    
    if ([vrcs count] < 1)
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRControllers active");
    }
    else
    {
        response->mutable_status()->set_status(1);
    }
    
    for (VRController *vrc in vrcs)
    {
        NSString *uid = nil;
        if ([cache doesContain:vrc])
            uid = [cache uidForObject:vrc];
        else
            uid = [cache addObject:vrc];
        
        osirixgrpc::VRController *vrc_ = response->mutable_vr_controllers()->Add();
        vrc_->set_osirixrpc_uid([uid UTF8String]);
    }
    
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

@end
