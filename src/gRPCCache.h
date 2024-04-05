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
    NSMapTable *cache;
}

/**
 The singleton  cache
 */
@property (class, readonly, strong) gRPCCache *objectCache;

/**
 Add an OsiriX object to the cache
 
 @param obj The object to add to the cache.  This will be a no-op if already referenced.
 
 @return The unique ID for the cahced object.
 */
-(NSString *)addObject:(id)obj;

/**
 Remove an OsiriX object from the cache
 
 @param obj The object to be removed from the cache.  This will be a no-op if not present.
 
 @return void
 */
-(void)removeObject:(id)obj;

/**
 Does the cache contain a specifid OsiriX object?
 
 @param obj The object to be checked.
 
 @return BOOL
 */
-(BOOL)doesContain:(id)obj;

/**
 Return the unique identifier for an OsiriX object.
 
 @param obj The object to be searched.
 
 @return An NSSrting containing the unique identifier. Returns `nil` if the object if not cached.
 */
-(NSString *)uidForObject:(id)obj;

/**
 Return the OsiriX object cached for a unique identifier..
 
 @param uid An NSString specifying the unique identifer.
 
 @return The OsiriX object.  `nil` if no object is cached for the uid.
 */
-(id)objectForUID:(NSString *)uid;


/**
 Return the array of all contained uids.
 
 @return An NSArray of the uids (all NSString references).
 */
-(NSArray *)uids;


/**
 Empty the cache.
 
 @return void
 */
-(void)clearCache;

@end
