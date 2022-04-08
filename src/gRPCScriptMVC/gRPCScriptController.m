#import "gRPCScriptController.h"
#import "gRPCScriptControllerInterpreterCellView.h"
#import "gRPCScriptControllerBlockingCellView.h"
#import "gRPCScriptControllerTypeCellView.h"
#import "gRPCLog.h"

@implementation gRPCScriptController

@synthesize scripts, storageURL;

+ (NSString *) gRPCScriptControllerErrorDomain
{
    return [NSString stringWithFormat:@"%@.scriptControllerErrorDomain", [gRPCPluginFilter pluginIdentifier]];
}

#pragma mark -
#pragma mark Initializer

- (id)initWithStorageURL:(NSURL *)url
{
    self = [super initWithWindowNibName:@"gRPCScriptWindow"];
    if (!self) {
        gRPCLogError(@"Could not initialize script controller");
        return  nil;
    }
    
    storageURL = [url copy];
    NSFileManager *manager = [NSFileManager defaultManager];
    BOOL isDirectory;
    BOOL fileExists = [manager fileExistsAtPath:[storageURL path] isDirectory:&isDirectory];
    if (!fileExists || !isDirectory)
    {
        gRPCLogError(@"srageURL not available");
        return nil;
    }
    
    [self loadScripts];
    
    return self;
}

- (void)dealloc
{
    [scripts release];
    [storageURL release];
    [super dealloc];
}

#pragma mark -
#pragma mark Storage/retrieval

- (NSURL *) databaseFile
{
    return [storageURL URLByAppendingPathComponent:@".scripts.db"];
}

- (BOOL) saveScripts
{
    NSError *error;
    NSData *archivedData = [NSKeyedArchiver archivedDataWithRootObject:scripts requiringSecureCoding:NO error:&error];
    if (!archivedData)
    {
        gRPCLogError(@"Could not extract archive data: %@", error);
        return NO;
    }
    [archivedData writeToURL:[self databaseFile] atomically:YES];
    return YES;
}

- (BOOL) loadScripts
{
    NSFileManager *manager = [NSFileManager defaultManager];
    
    // This happens if the file is not available yet.
    if (![manager fileExistsAtPath:[[self databaseFile] path]])
    {
        scripts = [[NSMutableArray alloc] init];
        return YES;
    }
    
    if (scripts)
        [scripts release];
    
    NSData *archivedData = [NSData dataWithContentsOfURL:[self databaseFile]];
    
    NSError *error;
    NSSet *classes = [NSSet setWithObjects:[NSMutableArray class], [gRPCScript class], nil];
    scripts = [[NSKeyedUnarchiver unarchivedObjectOfClasses:classes fromData:archivedData error:&error] retain];
    if (!scripts)
    {
        gRPCLogError(@"Could not load scripts: %@", error);
        return NO;
    }
    
    return YES;
}

#pragma mark -
#pragma mark Accessors

- (gRPCScript *)scriptWithName:(NSString *)name
{
    for (gRPCScript *script in scripts)
    {
        if ([script.name isEqualToString:name])
        {
            return script;
        }
    }
    return nil;
}

- (BOOL)scriptPresentWithName:(NSString *)name
{
    for (gRPCScript *script in scripts)
    {
        if ([script.name isEqualToString:name])
        {
            return TRUE;
        }
    }
    return FALSE;
}

- (NSArray *) scriptNamesForType:(gRPCScriptType)type
{
    
    NSMutableArray *scriptNames = [NSMutableArray array];
    for (gRPCScript *script in scripts)
    {
        if ([script type] == type)
        {
            [scriptNames addObject:[script name]];
        }
    }
    return scriptNames;
}

- (NSArray *) scriptNames
{
    NSMutableArray *scriptNames = [NSMutableArray array];
    for (gRPCScript *script in scripts)
        [scriptNames addObject:[script name]];
    return scriptNames;
}

# pragma mark -
# pragma mark Register/unregister

- (void) unregisterScript: (gRPCScript *)script
{
    [scripts removeObject:script];
    [self saveScripts];
}

- (void) unregisterScripts:(NSArray *)scripts
{
    for (gRPCScript *script in scripts)
    {
        [self unregisterScript: script];
    }
}

- (void) registerScriptAtURL:(NSURL *)url
{
    // Find the default name of the script
   NSString *name = [gRPCScript detectNameOfScriptAtURL:url];
    
    // Add to the storage - there are many defaults that can be later changed by the user.
    gRPCScript *script = [[gRPCScript alloc] initWithURL:url interpreter:[NSURL fileURLWithPath:@"/Users/adminmblackledge/opt/miniconda3/bin/python"] name:name type:gRPCImageTool isBlocking:NO];
    [scripts addObject:script];
    [self saveScripts];
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
        gRPCScript *script = [scripts objectAtIndex:row];
        [script setInterpreter:url];
        [self saveScripts];
        [scriptTable reloadData];
    }
}

- (IBAction)blockingChanged:(id)sender
{
    int value = [(NSButton *)sender intValue];
    long row = [scriptTable rowForView:sender];
    gRPCScript *script = [scripts objectAtIndex:row];
    [script setBlocking:value>0?YES:NO];
    [self saveScripts];
    [scriptTable reloadData];
}

- (IBAction)typeChanged:(id)sender
{
    long value = [(NSPopUpButton *)sender indexOfSelectedItem];
    long row = [scriptTable rowForView:sender];
    gRPCScript *script = [scripts objectAtIndex:row];
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
    [self saveScripts];
    [scriptTable reloadData];
}

- (IBAction) nameChanged:(id)sender
{
    NSString *name = [(NSTextField *)sender stringValue];
    long row = [scriptTable rowForView:sender];
    gRPCScript *script = [scripts objectAtIndex:row];
    [script setName:name];
    [self saveScripts];
    [scriptTable reloadData];
}

- (NSInteger) numberOfRowsInTableView:(NSTableView *)tableView
{
    return [scripts count];
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
    gRPCScript *script = (gRPCScript *)[scripts objectAtIndex:row];
    
    if ([identifier isEqualToString:@"location"]){
        NSTableCellView *view = [tableView makeViewWithIdentifier:@"location" owner:self];
        [[view textField] setStringValue: [[script url] path]];
        [[view textField] setToolTip:[[script url] path]];
        return view;
    }
    else if ([identifier isEqualToString:@"interpreter"])
    {
        gRPCScriptControllerInterpreterCellView *view = [tableView makeViewWithIdentifier:@"interpreter" owner:self];
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
- (void) registerScriptAction
{
    NSOpenPanel *openPanel = [NSOpenPanel openPanel];
    [openPanel setTitle:@"Select the script file location"];
    [openPanel setCanChooseFiles:YES];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanCreateDirectories:NO];
    if ([openPanel runModal] == NSModalResponseOK)
    {
        NSURL *url = [openPanel URL];
        [self registerScriptAtURL:url];
    }
    [scriptTable reloadData];
}

// Used by the IBAction for user requests to unregister a script
- (void) unregisterScriptAction
{
    NSInteger row = [scriptTable selectedRow];
    gRPCScript *script = [scripts objectAtIndex:row];
    [self unregisterScript:script];
    [scriptTable reloadData];
}

- (IBAction)addRemoveScript:(id)sender
{
    NSSegmentedCell *cell = (NSSegmentedCell *)sender;
    switch ([cell selectedSegment]) {
        case 0:
            [self unregisterScriptAction];
            break;
        case 1:
            [self registerScriptAction];
            break;
        default:
            break;
    }
}

@end
