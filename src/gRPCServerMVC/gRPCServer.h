#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@interface gRPCServer : NSObject
{
    NSThread *serverThread;
    NSLock *lock;
}

@property (readonly) NSString *address;
@property (readonly) BOOL active;

-(id)initWithAddress:(NSString *)address;

-(void)start;
-(void)shutdown;

@end
