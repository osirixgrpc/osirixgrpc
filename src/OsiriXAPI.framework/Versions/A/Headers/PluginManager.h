/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>
#import "PluginFilter.h"
/** \brief Mangages PluginFilter loading */
@interface PluginManager : NSObject
{
	NSMutableArray *downloadQueue;
	BOOL startedUpdateProcess;
}

@property(retain,readwrite) NSMutableArray *downloadQueue;

+ (PluginManager*) sharedInstance;
+ (void) startCheckForPluginsUpdatesVerbose: (BOOL) verbose;

+ (int) compareVersion: (NSString *) v1 withVersion: (NSString *) v2;
+ (NSDictionary*) plugins;
+ (NSDictionary*) pluginsInstances;
+ (NSDictionary*) pluginsDict;
+ (NSDictionary*) pluginsBundleDictionnary;
+ (NSDictionary*) pluginsLoadError;
+ (NSDictionary*) fileFormatPlugins;
+ (NSDictionary*) reportPlugins;
+ (NSArray*) preProcessPlugins;
+ (NSMenu*) fusionPluginsMenu;
+ (NSArray*) fusionPlugins;
+ (NSImage*) pluginIconForBundle: (NSBundle*) plugin;
+ (NSString*) versionForPath: (NSString*) path;
+ (NSString*) displayedVersionForPath: (NSString*) path;

+ (BOOL) pluginsAlertAlreadyDisplayed;
+ (void) setPluginsAlertAlreadyDisplayed:(BOOL) p;

+ (void) startProtectForCrashWithFilter: (id) filter;
+ (void) startProtectForCrashWithPath: (NSString*) path;
+ (void) endProtectForCrash;

#ifdef OSIRIX_VIEWER

+ (NSString*) pathResolved:(NSString*) inPath;
+ (void)discoverPlugins;
+ (void) unloadPluginWithName: (NSString*) name;
+ (void) loadPluginAtPath: (NSString*) path;
+ (void) setMenus:(NSMenu*) filtersMenu :(NSMenu*) roisMenu :(NSMenu*) othersMenu :(NSMenu*) dbMenu :(NSMenu*) reportMenu;
+ (BOOL) isComPACS;
+ (void) installPluginFromPath: (NSString*) path;
+ (void) installPluginFromPath: (NSString*) path andActivate: (BOOL) activate;
+ (NSString*)activePluginsDirectoryPath;
+ (NSString*)inactivePluginsDirectoryPath;
+ (NSString*)userActivePluginsDirectoryPath;
+ (NSString*)userInactivePluginsDirectoryPath;
+ (NSString*)systemActivePluginsDirectoryPath;
+ (NSString*)systemInactivePluginsDirectoryPath;
+ (NSString*)appActivePluginsDirectoryPath;
+ (NSString*)appInactivePluginsDirectoryPath;
+ (NSArray*)activeDirectories;
+ (NSArray*)inactiveDirectories;
+ (void)movePluginFromPath:(NSString*)sourcePath toPath:(NSString*)destinationPath;
+ (void)activatePluginWithPath:(NSString*) path;
+ (void)deactivatePluginWithPath:(NSString*) path;
+ (void)changeAvailabilityOfPluginWithPath:(NSString*)pluginName to:(NSString*)availability;
+ (NSString*)deletePluginWithName:(NSString*)pluginName;
+ (NSString*) deletePluginWithName:(NSString*)pluginName availability: (NSString*) availability isActive:(BOOL) isActive;
+ (NSArray*)pluginsList;
+ (void)createDirectory:(NSString*)directoryPath;
+ (NSArray*)availabilities;

- (IBAction)checkForUpdates:(id)sender;
- (void)displayUpdateMessage:(NSDictionary*)messageDictionary;

#endif

@end
