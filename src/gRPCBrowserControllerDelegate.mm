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

@end
