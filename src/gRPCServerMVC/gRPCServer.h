#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@interface gRPCServer : NSObject
{
    NSThread *serverThread;
    NSLock *lock;
}

@property (readonly) NSString *ipAddress;
@property (readonly) NSInteger port;
@property (readonly) BOOL active;

-(id)initWithIPAddress:(NSString *)ipAddress andPort:(NSInteger)port;

-(BOOL)start:(NSError **)error;
-(void)shutdown;

@end
