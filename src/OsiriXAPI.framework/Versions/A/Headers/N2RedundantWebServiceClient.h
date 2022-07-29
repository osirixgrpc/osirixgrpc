/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import "N2WebServiceClient.h"


@interface N2RedundantWebServiceClient : N2WebServiceClient {
	NSArray* _urls;
}

@property(retain) NSArray* urls;

@end
