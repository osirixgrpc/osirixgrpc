#import <Quartz/Quartz.h>

#import "gRPCServerController.h"
#import "gRPCPluginFilter.h"
#import "gRPCLog.h"
#import "gRPCServerControllerActiveCellView.h"

@implementation gRPCServerController

@synthesize servers = _servers;

+ (BOOL) isValidAddress:(NSString *) address
{
    BOOL bOK = TRUE;
    NSArray *components = [address componentsSeparatedByString:@":"];
    if ((int)[components count] != 2){
        bOK = FALSE;
    }
    return bOK;
}

+ (NSString *) serverConfigurationPath
{
    NSString *pluginSupportDirectory = [gRPCPluginFilter pluginSupportDirectory];
    return [pluginSupportDirectory stringByAppendingPathComponent:@"server_configs.json"];
}

// Create a representation object of a server array that can be converted to JSON
- (NSArray *) jsonServerRepresentation:(NSArray *) servers
{
    NSMutableArray *jsonArray = [[NSMutableArray alloc] init];
    for (gRPCServer *server in servers)
    {
        NSString *isActive = @"NO";
        if ([server active])
        {
            isActive = @"YES";
        }
        NSDictionary *serverRepresentation = [NSDictionary dictionaryWithObjectsAndKeys:[server address], @"address", isActive, @"active", nil];
        [jsonArray addObject:serverRepresentation];
    }
    return jsonArray;
}

- (void) saveServers:(NSArray *) servers
{
    NSString *configPath = [gRPCServerController serverConfigurationPath];
    NSArray *serverRepresentations = [self jsonServerRepresentation:servers];
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:serverRepresentations options:NSJSONWritingPrettyPrinted error:nil];
    [jsonData writeToFile:configPath atomically:YES];
    [serverRepresentations release];
}

- (NSMutableArray *) loadServers
{
    NSString *configPath = [gRPCServerController serverConfigurationPath];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSMutableArray *servers = nil;
    if (![fileManager fileExistsAtPath:configPath])
    {
        gRPCServer *defaultServer = [[gRPCServer alloc] initWithAdress:@"localhost:8888"];
        [defaultServer start];
        servers = [NSMutableArray arrayWithObjects:defaultServer, nil];
        [servers retain];
        [self saveServers:servers];
        [defaultServer release];
    }
    else
    {
        NSData *jsonData = [NSData dataWithContentsOfFile:configPath];
        NSArray *serverRepresentations = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:nil];
        servers = [[NSMutableArray alloc] init];
        for (NSDictionary *serverRepresentation in serverRepresentations)
        {
            NSString *address = [serverRepresentation objectForKey:@"address"];
            NSString *isActive = [serverRepresentation objectForKey:@"active"];
            gRPCServer *server = [[gRPCServer alloc] initWithAdress:address];
            if ([isActive isEqualToString:@"YES"])
            {
                [server start];
            }
            [servers addObject:server];
        }
    }
    return servers;
}

- (void) removeServerAtIndex:(NSInteger) index
{
    
}

- (void) addServer:(gRPCServer *) server
{
    
}

- (void) dealloc
{
    [_servers release];
    [super dealloc];
}

- (id) init
{
    self = [super initWithWindowNibName:@"gRPCServerWindow"];
    if (!self) {
        gRPCLogError(@"Could not initialize server controller");
        return  nil;
    }
    _servers = [self loadServers];
    return self;
}

# pragma mark -
# pragma mark Window Methods

- (void) windowDidLoad
{
    // Can be used to perform any set-up of the window.
    [super windowDidLoad];
}

- (void) setWindowStatus:(NSString *) value
{
    [statusField setStringValue:value];
}

- (void) clearWindowStatus
{
    [statusField setStringValue:@" "];
}

- (void) removeServer
{
    NSInteger selectedRow = [serverTable selectedRow];
    
}

- (void) addServer
{
    // Ensure that the form is empty.
    [newServerStatus setStringValue:@""];
    [newServerAddress setStringValue:@""];
    [newServerSheet makeFirstResponder:newServerOKButton];
    
    // Control is given to the new server sheet
    [[self window] beginSheet: newServerSheet completionHandler:nil];
}

- (IBAction) addRemoveServerConfig:(id) sender
{
    NSSegmentedCell *cell = (NSSegmentedCell *)sender;
    switch ([cell selectedSegment]) {
        case 0:
            [self removeServer];
            break;
        case 1:
            [self addServer];
            break;
        default:
            break;
    }
}

- (IBAction) startStopServer:(id) sender
{
    NSLog(@"Start/stop server");
}

- (IBAction) addressChanged:(id) sender
{
    NSLog(@"Address Changed");
}

# pragma mark -
# pragma mark TableView Delegate Methods

- (NSInteger) numberOfRowsInTableView:(NSTableView *)tableView
{
    return [[self servers] count];
}

- (NSView *) tableView:(NSTableView *) tableView viewForTableColumn:(NSTableColumn *) tableColumn row:(NSInteger) row
{
    NSString *identifier = [tableColumn identifier];
    
    gRPCServer *server = [[self servers] objectAtIndex:row];
    
    if ([identifier isEqualToString:@"address"])
    {
        NSTableCellView *view = [tableView makeViewWithIdentifier:@"address" owner:self];
        [[view textField] setStringValue: [server address]];
        [[view textField] setToolTip: [server address]];
        return view;
    }
    else if ([identifier isEqualToString:@"active"])
    {
        gRPCServerControllerActiveCellView *view = [tableView makeViewWithIdentifier:@"active" owner:self];
        if ([server active])
        {
            [[view imageView] setImage:[NSImage imageNamed: NSImageNameStatusAvailable]];
        }
        else
        {
            [[view imageView] setImage:[NSImage imageNamed: NSImageNameStatusUnavailable]];
        }
        return view;
    }
    else
    {
        return nil;
    }
}

# pragma mark modal sheet actions
- (IBAction) okPushed:(id) sender
{
    [self shakeWindow: newServerSheet];
}

- (IBAction) cancelPushed:(id) sender
{
    [[self window] endSheet:newServerSheet];
}

- (void) shakeWindow:(NSWindow *) window
{
    // Adapted from: https://stackoverflow.com/questions/10517386/how-to-give-nswindow-a-shake-effect-as-saying-no-as-in-login-failure-window
    static int numberOfShakes = 3;
    static float durationOfShake = 0.3f;
    static float vigourOfShake = 0.025f;

    CGRect frame = [window frame];
    CAKeyframeAnimation *shakeAnimation = [CAKeyframeAnimation animation];

    CGMutablePathRef shakePath = CGPathCreateMutable();
    CGPathMoveToPoint(shakePath, NULL, NSMinX(frame), NSMinY(frame));
    for (NSInteger index = 0; index < numberOfShakes; index++){
        CGPathAddLineToPoint(shakePath, NULL, NSMinX(frame) - frame.size.width * vigourOfShake, NSMinY(frame));
        CGPathAddLineToPoint(shakePath, NULL, NSMinX(frame) + frame.size.width * vigourOfShake, NSMinY(frame));
    }
    CGPathCloseSubpath(shakePath);
    shakeAnimation.path = shakePath;
    shakeAnimation.duration = durationOfShake;

    [window setAnimations:[NSDictionary dictionaryWithObject: shakeAnimation forKey:@"frameOrigin"]];
    [[window animator] setFrameOrigin:[window frame].origin];
}

@end
