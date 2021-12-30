#import <Cocoa/Cocoa.h>

#import "gRPCServer.h"

@interface gRPCServerController : NSWindowController <NSWindowDelegate, NSTableViewDataSource, NSTableViewDelegate>
{
    IBOutlet NSTextField *statusField;
    IBOutlet NSTableView *serverTable;
    IBOutlet NSWindow *newServerSheet;
    IBOutlet NSTextField *newServerAddress;
    IBOutlet NSTextField *newServerStatus;
    IBOutlet NSButton *newServerOKButton;
    IBOutlet NSButton *newServerCancelButton;
}

@property (readonly) NSMutableArray *servers;

+ (BOOL) isValidAddress:(NSString *)address;

+ (NSString *)serverConfigurationPath;
- (void)saveServers:(NSArray *)servers;
- (NSMutableArray *)loadServers;

- (IBAction) addRemoveServerConfig:(id) sender;
- (IBAction) startStopServer:(id) sender;

# pragma mark modal sheet actions
- (IBAction) okPushed:(id) sender;
- (IBAction) cancelPushed:(id) sender;


@end
