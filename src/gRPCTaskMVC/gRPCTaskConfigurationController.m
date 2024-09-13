#import "gRPCTaskConfigurationController.h"
#import "gRPCTask.h"
#import "gRPCUtilities.h"

@implementation gRPCTaskConfigurationController

@synthesize delegate, name, executable, type, arguments, blocking;

- (id) init
{
    self = [super initWithWindowNibName:@"gRPCTaskConfigurationPanel"];
    if (!self) {
        gRPCLogError(@"Could not initialize task config panel");
        return  nil;
    }
    return self;
}

- (void) windowDidLoad {
    [typeSelection addItemsWithTitles:@[@"Image", @"ROI", @"VR", @"Database"]];
    
    // Set up binding.
    [nameField bind:@"value" toObject:self withKeyPath:@"name" options:@{NSContinuouslyUpdatesValueBindingOption: @(YES)}];
    [typeSelection bind:@"selectedIndex" toObject:self withKeyPath:@"type" options:nil];
    [blockingField bind:@"value" toObject:self withKeyPath:@"blocking" options:nil];
    [argumentsField bind:@"value" toObject:self withKeyPath:@"arguments" options:@{NSContinuouslyUpdatesValueBindingOption: @(YES)}];
    [executablePath bind:@"value" toObject:self withKeyPath:@"executable" options:nil];
    
    [super windowDidLoad];
}

# pragma mark -
# pragma mark actions

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
    NSURL *path = [gRPCUtilities selectURLWithExtension:nil allowingDirectories:YES allowingFiles:YES];
    if (path)
        [self setArguments:[NSString stringWithFormat:@"%@ \"%@\"", arguments, [path path]]];
}

- (IBAction) loadFileAsExecutable:(id)sender
{
    NSURL *executable = [gRPCUtilities selectURLWithExtension:nil allowingDirectories:NO allowingFiles:YES];
    if (executable)
        [self setExecutable:executable];
}

@end
