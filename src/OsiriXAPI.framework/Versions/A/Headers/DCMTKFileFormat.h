/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

@interface DCMTKFileFormat : NSObject
{
    void *dcmtkDcmFileFormat;
}
@property void *dcmtkDcmFileFormat;

+ (NSArray*) prepareDICOMFieldsArrays;

+(NSString*) getNameForGroupAndElement:(int) gp element:(int) el;
+(int) getGroupAndElementForName:(NSString*) name group:(int*) gp element:(int*) el;

- (id) initWithFile: (NSString*) file;

@end
