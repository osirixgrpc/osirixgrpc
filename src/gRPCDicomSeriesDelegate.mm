#import "gRPCDicomSeriesDelegate.h"

#import <OsiriXAPI/DicomSeries.h>

@implementation gRPCDicomSeriesDelegate

+ (void) DicomSeriesPaths:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesPathsResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        NSSet *paths = [series paths];
        for (NSString *path in paths)
        {
            response->mutable_paths()->Add([path UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesPreviousSeries:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesPreviousSeriesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        DicomSeries *series_ = [series previousSeries];
        NSString *seriesUID = [cache uidForObject:series_];
        if (!seriesUID)
        {
            seriesUID = [cache addObject:series_];
        }
        response->mutable_previous_series()->set_osirixrpc_uid([seriesUID UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesNextSeries:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesNextSeriesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        DicomSeries *series_ = [series nextSeries];
        NSString *seriesUID = [cache uidForObject:series_];
        if (!seriesUID)
        {
            seriesUID = [cache addObject:series_];
        }
        response->mutable_next_series()->set_osirixrpc_uid([seriesUID UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesSortedImages:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesSortedImagesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        NSArray *images = [series sortedImages];
        for (DicomImage *image in images)
        {
            NSString *imageUID = [cache uidForObject:image];
            if (!imageUID)
            {
                imageUID = [cache addObject:image];
            }
            osirixgrpc::DicomImage *image_ = response->mutable_sorted_images()->Add();
            image_->set_osirixrpc_uid([imageUID UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesStudy:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesStudyResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        DicomStudy *study = [series study];
        NSString *studyUID = [cache uidForObject:study];
        if (!studyUID)
        {
            studyUID = [cache addObject:study];
        }
        response->mutable_study()->set_osirixrpc_uid([studyUID UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesImages:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesImagesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        NSSet *images = [series images];
        for (DicomImage *image in images)
        {
            NSString *imageUID = [cache uidForObject:image];
            if (!imageUID)
            {
                imageUID = [cache addObject:image];
            }
            osirixgrpc::DicomImage *image_ = response->mutable_images()->Add();
            image_->set_osirixrpc_uid([imageUID UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesSeriesInstanceUID:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesSeriesInstanceUIDResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        NSString *instanceUID = [series seriesInstanceUID];
        response->set_series_instance_uid([instanceUID UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesSeriesSOPClassUID:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesSeriesSOPClassUIDResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        NSString *seriesSOPClassUID = [series seriesSOPClassUID];
        response->set_series_sop_class_uid([seriesSOPClassUID UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesSeriesDescription:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesSeriesDescriptionResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        NSString *seriesDescription = [series seriesDescription];
        response->set_series_description([seriesDescription UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesModality:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesModalityResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        NSString *modality = [series modality];
        response->set_modality([modality UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesName:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesNameResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        NSString *name = [series name];
        response->set_name([name UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

+ (void) DicomSeriesDate:(const osirixgrpc::DicomSeries *) request :(osirixgrpc::DicomSeriesDateResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomSeries *series = [cache objectForUID:uid];
    
    if (series)
    {
        NSDate *date = [series date];
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
        response->mutable_status()->set_message("No DicomSeries cached");
    }
    
}

@end
