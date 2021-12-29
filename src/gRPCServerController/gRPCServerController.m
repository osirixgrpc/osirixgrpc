#import "gRPCServerController.h"

#import "gRPCPluginFilter.h"
#import "gRPCLog.h"

@implementation gRPCServerController

@synthesize configuration = _configuration;

+ (BOOL) isValidAddress:(NSString *)address
{
    BOOL bOK = TRUE;
    NSArray *components = [address componentsSeparatedByString:@":"];
    if ((int)[components count] != 2){
        bOK = FALSE;
    }
    return bOK;
}

+(NSString *)serverConfigurationPath
{
    NSString *pluginSupportDirectory = [gRPCPluginFilter pluginSupportDirectory];
    return [pluginSupportDirectory stringByAppendingPathComponent:@"server_configs.json"];
}

-(void)saveConfiguration:(NSDictionary *)configuration
{
    NSString *configPath = [gRPCServerController serverConfigurationPath];
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:configuration options:NSJSONWritingPrettyPrinted error:nil];
    [jsonData writeToFile:configPath atomically:YES];
}

-(NSMutableDictionary *)loadConfiguration
{
    NSString *configPath = [gRPCServerController serverConfigurationPath];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSMutableDictionary *configs = nil;
    if (![fileManager fileExistsAtPath:configPath])
    {
        configs = [NSMutableDictionary dictionaryWithObjectsAndKeys:@"localhost:8888", [gRPCServerController interactiveServerAddressKey], nil];
        [self saveConfiguration:configs];
    }
    else
    {
        NSData *jsonData = [NSData dataWithContentsOfFile:configPath];
        configs = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:nil];
    }
    return configs;
}

+ (NSString *) interactiveServerAddressKey
{
    return @"interactiveserveraddress";
}

- (NSString *) interactiveServerAddress
{
    return [_configuration objectForKey:[gRPCServerController interactiveServerAddressKey]];
}

- (void) setInteractiveServerAddress: (NSString *) address
{
    [_configuration setObject:address forKey:[gRPCServerController interactiveServerAddressKey]];
    [self saveConfiguration:_configuration];
}

-(void) dealloc
{
    [_configuration release];
    [super dealloc];
}

-(id) init
{
    self = [super initWithWindowNibName:@"gRPCServerWindow"];
    if (!self) {
        gRPCLogError(@"Could not initialize server controller");
        return  nil;
    }
    _configuration = [[self loadConfiguration] retain];
    return self;
}

- (IBAction)showWindow:(id)sender
{
    [super showWindow:sender];
    [addressField setStringValue:[self interactiveServerAddress]];
}

- (void) startInteractiveServer
{
    interactiveServer = [[gRPCServer alloc] initWithAdress:[self interactiveServerAddress]];
    [interactiveServer start];
}

- (void)setWindowStatus:(NSString *) value
{
    [statusField setStringValue:value];
}

- (void)clearWindowStatus
{
    [statusField setStringValue:@" "];
}

- (IBAction)cancelPushed:(id)sender
{
    [self clearWindowStatus];
    [[self window] performClose:self];
}

- (IBAction)changePushed:(id)sender
{
    NSString *newAddress = [addressField stringValue];
    if (![gRPCServerController isValidAddress:newAddress])
    {
        [self setWindowStatus:@"Must be form: address:port"];
    }
    else
    {
        [self setInteractiveServerAddress:newAddress];
        [self clearWindowStatus];
        [[self window] performClose:self];
    }
}

@end
