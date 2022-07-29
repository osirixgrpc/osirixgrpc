/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

/** \brief base class for Window Controllers in OsiriX
*
*Root class for the Viewer Window Controllers such as ViewerController
*and Window3DController
*/

#import <Cocoa/Cocoa.h>
@class DicomDatabase, ROI;


#ifdef __cplusplus
extern "C"
{
#endif

NSInteger OSIRunPanel( NSAlertStyle style, NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...);

NSInteger OSIRunCriticalAlertPanel( NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...);
NSInteger OSIRunInformationalAlertPanel( NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...);
NSInteger OSIRunAlertPanel( NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...);

#ifdef __cplusplus
}
#endif

enum OsiriXBlendingTypes {BlendingPlugin = -1, BlendingFusion = 1, BlendingSubtraction, BlendingMultiplication, BlendingRed, BlendingGreen, BlendingBlue, Blending2DRegistration, Blending3DRegistration, BlendingLL};

#ifdef id
#define redefineID
#undef id
#endif

@class DicomImage, DicomSeries, DicomStudy;

@interface OSIWindowController : NSWindowController <NSWindowDelegate>
{
	int _blendingType;
	
	BOOL magneticWindowActivated;
	BOOL windowIsMovedByTheUserO;
    NSTimeInterval windowDidMoveLastTimeInterval;
	NSRect savedWindowsFrameO;
	NSTimeInterval windowInitTime;
    
	DicomDatabase* _database;
}

@property(nonatomic,retain) DicomDatabase* database;
@property NSTimeInterval windowInitTime;

-(void)refreshDatabase:(NSDictionary*)dict;
- (void) autoreleaseIfClosed;
+ (BOOL) dontWindowDidChangeScreen;
+ (void) setDontEnterWindowDidChangeScreen:(BOOL) a;
+ (void) setDontEnterMagneticFunctions:(BOOL) a;
- (void) setMagnetic:(BOOL) a;
- (BOOL) magnetic;
+ (NSArray*) allMagneticWindowControllers;

+ (void) setWindowAppearance: (NSWindow*) window;
+ (NSColor*) darkAppearanceFontColor;
+ (NSColor*) darkAppearanceFontColorWithAlpha: (float) alpha;
+ (NSColor*) darkAppearanceBackgroundColor;
+ (NSColor*) darkAppearanceBlackColor;
+ (NSColor*) darkAppearanceBlackColorWithAlpha: (float) alpha;
+ (float) darkAppearanceFontColorWhiteLevel;

- (NSMutableArray*) pixList;
- (void) addToUndoQueue:(NSString*) what;
- (int)blendingType;

- (void) addROI:(ROI*) roi;
- (void) selectROI:(ROI*) roi deselectingOther:(BOOL)deselectOther;

- (IBAction) redo:(id) sender;
- (IBAction) undo:(id) sender;

- (IBAction) applyShading:(id) sender;
- (void) updateAutoAdjustPrinting: (id) sender;

#pragma mark-
#pragma mark current Core Data Objects
- (DicomStudy *)currentStudy;
- (DicomSeries *)currentSeries;
- (DicomImage *)currentImage;

- (float)curWW;
- (float)curWL;
@end

#ifdef redefineID
#define id Id
#undef redefineID
#endif
