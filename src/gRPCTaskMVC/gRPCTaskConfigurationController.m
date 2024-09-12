#import "gRPCTaskConfigurationController.h"
#import "gRPCTask.h"

@implementation gRPCTaskConfigurationController

@synthesize delegate;

- (id) initWithName: (NSString *)name executable: (NSURL *)executable arguments: (NSString *) arguments type: (gRPCTaskType)type blocking: (BOOL) blocking
{
    self = [super initWithWindowNibName:@"gRPCTaskConfigurationPanel"];
    if (!self) {
        gRPCLogError(@"Could not initialize task config panel");
        return  nil;
    }
    
    [nameField setStringValue:name];
    [executablePath setURL:executable];
    
    return self;
}

- (void)windowDidLoad {
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}


- (IBAction) okPushed:(id)sender
{
    [delegate didPressOK];
}

- (IBAction) cancelPushed:(id)sender
{
    [delegate didPressCancel];
}

- (IBAction) loadFileAsArgument:(id)sender
{
    NSLog(@"Load argument pushed");
}

- (IBAction) loadFileAsExecutable:(id)sender
{
    NSLog(@"Load executable pushed");
}

@end
