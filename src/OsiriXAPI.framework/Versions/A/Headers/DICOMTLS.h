/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "DDKeychain.h"

typedef enum
{
	RequirePeerCertificate = 0,
	VerifyPeerCertificate,
	IgnorePeerCertificate
} TLSCertificateVerificationType;

#define TLSTESTFILE @"/private/tmp/OsiriX-DcmTLSTransportLayer"
#define TLS_SEED_FILE @"/private/tmp/OsiriXTLSSeed"
#define TLS_WRITE_SEED_FILE @"/private/tmp/OsiriXTLSSeedWrite"
#define TLS_PRIVATE_KEY_FILE @"/private/tmp/TLSKey"
#define TLS_CERTIFICATE_FILE @"/private/tmp/TLSCert"
#define TLS_TRUSTED_CERTIFICATES_DIR @"/private/tmp/TLSTrustedCert" 
#define TLS_KEYCHAIN_IDENTITY_NAME_CLIENT @"com.osirixviewer.dicomtlsclient"
#define TLS_KEYCHAIN_IDENTITY_NAME_SERVER @"com.osirixviewer.dicomtlsserver"

/** \brief
 A utility class for secure DICOM connections with TLS.
 It provides an access to Mac OS X Keychain.
 */
@interface DICOMTLS : NSObject {

}

#pragma mark Cipher Suites
/**
	Returns the list of available Ciphersuites.
	These are basically the one available through DCMTK.
 */
+ (NSArray*)availableCipherSuites;
+ (NSArray*)defaultCipherSuites;

+ (NSString*) TLS_PRIVATE_KEY_PASSWORD;
+ (void) eraseKeys;

#pragma mark Keychain Access
+ (NSString*) opensslSync;
+ (void)generateCertificateAndKeyForLabel:(NSString*)label withStringID:(NSString*)stringID;
+ (void)generateCertificateAndKeyForLabel:(NSString*)label;
+ (void)generateCertificateAndKeyForServerAddress:(NSString*)address port:(int)port AETitle:(NSString*)aetitle withStringID:(NSString*)stringID;
+ (void)generateCertificateAndKeyForServerAddress:(NSString*)address port:(int)port AETitle:(NSString*)aetitle;
+ (NSString*)uniqueLabelForServerAddress:(NSString*)address port:(NSString*)port AETitle:(NSString*)aetitle;
+ (NSString*)keyPathForLabel:(NSString*)label withStringID:(NSString*)stringID;
+ (NSString*)keyPathForLabel:(NSString*)label;
+ (NSString*)keyPathForServerAddress:(NSString*)address port:(int)port AETitle:(NSString*)aetitle withStringID:(NSString*)stringID;
+ (NSString*)keyPathForServerAddress:(NSString*)address port:(int)port AETitle:(NSString*)aetitle;
+ (NSString*)certificatePathForLabel:(NSString*)label withStringID:(NSString*)stringID;
+ (NSString*)certificatePathForLabel:(NSString*)label;
+ (NSString*)certificatePathForServerAddress:(NSString*)address port:(int)port AETitle:(NSString*)aetitle withStringID:(NSString*)stringID;
+ (NSString*)certificatePathForServerAddress:(NSString*)address port:(int)port AETitle:(NSString*)aetitle;
	
@end
