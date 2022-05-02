#import "gRPCROIVolumeDelegate.h"

#import <OsiriXAPI/ROIVolume.h>

@implementation gRPCROIVolumeDelegate

+ (void) ROIVolumeTexture:(const osirixgrpc::ROIVolume *) request :(osirixgrpc::ROIVolumeTextureResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        BOOL texture = [rv texture];
        response->set_texture(texture);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
}

+ (void) ROIVolumeSetTexture:(const osirixgrpc::ROIVolumeSetTextureRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        BOOL texture = request->texture();
        [rv setTexture:texture];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
}

+ (void) ROIVolumeVolume:(const osirixgrpc::ROIVolume *) request :(osirixgrpc::ROIVolumeVolumeResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        float volume = [rv volume];
        response->set_volume(volume);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
}

+ (void) ROIVolumeColor:(const osirixgrpc::ROIVolume *) request :(osirixgrpc::ROIVolumeColorResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        response->set_r([rv red]);
        response->set_g([rv green]);
        response->set_b([rv blue]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
    
}

+ (void) ROIVolumeSetColor:(const osirixgrpc::ROIVolumeSetColorRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        [rv setRed:(float) request->r()];
        [rv setGreen:(float) request->g()];
        [rv setBlue:(float) request->b()];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
}

+ (void) ROIVolumeOpacity:(const osirixgrpc::ROIVolume *) request :(osirixgrpc::ROIVolumeOpacityResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        float opacity = [rv opacity];
        response->set_opacity(opacity);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
}

+ (void) ROIVolumeSetOpacity:(const osirixgrpc::ROIVolumeSetOpacityRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        float opacity = request->opacity();
        [rv setOpacity:opacity];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
}

+ (void) ROIVolumeFactor:(const osirixgrpc::ROIVolume *) request :(osirixgrpc::ROIVolumeFactorResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        float factor = [rv factor];
        response->set_factor(factor);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
}

+ (void) ROIVolumeSetFactor:(const osirixgrpc::ROIVolumeSetFactorRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        float factor = request->factor();
        [rv setFactor:factor];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
}

+ (void) ROIVolumeVisible:(const osirixgrpc::ROIVolume *) request :(osirixgrpc::ROIVolumeVisibleResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        BOOL visible = [rv visible];
        response->set_visible(visible);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
    
}

+ (void) ROIVolumeName:(const osirixgrpc::ROIVolume *) request :(osirixgrpc::ROIVolumeNameResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROIVolume *rv = [cache objectForUID:uid];
    
    if (rv)
    {
        NSString *name = [rv name];
        response->set_name([name UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROIVolume cached");
    }
    
}

@end
