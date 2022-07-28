/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSData (N2)

+(NSData*)dataWithFirstBytes:(unsigned long) size ofFile:(NSString*)file;
+(NSData*)dataWithHex:(NSString*)hex;
-(NSData*)initWithHex:(NSString*)hex;
+(NSData*)dataWithBase64:(NSString*)base64;
-(NSData*)initWithBase64:(NSString*)base64;
-(NSString*)base64;
-(NSString*)hex;
-(NSData*)md5;
+(NSData*)dataWithShort:(unsigned short)s;
+(NSData*)dataWithLong:(unsigned long)s;
-(NSString*)dataAsStringWithEncoding: (NSStringEncoding) encoding;
- (NSArray *)multipartArrayWithBoundary:(NSString *)boundary;
- (NSArray *)multipartArrayWithBoundary:(NSString *)boundary latestPosition: (unsigned long*) latestPosition;
- (NSArray *)multipartArray;

- (NSData *)AES256EncryptWithKey:(NSString *)key;
- (NSData *)AES256DecryptWithKey:(NSString *)key;

#ifdef OSIRIX_VIEWER
+ (NSString*) decryptFile: (NSString*) file;
+ (NSString*) encryptFile: (NSString*) file;
#endif

+ (BOOL) decryptFile: (NSString*) file toPath: (NSString*) path;
+ (BOOL) encryptFile: (NSString*) file toPath: (NSString*) path;
@end
