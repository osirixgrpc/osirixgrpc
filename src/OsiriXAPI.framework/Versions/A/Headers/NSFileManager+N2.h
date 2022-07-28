/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "N2DirectoryEnumerator.h"

NS_ASSUME_NONNULL_BEGIN

@interface NSFileManager (N2)

-(BOOL) testWritingPermission:(NSString*) path error: (NSError* _Nullable *) error;
-(void) correctWritingPermissionForDirectory:(NSString*) path error: (NSError* _Nullable *) error;

-(void) moveItemAtPathToTrash: (NSString*) path;
-(NSString*)userApplicationSupportFolderForApp;
-(NSString*)tmpFilePathInDir:(NSString*)dirPath;
-(NSString*)tmpDirPath;
-(NSString*)tmpFilePathInTmp;
-(NSString*)tmpFilePathInTmpWithExtension: (NSString*) ext;
-(void) chmodPath: (NSString*) path;
-(NSString*)confirmDirectoryAtPath:(NSString*)dirPath;
-(NSString*)confirmNoIndexDirectoryAtPath:(NSString*)path;
-(NSString*)confirmDirectoryAtPath:(NSString*)dirPath createIntermediateDirectories: (BOOL) createIntermediateDirectories;
-(NSString*)confirmDirectoryAtPath:(NSString*)dirPath subDirectory: (BOOL) subDirectory createIntermediateDirectories: (BOOL) createIntermediateDirectories;
-(unsigned long long)folderSize:(NSString*)path;
-(NSUInteger)sizeAtPath:(NSString*)path;
-(NSUInteger)sizeAtFSRef:(FSRef*)theFileRef;
-(unsigned long long) fileSize:(NSString*) filePath;
-(BOOL)copyItemAtPath:(NSString*)srcPath toPath:(NSString*)dstPath byReplacingExisting:(BOOL)replace error:(NSError* _Nullable *)err;
-(BOOL) removeItemsWithPrefix:(NSString *)path error:(NSError * _Nullable *)error;
-(BOOL)applyFileModeOfParentToItemAtPath:(NSString*)path;

-(NSArray*)filesWithExtension: (NSString*) extension inDirectory: (NSString*) directory;
-(NSArray*)filesWithExtensions: (NSArray*) extensions inDirectory: (NSString*) directory;

-(NSString*)destinationOfAliasAtPath:(NSString*)path;
-(NSString*)destinationOfAliasOrSymlinkAtPath:(NSString*)path;
-(NSString*)destinationOfAliasOrSymlinkAtPath:(NSString*)path resolved:(BOOL* _Nullable)r;

-(N2DirectoryEnumerator*)enumeratorAtPath:(NSString*)path limitTo:(NSInteger)maxNumberOfFiles;
-(N2DirectoryEnumerator*)enumeratorAtPath:(NSString*)path filesOnly:(BOOL)filesOnly;
-(N2DirectoryEnumerator*)enumeratorAtPath:(NSString*)path filesOnly:(BOOL)filesOnly recursive:(BOOL)recursive;

-(unsigned long) crc32ForPath: (NSString*) path;
-(NSString*) volumeFormatForPath:(NSString*) path localized:(NSString*_Nonnull*_Nonnull) localized;

- (BOOL) getTotalSize: (unsigned long long*) total andFreeSize: (unsigned long long*) free forPath: (NSString*) path;

@end

NS_ASSUME_NONNULL_END
