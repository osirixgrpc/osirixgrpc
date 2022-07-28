/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#include <sys/stat.h>


@interface N2DirectoryEnumerator : NSDirectoryEnumerator {
@private
	NSString* basepath;
	NSString* currpath;
	NSMutableArray* DIRs;
	NSUInteger counter, max;
	BOOL _filesOnly;
	BOOL _recursive;
}

@property BOOL filesOnly;
@property BOOL recursive;

-(id)initWithPath:(NSString*)path maxNumberOfFiles:(NSInteger)n;

- (int)stat:(struct stat*)s;

@end
