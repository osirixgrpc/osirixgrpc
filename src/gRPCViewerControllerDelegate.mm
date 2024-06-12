#import "gRPCViewerControllerDelegate.h"

#import "vrcontroller.pb.h"
#import <OsiriXAPI/ViewerController.h>
#import <OsiriXAPI/VRController.h>
#import <OsiriXAPI/AppController.h>
#import <OsiriXAPI/ROI.h>
#import <OsiriXAPI/MyPoint.h>
#import <OsiriXAPI/DCMView.h>
#import <OsirixAPI/Notifications.h>

@implementation gRPCViewerControllerDelegate

+ (NSArray *) VRControllersAssociatedWithVewierController:(ViewerController *) viewer withStyle: (nullable NSString *)style
{
    NSArray *viewers = [[AppController sharedAppController] FindRelatedViewers:[viewer pixList:0]];
    NSMutableArray *vr_viewers = [NSMutableArray array];
    for( NSWindowController *v in viewers)
    {
        if( [v.windowNibName isEqualToString: @"VR"])
        {
            if (style)
            {
                VRController *vv = (VRController*) v;
                if( [vv.style isEqualToString: style])
                    [vr_viewers addObject:vv];
            }
            else
                [vr_viewers addObject:v];
        }
    }
    return vr_viewers;
}

+ (void) ViewerControllerCloseViewer:(const osirixgrpc::ViewerController *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        [[vc window] close];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerPixList:(const osirixgrpc::ViewerControllerPixListRequest *) request :(osirixgrpc::ViewerControllerPixListResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        long movie_idx = (long)request->movie_idx();
        NSArray *pixList = [vc pixList:movie_idx];
        for (DCMPix *pix in pixList)
        {
            NSString *pix_uid = [cache uidForObject:pix];
            if (!pix_uid)
            {
                pix_uid = [cache addObject:pix];
            }
            osirixgrpc::DCMPix *pix_ = response->mutable_pix()->Add();
            pix_->set_osirixrpc_uid([pix_uid UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerNeedsDisplayUpdate:(const osirixgrpc::ViewerController *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        response->mutable_status()->set_status(1);
        [vc needsDisplayUpdate];
        for( DCMView *v in [[vc seriesView] imageViews])
        {
            [v drawRect: [v frame]];
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerROIList:(const osirixgrpc::ViewerControllerROIListRequest *) request :(osirixgrpc::ViewerControllerROIListResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        long movie_idx = (long)request->movie_idx();
        NSArray *roiList = [vc roiList:movie_idx];
        
        for (NSArray *roi_slice in roiList)
        {
            osirixgrpc::ViewerControllerROIListResponse_ROISlice *roi_slice_ = response->mutable_roi_slices()->Add();
            
            for (ROI *roi in roi_slice)
            {
                NSString *roi_uid = [cache uidForObject:roi];
                if (!roi_uid)
                {
                    roi_uid = [cache addObject:roi];
                }
                osirixgrpc::ROI *roi_ = roi_slice_->mutable_rois()->Add();
                roi_->set_osirixrpc_uid([roi_uid UTF8String]);
            }
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerNewROI:(const osirixgrpc::ViewerControllerNewROIRequest *) request :(osirixgrpc::ViewerControllerNewROIResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        int iType = request->itype();
        NSString *name = stringFromGRPCString(request->name());
        DCMView *view = [vc imageView];
        ROI *roi = nil;
        switch (iType)
        {
            case tPlain:
            {
                int bufferRows = request->buffer().rows();
                int bufferColumns = request->buffer().columns();
                int bufferLength = request->buffer().buffer_size();
                if (bufferRows * bufferColumns == bufferLength)
                {
                    unsigned char *buffer = (unsigned char *)malloc(bufferLength * sizeof(unsigned char));
                    for (int i = 0; i < bufferLength; i++)
                    {
                        if (request->buffer().buffer(i))
                            buffer[i] = 0xff;
                        else
                            buffer[i] = 0x00;
                    }
                    int positionX = request->buffer_position_x();
                    int positionY = request->buffer_position_y();
                    roi = [[ROI alloc] initWithTexture:buffer
                                             textWidth:bufferColumns
                                            textHeight:bufferRows
                                              textName:name
                                             positionX:positionX
                                             positionY:positionY
                                              spacingX:view.curDCM.pixelSpacingX
                                              spacingY:view.curDCM.pixelSpacingY
                                           imageOrigin:[DCMPix originCorrectedAccordingToOrientation: view.curDCM]];
                }
                break;
            }
            
            case tDynAngle:
            case tAxis:
            case tCPolygon:
            case tOPolygon:
            case tMesure:
            case tArrow:
            case tAngle:
            case tPencil:
            case tLayerROI:
            case tTAGT:
            {
                roi = [[ROI alloc] initWithType:iType
                                               :view.curDCM.pixelSpacingX
                                               :view.curDCM.pixelSpacingY
                                               :[DCMPix originCorrectedAccordingToOrientation: view.curDCM]];
                
                [roi setName:name];
                
                int count = request->points_size();
                NSMutableArray *point_array = [NSMutableArray arrayWithCapacity:count];
                for (int i = 0; i < count; i++)
                {
                    NSPoint point;
                    osirixgrpc::ViewerControllerNewROIRequest_Point2D point_ = request->points(i);
                    point.x = point_.x();
                    point.y = point_.y();
                    MyPoint *point__ = [MyPoint point:point];
                    [point_array setObject:point__ atIndexedSubscript:i];
                }
                [roi setPoints:point_array];
                break;
            }
                
            case tOvalAngle:
            case tOval:
            case tText:
            case t2DPoint:
            case tROI:
            {
                NSRect rect;
                rect.origin.x = request->rectangle().origin_x();
                rect.origin.y = request->rectangle().origin_y();
                rect.size.height = request->rectangle().height();
                rect.size.width = request->rectangle().width();
                roi = [[ROI alloc] initWithType:iType
                                               :view.curDCM.pixelSpacingX
                                               :view.curDCM.pixelSpacingY
                                               :[DCMPix originCorrectedAccordingToOrientation: view.curDCM]];
                [roi setROIRect:rect];
                [roi setName:name];
                break;
            }
                
            default:
            break;
    
         
        }
        
        BOOL bOK;
        if (roi)
            bOK = [roi valid];
        
        if (!(roi == nil) && bOK)
        {
            // Set color
            int r = request->color().r();
            int g = request->color().g();
            int b = request->color().b();
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
            
            // Set thickness
            float thickness = request->thickness();
            [roi setThickness:thickness];
            
            // Set opacity
            float opacity = request->opacity();
            [roi setOpacity:opacity];
                
            // Add to viewer list
            int movieIdx = request->movie_idx();
            int idx = request->idx();
            NSMutableArray *rois = [vc roiList:movieIdx];
            [(NSMutableArray *)[rois objectAtIndex:idx] addObject:[roi autorelease]];
            
            // Set the DCMPix
            [roi setPix:[[vc pixList:movieIdx] objectAtIndex:idx]];
            
            // Add to cache
            NSString *roi_uid = [cache addObject:roi];
            response->mutable_roi()->set_osirixrpc_uid([roi_uid UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Could not create ROI");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerCurDCM:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerCurDCMResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        short movieIdx = [vc curMovieIndex];
        short idx = [(DCMView *)[vc imageView] curImage];
        NSArray *pixList = [vc pixList:movieIdx];
        DCMPix *pix = [pixList objectAtIndex:idx];
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
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerROIsWithName:(const osirixgrpc::ViewerControllerROIsWithNameRequest *) request :(osirixgrpc::ViewerControllerROIsWithNameResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        NSString *name = stringFromGRPCString(request->name())
        BOOL in4D = request->in_4d();
        
        NSArray *rois;
        if (in4D)
        {
            rois = [vc roisWithName:name in4D:TRUE];
        }
        else
        {
            int movie_idx = request->movie_idx();
            rois = [vc roisWithName:name forMovieIndex:movie_idx];
        }
        
        for (ROI *roi in rois)
        {
            NSString *roi_uid = [cache uidForObject:roi];
            if (!roi_uid)
            {
                roi_uid = [cache addObject:roi];
            }
            osirixgrpc::ROI *roi_ = response->mutable_rois()->Add();
            roi_->set_osirixrpc_uid([roi_uid UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerSelectedROIs:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerSelectedROIsResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        NSArray *rois = [vc selectedROIs];
        for (ROI *roi in rois)
        {
            NSString *roi_uid = [cache uidForObject:roi];
            if (!roi_uid)
            {
                roi_uid = [cache addObject:roi];
            }
            osirixgrpc::ROI *roi_ = response->mutable_rois()->Add();
            roi_->set_osirixrpc_uid([roi_uid UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerIsDataVolumic:(const osirixgrpc::ViewerControllerIsDataVolumicRequest *) request :(osirixgrpc::ViewerControllerIsDataVolumicResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        BOOL in4D = request->in_4d();
        BOOL isVolumic = [vc isDataVolumicIn4D:in4D];
        response->set_is_volumic(isVolumic);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerCopyViewerWindow:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerCopyViewerWindowResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())

    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        @try
        {
            ViewerController *new2DViewer = [vc copyViewerWindow];
            NSString *new_uid = [cache addObject:new2DViewer];
            response->mutable_viewer_controller()->set_osirixrpc_uid([new_uid UTF8String]);
            response->mutable_status()->set_status(1);
        }
        @catch (NSException *exception)
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Could not generate new viewer");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerResampleViewerController:(const osirixgrpc::ViewerControllerResampleViewerControllerRequest *) request :(osirixgrpc::ViewerControllerResampleViewerControllerResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        NSString *uid_fixed = stringFromGRPCString(request->fixed_viewer_controller().osirixrpc_uid())
        ViewerController *vc_fixed = [cache objectForUID:uid_fixed];
        if (vc_fixed)
        {
            ViewerController *new2DViewer = [vc_fixed resampleSeries:vc];
            NSString *new_uid = [cache addObject:new2DViewer];
            response->mutable_resampled_viewer()->set_osirixrpc_uid([new_uid UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("No fixed ViewerController cached");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerBlendingController:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerBlendingControllerResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        ViewerController *blending_viewer = [vc blendingController];
        if (blending_viewer)
        {
            NSString *blending_uid = [cache uidForObject:blending_viewer];
            if (!blending_uid)
            {
                blending_uid = [cache addObject:blending_viewer];
            }
            response->mutable_blending_viewer()->set_osirixrpc_uid([blending_uid UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("No blending controller active");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerVRControllers:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerVRControllersResponse *) response :(gRPCCache *) cache
{
    
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        NSArray *viewers = [gRPCViewerControllerDelegate VRControllersAssociatedWithVewierController:vc withStyle:nil];
        for( VRController *v in viewers)
        {
            NSString *vr_uid = [cache uidForObject:v];
            if (!vr_uid)
            {
                vr_uid = [cache addObject:v];
            }
            osirixgrpc::VRController *vrc = response->mutable_vr_controllers()->Add();
            vrc->set_osirixrpc_uid([vr_uid UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
    
}

+ (void) ViewerControllerTitle:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerTitleResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        NSString *title = [[vc window] title];
        response->set_title([title UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerModality:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerModalityResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        NSString *modality = [vc modality];
        response->set_modality([modality UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerMovieIdx:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerMovieIdxResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        short movie_idx = [vc curMovieIndex];
        response->set_movie_idx((int) movie_idx);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerSetMovieIdx:(const osirixgrpc::ViewerControllerSetMovieIdxRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        int movie_idx = request->movie_idx();
        if (movie_idx > [vc maxMovieIndex] || movie_idx < 0)
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Invalid movie index");
        }
        else
        {
            [vc setMovieIndex:(short)movie_idx];
            response->mutable_status()->set_status(1);
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerMaxMovieIdx:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerMaxMovieIdxResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        unsigned int maxMovieIndex = (unsigned int)[vc maxMovieIndex];
        response->set_max_movie_idx(maxMovieIndex);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerIdx:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerIdxResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        response->mutable_status()->set_status(1);
        response->set_idx((int)[[vc imageView] curImage]);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerSetIdx:(const osirixgrpc::ViewerControllerSetIdxRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        long idx = (long)request->idx();
        if (idx >= [[vc pixList] count] || idx < 0)
        {
            NSString *msg = [NSString stringWithFormat:@"Index %ld is out of range", idx];
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message([msg UTF8String]);
        }
        else
        {
            response->mutable_status()->set_status(1);
            [[vc imageView] setIndex:(unsigned short)idx];
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerDisplayedIdx:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerDisplayedIdxResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        response->mutable_status()->set_status(1);
        response->set_displayed_idx((int)[vc imageIndex]);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerSetDisplayedIdx:(const osirixgrpc::ViewerControllerSetDisplayedIdxRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        long idx = (long)request->displayed_idx();
        if (idx >= [[vc pixList] count] || idx < 0)
        {
            NSString *msg = [NSString stringWithFormat:@"Index %ld is out of range", idx];
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message([msg UTF8String]);
        }
        else
        {
            response->mutable_status()->set_status(1);
            [vc setImageIndex:(unsigned long)idx];
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerFlippedData:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerFlippedDataResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        response->mutable_status()->set_status(1);
        response->set_flipped_data([[vc imageView] flippedData]);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerWLWW:(const osirixgrpc::ViewerController *) request :(osirixgrpc::ViewerControllerWLWWResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        response->mutable_status()->set_status(1);
        response->set_wl([vc curWL]);
        response->set_ww([vc curWW]);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
    
}

+ (void) ViewerControllerSetWLWW:(const osirixgrpc::ViewerControllerSetWLWWRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        response->mutable_status()->set_status(1);
        [vc setWL:request->wl() WW:request->ww()];
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+ (void) ViewerControllerOpenVRViewerForMode:(const osirixgrpc::ViewerControllerOpenVRViewerForModeRequest *) request :(osirixgrpc::ViewerControllerOpenVRViewerForModeResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    
    if (vc)
    {
        NSString *mode = stringFromGRPCString(request->mode());
        if ([mode isEqualToString:@"VR"] || [mode isEqualToString:@"MIP"])
        {
            // Check whether one exists
            NSArray *viewers = [gRPCViewerControllerDelegate VRControllersAssociatedWithVewierController:vc withStyle:@"standard"];
            
            // Create one if not
            if([viewers count] == 0)
            {
                // Simulate a button click
                NSMenuItem *mitem = [[NSMenuItem alloc] initWithTitle:@"3D Volume Rendering" action:NULL keyEquivalent:@""];
                [mitem setTag:4];
                [vc VRViewer:mitem];
                [mitem release];
                
                // Find the opened window
                viewers = [gRPCViewerControllerDelegate VRControllersAssociatedWithVewierController:vc withStyle:@"standard"];
            }
            
            if ([viewers count] > 0)
            {
                VRController *vrc = (VRController *)[viewers objectAtIndex:0];
                [vrc setRenderingMode:mode];
                [[vrc window] makeKeyAndOrderFront:self];
                
                NSString *vrcUID = [cache uidForObject:vrc];
                if (!vrcUID)
                {
                    vrcUID = [cache addObject:vrc];
                }
                response->mutable_vr_controller()->set_osirixrpc_uid([vrcUID UTF8String]);
                response->mutable_status()->set_status(1);
            }
            else {
                response->mutable_status()->set_status(0);
                response->mutable_status()->set_message("Could not find opened VR window");
            }
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Unavailable mode");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

+(void) ViewerControllerFuseWithViewer:(const osirixgrpc::ViewerControllerFuseWithViewerRequest *)request :(osirixgrpc::Response *)response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->viewer_controller().osirixrpc_uid())
    
    ViewerController *vc = [cache objectForUID:uid];
    if (vc)
    {
        NSString *fuid = stringFromGRPCString(request->fusion_viewer_controller().osirixrpc_uid())
        ViewerController *fvc = [cache objectForUID:fuid];
        if (fvc)
        {
            [vc ActivateBlending:fvc];
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("No fusion ViewerController cached");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No ViewerController cached");
    }
}

@end
