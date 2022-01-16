#import <Quartz/Quartz.h>
#import <Security/SecImportExport.h>
#import <Security/SecCertificate.h>

#import "gRPCServerController.h"
#import "gRPCPluginFilter.h"
#import "gRPCLog.h"
#import "gRPCUtilities.h"
#import "gRPCServerControllerActiveCellView.h"

@implementation gRPCServerController

- (BOOL) isValidAddress:(NSString *) address
{
    BOOL bOK = TRUE;
    NSArray *components = [address componentsSeparatedByString:@":"];
    if ((int)[components count] != 2)
    {
        bOK = FALSE;
    }
    if (![(NSString *)[components objectAtIndex:0] isEqualToString:@"localhost"])
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
        
        NSDictionary *serverRepresentation = [NSDictionary dictionaryWithObjectsAndKeys:[server address], @"address", isActive, @"active", [[server certificateAuthorityURL] path], @"certificateAuthorityPath", [[server serverCertificateURL] path], @"serverCertificatePath", [[server serverKeyURL] path], @"serverKeyPath", nil];
        
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
            NSString *address = [serverRepresentation objectForKey:@"address"];
            NSString *isActive = [serverRepresentation objectForKey:@"active"];
            NSURL *certificateAuthorityURL = [NSURL fileURLWithPath:[serverRepresentation objectForKey:@"certificateAuthorityPath"]];
            NSURL *serverCertificateURL = [NSURL fileURLWithPath:[serverRepresentation objectForKey:@"serverCertificatePath"]];
            NSURL *serverKeyURL = [NSURL fileURLWithPath:[serverRepresentation objectForKey:@"serverKeyPath"]];
            gRPCServer *server = [[gRPCServer alloc] initWithAdress:address certificateAuthority:certificateAuthorityURL serverCertificate:serverCertificateURL serverKey:serverKeyURL];
            if ([isActive isEqualToString:@"YES"])
            {
                [server start];
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
    [newServerIPAddress setStringValue:@"localhost"];
    [newServerPort setStringValue:@""];
    [newServerCertificateAuthorityFile setURL:[NSURL fileURLWithPath:NSHomeDirectory()]];
    [newServerCertificateFile setURL:[NSURL fileURLWithPath:NSHomeDirectory()]];
    [newServerKeyFile setURL:[NSURL fileURLWithPath:NSHomeDirectory()]];
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
        [server start];
        [serverTable reloadData];
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
    NSString *port = [newServerPort stringValue];
    NSString *address = [NSString stringWithFormat:@"%@:%@", ipAddress, port];
    if (![self isValidAddress:address])
    {
        [self shakeWindow: newServerSheet];
        [self setNewServerStatus:@"address must have form: 'localhost:1234'"];
        return;
    }
    
    NSURL *certificateAuthorityURL = [newServerCertificateAuthorityFile URL];
    if (![[certificateAuthorityURL pathExtension] isEqualToString:@"pem"])
    {
        [self shakeWindow: newServerSheet];
        [self setNewServerStatus:@"Incorrect certificate authority"];
        return;
    }
    
    NSURL *serverCertificateURL = [newServerCertificateFile URL];
    if (![[serverCertificateURL pathExtension] isEqualToString:@"pem"])
    {
        [self shakeWindow: newServerSheet];
        [self setNewServerStatus:@"Incorrect server certificate"];
        return;
    }
    
    NSURL *serverKeyURL = [newServerKeyFile URL] ;
    if (![[serverKeyURL pathExtension] isEqualToString:@"pem"])
    {
        [self shakeWindow: newServerSheet];
        [self setNewServerStatus:@"Incorrect server key"];
        return;
    }
    
    // Create a new server
    gRPCServer *server = [[gRPCServer alloc] initWithAdress:address certificateAuthority:certificateAuthorityURL serverCertificate:serverCertificateURL serverKey:serverKeyURL];
    [self addServer:server];
    [server release];
    [[self window] endSheet:newServerSheet];
    [serverTable reloadData];
}

- (IBAction) cancelPushed:(id) sender
{
    [[self window] endSheet:newServerSheet];
}

- (IBAction) certificateAuthoritySelectPushed:(id) sender
{
    NSURL *caURL = [gRPCUtilities selectURLWithExtension:@"pem" allowingDirectories:NO allowingFiles:YES];
    if (caURL == nil)
    {
        return;
    }
    [newServerCertificateAuthorityFile setURL:caURL];
    [newServerCertificateAuthorityFile setToolTip:[caURL path]];
}

- (IBAction) serverCertificateSelectPushed:(id) sender
{
    NSURL *certURL = [gRPCUtilities selectURLWithExtension:@"pem" allowingDirectories:NO allowingFiles:YES];
    if (certURL == nil)
    {
        return;
    }
    [newServerCertificateFile setURL:certURL];
    [newServerCertificateFile setToolTip:[certURL path]];
}

- (IBAction) serverKeySelectPushed:(id) sender
{
    NSURL *keyURL = [gRPCUtilities selectURLWithExtension:@"pem" allowingDirectories:NO allowingFiles:YES];
    if (keyURL == nil)
    {
        return;
    }
    [newServerKeyFile setURL:keyURL];
    [newServerKeyFile setToolTip:[keyURL path]];
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
