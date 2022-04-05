#import <Cocoa/Cocoa.h>

#import "gRPCServer.h"

@interface gRPCServerController : NSWindowController <NSWindowDelegate, NSTableViewDataSource, NSTableViewDelegate>
{
    NSMutableArray *servers;
    IBOutlet NSTextField *status;
    IBOutlet NSTableView *serverTable;
    
    IBOutlet NSWindow *newServerSheet;
    IBOutlet NSTextField *newServerIPAddress;
    IBOutlet NSTextField *newServerPort;
    IBOutlet NSTextField *newServerStatus;
    IBOutlet NSButton *newServerOKButton;
    IBOutlet NSButton *newServerCancelButton;
}

- (BOOL) isValidIPAddress:(NSString *)address andPort:(NSInteger) port;

+ (NSString *)serverConfigurationPath;
- (void)saveServers:(NSArray *)servers;
- (NSMutableArray *)loadServers;
- (BOOL)containsServerWithIPAddress:(NSString *)address andPort:(NSInteger)port;

- (IBAction) addRemoveServerConfig:(id) sender;
- (IBAction) startStopServer:(id) sender;

# pragma mark modal sheet actions
- (IBAction) okPushed:(id) sender;
- (IBAction) cancelPushed:(id) sender;


@end
