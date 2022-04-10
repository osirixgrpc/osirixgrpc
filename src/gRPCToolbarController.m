#import "gRPCToolbarController.h"
#import "gRPCTaskController.h"

@implementation gRPCToolbarController

- (id) initWithScriptController:(gRPCScriptController *) scriptController_ andTaskController:(gRPCTaskController *) taskController_
{
    if (self = [super init])
    {
        scriptController = [scriptController_ retain];
        taskController = [taskController_ retain];
    }
    return self;
}

- (void) dealloc
{
    [scriptController release];
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
    
    for (gRPCScript *script in [scriptController scripts])
    {
        gRPCScriptType type = [script type];
        NSMenu *subMenu = nil;
        if (type == gRPCImageTool)
            subMenu = imageFilterMenu;
        else if (type == gRPCROITool)
            subMenu = roiFilterMenu;
        if (subMenu)
        {
            NSMenuItem *scriptMenuItem = [[[NSMenuItem alloc] initWithTitle:[script name] action:@selector(runScript:) keyEquivalent:@""] autorelease];
            [subMenu addItem:scriptMenuItem];
            [scriptMenuItem setTarget:self];
        }
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
    
    for (gRPCScript *script in [scriptController scripts])
    {
        gRPCScriptType type = [script type];
        if (type == gRPCVolumeRenderTool)
        {
            NSMenuItem *scriptMenuItem = [[[NSMenuItem alloc] initWithTitle:[script name] action:@selector(runScript:) keyEquivalent:@""] autorelease];
            [menu addItem:scriptMenuItem];
            [scriptMenuItem setTarget:self];
        }
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
    
    for (gRPCScript *script in [scriptController scripts])
    {
        gRPCScriptType type = [script type];
        if (type == gRPCDatabaseTool)
        {
            NSMenuItem *scriptMenuItem = [[[NSMenuItem alloc] initWithTitle:[script name] action:@selector(runScript:) keyEquivalent:@""] autorelease];
            [menu addItem:scriptMenuItem];
            [scriptMenuItem setTarget:self];
        }
    }
    
    [popUpButtonBrowserController setMenu:menu];
    [menu release];
    
    [toolbarItem setView: popUpButtonViewBrowserController];
    [toolbarItem setMinSize:NSMakeSize(NSWidth([popUpButtonViewBrowserController frame]), NSHeight([popUpButtonViewBrowserController frame]))];
    [toolbarItem setMaxSize:NSMakeSize(NSWidth([popUpButtonViewBrowserController frame]), NSHeight([popUpButtonViewBrowserController frame]))];
    return toolbarItem;
}

- (void) runScript: (NSMenuItem *)item
{
    // Get the relevant variables
    NSString *scriptName = [item title];
    gRPCScript *script = [scriptController scriptWithName:scriptName];
    [taskController runScript:script];
}

@end
