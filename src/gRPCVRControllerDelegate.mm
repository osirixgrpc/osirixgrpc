#import "gRPCVRControllerDelegate.h"

#import <OsiriXAPI/VRController.h>
#import <OsiriXAPI/ROIVolume.h>

@implementation gRPCVRControllerDelegate

+ (void) VRControllerViewer2D:(const osirixgrpc::VRController *) request :(osirixgrpc::VRControllerViewer2DResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    VRController *vrc = [cache objectForUID:uid];
    
    if (vrc)
    {
        ViewerController *vc = [vrc viewer2D];
        NSString *vc_uid = [cache uidForObject:vc];
        if (!vc_uid)
        {
            vc_uid = [cache addObject:vc];
        }
        response->mutable_viewer_controller()->set_osirixrpc_uid([vc_uid UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRController cached");
    }
}

+ (void) VRControllerBlendingController:(const osirixgrpc::VRController *) request :(osirixgrpc::VRControllerBlendingControllerResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    VRController *vrc = [cache objectForUID:uid];
    
    if (vrc)
    {
        ViewerController *vc = [vrc blendingController];
        if (vc)
        {
            NSString *vc_uid = [cache uidForObject:vc];
            if (!vc_uid)
            {
                vc_uid = [cache addObject:vc];
            }
            response->mutable_viewer_controller()->set_osirixrpc_uid([vc_uid UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRController cached");
    }
}

+ (void) VRControllerStyle:(const osirixgrpc::VRController *) request :(osirixgrpc::VRControllerStyleResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    VRController *vrc = [cache objectForUID:uid];
    
    if (vrc)
    {
        NSString *style = [vrc style];
        response->set_style([style UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRController cached");
    }

}

+ (void) VRControllerTitle:(const osirixgrpc::VRController *) request :(osirixgrpc::VRControllerTitleResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    VRController *vrc = [cache objectForUID:uid];
    
    if (vrc)
    {
        NSString *title = [[vrc window] title];
        response->set_title([title UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRController cached");
    }

}

+ (void) VRControllerROIVolumes:(const osirixgrpc::VRController *) request :(osirixgrpc::VRControllerROIVolumesResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    VRController *vrc = [cache objectForUID:uid];
    
    if (vrc)
    {
        NSArray *roiVolumes = [vrc roiVolumes];
        for (ROIVolume *rv in roiVolumes)
        {
            NSString *rv_uid = [cache uidForObject:rv];
            if (!rv_uid)
            {
                rv_uid = [cache addObject:rv];
            }
            osirixgrpc::ROIVolume *rv_ = response->mutable_roi_volumes()->Add();
            rv_->set_osirixrpc_uid([rv_uid UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRController cached");
    }
}

+ (void) VRControllerRenderingMode:(const osirixgrpc::VRController *) request :(osirixgrpc::VRControllerRenderingModeResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    VRController *vrc = [cache objectForUID:uid];
    
    if (vrc)
    {
        NSString *mode = [vrc renderingMode];
        response->set_rendering_mode([mode UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRController cached");
    }
}

+ (void) VRControllerSetRenderingMode:(const osirixgrpc::VRControllerSetRenderingModeRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->vr_controller().osirixrpc_uid());
    
    VRController *vrc = [cache objectForUID:uid];
    
    if (vrc)
    {
        NSString *mode = stringFromGRPCString(request->rendering_mode());
        if ([mode isEqual:@"MIP"] || [mode isEqual:@"VR"])
        {
            [vrc setRenderingMode:mode];
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Invalid rendering mode");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRController cached");
    }

}

+ (void) VRControllerWLWW:(const osirixgrpc::VRController *) request :(osirixgrpc::VRControllerWLWWResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    VRController *vrc = [cache objectForUID:uid];
    
    if (vrc)
    {
        float wl, ww;
        [vrc getWLWW:&wl :&ww];
        response->set_wl(wl);
        response->set_ww(ww);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRController cached");
    }

}

+ (void) VRControllerSetWLWW:(const osirixgrpc::VRControllerSetWLWWRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->vr_controller().osirixrpc_uid());
    
    VRController *vrc = [cache objectForUID:uid];
    
    if (vrc)
    {
        float wl = request->wl();
        float ww = request->ww();
        [vrc setWLWW:wl :ww];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No VRController cached");
    }
}

@end
