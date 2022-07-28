/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>

@interface WADOXML : NSObject <NSXMLParserDelegate>
{
    NSMutableDictionary *studies;
    
    NSString *studyInstanceUID, *seriesInstanceUID, *SOPInstanceUID;
    NSString *wadoURL, *webLogin, *transferSyntax;
}
@property (readonly) NSMutableDictionary *studies;
@property (retain) NSString *studyInstanceUID, *seriesInstanceUID, *SOPInstanceUID, *wadoURL, *webLogin, *transferSyntax;

- (void) parseURL: (NSURL*) url;
- (NSArray*) getWADOUrls;

@end
