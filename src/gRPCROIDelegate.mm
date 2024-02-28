#import "gRPCROIDelegate.h"

#import <OsiriXAPI/DCMPix.h>
#import <OsiriXAPI/ROI.h>
#import <OsiriXAPI/MyPoint.h>
#import <OsiriXAPI/Notifications.h>

@implementation gRPCROIDelegate

+ (void) ROIFlipHorizontally:(const osirixgrpc::ROI *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        [roi flipVertically:NO];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIFlipVertically:(const osirixgrpc::ROI *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        [roi flipVertically:YES];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIArea:(const osirixgrpc::ROI *) request :(osirixgrpc::ROIAreaResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        float area = [roi area];
        response->set_area(area);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROICentroid:(const osirixgrpc::ROI *) request :(osirixgrpc::ROICentroidResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        NSPoint point = [roi centroid];
        response->set_x((float) point.x);
        response->set_y((float) point.y);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIRotate:(const osirixgrpc::ROIRotateRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        NSPoint point;
        point.x = request->x();
        point.y = request->y();
        float degrees = request->degrees();
        [roi rotate:degrees :point];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIMove:(const osirixgrpc::ROIMoveRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        NSPoint point;
        point.x = request->columns();
        point.y = request->rows();
        ROI_mode mode = [roi ROImode];
        if (mode == ROI_selected)
        {
            [roi roiMove:point];
        }
        else
        {
            [roi setROIMode:ROI_selected];
            [roi roiMove:point];
            [roi setROIMode:mode];
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIPix:(const osirixgrpc::ROI *) request :(osirixgrpc::ROIPixResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        DCMPix *pix = [roi pix];
        NSString *pix_uid = [cache uidForObject:pix];
        if (!pix_uid)
        {
            pix_uid = [cache addObject:pix];
        }
        response->mutable_pix()->set_osirixrpc_uid([pix_uid UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIIType:(const osirixgrpc::ROI *) request :(osirixgrpc::ROIITypeResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        int itype = (int)[roi type];
        response->set_itype(itype);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIName:(const osirixgrpc::ROI *) request :(osirixgrpc::ROINameResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        NSString *name = [roi name];
        response->set_name([name UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROISetName:(const osirixgrpc::ROISetNameRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        NSString *name = stringFromGRPCString(request->name());
        [roi setName:name];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIColor:(const osirixgrpc::ROI *) request :(osirixgrpc::ROIColorResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        RGBColor color = [roi rgbcolor];
        response->set_r((int) color.red / 256);
        response->set_g((int) color.green / 256);
        response->set_b((int) color.blue / 256);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROISetColor:(const osirixgrpc::ROISetColorRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        int r = request->r();
        int g = request->g();
        int b = request->b();
        r = r > 255 ? 255 : r;
        r = r < 0 ? 0 : r;
        g = g > 255 ? 255 : g;
        g = g < 0 ? 0 : g;
        b = b > 255 ? 255 : b;
        b = b < 0 ? 0 : b;
        
        RGBColor color;
        color.red = (unsigned short) (r * 256);
        color.green = (unsigned short) (g * 256);
        color.blue = (unsigned short) (b * 256);
        [roi setColor:color];

        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIOpacity:(const osirixgrpc::ROI *) request :(osirixgrpc::ROIOpacityResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        float opacity = [roi opacity];
        response->set_opacity(opacity);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROISetOpacity:(const osirixgrpc::ROISetOpacityRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        float opacity = request->opacity();
        opacity = opacity > 1.0 ? 1.0 : opacity;
        opacity = opacity < 0.0 ? 0.0 : opacity;
        [roi setOpacity:opacity];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIThickness:(const osirixgrpc::ROI *) request :(osirixgrpc::ROIThicknessResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        float thickness = [roi thickness];
        response->set_thickness(thickness);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROISetThickness:(const osirixgrpc::ROISetThicknessRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        float thickness = request->thickness();
        [roi setThickness:thickness];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROIPoints:(const osirixgrpc::ROI *) request :(osirixgrpc::ROIPointsResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        NSArray *points = [roi points];
        for (int i = 0; i < [points count]; i++)
        {
            MyPoint *point = [points objectAtIndex:i];
            osirixgrpc::ROIPointsResponse_Point2D *point_ = response->mutable_points()->Add();
            point_->set_x((float)[point x]);
            point_->set_y((float)[point y]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

+ (void) ROISetPoints:(const osirixgrpc::ROISetPointsRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->roi().osirixrpc_uid());
    
    ROI *roi = [cache objectForUID:uid];
    
    if (roi)
    {
        int count = request->points_size();
        NSMutableArray *point_array = [NSMutableArray arrayWithCapacity:count];
        for (int i = 0; i < count; i++)
        {
            NSPoint point;
            osirixgrpc::ROISetPointsRequest_Point2D point_ = request->points(i);
            point.x = point_.x();
            point.y = point_.y();
            MyPoint *point__ = [MyPoint point:point];
            [point_array setObject:point__ atIndexedSubscript:i];
        }
        [roi setPoints:point_array];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ROI cached");
    }
    
}

@end
