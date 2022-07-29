/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <DicomDatabase.h>

typedef enum  {
    cloudDisconnected = 0,
    cloudConnected,
    cloudAuthenticationError,
    cloudExpired,
    cloudUnavailable
} CloudConnectionState;

@interface CloudDicomDatabase : DicomDatabase {
    CloudConnectionState connectionState;
    NSTimeInterval lastLoginFailure;
    NSDictionary *settings;
    NSTimer *checkTimer;
    NSMutableDictionary *retrieveQueue;
    NSTimeInterval lastFullAlbumSync;
}

@property (retain, nonatomic) NSDictionary *settings;
@property (retain, nonatomic) NSTimer *checkTimer;
@property (readonly) CloudConnectionState connectionState;

-(CloudConnectionState)login;
-(void)check;
-(void)logout;

-(void)prepareURLRequestForAuthentication:(NSMutableURLRequest*) request;
-(void)prepareURLRequestForWADO:(NSMutableURLRequest*) request;
-(BOOL)isCloudServerURL: (NSURL*) url;
-(NSArray*)allCloudStudies;
-(void)validateLocalStudies;
-(void)activateCloud;

- (NSDictionary*)server;
- (NSDictionary*)subscription;
- (void) refreshgToken;

-(BOOL)isInRetrieveQueue:(NSString*) uid;
-(void)addToRetrieveQueue:(NSString*) uid;
-(void)removeFromRetrieveQueue:(NSString*) uid;

+(void)buildCloudPaths;
+(BOOL)isCloudPath: (NSString*) path;

-(void)removeStudyInstanceUIDs:(NSArray *)studiesInstanceUIDs;
-(void)removeStudyInstanceUIDs:(NSArray *)studiesInstanceUIDs fromAlbum:(DicomAlbum *)dicomAlbum;
-(void)addStudyInstanceUIDs:(NSArray *)studiesInstanceUIDs toAlbum:(DicomAlbum *)album;
-(void)setStudyInstanceUIDs:(NSArray *)studiesInstanceUIDs forAlbum:(DicomAlbum *)dicomAlbum;

-(void)setValue:(NSString*)value forKey:(NSString*)key forStudy:(NSManagedObject*)object;
-(id)getValueForKey:(NSString*)key forStudy:(NSManagedObject*)object;
-(BOOL)syncToCloudDatabase;
@end
