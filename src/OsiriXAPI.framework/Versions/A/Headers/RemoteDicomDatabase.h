/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "DicomDatabase.h"

@class DicomImage, DicomAlbum;

@interface RemoteDicomDatabase : DicomDatabase {
	NSString* _baseBaseDirPath;
	NSString* _sqlFileName;
	NSString* _address;
	NSInteger _port;
    BOOL _TLS;
	NSHost* _host;
	NSRecursiveLock* _updateLock;
	NSTimer* _updateTimer;
	NSTimeInterval _timestamp;
    dispatch_semaphore_t _connectionsSemaphoreId;
    NSString *password;
    
    BOOL remoteDBWaitingForLoad;
    NSString *remoteDBPathToLoad;
    int remoteCopyNumberOfFiles;
}

@property(readonly,retain) NSString* address;
@property(readonly) NSInteger port;
@property(readonly) BOOL TLS;
@property(readonly,retain) NSHost* host;
@property(retain) NSString *remoteDBPathToLoad;
@property int remoteCopyNumberOfFiles;

+(RemoteDicomDatabase*)databaseForLocation:(NSString*)location port:(NSUInteger)port name:(NSString*)name update:(BOOL)flagUpdate;
+(RemoteDicomDatabase*)databaseForLocation:(NSString*)location port:(NSUInteger)port tls:(BOOL)tls name:(NSString*)name update:(BOOL)flagUpdate;

-(id)initWithLocation:(NSString*)location port:(NSUInteger)port;
-(id)initWithHost:(NSHost*)host port:(NSInteger)port update:(BOOL)flagUpdate;
-(id)initWithHost:(NSHost*)host port:(NSInteger)port TLS: (BOOL) tls update:(BOOL)flagUpdate;

-(NSThread*) initiateUpdate;
-(NSThread*) forceInitiateUpdate;

-(NSString*)cacheDataForImage:(DicomImage *)image;
-(NSString*)cacheDataForImage:(DicomImage*)image maxFiles:(NSInteger)maxFiles;
-(NSString*)localPathForImage:(DicomImage*)image;

-(void)uploadFilesAtPaths:(NSArray*)paths imageObjects:(NSArray*)images;
-(void)uploadFilesAtPaths:(NSArray*)paths imageObjects:(NSArray*)images generatedByOsiriX:(BOOL)generatedByOsiriX;

-(void)addStudies:(NSArray*)dicomStudies toAlbum:(DicomAlbum*)dicomAlbum;
-(void)removeStudies:(NSArray*)dicomStudies fromAlbum:(DicomAlbum*)dicomAlbum;

-(void)object:(NSManagedObject*)object setValue:(id)value forKey:(NSString*)key;

+(NSDictionary*)fetchDicomDestinationInfoForAddress:(NSString*)address port:(NSInteger)port;
-(NSDictionary*)fetchDicomDestinationInfo;
-(NSString*)fetchDatabaseVersion;

-(void)storeScuImages:(NSArray*)dicomImages toDestinationAETitle:(NSString*)aet address:(NSString*)address port:(NSInteger)port transferSyntax:(int)exsTransferSyntax;


@end
