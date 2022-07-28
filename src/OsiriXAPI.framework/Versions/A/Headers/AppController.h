/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

// This will be added to the main inded page of the Doxygen documentation
/** \mainpage OsiriX index page
*  <img src= "../../../osirix/Binaries/Icons/SmallLogo.tif">
* \section Intro OsiriX DICOM workstation
*  Osirix is a free open source DICOM workstation with full 64 bit support.
*
*  We extend out thanks to other in the open source community.
*
*  VTK, ITK, and DCMTK open source projects are extensively used in OsiriX.
*
*  The OsiriX team.
*/

#import <AppKit/AppKit.h>

@class PreferenceController;
@class BrowserController;
@class SplashScreen;
@class DCMNetServiceDelegate;
@class WebPortal;
@class DCMPix;
@class XMLRPCInterface;

typedef enum
{
    linearIntegerGA,
    log4GA,
    log2GA
    
} GAMode;

enum compressionTechniqueType {
	compression_sameAsDefault = 0,
	compression_none = 1,
	compression_JPEG = 2,
	compression_JPEG2000 = 3,
    compression_JPEGLS = 4,
    compression_undefined = 255
};
typedef enum compressionTechniqueType compressionTechniqueType;

enum
{
	always = 0,
	cdOnly = 1,
	notMainDrive = 2,
	ask = 3
};

@class PluginFilter;

#ifdef __cplusplus
extern "C"
{
#endif
	NSString * documentsDirectoryFor( int mode, NSString *url) __deprecated;
	NSString * documentsDirectory() __deprecated;
    extern NSString* getMacAddress(void);

    extern BOOL hideListenerError;
    extern BOOL gDarkAppearance;
#ifdef __cplusplus
}
#endif


/** \brief  NSApplication delegate
*
*  NSApplication delegate 
*  Primarily manages the user defaults and server
*  Also controls some general main items
*
*
*/

@class AppController, ToolbarPanelController, ThumbnailsListPanel, BonjourPublisher;

extern AppController* OsiriX;

@interface AppController : NSObject	<NSNetServiceBrowserDelegate, NSNetServiceDelegate, NSSoundDelegate, NSMenuDelegate, NSUserNotificationCenterDelegate, NSTextFieldDelegate>
{
	IBOutlet BrowserController		*browserController;

    IBOutlet NSMenu					*filtersMenu;
	IBOutlet NSMenu					*roisMenu;
	IBOutlet NSMenu					*othersMenu;
	IBOutlet NSMenu					*dbMenu;
    IBOutlet NSMenu					*reportMenu;
	IBOutlet NSWindow				*dbWindow, *emailAddressWindow;
	IBOutlet NSMenu					*windowsTilingMenuRows, *windowsTilingMenuColumns;
    IBOutlet NSMenu                 *recentStudiesMenu;
    
	NSDictionary					*previousDefaults;
	
	BOOL							showRestartNeeded;
		
    SplashScreen					*splashController;
	
    volatile BOOL					quitting;
	BOOL							verboseUpdateCheck;
	NSNetService					*dicomBonjourPublisher, *dicomWebBonjourPublisher;
	
	NSTimer							*updateTimer;
	XMLRPCInterface					*XMLRPCServer;
	
	BOOL							checkAllWindowsAreVisibleIsOff, isSessionInactive, testingNodes;
	
	int								lastColumns, lastRows, lastCount, lastColumnsPerScreen;
    
    BonjourPublisher* _bonjourPublisher;
    
    long updateTotalData, updateReceivedData;
    NSMutableData *updateData;
    id appNapActivity;
    
    // DICOM Definition parser
    BOOL getCurrentModule, applicationDidFinishLaunching;
    NSString *previousContent, *previousOriginal, *currentFile, *currentModule;
    NSMutableDictionary *DICOMDefinitionDict;
    NSDictionary *currentAttribute;
    NSMutableDictionary *currentIDElements;
    
    IBOutlet NSWindow *notAvailableWindow;
    IBOutlet NSTextField *notAvailableText;
    
    // Registration key window
    NSString *currentRegistrationKey;
    NSString *upgradeRegistrationKey;
    BOOL keysFromAccountHidden;
    IBOutlet NSTextField *keyTextField;
    IBOutlet NSWindow *registrationKeyWindow;
    IBOutlet NSPopUpButton *availableKeysMenu;
    NSRecursiveLock *regurlLock;
}

@property BOOL checkAllWindowsAreVisibleIsOff, isSessionInactive, showRestartNeeded, applicationDidFinishLaunching;
@property(readonly) NSMenu *filtersMenu, *recentStudiesMenu, *windowsTilingMenuRows, *windowsTilingMenuColumns;
@property(readonly) NSNetService *dicomBonjourPublisher, *dicomWebBonjourPublisher;
@property(readonly) XMLRPCInterface *XMLRPCServer;
@property(readonly) BonjourPublisher* bonjourPublisher;
@property(readonly) int lastColumns, lastRows, lastCount;
@property(retain) id appNapActivity;
@property(retain) NSString *currentRegistrationKey, *upgradeRegistrationKey;
@property(retain) NSTimer *refreshOAuthTokensTimer;
@property BOOL keysFromAccountHidden;

+ (BOOL) hostReachable:(NSString*) host;
+ (void) thisFeatureIsNotAvailable: (NSString*) stringUrl;
+ (BOOL) isFDACleared;
+ (BOOL) isANVISA;
+ (BOOL) isMD;
+ (BOOL) willExecutePlugin;
+ (BOOL) willExecutePlugin:(id) filter;
+ (BOOL) hasMacOSXLion;
+ (BOOL) hasMacOSXSnowLeopard;
+ (BOOL) hasMacOSXLeopard;
+ (BOOL) hasOSXElCapitan;
+ (BOOL) hasOSXYosemite;
+ (BOOL) hasMacOSSierra;
+ (BOOL) hasMacOSSierra10122;
+ (BOOL) hasMacOSX: (NSString*) vers;
+ (BOOL) isOSXYosemite;
+ (int) isUnsupportedOS;
+ (BOOL) hasMacOSXMaverick;
+ (BOOL) hasNSParagraphStyleTabStopsBug;
+ (NSString*) UID;
+ (NSString*) getRK;
+ (void) restartOsiriX;
+ (NSImage*) webBrowserIcon;
+ (void) clearEvents;
+ (BOOL) runningOsiriXMDSubscriptionInLimitedMode;
+ (NSDictionary*) parametersForURL: (NSURL*) url;

+(NSString*) getLastLines: (int) lines forApplication: (NSString*) applicationName;
+(NSString*) getLastLines: (int) lines forApplication: (NSString*) applicationName authenticate:(BOOL) authenticate;

#pragma mark-
#pragma mark initialization of the main event loop singleton

+ (void) createNoIndexDirectoryIfNecessary:(NSString*) path __deprecated;
#ifndef OSIRIXLITE
+ (int) displayVeryImportantNotice64:(id) sender;
#else
+ (int) displayVeryImportantNotice32:(id) sender;
#endif
+ (NSURL*) baseURL;
+ (AppController*) sharedAppController; /**< Return the shared AppController instance */
+ (void) resizeWindowWithAnimation:(NSWindow*) window newSize: (NSRect) newWindowFrame;
+ (void) pause __deprecated;
+ (ThumbnailsListPanel*)thumbnailsListPanelForScreen:(NSScreen*)screen;
+ (NSString*)printStackTrace:(NSException*)e __deprecated; // use -[NSException printStackTrace] form NSException+N2
+ (BOOL) isKDUEngineAvailable;
+ (void) binpdf: (NSString*) file toFile: (NSString*) toFile;
+ (void) sendGAWithAction: (NSString*) action label:(NSString*) label;
+ (void) sendGAWithCategory:(NSString*) category action: (NSString*) action label:(NSString*) label;
+ (void) sendGAWithAction:(NSString*) action value:(int) intValue mode:(GAMode) gaMode;
+ (void) sendGAWithCategory:(NSString*) category action: (NSString*) action label:(NSString*) label value:(int) intValue mode:(GAMode) gaMode;
#pragma mark-
#pragma mark HTML Templates
+ (void)checkForHTMLTemplates __deprecated;
+ (BOOL) FPlistForKey: (NSString*) k;
+ (long) longForFPlistForKey: (NSString*) k;

+ (BOOL) isStarting;
+ (BOOL) isTerminating;

#pragma mark-
#pragma mark  Server management
- (void) terminate :(id) sender; /**< Terminate listener (Q/R SCP) */
- (void) restartSTORESCP; /**< Restart listener (Q/R SCP) */
- (void) startSTORESCP:(id) sender; /**< Start listener (Q/R SCP) */
- (void) startSTORESCPTLS:(id) sender; /**< Start TLS listener (Q/R SCP) */
- (void) installPlugins: (NSArray*) pluginsArray;
- (BOOL) isStoreSCPRunning;

#pragma mark-
#pragma mark static menu items
//===============OSIRIX========================
+ (NSString*) obfuscatedKey;
- (IBAction) enterNewRegistrationKey:(id)sender;
- (BOOL) enterNewRegistrationKeyWithString: (NSString*) newKey;
- (IBAction) about:(id)sender; /**< Display the about window */
- (IBAction) showPreferencePanel:(id)sender; /**< Show Preferences window */
#ifndef OSIRIX_LIGHT
#ifndef MACAPPSTORE
- (IBAction) checkForUpdates:(id) sender;  /**< Check for update */
#endif
- (IBAction) autoQueryRefresh:(id)sender;
#endif
//===============WINDOW========================
- (IBAction) setFixedTilingRows: (id) sender;
- (IBAction) setFixedTilingColumns: (id) sender;
- (void) initTilingWindows;
+ (void) delayedTileWindows:(id) sender;
+ (void) tileWindows:(id)sender;
- (IBAction) tileWindows:(id)sender;  /**< Tile open window */
- (IBAction) tile3DWindows:(id)sender; /**< Tile 3D open window */
- (void) tileWindows:(id)sender windows: (NSMutableArray*) viewersList display2DViewerToolbar: (BOOL) display2DViewerToolbar displayThumbnailsList: (BOOL) displayThumbnailsList;
- (void) checkWindowDisplay;
- (void) scaleToFit:(id)sender;    /**< Scale opened windows */
- (IBAction) closeAllViewers: (id) sender;  /**< Close All Viewers */
- (void) checkAllWindowsAreVisible:(id) sender;
- (void) checkAllWindowsAreVisible:(id) sender makeKey: (BOOL) makeKey;
//- (IBAction)toggleActivityWindow:(id)sender;
//===============HELP==========================
- (IBAction) sendEmail: (id) sender;   /**< Send email to lead developer */
- (IBAction) openOsirixWebPage: (id) sender;  /**<  Open OsiriX web page */
//- (IBAction) openOsirixDiscussion: (id) sender; /**< Open OsiriX discussion web page */
- (IBAction) osirix64bit: (id) sender;
//---------------------------------------------
- (IBAction) help: (id) sender;  /**< Open help window */
//=============================================

- (IBAction) killAllStoreSCU:(id) sender;
- (IBAction) displayPixmeoLogin:(id)sender;
- (id) splashScreen;

- (void) releaseObject: (id) obj afterDelay: (int) delay;

#pragma mark-
#pragma mark window routines
- (IBAction) updateViews:(id) sender;  /**< Update Viewers */
- (NSScreen *)dbScreen;  /**< Return monitor with DB */
- (NSArray *)viewerScreens; /**< Return array of monitors for displaying viewers */

 /** 
 * Find the WindowController with the named nib and using the pixList
 * This is commonly used to find the 3D Viewer associated with a ViewerController.
 * Conversely this could be used to find the ViewerController that created a 3D Viewer
 * Each 3D Viewer has its own distinctly named nib as does the ViewerController.
 * The pixList is the Array of DCMPix that the viewer uses.  It should uniquely identify related viewers
*/
- (id) FindViewer:(NSString*) nib :(NSArray*) pixList;
- (NSArray*) FindRelatedViewers:(NSArray*) pixList; /**< Return an array of all WindowControllers using the pixList */
- (IBAction) cancelModal: (id) sender;
- (IBAction) okModal: (id) sender;
- (IBAction)alternateModal:(id)sender;
- (NSString*) privateIP;
- (NSString *)computerName;
+ (NSString *)computerName;
- (void) killDICOMListenerWait:(BOOL) w;
- (void) runPreferencesUpdateCheck:(NSTimer*) timer;
+ (void) displayAppleScriptPermissionError: (NSDictionary*) errorInfo;
+ (void) resetThumbnailsList;
+ (void) checkForPreferencesUpdate: (BOOL) b;
+ (BOOL) USETOOLBARPANEL;
+ (void) setUSETOOLBARPANEL: (BOOL) b;
+ (NSRect) usefullRectForScreen: (NSScreen*) screen;
+ (NSArray*) sortObjects: (NSArray*) objects accordingToSeriesDescriptionsArray: (NSArray*) seriesDescriptionsOrder;
+ (NSArray*) sortObjects: (NSArray*) objects accordingToSeriesDescriptionsArray: (NSArray*) seriesDescriptionsOrder oneSeriesPerSeriesDescription: (BOOL) oneSeriesPerSeriesDescription;
- (NSMutableArray*) orderedWindowsAccordingToPositionByRows;
- (NSMutableArray*) orderedWindowsAccordingToPositionByRows: (NSArray*) a;
- (void) addStudyToRecentStudiesMenu: (NSManagedObjectID*) studyID;
- (void) loadRecentStudy: (id) sender;
- (void) buildRecentStudiesMenu;
- (NSMenu*) viewerMenu;
- (NSMenu*) fileMenu;
- (NSMenu*) exportMenu;
- (NSMenu*) imageTilingMenu;
- (NSMenu*) applyWindowProtocolMenu;
- (NSMenu*) VOILutMenu;
- (NSMenu*) orientationMenu;
- (NSMenu*) opacityMenu;
- (NSMenu*) wlwwMenu;
- (NSMenu*) convMenu;
- (NSMenu*) clutMenu;
- (NSMenu*) buildROIInformationsBoxMenu;
- (NSTimeInterval) runningTimeInterval;
+ (NSImage*) clutIconForClutName: (NSString*) clutName;
+ (NSImage*) clutIconForRed: (unsigned char*) redT green:(unsigned char*) greenT blue:(unsigned char*) blueT;
+ (void) setPopupMenuFont: (NSMenu*) menu;
+ (void) setPopupMenuFont: (NSMenu*) menu allItems: (BOOL) allItems;
+ (void) resetPopupMenuFont: (NSMenu*) menu;
+ (void) resetClutIcons;
+ (void) resetOpacityIcons;
+ (NSImage*) opacityIconForOpacityName: (NSString*) opacityName;
- (NSMenu*) workspaceMenu;
+ (NSImage*) wwwlIconForDcmPix: (DCMPix*) pix ww: (float) ww wl: (float) wl;
//+ (NSImage*) fusionIconForDcmPix: (DCMPix*) pix mode: (int) mode stack: (int) stack direction: (int) direction;
+ (NSImage*) convolutionIconForDcmPix: (DCMPix*) pix name: (NSString*) name;
+ (NSImage*) resizeImageForIcon: (NSImage*) im;
+ (NSRect) visibleFrameForScreen: (NSScreen*) screen;
+ (void) pingPlugin: (id) object userDict: (NSDictionary*) userDict;

#pragma mark-
#pragma mark User Notifications
- (void) growlTitle:(NSString*) title description:(NSString*) description name:(NSString*) name;
- (void) growlTitle:(NSString*) title description:(NSString*) description name:(NSString*) name userInfo: (NSDictionary*) userInfo;

//#pragma mark-
//#pragma mark display setters and getters
//- (IBAction) saveLayout: (id)sender;

#pragma mark-
#pragma mark 12 Bit Display support.
+ (BOOL)canDisplay12Bit;
+ (void)setCanDisplay12Bit:(BOOL)boo;
+ (void)setLUT12toRGB:(unsigned char*)lut;
+ (unsigned char*)LUT12toRGB;
+ (void)set12BitInvocation:(NSInvocation*)invocation;
+ (NSInvocation*)fill12BitBufferInvocation;

#pragma mark -
-(WebPortal*)defaultWebPortal;
-(BOOL) processOsiriXSchemeURL: (NSURL*) url;

#ifndef OSIRIX_LIGHT
-(NSString*)weasisBasePath;
#endif

-(void)setReceivingIcon;
-(void)unsetReceivingIcon;
-(void)setBadgeLabel:(NSString*)label;
-(void)playGrabSound;
-(IBAction)userManual:(id)sender;
@end

