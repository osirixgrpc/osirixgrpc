#import <OsiriXAPI/Notifications.h>
#import <OsiriXAPI/ROI.h>
#import <OsiriXAPI/ViewerController.h>
#import <OsiriXAPI/browserController.h>
#import <OsiriXAPI/VRController.h>
#import <OsiriXAPI/DCMPix.h>
#import <OsiriXAPI/DicomImage.h>
#import <OsiriXAPI/DicomSeries.h>
#import <OsiriXAPI/DicomStudy.h>

#import "gRPCCache.h"

@implementation gRPCCache

static gRPCCache *_objectCache = nil;

+ (gRPCCache *)objectCache
{
    if (_objectCache == nil)
    {
        _objectCache = [[gRPCCache alloc] init];
    }
    return _objectCache;
}

-(void) dealloc{
    [cache release];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:OsirixRemoveROINotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:OsirixCloseViewerNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:OsirixWindow3dCloseNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NSOutlineViewSelectionDidChangeNotification object:nil];
    [super dealloc];
}

-(id) init{
    cache = [NSMapTable mapTableWithKeyOptions:NSMapTableStrongMemory valueOptions:NSMapTableWeakMemory];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(osirixRemoveROINotificationTarget:) name:OsirixRemoveROINotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(osirixCloseViewerNotificationTarget:) name:OsirixCloseViewerNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(osirixWindow3dCloseNotificationTarget:) name:OsirixWindow3dCloseNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(NSOutlineViewSelectionDidChangeNotificationTarget:) name:NSOutlineViewSelectionDidChangeNotification object:[BrowserController currentBrowser]];
    return self;
}

- (void) cleanUpNilFiles {
    for (NSString *uid in [cache keyEnumerator]){
        id object = [cache objectForKey:uid];
        if (object == nil) {
            [cache removeObjectForKey:uid];
        }
    }
}

- (void) cleanupDatabaseFiles {
    // This is a little hacky.  This will be called prior to every access to look for stragglers.
    // These checks have some nasty dependecies and need to be run in order.
    
    // 0. Storage array
    NSMutableArray *uids_to_remove = [NSMutableArray array];
    
    // 1. Clean up images wth no file.
    for (NSString *uid in [cache keyEnumerator])
    {
        id object = [cache objectForKey:uid];
        if ([object isKindOfClass:[DicomImage class]]) {
            if (![[NSFileManager defaultManager] fileExistsAtPath:[(DicomImage *)object completePath]])
            {
                [uids_to_remove addObject:uid];
            }
        }
    }
    [self removeObjectsWithUids:uids_to_remove];
    [uids_to_remove removeAllObjects];
    
    // 2. Clean up series wth no images.
    for (NSString *uid in [cache keyEnumerator])
    {
        id object = [cache objectForKey:uid];
        if ([object isKindOfClass:[DicomSeries class]]) {
            if ([(DicomSeries *)object numberOfImages] == 0)
            {
                [uids_to_remove addObject:uid];
            }
        }
    }
    [self removeObjectsWithUids:uids_to_remove];
    [uids_to_remove removeAllObjects];
    
    // 3. Clean up studies wth no series.
    for (NSString *uid in [cache keyEnumerator])
    {
        id object = [cache objectForKey:uid];
        if ([object isKindOfClass:[DicomStudy class]]) {
            if ([[(DicomStudy *)object series] count] == 0)
            {
                [uids_to_remove addObject:uid];
            }
        }
    }
    [self removeObjectsWithUids:uids_to_remove];
    [uids_to_remove removeAllObjects];
}

-(void)osirixRemoveROINotificationTarget:(NSNotification *)notification
{
    ROI *roi = [notification object];
    if ([self doesContain:roi])
    {
        [self removeObject:roi];
    }
    [self cleanUpNilFiles];
}

-(void)osirixCloseViewerNotificationTarget:(NSNotification *)notification
{
    ViewerController *vc = [notification object];
    for (long j = 0; j < [vc maxMovieIndex]; j++)
    {
        NSArray *pixList = [vc pixList:j];
        NSArray *roiList = [vc roiList:j];
        
        for (DCMPix *pix in pixList){
            if ([self doesContain:pix])
            {
                [self removeObject:pix];
            }
        }
        for (NSArray *roi_slice in roiList){
            for (ROI *roi in roi_slice)
            {
                if ([self doesContain:roi])
                {
                    [self removeObject:roi];
                }
            }
        }
    }
    [self removeObject:vc];
    [self cleanUpNilFiles];
}

-(void)osirixWindow3dCloseNotificationTarget:(NSNotification *)notification
{
    VRController *vc = [notification object];
    if ([self doesContain:vc])
    {
        [self removeObject:vc];
    }
    [self cleanUpNilFiles];
}

-(void)NSOutlineViewSelectionDidChangeNotificationTarget:(NSNotification *)notification
{
    [self cleanupDatabaseFiles];
    [self cleanUpNilFiles];
}

-(NSString *)generateUniqueID
{
    NSString *uid = [[NSUUID UUID] UUIDString];
    return uid;
}

-(BOOL)doesContain:(id)obj
{
    bool containsObject = NO;
    for (id o in [cache objectEnumerator]) {
        if (o == obj) {
            containsObject = YES;
            break;
        }
    }
    return containsObject;
}

-(id)objectForUID:(NSString *)uid
{
    id obj = [cache objectForKey:uid];
    return obj;
}

-(NSString *)uidForObject:(id)obj
{
    NSString *uid = nil;
    for (NSString *uid_ in [cache keyEnumerator])
    {
        void * obj_ = [cache objectForKey:uid_];
        if (obj_ == obj)
        {
            uid = uid_;
        }
    }
    return uid;
}

-(NSArray *)uids
{
    NSEnumerator *keyEnumerator = [cache keyEnumerator];
    return [keyEnumerator allObjects];
}

-(void)clearCache
{
    [cache removeAllObjects];
}

-(NSString *)addObject:(id)obj{
    
    NSString *uid = [self uidForObject:obj];
    if(!uid)
    {
        uid = [self generateUniqueID];
        [cache setObject:obj forKey:uid];
    }
    return uid;
}

-(void) removeObjectsWithUids: (NSArray *)uids
{
    for (NSString* uid in uids)
        [cache removeObjectForKey:uid];
}

-(void)removeObject:(id)obj
{
    NSString *uid = [self uidForObject:obj];
    if (uid)
    {
        [cache removeObjectForKey:uid];
    }
}

@end
