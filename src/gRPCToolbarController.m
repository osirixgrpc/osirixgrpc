#import "gRPCToolbarController.h"
#import "gRPCTask.h"

@implementation gRPCToolbarController

- (id) initWithTaskController:(gRPCTaskController *) taskController_
{
    if (self = [super init])
    {
        taskController = [taskController_ retain];
    }
    return self;
}

- (void) dealloc
{
    [taskController release];
    [super dealloc];
}

+ (NSString *) browserControllerToolbarID
{
    return @"gRPCToolbarButtonBrowser";
}

+ (NSString *) viewerControllerToolbarID
{
    return @"gRPCToolbarButtonViewer";
}

+ (NSString *) vrControllerToolbarID
{
    return @"gRPCToolbarButtonVR";
}

- (NSToolbarItem *) toolbarItemForViewerController
{
    NSToolbarItem *toolbarItem = [[[NSToolbarItem alloc] initWithItemIdentifier: [gRPCToolbarController viewerControllerToolbarID]] autorelease];
    [toolbarItem setLabel: NSLocalizedString(@"gRPC Tasks", nil)];
    [toolbarItem setPaletteLabel: NSLocalizedString(@"gRPC Tasks", nil)];
    [toolbarItem setToolTip: NSLocalizedString(@"gRPC viewer commands", nil)];
    
    [[NSBundle bundleForClass:[self class]] loadNibNamed:@"gRPCMenuItem" owner:self topLevelObjects:nil];
    
    [popUpButtonViewerController removeAllItems];
    NSMenu *menu = [[NSMenu alloc] init];
    
    NSMenuItem *item0 = [[[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""] autorelease];
    [menu addItem:item0];
    
    NSMenuItem *imageFilterItem = [[[NSMenuItem alloc] initWithTitle:@"Image Filter" action:nil keyEquivalent:@""] autorelease];
    NSMenuItem *roiFilterItem = [[[NSMenuItem alloc] initWithTitle:@"ROI Filter" action:nil keyEquivalent:@""] autorelease];
    
    NSMenu *imageFilterMenu = [[[NSMenu alloc] init] autorelease];
    NSMenu *roiFilterMenu = [[[NSMenu alloc] init] autorelease];
    
    for (NSString *taskName in [taskController taskNamesForType:gRPCImageTask])
    {
        NSMenuItem *taskMenuItem = [[[NSMenuItem alloc] initWithTitle:taskName action:@selector(runImageTask:) keyEquivalent:@""] autorelease];
        [imageFilterMenu addItem:taskMenuItem];
        [taskMenuItem setTarget:self];
    }
    
    for (NSString *taskName in [taskController taskNamesForType:gRPCROITask])
    {
        NSMenuItem *taskMenuItem = [[[NSMenuItem alloc] initWithTitle:taskName action:@selector(runROITask:) keyEquivalent:@""] autorelease];
        [roiFilterMenu addItem:taskMenuItem];
        [taskMenuItem setTarget:self];
    }
    
    if ([[imageFilterMenu itemArray] count] > 0)
    {
        [menu addItem:imageFilterItem];
        [imageFilterItem setSubmenu:imageFilterMenu];
    }
    
    if ([[roiFilterMenu itemArray] count] > 0)
    {
        [menu addItem:roiFilterItem];
        [roiFilterItem setSubmenu:roiFilterMenu];
    }
    
    [popUpButtonViewerController setMenu:menu];
    [menu release];
    
    [toolbarItem setView: popUpButtonViewViewerController];
    [toolbarItem setMinSize:NSMakeSize(NSWidth([popUpButtonViewViewerController frame]), NSHeight([popUpButtonViewViewerController frame]))];
    [toolbarItem setMaxSize:NSMakeSize(NSWidth([popUpButtonViewViewerController frame]), NSHeight([popUpButtonViewViewerController frame]))];
    return toolbarItem;
}

- (NSToolbarItem *) toolbarItemForVRController
{
    NSToolbarItem *toolbarItem = [[[NSToolbarItem alloc] initWithItemIdentifier: [gRPCToolbarController vrControllerToolbarID]] autorelease];
    [toolbarItem setLabel: NSLocalizedString(@"gRPC Tasks", nil)];
    [toolbarItem setPaletteLabel: NSLocalizedString(@"gRPC Tasks", nil)];
    [toolbarItem setToolTip: NSLocalizedString(@"gRPC volume render commands", nil)];
    
    [[NSBundle bundleForClass:[self class]] loadNibNamed:@"gRPCMenuItem" owner:self topLevelObjects:nil];
    
    [popUpButtonVRController removeAllItems];
    NSMenu *menu = [[NSMenu alloc] init];
    
    NSMenuItem *item0 = [[[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""] autorelease];
    [menu addItem:item0];
    
    for (NSString *taskName in [taskController taskNamesForType:gRPCVolumeRenderTask])
    {
        NSMenuItem *taskMenuItem = [[[NSMenuItem alloc] initWithTitle:taskName action:@selector(runVRTask:) keyEquivalent:@""] autorelease];
        [menu addItem:taskMenuItem];
        [taskMenuItem setTarget:self];
    }
    
    [popUpButtonVRController setMenu:menu];
    [menu release];
    
    [toolbarItem setView: popUpButtonViewVRController];
    [toolbarItem setMinSize:NSMakeSize(NSWidth([popUpButtonViewVRController frame]), NSHeight([popUpButtonViewVRController frame]))];
    [toolbarItem setMaxSize:NSMakeSize(NSWidth([popUpButtonViewVRController frame]), NSHeight([popUpButtonViewVRController frame]))];
    return toolbarItem;
}

- (NSToolbarItem *) toolbarItemForBrowserController
{
    NSToolbarItem *toolbarItem = [[[NSToolbarItem alloc] initWithItemIdentifier: [gRPCToolbarController browserControllerToolbarID]] autorelease];
    [toolbarItem setLabel: NSLocalizedString(@"gRPC Tasks", nil)];
    [toolbarItem setPaletteLabel: NSLocalizedString(@"gRPC Tasks", nil)];
    [toolbarItem setToolTip: NSLocalizedString(@"gRPC browser commands", nil)];
    
    [[NSBundle bundleForClass:[self class]] loadNibNamed:@"gRPCMenuItem" owner:self topLevelObjects:nil];
    
    [popUpButtonBrowserController removeAllItems];
    NSMenu *menu = [[NSMenu alloc] init];
    
    NSMenuItem *item0 = [[[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""] autorelease];
    [menu addItem:item0];
    
    for (NSString *taskName in [taskController taskNamesForType:gRPCDatabaseTask])
    {
        NSMenuItem *taskMenuItem = [[[NSMenuItem alloc] initWithTitle:taskName action:@selector(runBrowserTask:) keyEquivalent:@""] autorelease];
        [menu addItem:taskMenuItem];
        [taskMenuItem setTarget:self];
    }
    
    [popUpButtonBrowserController setMenu:menu];
    [menu release];
    
    [toolbarItem setView: popUpButtonViewBrowserController];
    [toolbarItem setMinSize:NSMakeSize(NSWidth([popUpButtonViewBrowserController frame]), NSHeight([popUpButtonViewBrowserController frame]))];
    [toolbarItem setMaxSize:NSMakeSize(NSWidth([popUpButtonViewBrowserController frame]), NSHeight([popUpButtonViewBrowserController frame]))];
    return toolbarItem;
}

- (void) runImageTask: (NSMenuItem *)item
{
    // Get the relevant variables
    NSString *taskName = [item title];
    gRPCTask *task = [taskController taskWithName:taskName andType: gRPCImageTask];
    [taskController runTask:task];
}

- (void) runROITask: (NSMenuItem *)item
{
    // Get the relevant variables
    NSString *taskName = [item title];
    gRPCTask *task = [taskController taskWithName:taskName andType: gRPCROITask];
    [taskController runTask:task];
}

- (void) runVRTask: (NSMenuItem *)item
{
    // Get the relevant variables
    NSString *taskName = [item title];
    gRPCTask *task = [taskController taskWithName:taskName andType:gRPCVolumeRenderTask];
    [taskController runTask:task];
}

- (void) runBrowserTask: (NSMenuItem *)item
{
    // Get the relevant variables
    NSString *taskName = [item title];
    gRPCTask *task = [taskController taskWithName:taskName andType:gRPCDatabaseTask];
    [taskController runTask:task];
}

@end
