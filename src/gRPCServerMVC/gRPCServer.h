#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@interface gRPCServer : NSObject
{
    NSThread *serverThread;
    NSLock *lock;
}

@property (readonly) NSString *address;
@property (readonly) NSURL *certificateAuthorityURL;
@property (readonly) NSURL *serverCertificateURL;
@property (readonly) NSURL *serverKeyURL;
@property (readonly) BOOL active;

-(id)initWithAdress:(NSString *)address certificateAuthority:(NSURL *)certificateAuthotiryCertificateURL serverCertificate:(NSURL *)serverCertificateURL serverKey:(NSURL *)serverKeyURL;

-(void)start;
-(void)shutdown;

@end
