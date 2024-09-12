#import "gRPCServer.h"
#import "gRPCErrorCodes.h"
#import "gRPCService.h"
#import "gRPCLog.h"
#import "gRPCUtilities.h"
#import "gRPCPluginFilter.h"

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

@synthesize ipAddress = _ipAddress;
@synthesize port = _port;

-(void)dealloc
{
    [_ipAddress release];
    [lock release];
    [super dealloc];
}

-(id)initWithIPAddress:(NSString *)ipAddress andPort:(NSInteger)port
{
    self = [super init];
    if (!self) {
        gRPCLogError(@"Could not initialize server");
        return  nil;
    }
    lock = [[NSLock alloc] init];
    _ipAddress = [ipAddress retain];
    _port = port;
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

-(BOOL)start:(NSError **)error
{
    if ([self active])
    {
        gRPCLogDefault(@"Server cannot be started as already active.");
        NSDictionary *info = [NSDictionary dictionaryWithObjectsAndKeys:NSLocalizedString(@"Server has already started", nil), NSLocalizedDescriptionKey, nil];
        *error = [NSError errorWithDomain:[gRPCPluginFilter pluginIdentifier] code:gRPCServerStarted userInfo:info];
        return FALSE;
    }
    
    // Check the port is available
    NSInteger serverAvailable = [gRPCUtilities isPort:_port openAtIPAddress:_ipAddress withError:error];
    if (serverAvailable < 0)
    {
        gRPCLogDefault(@"Error occurred when checking for open port");
        return FALSE;
    }
    else if (serverAvailable == 1)
    {
        NSDictionary *info = [NSDictionary dictionaryWithObjectsAndKeys:NSLocalizedString(@"Port unavailable", nil), NSLocalizedDescriptionKey, nil];
        *error = [NSError errorWithDomain:[gRPCPluginFilter pluginIdentifier] code:gRPCPortUnavailable userInfo:info];
        return FALSE;
    }
    
    serverThread = [[NSThread alloc] initWithTarget:self selector:@selector(spawnInsecure) object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(endThreadNotification:) name:NSThreadWillExitNotification object:serverThread];
    [serverThread start];
    return TRUE;
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

// Always called as another thread.
-(void)spawnInsecure
{
    [lock lock];
    gRPCService service([gRPCCache objectCache]);
    [lock unlock];
    
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    
    grpc::ServerBuilder builder;
    [lock lock];
    NSString *address = [NSString stringWithFormat:@"%@:%d", _ipAddress, (int)_port];
    builder.AddListeningPort([address UTF8String], grpc::InsecureServerCredentials());
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
