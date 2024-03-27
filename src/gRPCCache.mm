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
    [super dealloc];
}

-(id) init{
    cache = [NSMapTable mapTableWithKeyOptions:NSMapTableStrongMemory valueOptions:NSMapTableWeakMemory];
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

-(BOOL)doesContain:(id)obj
{
    return [cache doesContain:obj];
}

-(id)objectForUID:(NSString *)uid
{
    return [cache objectForKey:uid];
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

-(void)removeObject:(id)obj
{
    NSString *uid = [self uidForObject:obj];
    
    if (uid)
    {
        [cache removeObjectForKey:uid];
    }
}

@end
