/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>
#import "PluginManager.h"

/** \brief Window Controller for PluginFilter management */

@interface PluginsTableView : NSTableView
{

}
@end

@interface PluginManagerController : NSWindowController <NSURLDownloadDelegate, WebPolicyDelegate>
{

    IBOutlet NSMenu	*filtersMenu;
	IBOutlet NSMenu	*roisMenu;
	IBOutlet NSMenu	*othersMenu;
	IBOutlet NSMenu	*dbMenu;
    IBOutlet NSMenu	*reportMenu;

	NSMutableArray* plugins;
	IBOutlet NSArrayController* pluginsArrayController;
	IBOutlet PluginsTableView *pluginTable;
	
	IBOutlet NSTabView *tabView;
	IBOutlet NSTabViewItem *installedPluginsTabViewItem, *webViewTabViewItem;
	
	IBOutlet WebView *webView;
	NSArray *pluginsListURLs;
	IBOutlet NSPopUpButton *pluginsListPopUp;
	NSString *downloadURL;
	IBOutlet NSButton *downloadButton;
	IBOutlet NSTextField *statusTextField;
	IBOutlet NSProgressIndicator *statusProgressIndicator;
    
    NSMutableDictionary *downloadingPlugins;
    
    IBOutlet NSView *errorPopoverView;
}

@property (retain) NSString *errorPopoverMessage;

- (NSMutableArray*)plugins;
- (NSArray*)availabilities;
- (IBAction)modifiyActivation:(id)sender;
- (IBAction)delete:(id)sender;
- (IBAction)modifiyAvailability:(id)sender;
- (IBAction)loadPlugins:(id)sender;
- (void)refreshPluginList;

- (NSArray*)availablePlugins;
- (void)generateAvailablePluginsMenu;
- (void)setURL:(NSString*)url;
- (IBAction)changeWebView:(id)sender;
- (void)setURLforPluginWithName:(NSString*)name;

- (void)setDownloadURL:(NSString*)url;
- (IBAction)download:(id)sender;

- (void)installDownloadedPluginAtPath:(NSString*)path;
- (BOOL)isZippedFileAtPath:(NSString*)path;
- (BOOL)unZipFileAtPath:(NSString*)path;
- (void)loadSubmitPluginPage;

@end
