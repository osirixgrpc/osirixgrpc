#import "gRPCToolbarController.h"

@implementation gRPCToolbarController

- (id) init
{
    if (self = [super init])
    {
        tasks = [[NSMutableArray alloc] init];
    }
    return self;
}

- (void) dealloc
{
    [tasks release];
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
    
    // Image Filter options
    NSMenuItem *imageFilterItem = [[[NSMenuItem alloc] initWithTitle:@"Image Filter" action:nil keyEquivalent:@""] autorelease];
    [menu addItem:imageFilterItem];
    
    NSMenu *imageFilterMenu = [[[NSMenu alloc] init] autorelease];
    [imageFilterItem setSubmenu:imageFilterMenu];
    
    // ADC uncertainty
    NSMenuItem *adcUncertaintyItem = [[[NSMenuItem alloc] initWithTitle:@"ADC uncertainty" action:@selector(adcUncertainty:) keyEquivalent:@""] autorelease];
    [imageFilterMenu addItem:adcUncertaintyItem];
    [adcUncertaintyItem setTarget:self];
    
    // WBDWI segmentation
    NSMenuItem *wbdwiSegItem = [[[NSMenuItem alloc] initWithTitle:@"WBDWI segmentation" action:@selector(wbdwiSegmentation:) keyEquivalent:@""] autorelease];
    [imageFilterMenu addItem:wbdwiSegItem];
    [wbdwiSegItem setTarget:self];
    
    // Stereo view
    NSMenuItem *stereoMIPItem = [[[NSMenuItem alloc] initWithTitle:@"Stereo MIP" action:@selector(stereoMIP:) keyEquivalent:@""] autorelease];
    [imageFilterMenu addItem:stereoMIPItem];
    [stereoMIPItem setTarget:self];

//    NSMenuItem *sep = [NSMenuItem separatorItem];
//    [menu addItem:sep];
    
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
    
    NSMenuItem *startTermItem = [[[NSMenuItem alloc] initWithTitle:@"Start gRPC VR" action:@selector(startGRPC) keyEquivalent:@""] autorelease];
    [menu addItem:startTermItem];
    [startTermItem setTarget:self];
    
    NSMenuItem *sep = [NSMenuItem separatorItem];
    [menu addItem:sep];
    
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
    
    NSMenuItem *startTermItem = [[[NSMenuItem alloc] initWithTitle:@"Start gRPC browser" action:@selector(startGRPC) keyEquivalent:@""] autorelease];
    [menu addItem:startTermItem];
    [startTermItem setTarget:self];
    
    NSMenuItem *sep = [NSMenuItem separatorItem];
    [menu addItem:sep];
    
    [popUpButtonBrowserController setMenu:menu];
    [menu release];
    
    [toolbarItem setView: popUpButtonViewBrowserController];
    [toolbarItem setMinSize:NSMakeSize(NSWidth([popUpButtonViewBrowserController frame]), NSHeight([popUpButtonViewBrowserController frame]))];
    [toolbarItem setMaxSize:NSMakeSize(NSWidth([popUpButtonViewBrowserController frame]), NSHeight([popUpButtonViewBrowserController frame]))];
    return toolbarItem;
}

- (void) wbdwiSegmentation: (NSMenuItem *)item
{
    NSTask * task = [[[NSTask alloc] init] autorelease];
    [tasks addObject:task];
    NSString *pythonFile = nil;
    NSString *pythonExecutable = nil;
    [task setLaunchPath:pythonExecutable];
    [task setArguments:@[pythonFile]];
    [task launch];
}

- (void) sereoMIP: (NSMenuItem *)item
{
    NSTask * task = [[[NSTask alloc] init] autorelease];
    [tasks addObject:task];
    NSString *pythonFile = @"/Users/adminmblackledge/Desktop/stereoMIP.py";
    NSString *pythonExecutable = @"/Users/adminmblackledge/opt/miniconda3/bin/python";
    [task setLaunchPath:pythonExecutable];
    [task setArguments:@[pythonFile]];
    [task launch];
//    [task waitUntilExit];
    
//    int status = [task terminationStatus];
//
//    if (status == 0) {
//        NSLog(@"Task succeeded.");
//    } else {
//        NSLog(@"Task failed.");
//    }
}

- (void) adcUncertainty: (NSMenuItem *)item
{
    NSLog(@"ADC uncertainty");
}

@end
