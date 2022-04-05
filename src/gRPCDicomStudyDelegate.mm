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
        if (modalities)
        {
            response->set_modalities([modalities UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Modalities not available");
        }
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
        NSNumber * noFiles = [study noFiles];
        if (noFiles)
        {
            response->set_no_files([noFiles intValue]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Number of files not available");
        }
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
        NSNumber *rawNoFiles = [study rawNoFiles];
        if (rawNoFiles)
        {
            response->set_no_files([rawNoFiles intValue]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Raw number of files not available");
        }
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
        NSNumber *noFilesExcludingMultiFrames = [study noFilesExcludingMultiFrames];
        if (noFilesExcludingMultiFrames)
        {
            response->set_no_files([noFilesExcludingMultiFrames intValue]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Number of files exclusing multi frames not available");
        }
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
        NSNumber *numberOfImages = [study numberOfImages];
        if (numberOfImages)
        {
            response->set_no_images([numberOfImages intValue]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Number of images not available");
        }
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
        if (name)
        {
            response->set_name([name UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Study name not available");
        }
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
        if (date)
        {
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
            response->mutable_status()->set_message("Study date not available");
        }
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
        if (date)
        {
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
            response->mutable_status()->set_message("Date added not available");
        }
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
        if (date)
        {
            NSDateComponents *comps = [[NSCalendar currentCalendar] components: NSCalendarUnitDay | NSCalendarUnitMonth | NSCalendarUnitYear fromDate:date];
            response->set_year((int)[comps year]);
            response->set_month((int)[comps month]);
            response->set_day((int)[comps day]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Date of birth not available");
        }
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
        NSString *institutionName = [study institutionName];
        if (institutionName)
        {
            response->set_institution_name([institutionName UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Institution name not available");
        }
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
        NSString *modality = [study modality];
        if (modality)
        {
            response->set_modality([modality UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Modality not available");
        }
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
        NSString *patientID = [study patientID];
        if (patientID)
        {
            response->set_patient_id([patientID UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Patient ID not available");
        }
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
        NSString *patientUID = [study patientUID];
        if (patientUID)
        {
            response->set_patient_uid([patientUID UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Patient UID not available");
        }
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
        NSString *patientSex = [study patientSex];
        if (patientSex)
        {
            response->set_patient_sex([patientSex UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Patient sex not available");
        }
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
        NSString *performingPhysician = [study performingPhysician];
        if (performingPhysician)
        {
            response->set_performing_physician([performingPhysician UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Performing physician not available");
        }
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
        NSString *referringPhysician = [study referringPhysician];
        if (referringPhysician)
        {
            response->set_referring_physician([referringPhysician UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Referring physician not available");
        }
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
        NSString *studyInstanceUID = [study studyInstanceUID];
        if (studyInstanceUID)
        {
            response->set_study_instance_uid([studyInstanceUID UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Study instance UID not available");
        }
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
        NSString *studyName = [study studyName];
        if (studyName)
        {
            response->set_study_name([[study studyName] UTF8String]);
            response->mutable_status()->set_status(1);
        }
        else
        {
            response->mutable_status()->set_status(0);
            response->mutable_status()->set_message("Study name not available");
        }
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No DicomStudy cached");
    }
    
}

@end
