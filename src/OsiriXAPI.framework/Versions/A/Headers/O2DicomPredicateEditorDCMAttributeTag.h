/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <OsiriX/DCMAttributeTag.h>


@interface O2DicomPredicateEditorDCMAttributeTag : DCMAttributeTag {
    NSString* _description;
    NSString* _cskey;
}

+ (id)tagWithGroup:(int)group element:(int)element vr:(NSString*)vr name:(NSString*)name description:(NSString*)description cskey:(NSString*)cskey;
+ (id)tagWithGroup:(int)group element:(int)element vr:(NSString*)vr name:(NSString*)name description:(NSString*)description;

- (NSString*)cskey;

@end
