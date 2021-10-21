#import "gRPCDicomStudyDelegate.h"

#import <OsiriXAPI/DicomStudy.h>

@implementation gRPCDicomStudyDelegate

+ (void) DicomStudyPaths:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyPathsResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        NSSet *paths = [study paths];
        for (NSString *path in paths)
        {
            response->mutable_paths()->Add([path UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
}

+ (void) DicomStudyImages:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyImagesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        NSSet *images = [study images];
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
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyModalities:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyModalitiesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        NSString *modalities = [study modalities];
        response->set_modalities([modalities UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyNoFiles:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyNoFilesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_no_files([[study noFiles] intValue]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyRawNoFiles:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyRawNoFilesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_no_files([[study rawNoFiles] intValue]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyNoFilesExcludingMultiFrames:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyNoFilesExcludingMultiFramesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_no_files([[study noFilesExcludingMultiFrames] intValue]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyNumberOfImages:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyNumberOfImagesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_no_images([[study numberOfImages] intValue]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudySeries:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudySeriesResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        NSSet *series = [study series];
        for (DicomSeries *serie in series)
        {
            NSString *seriesUID = [cache uidForObject:serie];
            if (!seriesUID)
            {
                seriesUID = [cache addObject:serie];
            }
            osirixgrpc::DicomSeries *serie_ = response->mutable_series()->Add();
            serie_->set_osirixrpc_uid([seriesUID UTF8String]);
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyName:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyNameResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        NSString *name = [study name];
        response->set_name([name UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyDate:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyDateResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        NSDate *date = [study date];
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
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyDateAdded:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyDateAddedResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        NSDate *date = [study dateAdded];
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
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyDateOfBirth:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyDateOfBirthResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        NSDate *date = [study dateOfBirth];
        NSDateComponents *comps = [[NSCalendar currentCalendar] components: NSCalendarUnitDay | NSCalendarUnitMonth | NSCalendarUnitYear fromDate:date];
        response->set_year((int)[comps year]);
        response->set_month((int)[comps month]);
        response->set_day((int)[comps day]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyInstitutionName:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyInstitutionNameResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_institution_name([[study institutionName] UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyModality:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyModalityResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_modality([[study modality] UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyPatientID:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyPatientIDResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_patient_id([[study patientID] UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyPatientUID:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyPatientUIDResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_patient_uid([[study patientUID] UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyPatientSex:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyPatientSexResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_patient_sex([[study patientSex] UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyPerformingPhysician:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyPerformingPhysicianResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_performing_physician([[study performingPhysician] UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyReferringPhysician:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyReferringPhysicianResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_referring_physician([[study referringPhysician] UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyStudyInstanceUID:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyStudyInstanceUIDResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_study_instance_uid([[study studyInstanceUID] UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

+ (void) DicomStudyStudyName:(const osirixgrpc::DicomStudy *) request :(osirixgrpc::DicomStudyStudyNameResponse *) response :(gRPCCache *)cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    DicomStudy *study = [cache objectForUID:uid];
    
    if (study)
    {
        response->set_study_name([[study studyName] UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

@end
