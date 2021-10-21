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
    [[NSNotificationCenter defaultCenter] removeObserver:self name:OsirixActiveLocalDatabaseDidChangeNotification object:nil];
    [super dealloc];
}

-(id) init{
    cache = [[NSMutableDictionary alloc] init];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(osirixRemoveROINotificationTarget:) name:OsirixRemoveROINotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(osirixCloseViewerNotificationTarget:) name:OsirixCloseViewerNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(osirixWindow3dCloseNotificationTarget:) name:OsirixWindow3dCloseNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(OsirixActiveLocalDatabaseDidChangeNotificationTarget:) name:OsirixActiveLocalDatabaseDidChangeNotification object:nil];
    return self;
}

-(void)osirixRemoveROINotificationTarget:(NSNotification *)notification
{
    // Remove the ROI if present.
    ROI *roi = [notification object];
    if ([self doesContain:roi])
    {
        [self removeObject:roi];
    }
}

-(void)osirixCloseViewerNotificationTarget:(NSNotification *)notification
{
    // A little more complicated as need to check for DCMPix also.  ROIs should be dealt with by another function.
    ViewerController *vc = [notification object];
    for (long j = 0; j < [vc maxMovieIndex]; j++)
    {
        NSArray *pixList = [vc pixList:j];
        
        for (DCMPix *pix in pixList){
            if ([self doesContain:pix])
            {
                [self removeObject:pix];
            }
        }
    }
    [self removeObject:vc];
}

-(void)osirixWindow3dCloseNotificationTarget:(NSNotification *)notification
{
    VRController *vc = [notification object];
    if ([self doesContain:vc])
    {
        [self removeObject:vc];
    }
}

-(void)OsirixActiveLocalDatabaseDidChangeNotificationTarget:(NSNotification *)notification
{
    // Might as well remove everything other than the BrowserController as everything will be closed down.
    for (id object in [cache objectEnumerator])
    {
        if (![object isKindOfClass:[BrowserController class]])
        {
            [self removeObject:object];
        }
    }
}

-(NSString *)generateUniqueID
{
    NSString *uid = [[NSUUID UUID] UUIDString];
    return uid;
}

-(BOOL)doesContain:(id)object
{
    return [cache doesContain:object];
}

-(id)objectForUID:(NSString *)uid
{
    return [cache objectForKey:uid];
}

-(NSString *)uidForObject:(id)object
{
    NSString *uid = nil;
    for (NSString *uid_ in [cache keyEnumerator])
    {
        void * object_ = [cache objectForKey:uid_];
        if (object_ == object)
        {
            uid = uid_;
        }
    }
    return uid;
}

-(NSArray *)uids
{
    return [cache allKeys];
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

-(void)removeObject:(id)obj
{
    NSString *uid = [self uidForObject:obj];
    
    if (uid)
    {
        [cache removeObjectForKey:uid];
    }
}

@end
