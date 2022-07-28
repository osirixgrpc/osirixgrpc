/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "N2ManagedDatabase.h"

enum {Compress, Decompress};

typedef enum  DatebaseFileSystemMode_
{
    integerDatabaseFileSystemMode = 0,
    acquiredDateDatabaseFileSystemMode = 1,
    addedDateDatabaseFileSystemMode = 2
}
DatebaseFileSystemMode;


extern NSString* const CurrentDatabaseVersion;
extern NSString* const OsirixDataDirName;
extern NSString* const O2ScreenCapturesSeriesName;

@class N2MutableUInteger, DicomAlbum, DataNodeIdentifier, DicomStudy, DicomSeries, DicomImage;
#ifndef OSIRIX_LIGHT
@class DCMTKQueryNode;
#endif

@interface DicomDatabase : N2ManagedDatabase {
	N2MutableUInteger* _dataFileIndex;
	NSString* _baseDirPath;
	NSString* _dataBaseDirPath;
    NSTimeInterval lastDatabaseDirPathCheck;
    NSString* _lastDataDirPathCheck;
    NSString* _sourcePath;
	NSString* _name;
	NSRecursiveLock* _processFilesLock;
	NSRecursiveLock* _importFilesFromIncomingDirLock;
	BOOL _isFileSystemFreeSizeLimitReached;
	NSTimeInterval _timeOfLastIsFileSystemFreeSizeLimitReachedVerification;
    NSTimeInterval _lastCleanForFreeSpaceTimeInterval;
	char baseDirPathC[4096], incomingDirPathC[4096], tempDirPathC[4096]; // these paths are used from the DICOM listener
    BOOL _hasPotentiallySlowDataAccess, dontImportFilesFromIncomingDirOnBackground;
    // compression/decompression
    NSMutableArray* _decompressQueue;
    NSMutableArray* _compressQueue;
    NSThread* _compressDecompressThread;
    NSMutableArray *compressingSOPs;
	// +Routing
	NSMutableArray *_routingSendQueues;
    NSMutableDictionary *_routingObjectIDs;
	NSRecursiveLock *_routingLock;
	// +Clean
	NSRecursiveLock* _cleanLock;
    NSString* uniqueTmpfolder;
    
    BOOL protectionAgainstReentry, saving;
    volatile BOOL _deallocating;
}

+(NSString*) localFieldForDICOMField: (NSString*) field;
+(NSString*) DICOMFieldForLocalField: (NSString*) field;

+(void)initializeDicomDatabaseClass;
+(void)recomputePatientUIDsInContext:(NSManagedObjectContext*)db;
+(void)recomputeBodyPartsInContext:(NSManagedObjectContext*)db;

+(NSString*)defaultBaseDirPath;
+(NSString*)baseDirPathForPath:(NSString*)path;
+(NSString*)baseDirPath;
+(NSString*)baseDirPathForMode:(int)mode path:(NSString*)path __deprecated;
+(NSArray*)allDatabases;
+(NSDictionary*)databaseDictionary;
+(DicomDatabase*)defaultDatabase;
-(BOOL)isDefaultDatabase;
+(NSManagedObject*)objectWithObjectID: (NSManagedObjectID*) objectID;
+(DicomImage*)imageWithObjectID: (NSManagedObjectID*) objectID;
+(DicomSeries*)seriesWithObjectID: (NSManagedObjectID*) objectID;
+(DicomStudy*)studyWithObjectID: (NSManagedObjectID*) objectID;
+(DicomDatabase*)databaseAtPath:(NSString*)path;
+(DicomDatabase*)databaseAtPath:(NSString*)path name:(NSString*)name;
+(DicomDatabase*)databaseAtPath:(NSString*)path name:(NSString*)name createIfNecessary:(BOOL)create;
+(DicomDatabase*)existingDatabaseAtPath:(NSString*)path;
+(DicomDatabase*)databaseForContext:(NSManagedObjectContext*)c; // hopefully one day this will be __deprecated
+(DicomDatabase*)activeLocalDatabase;
+(DicomDatabase*)currentLocalDatabase;
+(NSString*)OsiriXDataPath;
+(DicomDatabase*)databaseForPersistentStore:(NSPersistentStore*)c;
+(void)setActiveLocalDatabase:(DicomDatabase*)ldb;

@property(readonly,retain) NSString* baseDirPath, *uniqueTmpfolder; // OsiriX Data
@property(readonly,retain) NSString* dataBaseDirPath;
@property(readwrite,retain,nonatomic) NSString* name, *sourcePath;
@property(readonly) NSMutableArray *compressingSOPs;
@property BOOL hasPotentiallySlowDataAccess;
@property (nonatomic) NSTimeInterval timeOfLastIsFileSystemFreeSizeLimitReachedVerification, lastCleanForFreeSpaceTimeInterval;
@property (nonatomic) BOOL isFileSystemFreeSizeLimitReached, dontImportFilesFromIncomingDirOnBackground;

#ifndef OSIRIX_LIGHT
-(NSArray*)localObjectsForDistantObject: (DCMTKQueryNode*) o;
-(id)localObjectForDistantObject: (DCMTKQueryNode*) o;
#endif
-(BOOL)isLocal;
-(NSArray*)childrenArray: (id)item onlyImages: (BOOL)onlyImages;
-(NSArray*)childrenArray: (id)item onlyImages: (BOOL)onlyImages includeLocalizers: (BOOL) includeLocalizers;
-(NSArray*)childrenArray: (id)item onlyImages: (BOOL)onlyImages retrieveDistant: (BOOL) retrieveDistant;
-(NSArray*)childrenArray: (id)item onlyImages: (BOOL)onlyImages retrieveDistant: (BOOL) retrieveDistant includeLocalizers: (BOOL) includeLocalizers;
-(NSArray*)childrenArray: (id) item;
-(NSArray*)imagesArray: (id) item preferredObject: (int) preferredObject onlyImages:(BOOL) onlyImages sorted: (BOOL) sorted;
-(NSArray*)imagesArray: (id) item preferredObject: (int) preferredObject onlyImages:(BOOL) onlyImages;
-(NSArray*)imagesArray: (id) item preferredObject: (int) preferredObject;
-(NSArray*)imagesArray: (id) item onlyImages:(BOOL) onlyImages;
-(NSArray*)imagesArray: (id) item;
-(NSArray*)imagesPathArray: (id) item;

-(NSArray*) validateStudiesPatientUIDs: (NSArray*) distantStudies;
-(DataNodeIdentifier*)dataNodeIdentifier;

#pragma mark Entities
extern NSString* const DicomDatabaseImageEntityName;
extern NSString* const DicomDatabaseSeriesEntityName;
extern NSString* const DicomDatabaseStudyEntityName;
extern NSString* const DicomDatabaseAlbumEntityName;
extern NSString* const DicomDatabaseLogEntryEntityName;
-(NSEntityDescription*)imageEntity;
-(NSEntityDescription*)seriesEntity;
-(NSEntityDescription*)studyEntity;
-(NSEntityDescription*)albumEntity;
-(NSEntityDescription*)logEntryEntity;

#pragma mark Paths
// these paths are inside baseDirPath
// -(NSString*)sqlFilePath; // this is already defined in N2ManagedDatabase
-(NSString*)modelVersionFilePath; // this should become private
-(NSString*)loadingFilePath; // this should become private
// these paths are inside dataBaseDirPath
-(NSString*)dataDirPath;
-(NSString*)incomingDirPath;
-(NSString*)uniqueDcmFileInIncomingDirPath;
-(NSString*)uniqueDcmFileInIncomingDirPathStartingWithDot: (BOOL) startingWithDot;
-(NSString*)errorsDirPath;
-(NSString*)decompressionDirPath;
-(NSString*)toBeIndexedDirPath;
-(NSString*)reportsDirPath;
-(NSString*)tempDirPath;
-(NSString*)dumpDirPath;
-(NSString*)pagesDirPath;
-(NSString*)htmlTemplatesDirPath;
// these paths are used from the DICOM listener
-(const char*)baseDirPathC;
-(const char*)incomingDirPathC;
-(const char*)tempDirPathC;

-(NSUInteger)computeDataFileIndex; // this method should be private, but is declared because called from deprecated api
-(NSString*)uniquePathForNewDataFileWithExtension:(NSString*)ext;
-(NSString*)uniquePathForNewDataFileWithExtension:(NSString*)ext forStore: (NSPersistentStore*) store;

#pragma mark Albums
-(void)addDefaultAlbums;
-(NSArray*)albums;
+(NSPredicate*)predicateForSmartAlbumFilter:(NSString*)string;
-(void) saveAlbumsToPath:(NSString*) path;
-(void) loadAlbumsFromPath:(NSString*) path;

-(NSString*) statisticalDataForHTML:(BOOL) html getDATABASEsize:(BOOL) getDATABASEsize;

-(void) addStudies:(NSArray*)dicomStudies toAlbum:(DicomAlbum*)dicomAlbum;
-(DicomAlbum*) addAlbumWithName: (NSString*) newAlbumName predicate:(NSString*) predicate;
-(void) deleteAlbum: (DicomAlbum*) name;
-(void) editAlbum:(DicomAlbum*) album;
-(void) removeStudies:(NSArray*)dicomStudies fromAlbum:(DicomAlbum*)dicomAlbum;
-(NSArray*) distantStudiesInstanceUIDsForAlbum:(DicomAlbum*) album;
+(NSString*) localizedAlbum: (NSString*) name forLocale: (NSString*) currentLocale;
-(void) checkAllAlbumsHaveAnUID;

-(void) mainDatabaseCreated;
-(NSArray*) reindexObjects: (NSArray*) objects;
-(void) turnImagesAndSeriesIntoFault;

#pragma mark Add files
-(NSArray*)addFilesAtPaths:(NSArray*)paths;
-(NSArray*)addFilesAtPaths:(NSArray*)paths postNotifications:(BOOL)postNotifications;
-(NSArray*)addFilesAtPaths:(NSArray*)paths postNotifications:(BOOL)postNotifications dicomOnly:(BOOL)dicomOnly;
-(NSArray*)addFilesAtPaths:(NSArray*)paths postNotifications:(BOOL)postNotifications dicomOnly:(BOOL)dicomOnly rereadExistingItems:(BOOL)rereadExistingItems;	
-(NSArray*)addFilesAtPaths:(NSArray*)paths postNotifications:(BOOL)postNotifications dicomOnly:(BOOL)dicomOnly rereadExistingItems:(BOOL)rereadExistingItems generatedByOsiriX:(BOOL)generatedByOsiriX;
-(NSArray*)addFilesAtPaths:(NSArray*)paths postNotifications:(BOOL)postNotifications dicomOnly:(BOOL)dicomOnly rereadExistingItems:(BOOL)rereadExistingItems generatedByOsiriX:(BOOL)generatedByOsiriX returnArray: (BOOL) returnArray;
-(NSArray*)addFilesAtPaths:(NSArray*)paths postNotifications:(BOOL)postNotifications dicomOnly:(BOOL)dicomOnly rereadExistingItems:(BOOL)rereadExistingItems generatedByOsiriX:(BOOL)generatedByOsiriX importedFiles: (BOOL) importedFiles returnArray: (BOOL) returnArray;

-(NSArray*)addFilesDescribedInDictionaries:(NSArray*)dicomFilesArray postNotifications:(BOOL)postNotifications rereadExistingItems:(BOOL)rereadExistingItems generatedByOsiriX:(BOOL)generatedByOsiriX; // returns NSArray<NSManagedObjectID>
-(NSArray*)addFilesDescribedInDictionaries:(NSArray*)dicomFilesArray postNotifications:(BOOL)postNotifications rereadExistingItems:(BOOL)rereadExistingItems generatedByOsiriX:(BOOL)generatedByOsiriX returnArray: (BOOL) returnArray;
-(NSArray*)addFilesDescribedInDictionaries:(NSArray*)dicomFilesArray postNotifications:(BOOL)postNotifications rereadExistingItems:(BOOL)rereadExistingItems generatedByOsiriX:(BOOL)generatedByOsiriX importedFiles: (BOOL) importedFiles returnArray: (BOOL) returnArray;
-(NSArray*)addFilesAtPaths:(NSArray*)paths postNotifications:(BOOL)postNotifications dicomOnly:(BOOL)dicomOnly rereadExistingItems:(BOOL)rereadExistingItems generatedByOsiriX:(BOOL)generatedByOsiriX importedFiles: (BOOL) importedFiles returnArray: (BOOL) returnArray dicomFileDictionary: (NSArray*) dicomFilesArray;
-(NSArray*)addFilesDescribedInDictionaries:(NSArray*)dicomFilesArray postNotifications:(BOOL)postNotifications rereadExistingItems:(BOOL)rereadExistingItems generatedByOsiriX:(BOOL)generatedByOsiriX importedFiles: (BOOL) importedFiles returnArray: (BOOL) returnArray changesDictionary:(NSDictionary**) objectsDictionary;
-(NSArray*)addFilesDescribedInDictionaries:(NSArray*)dicomFilesArray postNotifications:(BOOL)postNotifications rereadExistingItems:(BOOL)rereadExistingItems generatedByOsiriX:(BOOL)generatedByOsiriX importedFiles: (BOOL) importedFiles returnArray: (BOOL) returnArray changesDictionary:(NSDictionary**) objectsDictionary mainThread: (NSThread*) mainThread;
-(NSArray*)addFilesAtPaths:(NSArray*)paths postNotifications:(BOOL)postNotifications dicomOnly:(BOOL)dicomOnly rereadExistingItems:(BOOL)rereadExistingItems generatedByOsiriX:(BOOL)generatedByOsiriX importedFiles: (BOOL) importedFiles returnArray: (BOOL) returnArray dicomFileDictionary: (NSArray*) dicomFileObjectsArray mainThread: (NSThread*) mainThread;

#pragma mark Incoming
+(BOOL)checkIfFileSystemFreeSizeLimitReachedAtPath: (NSString*) path;
-(BOOL)checkIfFileSystemFreeSizeLimitReached;
-(BOOL) hasFilesToImport;
-(NSInteger)importFilesFromIncomingDir;
-(NSInteger)importFilesFromIncomingDir: (NSNumber*) showGUI;
-(NSInteger)importFilesFromIncomingDir: (NSNumber*) showGUI listenerCompressionSettings: (int) listenerCompressionSettings;
-(BOOL)waitForCompressThread;
-(void)initiateImportFilesFromIncomingDirUnlessAlreadyImporting;
-(void)importFilesFromIncomingDirThread;
+(void)syncImportFilesFromIncomingDirTimerWithUserDefaults; // called from deprecated API

-(BOOL) searchForSmartAlbumStudiesOnDICOMNodes;
-(BOOL) searchForComparativeStudiesOnDICOMNodes;
-(BOOL) automaticallyRetrievePartialStudies;
-(BOOL) PACSOnDemandSeriesLevelSupport;
-(BOOL) PACSOnDemandForSearchField;
-(BOOL) syncToCloudDatabase;
-(NSArray*) comparativeServers;
-(NSArray*) smartAlbumStudiesDICOMNodes;
-(int) oldestStudyForComparatives;
-(BOOL) preferStudyWithMoreImages;
-(BOOL) containsStore: (NSPersistentStore*) store;

#pragma mark Compress/decompress
-(BOOL)compressFilesAtPaths:(NSArray*)paths;
-(BOOL)compressFilesAtPaths:(NSArray*)paths intoDirAtPath:(NSString*)destDir;
-(BOOL)decompressFilesAtPaths:(NSArray*)paths;
-(BOOL)decompressFilesAtPaths:(NSArray*)paths intoDirAtPath:(NSString*)destDir;
-(void)initiateCompressFilesAtPaths:(NSArray*)paths;
-(void)initiateCompressFilesAtPaths:(NSArray*)paths intoDirAtPath:(NSString*)destDir;
-(void)initiateDecompressFilesAtPaths:(NSArray*)paths;
-(void)initiateDecompressFilesAtPaths:(NSArray*)paths intoDirAtPath:(NSString*)destDir;
-(void)processFilesAtPaths:(NSArray*)paths intoDirAtPath:(NSString*)destDir mode:(int)mode;

#pragma mark Other
-(BOOL)rebuildAllowed;
// some of these methods should be private, but is declared because called from deprecated api
-(void)rebuild;
-(void)rebuild:(BOOL)complete;
-(void)checkForExistingReportForStudy:(NSManagedObject*)study;
-(void)checkReportsConsistencyWithDICOMSR;
-(void)rebuildSqlFile;
-(void)checkForHtmlTemplates;
-(void)copyFilesThread:(NSDictionary*)dict;
- (NSSet*) deleteObjectIDs: (NSArray*) objectsToDelete;

// methods to overload when one needs to ask for confirmation about autorouting
-(BOOL)allowAutoroutingWithPostNotifications:(BOOL)postNotifications rereadExistingItems:(BOOL)rereadExistingItems;
+(void)forgetAbout:(DicomDatabase*)db;
+(NSManagedObject *) clone:(NSManagedObject *)source inContext:(NSManagedObjectContext *)context;
@end

#import "DicomDatabase+Routing.h"
#import "DicomDatabase+Clean.h"

