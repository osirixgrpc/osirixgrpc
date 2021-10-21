#import "gRPCCache.h"

#define delegateDeclaration(messageName, requestType, responseType)\
+ (void) messageName:(const osirixgrpc::requestType *) request :(osirixgrpc::responseType *) response :(gRPCCache *) cache;

#define stringFromGRPCString(string)\
[NSString stringWithCString:string.c_str() encoding:[NSString defaultCStringEncoding]];
