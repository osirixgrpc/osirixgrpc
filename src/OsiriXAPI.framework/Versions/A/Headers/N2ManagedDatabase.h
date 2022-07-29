/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface N2ManagedDatabase : NSObject {
	@protected
    NSString *_sqlFilePath;
	@private
	NSManagedObjectContext *_managedObjectContext;
    NSPersistentStore *mainStore;
    id _mainDatabase;
    volatile BOOL _isDeallocating;
    
    NSTimeInterval timeOfLastModification;
    NSThread *associatedThread;
    BOOL isSaving;
    NSTimer *shareBetweenComputersTimer;
    NSMutableArray *postN2ManagedDatabaseNotificationArray;
    BOOL _isReadOnly, _isCD;
}
@property BOOL isSaving;
@property(readonly) NSThread* associatedThread;
@property(readonly) NSPersistentStore *mainStore;
@property(readonly,retain) NSString* sqlFilePath;
@property(readonly) NSManagedObjectModel* managedObjectModel;
@property(readwrite,retain) NSManagedObjectContext* managedObjectContext; // only change this value if you know what you're doing
@property NSTimeInterval timeOfLastModification;
@property(readonly,retain) id mainDatabase; // for independentDatabases
@property(nonatomic) BOOL isReadOnly, isCD;

-(BOOL)isMainDatabase;
-(id)getMainDatabase;

-(BOOL) canLockDatabase;
-(void) setLocked: (BOOL) readOnly;
-(BOOL) isLocked;

// locking actually locks the context
-(void)lock;
-(BOOL)lockBeforeDate:(NSDate*) date;
-(BOOL)tryLock;
-(void)unlock;
#ifndef NDEBUG
-(void) checkForCorrectContextThread;
-(void) checkForCorrectContextThread: (NSManagedObjectContext*) c;
#endif
// write locking uses writeLock member
//-(void)writeLock;
//-(BOOL)tryWriteLock;
//-(void)writeUnlock;
+ (NSDictionary*) storeOptions;
+(NSString*) modelName;
-(BOOL) deleteSQLFileIfOpeningFailed;
-(BOOL) dumpSqlFile;
-(NSManagedObjectModel*)managedObjectModel;
-(NSPersistentStore*) addPersistentStoreWithPath: (NSString*) sqlFilePath;
-(void) removeAllSecondaryStores;

-(id)initWithPath:(NSString*)sqlFilePath;
-(id)initWithPath:(NSString*)sqlFilePath context:(NSManagedObjectContext*)context;
-(id)initWithMainDatabase:(N2ManagedDatabase*)mainDbReference;
-(id)initWithPath:(NSString*)p context:(NSManagedObjectContext*)c mainDatabase:(N2ManagedDatabase*)mainDbReference;

- (void) renewManagedObjectContext;
-(NSManagedObjectContext*)independentContext:(BOOL)independent;
-(NSManagedObjectContext*)independentContext;
-(id)independentDatabase;
-(id)independentDatabaseIfNotMainThread;
-(BOOL) managedObjectContextExist;
-(NSEntityDescription*)entityForName:(NSString*)name;

-(id)objectWithID:(id)oid;
-(id)objectWithID:(id)oid existingObjectsOnly:(BOOL) existingObjectsOnly;
-(NSArray*)objectsWithIDs:(NSArray*)objectIDs;
-(void)deleteObjects:(NSArray *)objects;

// in these methods, e can be an NSEntityDescription* or an NSString*
-(NSArray*)objectsForEntity:(id)e;
-(NSArray*)objectsForEntity:(id)e propertiesToFetch: (NSArray*) propertiesToFetch;
-(NSArray*)objectsForEntity:(id)e predicate:(NSPredicate*)p propertiesToFetch: (NSArray*) propertiesToFetch;
-(NSArray*)objectsForEntity:(id)e predicate:(NSPredicate*)p;
-(NSArray*)objectsForEntity:(id)e predicate:(NSPredicate*)p error:(NSError**)err;
-(NSArray*)objectsForEntity:(id)e predicate:(NSPredicate*)p error:(NSError**)error fetchLimit:(NSUInteger)fetchLimit sortDescriptors:(NSArray*)sortDescriptors;
-(NSArray*)objectsForEntity:(id)e predicate:(NSPredicate*)p error:(NSError**)error fetchLimit:(NSUInteger)fetchLimit fetchOffset:(NSUInteger)fetchOffset sortDescriptors:(NSArray*)sortDescriptors;
-(NSArray*)objectsForEntity:(id)e predicate:(NSPredicate*)p error:(NSError**)error fetchLimit:(NSUInteger)fetchLimit fetchOffset:(NSUInteger)fetchOffset sortDescriptors:(NSArray*)sortDescriptors propertiesToFetch:(NSArray*) propertiesToFetch;
-(NSUInteger)countObjectsForEntity:(id)e;
-(NSUInteger)countObjectsForEntity:(id)e predicate:(NSPredicate*)p;
-(NSUInteger)countObjectsForEntity:(id)e predicate:(NSPredicate*)p error:(NSError**)err;
-(id)newObjectForEntity:(id)e;
-(void) sqlFileChanged;
-(BOOL)save;
-(BOOL)save:(NSError**)err;
-(void)refreshObjectsFromNotification:(NSDictionary*) n;

-(void)deleteSqlFiles;
+(void)deleteSqlFiles: (NSString*) sqlIndex;
+(void)showNotMainThreadWarning:(BOOL)w;
-(BOOL)isCloudSync;

-(void)deleteAllPersistenStores;
-(void)reloadPersistentStores;
@end

@interface N2ManagedDatabase (Protected)

-(NSManagedObjectContext*)contextAtPath:(NSString*)sqlFilePath;

@end

@interface N2ManagedObjectContext : NSManagedObjectContext {
	N2ManagedDatabase* _database;
    BOOL dicomDatabaseClass, webDatabaseClass;
    NSString *allocatedByStack;
}

@property(assign) N2ManagedDatabase* database;
@property(readonly) NSString *allocatedByStack;

+ (int) dicomManagedObjectContextCounter;
+ (int) webManagedObjectContextCounter;
@end

