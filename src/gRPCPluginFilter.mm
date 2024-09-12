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

// Called when OsiriX starts up.  This must instantiate all objects and the relevant server(s)
- (void) initPlugin
{
    // Check that a support directory exists and create of not.
    [self checkSupportDirectoryExists];
    
    // Start the task manager
    taskController = [[gRPCTaskController alloc] initWithStorageURL:[NSURL fileURLWithPath:[gRPCPluginFilter pluginSupportDirectory]]];
    
    // Create the service controller and start a service.
    serverController = [[gRPCServerController alloc] initWithStorageURL:[NSURL fileURLWithPath:[gRPCPluginFilter pluginSupportDirectory]]];
    
    // The toolbar controller will be used to control all interactions with the toolbar buttons (for starting user tasks)
    toolbarController = [[gRPCToolbarController alloc] initWithTaskController:taskController];
}

- (void) dealloc
{
    [taskController release];
    [serverController release];
    [toolbarController release];
    [super dealloc];
}

/* Deal with all requests from the menu bar.
 
 This will include:
 - GRPC server configuration.
 - Installation and removal of pre-defined scripts.
 */
- (long) filterImage:(NSString*) menuName
{
    if ([menuName isEqualToString:@"Server Configuration"]) {
        [serverController showWindow:self];
    }

    if ([menuName isEqualToString:@"Task Management"]) {
        [taskController showWindow:self];
    }

    if ([menuName isEqualToString:@"Task Console"]) {
        [[taskController taskConsole] showWindow:self];
    }

    return 0;
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
