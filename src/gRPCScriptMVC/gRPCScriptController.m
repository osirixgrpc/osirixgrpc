#import "gRPCScriptController.h"
#import "gRPCScriptControllerInterpreterCellView.h"
#import "gRPCScriptControllerBlockingCellView.h"
#import "gRPCScriptControllerTypeCellView.h"
#import "gRPCLog.h"

@implementation gRPCScriptController

+ (NSString *) gRPCScriptControllerErrorDomain
{
    return [NSString stringWithFormat:@"%@.scriptControllerErrorDomain", [gRPCPluginFilter pluginIdentifier]];
}

#pragma mark -
#pragma mark Initializer

- (id)initWithScriptManager:(gRPCScriptManager *)scriptManager_
{
    self = [super initWithWindowNibName:@"gRPCScriptWindow"];
    if (!self) {
        gRPCLogError(@"Could not initialize script window");
        return  nil;
    }
    
    scriptManager = [scriptManager_ retain];
    
    return self;
}

- (void)dealloc
{
    [scriptManager release];
    [super dealloc];
}

# pragma mark -
# pragma mark Script window methods

- (IBAction)interpreterChanged:(id)sender
{
    NSOpenPanel *openPanel = [NSOpenPanel openPanel];
    [openPanel setTitle:@"Select the interpreter"];
    [openPanel setCanChooseFiles:YES];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanCreateDirectories:NO];
    if ([openPanel runModal] == NSModalResponseOK)
    {
        NSURL *url = [openPanel URL];
        long row = [scriptTable rowForView:sender];
        gRPCScript *script = [scriptManager.scripts objectAtIndex:row];
        [script setInterpreter:url];
        [scriptManager saveScripts];
        [scriptTable reloadData];
    }
}

- (IBAction)blockingChanged:(id)sender
{
    int value = [(NSButton *)sender intValue];
    long row = [scriptTable rowForView:sender];
    gRPCScript *script = [scriptManager.scripts objectAtIndex:row];
    [script setBlocking:value>0?YES:NO];
    [scriptManager saveScripts];
    [scriptTable reloadData];
}

- (IBAction)typeChanged:(id)sender
{
    long value = [(NSPopUpButton *)sender indexOfSelectedItem];
    long row = [scriptTable rowForView:sender];
    gRPCScript *script = [scriptManager.scripts objectAtIndex:row];
    switch (value) {
        case 0:
            [script setType:gRPCImageTool];
            break;
        case 1:
            [script setType:gRPCROITool];
            break;
        case 2:
            [script setType:gRPCVolumeRenderTool];
            break;
        case 3:
            [script setType:gRPCDatabaseTool];
            break;
        default:
            gRPCLogError(@"Incorrect button value encountered.");
    }
    [scriptManager saveScripts];
    [scriptTable reloadData];
}

- (IBAction) nameChanged:(id)sender
{
    NSString *name = [(NSTextField *)sender stringValue];
    long row = [scriptTable rowForView:sender];
    gRPCScript *script = [scriptManager.scripts objectAtIndex:row];
    [script setName:name];
    [scriptManager saveScripts];
    [scriptTable reloadData];
}

- (NSInteger) numberOfRowsInTableView:(NSTableView *)tableView
{
    return [[scriptManager scripts] count];
}

- (void) windowDidLoad
{
    [super windowDidLoad];
    [scriptTable setUsesAutomaticRowHeights:NO];
    [scriptTable setRowHeight:25.0];
}

- (CGFloat) tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row
{
    return 25.0;
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    NSString *identifier = [tableColumn identifier];
    gRPCScript *script = (gRPCScript *)[[scriptManager scripts] objectAtIndex:row];
    
    if ([identifier isEqualToString:@"location"]){
        NSTableCellView *view = [tableView makeViewWithIdentifier:@"location" owner:self];
        [[view textField] setStringValue: [[script url] path]];
        [[view textField] setToolTip:[[script url] path]];
        return view;
    }
    else if ([identifier isEqualToString:@"interpreter"])
    {
        gRPCScriptControllerInterpreterCellView *view = [tableView makeViewWithIdentifier:@"interpreter" owner:self];
        gRPCLogDefault(@"Interpreter: %@", [[script interpreter] path]);
        [[view textField] setStringValue: [[script interpreter] path]];
        [[view textField] setToolTip:[[script interpreter] path]];
        return view;
    }
    else if ([identifier isEqualToString:@"blocking"])
    {
        gRPCScriptControllerBlockingCellView *view = [tableView makeViewWithIdentifier:@"blocking" owner:self];
        [[view checkBox] setIntValue:[script blocking]?1:0];
        return view;
    }
    else if ([identifier isEqualToString:@"name"])
    {
        NSTableCellView *view = [tableView makeViewWithIdentifier:@"name" owner:self];
        [[view textField] setStringValue:[script name]];
        return view;
    }
    else if ([identifier isEqualToString:@"language"])
    {
        NSTableCellView *view = [tableView makeViewWithIdentifier:@"language" owner:self];
        [[view textField] setStringValue:[gRPCScript descriptionForScriptLanguage:[script language]]];
        return view;
    }
    else if ([identifier isEqualToString:@"type"])
    {
        gRPCScriptControllerTypeCellView *view = [tableView makeViewWithIdentifier:@"type" owner:self];
        [[view popUpButton] addItemsWithTitles:@[@"Image", @"ROI", @"VR", @"Database"]];
        gRPCLogDefault(@"Type: %lu", [script type]);
        switch ([script type]) {
            case gRPCImageTool:
                [[view popUpButton] selectItemAtIndex:0];
                break;
            case gRPCROITool:
                [[view popUpButton] selectItemAtIndex:1];
                break;
            case gRPCVolumeRenderTool:
                [[view popUpButton] selectItemAtIndex:2];
                break;
            case gRPCDatabaseTool:
                [[view popUpButton] selectItemAtIndex:3];
                break;
            default:
                break;
        }
        return view;
    }
    else
    {
        return nil;
    }
}

// Used by the IBAction for user requests to register a script
- (void) registerScript
{
    NSOpenPanel *openPanel = [NSOpenPanel openPanel];
    [openPanel setTitle:@"Select the script file location"];
    [openPanel setCanChooseFiles:YES];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanCreateDirectories:NO];
    if ([openPanel runModal] == NSModalResponseOK)
    {
        NSURL *url = [openPanel URL];
        [scriptManager registerScriptAtURL:url];
    }
    [scriptTable reloadData];
}

// Used by the IBAction for user requests to unregister a script
- (void) unregisterScript
{
    NSInteger row = [scriptTable selectedRow];
    gRPCScript *script = [[scriptManager scripts] objectAtIndex:row];
    [scriptManager unregisterScript:script];
    [scriptTable reloadData];
}

- (IBAction)addRemoveScript:(id)sender
{
    NSSegmentedCell *cell = (NSSegmentedCell *)sender;
    switch ([cell selectedSegment]) {
        case 0:
            [self unregisterScript];
            break;
        case 1:
            [self registerScript];
            break;
        default:
            break;
    }
}

@end
