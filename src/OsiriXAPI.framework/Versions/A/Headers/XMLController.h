/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>
#import "OSIWindowController.h"
#import "XMLOutlineView.h"

@class ViewerController;
@class DCMObject;
@class DICOMFieldMenu;

/** \brief Window Controller for XML parsing */

@interface XMLController : OSIWindowController <NSToolbarDelegate, NSWindowDelegate, NSSearchFieldDelegate>
{
    IBOutlet XMLOutlineView		*table;
	IBOutlet NSScrollView		*tableScrollView;
    IBOutlet NSSearchField		*search;
    IBOutlet NSView				*searchView, *dicomEditingView;
    
    int searchCount, searchIndex;
    id currentSearchItem;
    int currentSearchRow;
	
    unsigned long               srcFileSize;
	NSStringEncoding            srcFileEncoding;
    NSMutableArray				*xmlDcmData;
    NSData						*xmlData;    
    NSToolbar					*toolbar;	
	NSString					*srcFile;
	NSXMLDocument				*xmlDocument;
    DCMObject                   *dcmDocument;
	DicomImage                  *imObj;
	NSMutableArray				*dictionaryArray;
	
	ViewerController			*viewer;
	
	BOOL						isDICOM, dontClose;
	BOOL						editingActivated;
	BOOL						allowSelectionChange;
	
	int							editingLevel;
	
	IBOutlet NSWindow			*addWindow;
	IBOutlet NSTextField		*addValue;
	
	IBOutlet NSWindow			*validatorWindow;
	IBOutlet NSTextView			*validatorText;
	
	BOOL						dontListenToIndexChange;
    NSMutableArray              *modificationsToApplyArray, *modifiedFields, *modifiedValues;
    NSMutableDictionary         *cache;
    
    DICOMFieldMenu *DICOMField;
    NSString *addDICOMFieldTextField;
}

@property (retain) NSString *addDICOMFieldTextField;
@property (retain) DICOMFieldMenu *DICOMField;
@property (retain) id currentSearchItem;
@property int editingLevel, searchCount, searchIndex;

- (BOOL) modificationsToApply;

+ (XMLController*) windowForViewer: (ViewerController*) v;
+ (NSDictionary *) DICOMDefitionsLinks;
+ (void) prepareDICOMDefitionsLinks;

- (void) changeImageObject:(DicomImage*) image;
- (id) initWithImage:(DicomImage*) image windowName:(NSString*) name viewer:(ViewerController*) v;
- (void) setupToolbar;
- (NSMenu*) menuForRow:(int) row;
- (IBAction) addDICOMField:(id) sender;
- (IBAction) executeAdd:(id) sender;
- (IBAction) validatorWebSite:(id) sender;
- (IBAction) verify:(id) sender;
- (void) reload:(id) sender;
- (void) reloadFromDCMDocument;
- (BOOL) item: (id) item containsString: (NSString*) s;
- (void) expandAllItems: (id) sender;
- (void) deepExpandAllItems: (id) sender;
- (void) expandAll: (BOOL) deep;
- (void) collapseAllItems: (id) sender;
- (void) deepCollapseAllItems: (id) sender;
- (void) collapseAll: (BOOL) deep;
- (IBAction) setSearchString:(id) sender;
- (NSString*) srcFile;
- (NSString*) stringsSeparatedForNode:(NSXMLNode*) node;
- (void) traverse: (NSXMLNode*) node string:(NSMutableString*) string;
- (void) clickInDefinitionCell: (NSCell*) cell event: (NSEvent*) event;

@property(readonly) NSManagedObject *imObj;
@property(readonly) ViewerController *viewer;
@property(nonatomic) BOOL editingActivated;
@end
