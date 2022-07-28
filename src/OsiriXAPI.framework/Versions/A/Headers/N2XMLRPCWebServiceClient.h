/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "N2RedundantWebServiceClient.h"


@interface N2XMLRPCWebServiceClient : N2RedundantWebServiceClient {
}

-(id)execute:(NSString*)methodName arguments:(NSArray*)args;

@end
