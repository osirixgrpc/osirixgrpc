#import <Foundation/Foundation.h>

/**
 `gRPCCache` is used for storing references to all requested OsiriX objects (e.g. DCMPix, ROI, DicomImage) by an external client.
 It holds on to a unique ID (UID) for each object such that when a client sends a message requesting to perform an operation on a UID, it knows which object is being referenced.
 If a UID does not yet exist for the requested object, one is automatically created.
 If the object is destroyed (e.g. ViewerController closed), the UID will be removed and any further operations on the object are not allowed.
 
 @warning This class should never be instantiated or sub-classed, rather a singleton variable exists.
 */

@interface gRPCCache : NSObject
{
    NSMutableDictionary *cache;
}

/**
 The singleton  cache
 */
@property (class, readonly, strong) gRPCCache *objectCache;

/**
 Add an OsiriX object to the cache
 
 @param obj The object to add to the dictionary.  This will be a no-op if already referenced.
 
 @return The unique ID for the cahced object.
 */
-(NSString *)addObject:(id)obj;
-(void)removeObject:(id)obj;

-(BOOL)doesContain:(id)object;
-(NSString *)uidForObject:(id)object;
-(id)objectForUID:(NSString *)uid;

-(NSArray *)uids;

-(void)clearCache;

@end
