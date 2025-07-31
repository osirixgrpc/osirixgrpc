#import "gRPCTaskConfigurationController.h"
#import "gRPCTask.h"
#import "gRPCUtilities.h"

@implementation gRPCTaskConfigurationController

@synthesize delegate, task;

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
    [nameField bind:@"value" toObject:self withKeyPath:@"task.name" options:@{NSContinuouslyUpdatesValueBindingOption: @(YES)}];
    [typeSelection bind:@"selectedIndex" toObject:self withKeyPath:@"task.type" options:nil];
    [blockingField bind:@"value" toObject:self withKeyPath:@"task.blocking" options:nil];
    [argumentsField bind:@"value" toObject:self withKeyPath:@"task.arguments" options:@{NSContinuouslyUpdatesValueBindingOption: @(YES)}];
    [executablePath bind:@"value" toObject:self withKeyPath:@"task.executable" options:nil];
    
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
    NSURL *url = [gRPCUtilities selectURLWithExtension:nil allowingDirectories:YES allowingFiles:YES];
    if (url)
        [self.task setArguments:[NSString stringWithFormat:@"%@ '%@'", task.arguments, [url path]]];
}

- (IBAction) loadFileAsExecutable:(id)sender
{
    NSURL *executable = [gRPCUtilities selectURLWithExtension:nil allowingDirectories:NO allowingFiles:YES];
    if (executable)
        [self.task setExecutable:executable];
}

@end
