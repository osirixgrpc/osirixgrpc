//
//  ServiceManager.m
//  ConsoleApp
//
//  Created by Richard Holbrey on 12/12/2020.
//

#import "gRPCServer.h"
#import "gRPCService.h"
#import "gRPCLog.h"

#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

// See https://philjordan.eu/article/mixing-objective-c-c++-and-objective-c++ for why this needs to be here.
@interface gRPCServer()
{
    std::unique_ptr<grpc::Server> server;
}
@end

@implementation gRPCServer

@synthesize address = _address, serverCertificateURL = _serverCertificateURL, serverKeyURL = _serverKeyURL, certificateAuthorityURL = _certificateAuthorityURL;

-(void)dealloc
{
    [_address release];
    [_certificateAuthorityURL release];
    [_serverCertificateURL release];
    [_serverKeyURL release];
    [lock release];
    [super dealloc];
}

-(id)initWithAdress:(NSString *)address certificateAuthority:(NSURL *)certificateAuthotiryCertificateURL serverCertificate:(NSURL *)serverCertificateURL serverKey:(NSURL *)serverKeyURL
{
    self = [super init];
    if (!self) {
        gRPCLogError(@"Could not initialize server");
        return  nil;
    }
    lock = [[NSLock alloc] init];
    _address = [address retain];
    _certificateAuthorityURL = [certificateAuthotiryCertificateURL retain];
    _serverCertificateURL = [serverCertificateURL retain];
    _serverKeyURL = [serverKeyURL retain];
    
    return self;
}

-(BOOL)active
{
    if (!serverThread)
    {
        return NO;
    }
    return [serverThread isExecuting];
}

-(void)endThreadNotification:(NSNotification *)notification
{
    if ([notification object] == serverThread)
    {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:NSThreadWillExitNotification object:serverThread];
        [serverThread release];
        serverThread = nil;
    }
}

-(void)start
{
    if ([self active])
    {
        gRPCLogError(@"Server cannot be started as already active.");
        return;
    }
    serverThread = [[NSThread alloc] initWithTarget:self selector:@selector(spawnSecure) object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(endThreadNotification:) name:NSThreadWillExitNotification object:serverThread];
    [serverThread start];
}

-(void)shutdown
{
    if (![self active])
    {
        gRPCLogError(@"Server cannot be shut down as not active.");
        return;
    }
    [lock lock];
    server->Shutdown(); // This should end the spawned thread.
    [lock unlock];
}

- (NSString *)readFileContentsAtPath:(NSString *)filePath
{
    NSString* content = [NSString stringWithContentsOfFile:filePath
                                                  encoding:NSUTF8StringEncoding
                                                      error:NULL];
    return content;
}

- (NSString *)readFileContentsAtURL:(NSURL *)url
{
    NSString* content = [NSString stringWithContentsOfURL:url
                                                  encoding:NSUTF8StringEncoding
                                                      error:NULL];
    return content;
}

-(void)spawnSecure
{
    // See https://github.com/grpc/grpc/issues/9593
    [lock lock];
    gRPCService service([gRPCCache objectCache]);
    
    grpc::EnableDefaultHealthCheckService(true);
    
    // Create the server builder
    grpc::ServerBuilder builder;
    
    // Load in the CA and server keys for ssl encryption
    NSString *serverKey = [self readFileContentsAtURL:_serverKeyURL];
    NSString *serverCert = [self readFileContentsAtURL:_serverCertificateURL];
    NSString *CACert = [self readFileContentsAtURL:_certificateAuthorityURL];
    
    
    grpc::SslServerCredentialsOptions::PemKeyCertPair keycert =
    {
        [serverKey cStringUsingEncoding:NSASCIIStringEncoding],
        [serverCert cStringUsingEncoding:NSASCIIStringEncoding]
    };
    
    grpc::SslServerCredentialsOptions sslOps;
    sslOps.pem_root_certs = [CACert cStringUsingEncoding:NSASCIIStringEncoding];
    sslOps.pem_key_cert_pairs.push_back ( keycert );
    sslOps.client_certificate_request = GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY;
    
    builder.AddListeningPort([_address UTF8String], grpc::SslServerCredentials(sslOps));
    
    builder.RegisterService(&service);
    builder.SetMaxMessageSize(512 * 1024 * 1024);
    builder.SetMaxSendMessageSize(512 * 1024 * 1024);
    builder.SetMaxReceiveMessageSize(512 * 1024 * 1024);
    
    // See https://chromium.googlesource.com/external/github.com/grpc/grpc/+/chromium-deps/2016-07-19/examples/cpp/helloworld/greeter_async_server.cc
    server = builder.BuildAndStart();
    [lock unlock];
    
    @try {
        // Wait for the server to shutdown. Note that some other thread must be
        // responsible for shutting down the server for this call to ever return.
        server->Wait();
        NSLog(@"Successfully started: %@", _address);
    }
    @catch (NSException *exception) {
        gRPCLogDefault([NSString stringWithFormat:@"Following error occurred: %@\nEnding server.", [exception description]]);
        return;
    }
    
}

// Always called as another thread.
-(void)spawn
{
    [lock lock];
    gRPCService service([gRPCCache objectCache]);
    [lock unlock];
    
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    
    grpc::ServerBuilder builder;
    [lock lock];
    builder.AddListeningPort([_address UTF8String], grpc::InsecureServerCredentials());
    [lock unlock];
    
    builder.RegisterService(&service);
    builder.SetMaxMessageSize(512 * 1024 * 1024);
    builder.SetMaxSendMessageSize(512 * 1024 * 1024);
    builder.SetMaxReceiveMessageSize(512 * 1024 * 1024);
    
    [lock lock];
    // See https://chromium.googlesource.com/external/github.com/grpc/grpc/+/chromium-deps/2016-07-19/examples/cpp/helloworld/greeter_async_server.cc
    server = builder.BuildAndStart();
    [lock unlock];
    
    @try {
        // Wait for the server to shutdown. Note that some other thread must be
        // responsible for shutting down the server for this call to ever return.
        server->Wait();
    }
    @catch (NSException *exception) {
        gRPCLogDefault([NSString stringWithFormat:@"Following error occurred: %@\nEnding server.", [exception description]]);
        return;
    }
}

@end
