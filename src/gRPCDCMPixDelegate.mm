#import "gRPCDCMPixDelegate.h"

#import <OsiriXAPI/DCMPix.h>
#import <OsiriXAPI/ROI.h>

@implementation gRPCDCMPixDelegate

+ (void) DCMPixConvertToRGB:(const osirixgrpc::DCMPixConvertToRGBRequest *) request  :(osirixgrpc::Response *) response : (gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->pix().osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        if (![pix isRGB])
        {
            int rgb_channel = request->rgb_channel();
            if (rgb_channel >= 0 && rgb_channel <= 3)
            {
                float cwl, cww;
                float min = FLT_MAX, max = FLT_MIN;
                float *data = [pix fImage];
                for (int i = 0; i < [pix pwidth] * [pix pheight]; i++) {
                    min = data[i] < min ? data[i] : min;
                    max = data[i] > max ? data[i] : max;
                }
                cwl = (min + max)/2;
                cww = max - min;
                [pix ConvertToRGB: (long)rgb_channel : (long)cwl: (long)cww];
                response->mutable_status()->set_status(1);
            }
            else
            {
                response->mutable_status()->set_status(0);
                response->mutable_status()->set_message("Requested RGB type not understood");
            }
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Data already RGB");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixConvertToBW:(const osirixgrpc::DCMPixConvertToBWRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->pix().osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        if ([pix isRGB])
        {
            int bw_channel = request->bw_channel();
            if (bw_channel >= 0 && bw_channel <= 3)
            {
                [pix ConvertToBW: (long)bw_channel];
                response->mutable_status()->set_status(1);
            }
            else
            {
                response->mutable_status()->set_status(0);
                response->mutable_status()->set_message("Requested BW type not understood");
            }
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Data already BW");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixIsRGB:(const osirixgrpc::DCMPix *) request : (osirixgrpc::DCMPixIsRGBResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        response->set_is_rgb([pix isRGB]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixComputeROI:(const osirixgrpc::DCMPixComputeROIRequest *) request :(osirixgrpc::DCMPixComputeROIResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->pix().osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        NSString *uid_roi = stringFromGRPCString(request->roi().osirixrpc_uid());
        ROI *roi = [cache objectForUID:uid_roi];
        if (roi)
        {
            float mean, total, dev, max, min;
            [pix computeROI:roi :&mean :&total :&dev :&min :&max];
            response->set_mean(mean);
            response->set_total(total);
            response->set_std_dev(dev);
            response->set_max(max);
            response->set_min(min);
            
            long count = 0;
            float *values = (float *)[pix getROIValue: &count :roi :nil];
            float kurtosis = [DCMPix kurtosis:values length:count mean:mean];
            float skewness = [DCMPix skewness:values length:count mean:mean];
            if (values)
            {
                free(values);
            }
            
            response->set_kurtosis(kurtosis);
            response->set_skewness(skewness);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("No ROI cached");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixROIValues:(const osirixgrpc::DCMPixROIValuesRequest *) request :(osirixgrpc::DCMPixROIValuesResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->pix().osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        NSString *uid_roi = stringFromGRPCString(request->roi().osirixrpc_uid());
        ROI *roi = [cache objectForUID:uid_roi];
        if (roi)
        {
            float *values;
            @try
            {
                long count = 0;
                float *locations;
                values = (float *)[pix getROIValue: &count :roi :&locations];
                
                for (int i = 0; i < count; i++)
                {
                    response->mutable_values()->Add(values[i]);
                    response->mutable_column_indices()->Add(locations[2 * i]);
                    response->mutable_row_indices()->Add(locations[2 * i + 1]);
                }
                response->mutable_status()->set_status(1);
            }
            @catch (NSException *exception)
            {
                response->mutable_status()->set_status(1);
                response->mutable_status()->set_message("Could not compute indices");
            }
            @finally
            {
                if (values)
                    free(values);
            }
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("No ROI cached");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixShape:(const osirixgrpc::DCMPix *) request :(osirixgrpc::DCMPixShapeResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        long w = [pix pwidth];
        long h = [pix pheight];
        response->set_columns((int) w);
        response->set_rows((int) h);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixSpacing:(const osirixgrpc::DCMPix *) request :(osirixgrpc::DCMPixSpacingResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        float spx = [pix pixelSpacingX];
        float spy = [pix pixelSpacingY];
        response->set_spacing_columns(spx);
        response->set_spacing_rows(spy);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixOrigin:(const osirixgrpc::DCMPix *) request :(osirixgrpc::DCMPixOriginResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        float orix = [pix originX];
        float oriy = [pix originY];
        float oriz = [pix originZ];
        response->set_origin_x(orix);
        response->set_origin_y(oriy);
        response->set_origin_z(oriz);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixOrientation:(const osirixgrpc::DCMPix *) request :(osirixgrpc::DCMPixOrientationResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        double orientation[9];
        [pix orientationDouble:orientation];
        for (int i = 0; i < 9; i++)
            response->mutable_orientation()->Add(orientation[i]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixSliceLocation:(const osirixgrpc::DCMPix *) request :(osirixgrpc::DCMPixSliceLocationResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        double sliceLocation = [pix sliceLocation];
        response->set_slice_location((float) sliceLocation);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixSourceFile:(const osirixgrpc::DCMPix *) request :(osirixgrpc::DCMPixSourceFileResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        NSString *sourceFile = [pix sourceFile];
        response->set_source_file([sourceFile UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixImage:(const osirixgrpc::DCMPix *) request :(osirixgrpc::DCMPixImageResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        @try
        {
            int width = (int)[pix pwidth];
            int height = (int)[pix pheight];
            response->set_columns(width);
            response->set_rows(height);
            if ([pix isRGB])
            {
                response->set_is_argb(TRUE);
                unsigned char *raw_data = (unsigned char *)[pix fImage];
                for (long i = 0; i < width * height * 4; i+=4)
                {
                    response->mutable_image_data_argb()->Add(raw_data[i]);
                    response->mutable_image_data_argb()->Add(raw_data[i+1]);
                    response->mutable_image_data_argb()->Add(raw_data[i+2]);
                    response->mutable_image_data_argb()->Add(raw_data[i+3]);
                }
            }
            else
            {
                response->set_is_argb(FALSE);
                float *raw_data = (float *)[pix fImage];
                for (long i = 0; i < width * height; i++)
                {
                    response->mutable_image_data_float()->Add(raw_data[i]);
                }
            }
            response->mutable_status()->set_status(1);
        }
        @catch (NSException *exception)
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Could not create image");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixSetImage:(const osirixgrpc::DCMPixSetImageRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->pix().osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        int width = (int)[pix pwidth];
        int height = (int)[pix pheight]; //TODO - I think gRPC allows you to get the size of a repeated element so better to use this.
        bool isArgb = [pix isRGB];
        
        @try
        {
            if (isArgb)
            {
                unsigned char *raw_data = (unsigned char *)[pix fImage];
                int data_size = request->image_data_argb_size();
                if (data_size == 4 * width * height)
                {
                    for (int i = 0; i < width * height * 4; i+=4)
                    {
                        raw_data[i] = (unsigned char)request->image_data_argb(i);
                        raw_data[i+1] = (unsigned char)request->image_data_argb(i+1);
                        raw_data[i+2] = (unsigned char)request->image_data_argb(i+2);
                        raw_data[i+3] = (unsigned char)request->image_data_argb(i+3);
                    }
                    response->mutable_status()->set_status(1);
                }
                else{
                    response->mutable_status()->set_status(0);
                    response->mutable_status()->set_message("Incompatible image shape");
                }
            }
            else
            {
                float *raw_data = (float *)[pix fImage];
                int data_size = request->image_data_float_size();
                if (data_size == width * height)
                {
                    for (int i = 0; i < width * height; i++)
                    {
                        raw_data[i] = request->image_data_float(i);
                    }
                    response->mutable_status()->set_status(1);
                }
                else
                {
                    response->mutable_status()->set_status(0);
                    response->mutable_status()->set_message("Incompatible image shape");
                }
            }
            
        }
        @catch (NSException *exception)
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Could not create image");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixGetMapFromROI:(const osirixgrpc::DCMPixGetMapFromROIRequest *) request :(osirixgrpc::DCMPixGetMapFromROIResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->pix().osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        NSString *uid_ = stringFromGRPCString(request->roi().osirixrpc_uid());
        ROI *roi = [cache objectForUID:uid_];
        if (roi)
        {
            if ([roi type] == tPlain || [roi type] == tCPolygon || [roi type] == tOPolygon || [roi type] == tPencil)
            {
                NSSize s;
                NSPoint o;
                unsigned char* texture;
                
                BOOL freeTexture = NO;
                if ([roi type] == tPlain) {
                    texture = [roi textureBuffer];
                    s.width = [roi textureWidth];
                    s.height = [roi textureHeight];
                    o.x = [roi textureUpLeftCornerX];
                    o.y = [roi textureUpLeftCornerY];
                }
                else
                {
                    texture = (unsigned char *)[DCMPix getMapFromPolygonROI: roi size: &s origin: &o];
                    freeTexture = YES;
                }
                
                int w = (int)[pix pwidth];
                int h = (int)[pix pheight];
                
                response->set_rows(h);
                response->set_columns(w);
                for (int i = 0; i < h; i++) {
                    for (int j = 0; j < w; j++) {
                        if(i>=o.y && j>=o.x && i<(o.y+s.height) && j<(o.x+s.width))
                        {
                            int idx = (i-o.y)*s.width + (j-o.x);
                            if (texture[idx] == 0xff)
                                response->mutable_map()->Add(TRUE);
                            else
                                response->mutable_map()->Add(FALSE);
                        }
                        else
                            response->mutable_map()->Add(FALSE);
                    }
                }
                
                if (freeTexture)
                    free(texture);
                
                response->mutable_status()->set_status(1);
            }
            else
            {
                response->mutable_status()->set_status(0);
                response->mutable_status()->set_message("Invalid ROI");
            }
                
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("No ROI cached");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
    
}

+ (void) DCMPixDicomImage:(const osirixgrpc::DCMPix *) request :(osirixgrpc::DCMPixDicomImageResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        DicomImage *dicomImage = [pix imageObj];
        NSString *dicomImageUID = [cache uidForObject:dicomImage];
        if (!dicomImageUID)
        {
            dicomImageUID = [cache addObject:dicomImage];
        }
        response->mutable_dicom_image()->set_osirixrpc_uid([dicomImageUID UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
}

+ (void) DCMPixDicomSeries:(const osirixgrpc::DCMPix *) request :(osirixgrpc::DCMPixDicomSeriesResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        DicomSeries *dicomSeries = [pix seriesObj];
        NSString *dicomSeriesUID = [cache uidForObject:dicomSeries];
        if (!dicomSeriesUID)
        {
            dicomSeriesUID = [cache addObject:dicomSeries];
        }
        response->mutable_dicom_series()->set_osirixrpc_uid([dicomSeriesUID UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
}

+ (void) DCMPixDicomStudy:(const osirixgrpc::DCMPix *) request :(osirixgrpc::DCMPixDicomStudyResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DCMPix *pix = [cache objectForUID:uid];
    
    if (pix)
    {
        DicomStudy *dicomStudy = [pix studyObj];
        NSString *dicomStudyUID = [cache uidForObject:dicomStudy];
        if (!dicomStudyUID)
        {
            dicomStudyUID = [cache addObject:dicomStudy];
        }
        response->mutable_dicom_study()->set_osirixrpc_uid([dicomStudyUID UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DCMPix cached");
    }
}

@end
