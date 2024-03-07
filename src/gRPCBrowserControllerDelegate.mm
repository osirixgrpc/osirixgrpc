#import "gRPCBrowserControllerDelegate.h"

#import <OsiriXAPI/browserController.h>

@implementation gRPCBrowserControllerDelegate

+ (void) BrowserControllerDatabaseSelection:(const osirixgrpc::BrowserController *) request :(osirixgrpc::BrowserControllerDatabaseSelectionResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->osirixrpc_uid());
    
    BrowserController *bc = [cache objectForUID:uid];
    
    if (bc)
    {
        NSArray *selection = [bc databaseSelection];
        for (id item in selection)
        {
            if ([item isKindOfClass:[DicomStudy class]])
            {
                NSString *studyUID = [cache uidForObject:item];
                if (!studyUID)
                {
                    studyUID = [cache addObject:item];
                }
                osirixgrpc::DicomStudy *study_ = response->mutable_studies()->Add();
                study_->set_osirixrpc_uid([studyUID UTF8String]);
            }
            else if ([item isKindOfClass:[DicomSeries class]])
            {
                NSString *seriesUID = [cache uidForObject:item];
                if (!seriesUID)
                {
                    seriesUID = [cache addObject:item];
                }
                osirixgrpc::DicomSeries *series_ = response->mutable_series()->Add();
                series_->set_osirixrpc_uid([seriesUID UTF8String]);
            }
        }
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No BrowserController cached");
    }

}

+ (void) BrowserControllerCopyFilesIfNeeded:(const osirixgrpc::BrowserControllerCopyFilesIfNeededRequest *) request :(osirixgrpc::Response *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->browser().osirixrpc_uid());
    
    BrowserController *bc = [cache objectForUID:uid];
    
    if (bc)
    {
        int n_paths = request->paths_size();
        NSMutableArray *paths = [NSMutableArray array];
        for (int i = 0; i < n_paths; i++)
        {
            NSString *path = stringFromGRPCString(request->paths(i));
            [paths addObject:path];
        }
        [bc copyFilesIntoDatabaseIfNeeded:paths options:[NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:YES], @"COPYDATABASE", [NSNumber numberWithInt:0], @"COPYDATABASEMODE", [NSNumber numberWithBool:YES], @"async", nil]];
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No BrowserController cached");
    }

}

+ (void) BrowserControllerOpenViewerFromImages:(const osirixgrpc::BrowserControllerOpenViewerFromImagesRequest *) request :(osirixgrpc::BrowserControllerOpenViewerFromImagesResponse *) response :(gRPCCache *) cache
{
    NSString *uid = stringFromGRPCString(request->browser().osirixrpc_uid());

    BrowserController *bc = [cache objectForUID:uid];

    if (bc)
    {
        NSMutableArray *frames = [NSMutableArray init];
        int n_frames = request->frames_size();
        for (int i = 0; i < n_frames; i++) {
            osirixgrpc::BrowserControllerOpenViewerFromImagesRequest_FrameImages frame = request->frames(i);
            NSMutableArray *frame_images = [NSMutableArray init];
            int n_images = frame.images_size();
            for (int j = 0; j < n_images; j++) {
                osirixgrpc::DicomImage dicom_image = frame.images(j);
                NSString *dicom_image_uid = stringFromGRPCString(dicom_image.osirixrpc_uid());
                DicomImage *image = [cache objectForUID:dicom_image_uid];
                [frame_images addObject:image];
            }
            [frames addObject:frame_images];
        }
        ViewerController *opened_viewer = [bc openViewerFromImages:frames movie:request->movie() viewer:nil keyImagesOnly:NO];
        
        // Add to cache
        NSString *viewer_uid = [cache addObject:opened_viewer];
        response->mutable_viewer()->set_osirixrpc_uid([viewer_uid UTF8String]);
        response->mutable_status()->set_status(1);
    }
    else
    {
        response->mutable_status()->set_status(0);
        response->mutable_status()->set_message("No BrowserController cached");
    }

}

@end
