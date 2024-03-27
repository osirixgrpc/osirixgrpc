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
    id obj = [cache objectForKey:uid];
    
    // Check whether still active
    if (obj == nil) {
        [cache removeObjectForKey:uid];
    }
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

-(void)removeObject:(id)obj
{
    NSString *uid = [self uidForObject:obj];
    
    if (uid)
    {
        [cache removeObjectForKey:uid];
    }
}

@end
