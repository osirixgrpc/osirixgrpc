#import <Foundation/Foundation.h>

// The codes used for error handling
typedef enum : NSUInteger {
    gRPCSocketError,
    gRPCInvalidIPAddress,
    gRPCServerStarted,
    gRPCPortUnavailable,
} errorCodes;
