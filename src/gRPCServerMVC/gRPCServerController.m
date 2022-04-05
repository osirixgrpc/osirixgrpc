#import <Quartz/Quartz.h>
#import <Security/SecImportExport.h>
#import <Security/SecCertificate.h>

#import "gRPCServerController.h"
#import "gRPCPluginFilter.h"
#import "gRPCLog.h"
#import "gRPCUtilities.h"
#import "gRPCServerControllerActiveCellView.h"

@implementation gRPCServerController

- (BOOL) isValidIPAddress:(NSString *)address andPort:(NSInteger) port
{
    BOOL bOK = TRUE;
    if (![address isEqualToString:@"127.0.0.1"])
    {
        bOK = FALSE;
    }
    if (![gRPCUtilities isValidPortNumber:port])
    {
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
        
        NSDictionary *serverRepresentation = [NSDictionary dictionaryWithObjectsAndKeys:[server ipAddress], @"ipaddress", [NSString stringWithFormat:@"%d", (int)[server port]], @"port", isActive, @"active", nil];
        
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
    NSMutableArray *servers_ = [[NSMutableArray alloc] init];
    if ([fileManager fileExistsAtPath:configPath])
    {
        NSData *jsonData = [NSData dataWithContentsOfFile:configPath];
        NSArray *serverRepresentations = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:nil];
        for (NSDictionary *serverRepresentation in serverRepresentations)
        {
            NSString *ipAddress = [serverRepresentation objectForKey:@"ipaddress"];
            NSInteger port = [[serverRepresentation objectForKey:@"port"] integerValue];
            NSString *isActive = [serverRepresentation objectForKey:@"active"];
            gRPCServer *server = [[gRPCServer alloc] initWithIPAddress:ipAddress andPort:port];
            if ([isActive isEqualToString:@"YES"])
            {
                NSError *err;
                BOOL ok = [server start:&err];
                if (!ok)
                {
                    gRPCLogDefault(@"Could not start server after loading. Error: %@", [err localizedDescription]);
                }
            }
            [servers_ addObject:server];
        }
    }
    return servers_;
}

- (void) removeServerAtIndex:(NSInteger) index
{
    if (index < 0 || index >= [servers count])
    {
        gRPCLogDefault(@"Attempted to remove server outside of index range");
        return;
    }
    gRPCServer *server = [servers objectAtIndex:index];
    [self removeServer:server];
}

- (void) removeServer:(gRPCServer *) server
{
    if (![servers containsObject:server])
    {
        gRPCLogDefault(@"Tried to remove invalid server");
        return;
    }
    if ([server active])
    {
        [server shutdown];
    }
    [servers removeObject:server];
    [self saveServers:servers];
}

- (void) addServer:(gRPCServer *) server
{
    [servers addObject:server];
    [self saveServers:servers];
}

- (BOOL)containsServerWithIPAddress:(NSString *)ipAddress andPort:(NSInteger)port
{
    BOOL serverContained = FALSE;
    for (gRPCServer * server in servers)
    {
        if ([ipAddress isEqualToString:[server ipAddress]] && port == [server port])
        {
            serverContained = TRUE;
        }
    }
    return serverContained;
}

- (void) dealloc
{
    [servers release];
    [super dealloc];
}

- (id) init
{
    self = [super initWithWindowNibName:@"gRPCServerWindow"];
    if (!self) {
        gRPCLogError(@"Could not initialize server controller");
        return  nil;
    }
    servers = [self loadServers];
    return self;
}

# pragma mark -
# pragma mark Window Methods

- (void) windowDidLoad
{
    // Can be used to perform any set-up of the window.
    [super windowDidLoad];
    [serverTable reloadData];
}

- (void) setWindowStatus:(NSString *) value
{
    [status setStringValue:value];
}

- (void) clearWindowStatus
{
    [self setWindowStatus:@" "];
}

- (void) removeServerConfig
{
    NSInteger selectedRow = [serverTable selectedRow];
    gRPCServer *server = [servers objectAtIndex:selectedRow];
    if ([server active])
    {
        [server shutdown];
    }
    [self removeServer:server];
    [serverTable reloadData];
    [self setWindowStatus:@"Removed Server"];
}

- (void) addServerConfig
{
    // Ensure that the form is empty.
    [newServerStatus setStringValue:@""];
    [newServerIPAddress setStringValue:@"127.0.0.1"];
    [newServerPort setStringValue:@""];
    [newServerSheet makeFirstResponder:newServerOKButton];
    
    // Control is given to the new server sheet
    [[self window] beginSheet: newServerSheet completionHandler:nil];
    [self setWindowStatus:@"Added Server"];
}

- (IBAction) addRemoveServerConfig:(id) sender
{
    NSSegmentedCell *cell = (NSSegmentedCell *)sender;
    switch ([cell selectedSegment]) {
        case 0:
            [self removeServerConfig];
            break;
        case 1:
            [self addServerConfig];
            break;
        default:
            break;
    }
}

- (void) stopServer
{
    NSInteger index = [serverTable selectedRow];
    gRPCServer *server = [servers objectAtIndex:index];
    if ([server active])
    {
        [server shutdown];
        [serverTable reloadData];
    }
}

- (void) startServer
{
    NSInteger index = [serverTable selectedRow];
    gRPCServer *server = [servers objectAtIndex:index];
    if (![server active])
    {
        NSError *err;
        BOOL ok = [server start:&err];
        if (ok)
        {
            [serverTable reloadData];
        }
        else
        {
            gRPCLogDefault(@"Could not starte server. Error: %@", err)
            [self setWindowStatus:[NSString stringWithFormat:@"%@", [err localizedDescription]]];
        }
    }
}

- (IBAction) startStopServer:(id) sender
{
    NSSegmentedCell *cell = (NSSegmentedCell *)sender;
    switch ([cell selectedSegment]) {
        case 0:
            [self stopServer];
            break;
        case 1:
            [self startServer];
            break;
        default:
            break;
    }
}

# pragma mark -
# pragma mark TableView Delegate Methods

- (NSInteger) numberOfRowsInTableView:(NSTableView *)tableView
{
    return [servers count];
}

- (NSView *) tableView:(NSTableView *) tableView viewForTableColumn:(NSTableColumn *) tableColumn row:(NSInteger) row
{
    NSString *identifier = [tableColumn identifier];
    
    gRPCServer *server = [servers objectAtIndex:row];
    
    if ([identifier isEqualToString:@"address"])
    {
        NSTableCellView *view = [tableView makeViewWithIdentifier:@"address" owner:self];
        NSString *address = [NSString stringWithFormat:@"%@:%d", [server ipAddress], (int)[server port]];
        [[view textField] setStringValue: address];
        [[view textField] setToolTip: address];
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

# pragma mark -
# pragma mark Modal Sheet Actions

- (void) setNewServerStatus:(NSString *) status
{
    [newServerStatus setStringValue:status];
}

- (IBAction) okPushed:(id) sender
{
    // Perform checks of the user values
    NSString *ipAddress = [newServerIPAddress stringValue];
    NSInteger port = [newServerPort integerValue];
    if (![self isValidIPAddress:ipAddress andPort:port])
    {
        [self shakeWindow: newServerSheet];
        [self setNewServerStatus:@"address must have form: '127.0.0.1:1234'"];
        return;
    }
    
    if ([self containsServerWithIPAddress:ipAddress andPort:port])
    {
        [self shakeWindow: newServerSheet];
        [self setNewServerStatus:@"address already contained"];
        return;
    }
    
    // Create a new server
    gRPCServer *server = [[gRPCServer alloc] initWithIPAddress:ipAddress andPort:port];
    [self addServer:server];
    [server release];
    [[self window] endSheet:newServerSheet];
    [serverTable reloadData];
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
