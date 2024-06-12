#import "gRPCDicomImageDelegate.h"

#import <OsiriXAPI/DicomImage.h>

@implementation gRPCDicomImageDelegate

+ (void) DicomImageWidth:(const osirixgrpc::DicomImage *) request :(osirixgrpc::DicomImageWidthResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomImage *image = [cache objectForUID:uid];
    
    if (image)
    {
        NSNumber *width = [image width];
        response->set_width([width intValue]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomImage cached");
    }
    
}

+ (void) DicomImageHeight:(const osirixgrpc::DicomImage *) request :(osirixgrpc::DicomImageHeightResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomImage *image = [cache objectForUID:uid];
    
    if (image)
    {
        NSNumber *height = [image height];
        response->set_height([height intValue]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomImage cached");
    }
    
}

+ (void) DicomImageSOPInstanceUID:(const osirixgrpc::DicomImage *) request :(osirixgrpc::DicomImageSOPInstanceUIDResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomImage *image = [cache objectForUID:uid];
    
    if (image)
    {
        NSString *sopUID = [image sopInstanceUID];
        response->set_sop_instance_uid([sopUID UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomImage cached");
    }
    
}

+ (void) DicomImageCompletePath:(const osirixgrpc::DicomImage *) request :(osirixgrpc::DicomImageCompletePathResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomImage *image = [cache objectForUID:uid];
    
    if (image)
    {
        NSString *path = [image completePath];
        response->set_complete_path([path UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomImage cached");
    }
    
}

+ (void) DicomImageDate:(const osirixgrpc::DicomImage *)request :(osirixgrpc::DicomImageDateResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomImage *image = [cache objectForUID:uid];
    
    if (image)
    {
        NSDate *date = [image date];
        NSDateComponents *comps = [[NSCalendar currentCalendar] components:NSCalendarUnitNanosecond | NSCalendarUnitSecond | NSCalendarUnitMinute | NSCalendarUnitHour | NSCalendarUnitDay | NSCalendarUnitMonth | NSCalendarUnitYear fromDate:date];
        response->set_year((int)[comps year]);
        response->set_month((int)[comps month]);
        response->set_day((int)[comps day]);
        response->set_hour((int)[comps hour]);
        response->set_minute((int)[comps minute]);
        response->set_second((int)[comps second]);
        response->set_millisecond(1000 * (int)[comps nanosecond]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomImage cached");
    }
    
}

+ (void) DicomImageNumberOfFrames:(const osirixgrpc::DicomImage *) request :(osirixgrpc::DicomImageNumberOfFramesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomImage *image = [cache objectForUID:uid];
    
    if (image)
    {
        int frames = [[image numberOfFrames] intValue];
        response->set_number_of_frames(frames);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomImage cached");
    }
    
}

+ (void) DicomImageModality:(const osirixgrpc::DicomImage *) request :(osirixgrpc::DicomImageModalityResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomImage *image = [cache objectForUID:uid];
    
    if (image)
    {
        response->set_modality([[image modality] UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomImage cached");
    }
    
}

+ (void) DicomImageSeries:(const osirixgrpc::DicomImage *) request :(osirixgrpc::DicomImageSeriesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomImage *image = [cache objectForUID:uid];
    
    if (image)
    {
        DicomSeries *series = [image series];
        NSString *seriesUID = [cache uidForObject:series];
        if (!seriesUID)
        {
            seriesUID = [cache addObject:series];
        }
        response->mutable_series()->set_osirixrpc_uid([seriesUID UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomImage cached");
    }
    
}

+ (void) DicomImageSliceLocation:(const osirixgrpc::DicomImage *) request :(osirixgrpc::DicomImageSliceLocationResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomImage *image = [cache objectForUID:uid];
    
    if (image)
    {
        response->set_slice_location([[image sliceLocation] floatValue]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomImage cached");
    }
    
}

+ (void) DicomImageInstanceNumber:(const osirixgrpc::DicomImage *) request :(osirixgrpc::DicomImageInstanceNumberResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomImage *image = [cache objectForUID:uid];
    
    if (image)
    {
        response->set_instance_number([[image instanceNumber] intValue]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomImage cached");
    }
    
}

@end
