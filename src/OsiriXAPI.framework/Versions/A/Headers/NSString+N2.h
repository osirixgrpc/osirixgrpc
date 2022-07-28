/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

#define WebPortalLocalized( key, comment) [key localizedForWebPortal]
#define N2NonNullString( a) a ? a : @""

@interface NSString (N2)

+ (id) stringWithData: (NSData*) data;
-(NSString*)stringBetweenString:(NSString*) aStr andString:(NSString*) bStr;
-(NSArray*)stringsBetweenString:(NSString*) aStr andString:(NSString*) bStr;
-(NSString*)markedString;
-(NSString*)stringByTruncatingToLength:(NSInteger)theWidth;
+(NSString*)sizeString:(unsigned long long)size;
+(NSString*)timeString:(NSTimeInterval)time;
+(NSString*)timeString:(NSTimeInterval)time maxUnits:(NSInteger)maxUnits;
+(NSString*)timeString:(NSTimeInterval)time maxUnits:(NSInteger)maxUnits abbreviated:(BOOL)abbreviated;
-(NSString*)stringByTrimmingStartAndEnd;
-(NSString*)stringByDeletingPrefix:(NSString*)prefix;
-(NSString*)stringByDeletingSuffix:(NSString*)suffix;
+(NSString*)randomStringWithLength: (int) len;

-(NSString*)urlEncodedString;
-(NSString*)urlDecodedString;

-(NSString*)xmlEscapedString;
-(NSString*)xmlUnescapedString;
-(id)JSON; // NSDictionary or NSArray
-(id)valueForJSONKey: (NSString*) key;
-(NSString*)ASCIIString;
-(NSString*)quotedPrintableString;
-(NSString*)txtToHtml;
-(NSString*)resolveNSLocalizedStrings;
-(NSString*)resolveNSLocalizedStringsForLanguage:(NSString*)language;
-(NSString*)resolveNSLocalizedStringsEscapeQuotationMarks: (BOOL) escapeQuotationMarks;
-(NSString*)resolveNSLocalizedStringsForLanguage:(NSString*)language inBundle:(NSBundle*)bundle;
-(NSString*)resolveNSLocalizedStringsForLanguage:(NSString*)language inBundle:(NSBundle*)bundle escapeQuotationMarks: (BOOL) escapeQuotationMarks;
-(NSString*)localizedForLanguage: (NSString*) language;
-(NSString*)localizedForWebPortal;
-(NSString*)numberToSuperscript;
-(NSSize)sizeOfStringWithFont:(NSFont *)font;

-(NSString*)stringByConditionallyResolvingAlias;
-(NSString*)stringByConditionallyResolvingSymlink;

-(BOOL)contains:(NSString*)str;

-(NSString*)stringAfterString:(NSString*) aStr;
-(NSString*)stringByPrefixingLinesWithString:(NSString*)prefix;
+(NSString*)stringByRepeatingString:(NSString*)string times:(NSUInteger)times;
-(NSString*)suspendedString;
-(BOOL)validURL;
-(NSString*)correctWebURL;
-(NSRange)range;

//-(NSString*)resolvedPathString;
-(NSString*)stringByComposingPathWithString:(NSString*)rel;

-(NSArray*)componentsWithLength:(NSUInteger)len;

-(BOOL)isEmail;

-(void)splitStringAtCharacterFromSet:(NSCharacterSet*)charset intoChunks:(NSString**)part1 :(NSString**)part2 separator:(unichar*)separator;

-(NSString*)md5;
-(NSString*)sha1;
@end

@interface NSAttributedString (N2)

-(NSRange)range;

@end;
