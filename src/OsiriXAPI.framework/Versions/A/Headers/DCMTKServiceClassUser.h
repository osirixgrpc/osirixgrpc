/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



/********** 
Super Class for SCU classes such as verifySCU, storeSCU, moveSCU, findSCU
**********/

#import <Cocoa/Cocoa.h>

#ifdef __cplusplus
#undef verify
#include "osconfig.h" /* make sure OS specific configuration is included first */
#include "dcdatset.h"
#include "dimse.h"
#include "dccodec.h"

#else

typedef int E_TransferSyntax;
typedef int T_DIMSE_BlockingMode;
typedef char* OFCondition;
typedef char* T_ASC_Parameters;
typedef char* T_ASC_Association;
typedef char* T_ASC_Network;

#endif

/** \brief  Base Class for SCU classes such as verifySCU, storeSCU, moveSCU, findSCU 
*
* SCU classes are usually outgoing connections
* based on DCMTK 
*/

#import "DICOMTLS.h"
#import "DDKeychain.h"

@interface DCMTKServiceClassUser: NSObject <NSCopying> {
	NSString *_callingAET;
	NSString *_calledAET;
	int _port;
	NSString *_hostname;
	NSMutableDictionary *_extraParameters;
	BOOL _shouldAbort;
	int _transferSyntax;
	float _compression;
	
	//network parameters
	BOOL _verbose;
	BOOL _debug;
	BOOL _abortAssociation;
	unsigned long _maxReceivePDULength ;
	//unsigned long _repeatCount ;
	int _repeatCount ;
	int _cancelAfterNResponses;
	E_TransferSyntax _networkTransferSyntax;
	T_DIMSE_BlockingMode    _blockMode;
	int  _dimse_timeout;
	int  _acse_timeout;
	
	//TLS settings
	BOOL _secureConnection;
	BOOL _doAuthenticate;
	int  _keyFileFormat;
	NSArray *_cipherSuites;
	NSString *_readSeedFile;
	NSString *_writeSeedFile;
	TLSCertificateVerificationType certVerification;
	NSString *_dhparam;
}

@property BOOL abortAssociation;
@property (retain) NSString *hostname, *callingAET, *calledAET;
@property (readonly) NSMutableDictionary *extraParameters;
@property int port, transferSyntax, dimse_timeout, acse_timeout;
@property (retain) NSString *writeSeedFile, *readSeedFile, *dhparam;

- (id) initWithCallingAET:(NSString *)myAET  
			calledAET:(NSString *)theirAET  
			hostname:(NSString *)hostname 
			port:(int)port 
			transferSyntax:(int)transferSyntax
			compression: (float)compression
			extraParameters:(NSDictionary *)extraParameters;
			
- (OFCondition) addPresentationContext:(T_ASC_Parameters *)params abstractSyntax:(const char *)abstractSyntax;
- (NSMutableDictionary *) extraParameters;
@end
