/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#ifndef OSIRIXLIGHT

#import "QueryOutlineView.h"
#import "sourcesTableView.h"
#import <AppKit/AppKit.h>
#import "SFAuthorizationView+OsiriX.h"
#import "BrowserController.h"

@class QueryArrayController;
@class QueryFilter;
@class DicomStudy;
@class DICOMFieldMenu;
@class DicomDatabase;

#define MAXINSTANCE 40

enum {
    anyDateRadio = 0,
    hoursRadio = 1,
    daysRadio = 2,
    weeksRadio = 3,
    monthsRadio = 4,
    onDateRadio = 5,
    intervalRadio = 6
};

enum
{
    anyDate = 0,
    today = 1,
    yesteday = 2,
    last7Days = 3,
    lastMonth = 4,
    between = 5,
    on = 6,
    last2Days = 7,
    last3Months = 8,
    dayBeforeYesterday = 9,
    todayAM = 10,
    todayPM = 11,
    after = 12,
    last2Months = 13,
    lastYear = 14,
    last5Months = 15,
    last6Months = 16,
    last8Months = 17,
    last10Months = 18,
    last12Months = 19
};

/** \brief Window Controller for Q/R */
@interface QueryController : NSWindowController <NSWindowDelegate, NSOutlineViewDelegate, NSTableViewDelegate, NSMenuDelegate>
{
    IBOutlet    QueryOutlineView			*outlineView;
	IBOutlet	NSProgressIndicator			*progressIndicator;
	IBOutlet	NSSearchField				*searchFieldName, *searchFieldRefPhysician, *searchFieldID, *searchFieldAN, *searchFieldStudyDescription, *searchFieldBodyPart, *searchFieldComments, *searchInstitutionName, *searchCustomField, *searchFieldStudyInstanceUID;
	
				NSMutableArray				*sourcesArray;
	IBOutlet	sourcesTableView			*sourcesTable;
	IBOutlet	NSTextField					*selectedResultSource;
	IBOutlet	NSTextField					*numberOfStudies;
	IBOutlet	NSPopUpButton				*presetsPopup;
	
	IBOutlet	NSWindow					*presetWindow;
	IBOutlet	NSTextField					*presetName;
	
    IBOutlet	NSMatrix					*mwlStatusMatrix;
	IBOutlet	NSMatrix					*birthdateFilterMatrix;
    IBOutlet    NSStackView                 *dateFilterMatrix;
    IBOutlet    NSPopUpButton               *hoursMenu, *daysMenu, *weeksMenu, *monthsMenu;
	IBOutlet	NSMatrix					*modalityFilterMatrix;
    IBOutlet    NSMatrix                    *statusFilterMatrix;
	IBOutlet	NSTabView					*PatientModeMatrix;
	IBOutlet	NSDatePicker				*fromDate, *toDate, *onDate;
	IBOutlet	NSTextField					*yearOldBirth, *searchBirthField;
    IBOutlet	NSPopUpButton				*sendToPopup;
    
    IBOutlet NSView*                        refreshGroup;
	
	int										autoQueryRemainingSecs[ MAXINSTANCE];
	IBOutlet NSTextField					*autoQueryCounter;
	
	BOOL									DatabaseIsEdited;
	IBOutlet NSWindow						*autoRetrieveWindow;
	
	NSMutableString							*pressedKeys;
    NSMutableArray							*resultArray;
    NSMutableArray							*queryFilters;
	
	NSString								*currentQueryKey, *queryArrayPrefs;
	int										checkAndViewTry;
	
	NSImage									*Realised3, *Realised2;
	NSTimer									*QueryTimer;
	IBOutlet NSImageView					*alreadyInDatabase, *partiallyInDatabase;
	
	QueryArrayController					*queryManager;
	
	BOOL									autoQuery, queryButtonPressed, performingCFind, avoidQueryControllerDeallocReentry;
	
	NSInteger								autoRefreshQueryResults;
	NSRecursiveLock							*autoQueryLock;
	
	NSInteger								numberOfRunningRetrieve;
    
    NSTimeInterval                          lastTemporaryCFindResultUpdate;
    NSMutableArray                          *temporaryCFindResultArray;
    BOOL                                    firstServerRealtimeResults;
    
    NSMutableArray                          *downloadedStudies, *autoretrieveQueue;
    
    NSString                                *customDICOMField;
    
    NSMutableArray                          *autoQRInstances;
    int                                     currentAutoQR;
    IBOutlet NSWindow                       *addAutoQRInstanceWindow;
    IBOutlet NSTextField                    *autoQRInstanceName;
    IBOutlet NSSegmentedControl             *autoQRNavigationControl;
    
    IBOutlet SFAuthorizationView            *authView;
    IBOutlet NSButton                       *authButton;
    
    NSMutableSet                            *performingQueryThreads;
    
    NSString *customDICOMFieldGroupAndElement;
    DICOMFieldMenu *DICOMField;
    NSArray *sortArrayCopy;
    int selectedSendToPopupIndex;
    
    NSDate *queryControllerToDate, *queryControllerFromDate, *queryControllerOnDate;
    
    NSDictionary *countPresetNode;
    NSThread *countPresetThread;
    
    NSMutableDictionary *localRawNoFilesCache;
    
    NSPoint menuWillOpenLocation;
    
    NSString *filterResult;
    NSArray *unfilteredResultArray;
}

@property (retain, nonatomic) NSDate *queryControllerToDate, *queryControllerFromDate, *queryControllerOnDate;
@property (readonly) NSRecursiveLock *autoQueryLock;
@property (readonly) QueryOutlineView *outlineView;
@property BOOL autoQuery, DatabaseIsEdited;
@property NSInteger autoRefreshQueryResults;
@property (nonatomic) int currentAutoQR;
@property (readonly) SFAuthorizationView* authView;
@property (retain) NSString *customDICOMFieldGroupAndElement;
@property (retain) DICOMFieldMenu *DICOMField;
@property (retain) NSDictionary *countPresetNode;
@property (retain) NSThread *countPresetThread;
@property (retain) NSMutableDictionary *localRawNoFilesCache;
@property (retain, nonatomic) NSString *filterResult;
@property (retain) NSString *resultsOutOf;
@property (retain) NSArray *unfilteredResultArray;
@property BOOL addWildcardToQuery;

+ (QueryController*) currentQueryController;
+ (QueryController*) currentAutoQueryController;
+ (void) purgeCache;
+ (NSString*) stringIDForStudy:(id) item;
+ (BOOL) echo: (NSString*) address port:(int) port AET:(NSString*) aet;
+ (BOOL) echoServer:(NSDictionary*)serverParameters;
+ (int) queryAndRetrieveAccessionNumber:(NSString*) an server: (NSDictionary*) aServer;
+ (int) queryAndRetrieveAccessionNumber:(NSString*) an server: (NSDictionary*) aServer showErrors: (BOOL) showErrors;
+ (void) retrieveStudies:(NSArray*) studies showErrors: (BOOL) showErrors;
+ (void) retrieveStudies:(NSArray*) studies showErrors: (BOOL) showErrors checkForPreviousAutoRetrieve: (BOOL) checkForPreviousAutoRetrieve;
+ (void) retrieveStudies:(NSArray*) studies showErrors: (BOOL) showErrors checkForPreviousAutoRetrieve: (BOOL) checkForPreviousAutoRetrieve onlyIfNeeded: (BOOL) onlyIfNeeded;

+ (NSMutableArray*) queryStudiesForFilters:(NSDictionary*) filters servers: (NSArray*) serversList showErrors: (BOOL) showErrors;
+ (NSMutableArray*) queryStudiesForFilters:(NSDictionary*) filters servers: (NSArray*) serversList showErrors: (BOOL) showErrors error:(NSError**) error;
+ (NSMutableArray*) querySeriesForFilters:(NSDictionary*) filters servers: (NSArray*) serversList showErrors: (BOOL) showErrors;

+ (NSArray*) queryStudiesForPatient:(DicomStudy*) study usePatientID:(BOOL) usePatientID usePatientName:(BOOL) usePatientName usePatientBirthDate: (BOOL) usePatientBirthDate servers: (NSArray*) serversList showErrors: (BOOL) showErrors;
+ (NSArray*) queryStudyInstanceUID:(NSString*) an server: (NSDictionary*) aServer;
+ (NSArray*) queryStudyInstanceUID:(NSString*) an server: (NSDictionary*) aServer showErrors: (BOOL) showErrors;
+ (NSArray*) querySOPInstancesForStudyInstanceUID:(NSString*) an server: (NSDictionary*) aServer;
+ (NSArray*) querySOPInstancesForStudyInstanceUID:(NSString*) an server: (NSDictionary*) aServer showErrors: (BOOL) showErrors;
+ (NSArray*) querySOPInstancesForStudyInstanceUID:(NSString*) an server: (NSDictionary*) aServer database: (DicomDatabase*) db showErrors: (BOOL) showErrors;
- (void) autoRetrieveSettings: (id) sender;
- (void) saveSettings;
+ (void) getDateAndTimeQueryFilterWithTag: (intervalType) tag fromDate:(NSDate*) from toDate:(NSDate*) to onDate:(NSDate*) onDate date: (QueryFilter**) dateQueryFilter time: (QueryFilter**) timeQueryFilter;
- (void) applyPresetDictionary: (NSDictionary *) presets;
- (void) emptyPreset:(id) sender;
- (NSMutableDictionary*) savePresetInDictionaryWithDICOMNodes: (BOOL) includeDICOMNodes;
- (id) initAutoQuery: (BOOL) autoQuery;
- (IBAction) cancel:(id)sender;
- (IBAction) ok:sender;
- (void) refreshAutoQR: (id) sender;
- (void) refreshList: (NSArray*) l;
- (void) setCurrentAutoQR: (int) index;
- (NSArray*) queryWithDisplayingErrors:(BOOL) showError;
- (NSArray*) queryWithDisplayingErrors:(BOOL) showError instance: (NSMutableDictionary*) instance index: (int) index;
- (IBAction) selectUniqueSource:(id) sender;
- (void) selectSourceForServer:(NSDictionary*)server;
- (QueryFilter*) getModalityQueryFilter:(NSArray*) modalityArray;
- (void) refreshSources;
- (IBAction) retrieveAndViewClick: (id) sender;
- (IBAction) retrieveAndView: (id) sender;
- (void) delete:(id)sender;
- (IBAction) view:(id) sender;
- (IBAction) setBirthDate:(id) sender;
- (NSArray*) queryPatientID:(NSString*) ID;
- (void) query:(id)sender;
- (void) retrieve:(id)sender;
- (void) retrieveClick:(id)sender;
- (void) retrieve:(id)sender onlyIfNotAvailable:(BOOL) onlyIfNotAvailable;
- (BOOL) performQuery:(NSNumber*) showErrors;
- (void) performRetrieve:(NSArray*) array;
- (void) setDateQuery:(id)sender;
- (void) setModalityQuery:(id)sender;
- (void) clearQuery:(id)sender;
- (int) dicomEcho:(NSDictionary*) aServer;
- (IBAction) verify:(id)sender;
//- (void) refresh: (id) sender;
//- (void) executeRefresh: (id) sender;
- (IBAction) pressButtons:(id) sender;
- (NSArray*) localSeries:(id) item;
- (NSArray*) localStudy:(id) item;
- (NSArray*) localSeries:(id) item context: (NSManagedObjectContext*) context;
- (NSArray*) localStudy:(id) item context: (NSManagedObjectContext*) context;
- (IBAction) endAddPreset:(id) sender;
- (void) buildPresetsMenu;
- (IBAction) autoQueryTimer:(id) sender;
- (IBAction) switchAutoRetrieving: (id) sender;
- (IBAction) selectModality: (id) sender;
- (void) displayAndRetrieveQueryResults: (NSDictionary*) instance;
- (void) autoQueryThread:(NSDictionary*) d;
- (void) autoQueryTimerFunction:(NSTimer*) t;
- (void)view:(NSView*)view recursiveBindEnableToObject:(id)obj withKeyPath:(NSString*)keyPath;
- (void) pressStateCellForRow: (int) clickedRow column: (int) clickedColumn event: (NSEvent*) event;
@end

#endif
