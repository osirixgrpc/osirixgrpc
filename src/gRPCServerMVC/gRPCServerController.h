#import <Cocoa/Cocoa.h>

#import "gRPCServer.h"

@interface gRPCServerController : NSWindowController <NSWindowDelegate>
{
    IBOutlet NSTextField *addressField;
    IBOutlet NSTextField *statusField;
    gRPCServer *interactiveServer;
}

@property (readonly) NSMutableDictionary *configuration;

+ (BOOL) isValidAddress:(NSString *)address;

+ (NSString *)serverConfigurationPath;
- (void)saveConfiguration:(NSDictionary *)configuration;
- (NSMutableDictionary *)loadConfiguration;

// Access to server configuration options
+ (NSString *) interactiveServerAddressKey;
- (NSString *) interactiveServerAddress;
- (void) setInteractiveServerAddress: (NSString *) address;

- (void) startInteractiveServer;

- (IBAction) changePushed:(id) sender;
- (IBAction) cancelPushed:(id) sender;

@end
