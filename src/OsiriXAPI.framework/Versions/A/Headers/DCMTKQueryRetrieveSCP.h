/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

/** \brief  DICOM Q/R SCP 
*
* DCMTKQueryRetrieveSCP is the Query/ Retrieve Server and listener
* based on DCMTK 
*/

#ifdef __cplusplus
class DcmQueryRetrieveSCP;
#else
typedef char* DcmQueryRetrieveSCP;
#endif

@interface DCMTKQueryRetrieveSCP : NSObject {
	int _port;
	NSString *_aeTitle;
	NSDictionary *_params;
	BOOL _abort;
	BOOL running;
    DcmQueryRetrieveSCP *localSCP;
}

+ (BOOL) storeSCP;
- (id)initWithPort:(int)port aeTitle:(NSString *)aeTitle  extraParamaters:(NSDictionary *)params;
- (void)run;
- (void)abort;
- (int) port;
- (NSString*) aeTitle;
- (BOOL) running;
@end
