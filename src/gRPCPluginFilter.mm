#import "gRPCPluginFilter.h"

#import "gRPCLog.h"

#import <OsiriXAPI/Notifications.h>
#import <OsiriXAPI/browserController.h>

@implementation gRPCPluginFilter

// Check that the support directory exists on the users system and create if not there.
- (void)checkSupportDirectoryExists
{
    NSString *pluginSupportDirectory = [gRPCPluginFilter pluginSupportDirectory];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:pluginSupportDirectory])
    {
        @try {
            [fileManager createDirectoryAtPath:pluginSupportDirectory withIntermediateDirectories:YES attributes:nil error:nil];
        }
        @catch (NSException *exception) {
            gRPCLogError(@"Could not create the application support directory: %@", exception);
        }
    }
}

+ (NSString *) pluginSupportDirectory
{
    NSArray *allPaths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
    NSString *libraryDirectory = [allPaths objectAtIndex:0];
    NSString *pluginSupportDirectory = [libraryDirectory stringByAppendingPathComponent:@"Application Support/OsiriXGRPC"];
    return pluginSupportDirectory;
}

+ (NSString *) pluginIdentifier
{
    return @"com.instituteofcancerresearch.osirixgrpc";
}

- (void) initPlugin
{
    [self checkSupportDirectoryExists];

    toolbarController = [[gRPCToolbarController alloc] init];
    
    // Start the script manager
    scriptManager = [[gRPCScriptManager alloc] initWithStorageURL:[NSURL fileURLWithPath:[gRPCPluginFilter pluginSupportDirectory]]];
    
    // Create the service controller and start a service.
    serverController = [[gRPCServerController alloc] init];
    [serverController startInteractiveServer];
}

- (void) dealloc
{
    [serverController release];
    [toolbarController release];
    [scriptManager release];
    [super dealloc];
}

- (long) filterImage:(NSString*) menuName
{
//    if ([menuName isEqualToString:@"Script Manager"]) {
//        gRPCScriptController *controller = [[gRPCScriptController alloc] initWithScriptManager:scriptManager];
//        [controller showWindow:self];
//    }
    if ([menuName isEqualToString:@"Server Configuration"]) {
        [serverController showWindow:self];
    }

    return 1;
}

-(NSArray *)toolbarAllowedIdentifiersForViewer:(ViewerController *)vc
{
    return [NSArray arrayWithObject:[gRPCToolbarController viewerControllerToolbarID]];
}

-(NSToolbarItem *)toolbarItemForItemIdentifier: (NSString *)itemIdent forViewer:(ViewerController *)vc
{
    if ([itemIdent isEqualToString:[gRPCToolbarController viewerControllerToolbarID]])
    {
        return [toolbarController toolbarItemForViewerController];
    }
    else
    {
        return 0;
    }
}

-(NSArray *)toolbarAllowedIdentifiersForBrowserController:(BrowserController *)bc
{
    return [NSArray arrayWithObject:[gRPCToolbarController browserControllerToolbarID]];
}

-(NSToolbarItem *)toolbarItemForItemIdentifier: (NSString *)itemIdent forBrowserController:(BrowserController *)bc
{
    if ([itemIdent isEqualToString:[gRPCToolbarController browserControllerToolbarID]])
    {
        return [toolbarController toolbarItemForBrowserController];
    }
    else
    {
        return 0;
    }
}

-(NSArray *)toolbarAllowedIdentifiersForVRViewer:(VRController *)bc
{
    return [NSArray arrayWithObject:[gRPCToolbarController vrControllerToolbarID]];
}

-(NSToolbarItem *)toolbarItemForItemIdentifier: (NSString *)itemIdent forVRViewer:(VRController *)bc
{
    if ([itemIdent isEqualToString:[gRPCToolbarController vrControllerToolbarID]])
    {
        return [toolbarController toolbarItemForVRController];
    }
    else
    {
        return 0;
    }
}

@end
