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
    IBOutlet NSPathControl *newServerCertificateAuthorityFile;
    IBOutlet NSPathControl *newServerCertificateFile;
    IBOutlet NSPathControl *newServerKeyFile;
    IBOutlet NSButton *newServerOKButton;
    IBOutlet NSButton *newServerCancelButton;
}

- (BOOL) isValidAddress:(NSString *)address;

+ (NSString *)serverConfigurationPath;
- (void)saveServers:(NSArray *)servers;
- (NSMutableArray *)loadServers;

- (IBAction) addRemoveServerConfig:(id) sender;
- (IBAction) startStopServer:(id) sender;

# pragma mark modal sheet actions
- (IBAction) okPushed:(id) sender;
- (IBAction) cancelPushed:(id) sender;
- (IBAction) certificateAuthoritySelectPushed:(id) sender;
- (IBAction) serverCertificateSelectPushed:(id) sender;
- (IBAction) serverKeySelectPushed:(id) sender;


@end
