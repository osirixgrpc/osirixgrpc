/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@class DicomDatabase, PrettyCell;

/*enum {
	DataNodeIdentifierTypeDefault,
	DataNodeIdentifierTypeLocal,
	DataNodeIdentifierTypeRemote,
	DataNodeIdentifierTypeDicom,
	DataNodeIdentifierTypeOther
};
typedef NSInteger DataNodeIdentifierType;*/


@interface DataNodeIdentifier : NSObject {
//	DataNodeIdentifierType _type;
	NSString* _location;
    NSString* _aetitle;
    NSUInteger _port;
	NSString* _description;
	NSDictionary* _dictionary;
    BOOL _checked;
    BOOL _detected; // i.e. if this node was detected through bonjour, or mounted
    BOOL _entered; // if this node is listed in the user defaults, entered by the user
}

//+(id)dataNodeIdentifierForLocation:(NSString*)location description:(NSString*)description dictionary:(NSDictionary*)dictionary;

//@property(readonly) DataNodeIdentifierType type;
@property(retain) NSString* location;
@property(retain) NSString* aetitle;
@property NSUInteger port;
@property(retain) NSString* description;
@property(retain) NSDictionary* dictionary;
@property BOOL detected;
@property BOOL entered;
@property BOOL checked;

-(id)initWithLocation:(NSString*)location port:(NSUInteger) port aetitle:(NSString*) aetitle description:(NSString*)description dictionary:(NSDictionary*)dictionary;

-(BOOL)isEqualToDataNodeIdentifier:(DataNodeIdentifier*)dni;
-(BOOL)isEqualToDictionary:(NSDictionary*)d;
-(NSComparisonResult)compare:(DataNodeIdentifier*)other;

-(DicomDatabase*)database;
-(float)freeSpacePercentage;
-(BOOL)isReadOnly;
-(NSString*)toolTip;
-(void)willBeRemoved;
-(void)willDisplayCell:(PrettyCell*)cell;

@end

@interface LocalDatabaseNodeIdentifier : DataNodeIdentifier
{
    NSTimeInterval _lastFreePercentageTime;
    NSImageView *_lastFreePercentageView;
}
@property(retain) NSImageView *lastFreePercentageView;

+(id)localDatabaseNodeIdentifierWithPath:(NSString*)path;
+(id)localDatabaseNodeIdentifierWithPath:(NSString*)path description:(NSString*)description dictionary:(NSDictionary*)dictionary;
    
@end

@interface RemoteDataNodeIdentifier : DataNodeIdentifier

@end

@interface RemoteDatabaseNodeIdentifier : RemoteDataNodeIdentifier

+(id)remoteDatabaseNodeIdentifierWithLocation:(NSString*)location port:(NSUInteger)port description:(NSString*)description dictionary:(NSDictionary*)dictionary;

+(NSHost*)location:(NSString*)location port:(NSUInteger)port toHost:(NSHost**)host port:(NSInteger*)port;
+(NSString*)location:(NSString*)location port:(NSUInteger) port toAddress:(NSString**)address port:(NSInteger*)outputPort;

@end

@interface DicomNodeIdentifier : RemoteDataNodeIdentifier

+(id)dicomNodeIdentifierWithLocation:(NSString*)location port:(NSUInteger)port aetitle:(NSString*)aetitle description:(NSString*)description dictionary:(NSDictionary*)dictionary;

+(NSString*)location:(NSString*)location port:(NSUInteger)port toAddress:(NSString**)address port:(NSInteger*)port aet:(NSString**)aet;

@end
