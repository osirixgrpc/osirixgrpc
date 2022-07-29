/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>
#import <PreferencePanes/NSPreferencePane.h>
#import "SFAuthorizationView+OsiriX.h"


@class PreferencesView, PreferencesWindowContext;


/** \brief Window Controller for Preferences */

@interface PreferencesWindowController : NSWindowController <NSWindowDelegate, NSSearchFieldDelegate, NSTableViewDataSource, NSTableViewDelegate, NSToolbarDelegate>
{
    NSSearchToolbarItem *searchItem API_AVAILABLE(macos(11.0));
    IBOutlet NSView *searchResultsPopoverView;
    IBOutlet NSTableView *searchResultsPopoverTable;
    NSPopover *searchResultsPopover;
    NSArray *searchResults;
    
    IBOutlet NSScrollView* scrollView;
	IBOutlet PreferencesView* panesListView;
	IBOutlet NSButton* authButton;
	IBOutlet SFAuthorizationView* authView;
	PreferencesWindowContext* currentContext;
	IBOutlet NSView* flippedDocumentView;
    NSSize paneListSize, windowSize;
    
    NSString *signedInLabel;
}

@property(readonly) SFAuthorizationView* authView;
@property(retain) NSString *signedInLabel;
@property(retain, nonatomic) NSArray *searchResults;
@property(retain) NSPopover *searchResultsPopover;

+ (PreferencesWindowController*) sharedPreferencesWindowController;
+(void) addPluginPaneWithResourceNamed:(NSString*)resourceName inBundle:(NSBundle*)parentBundle withTitle:(NSString*)title image:(NSImage*)image;
+(void) removePluginPaneWithBundle:(NSBundle*)parentBundle;

-(BOOL)isUnlocked;

-(IBAction)showAllAction:(id)sender;
-(IBAction)navigationAction:(id)sender;
-(IBAction)authAction:(id)sender;

-(void)reopenDatabase;
-(void)setCurrentContextWithResourceName: (NSString*) name;
-(void)setCurrentContext:(PreferencesWindowContext*)context;
@end


@interface PreferencesWindowContext : NSObject {
	NSString* _title;
	NSBundle* _parentBundle;
	NSString* _resourceName;
	NSPreferencePane* _pane;
    NSImage *icon;
}

@property(retain) NSString* title;
@property(retain) NSBundle* parentBundle;
@property(retain) NSString* resourceName;
@property(retain) NSImage *icon;
@property(nonatomic, retain) NSPreferencePane* pane;

-(id)initWithTitle:(NSString*)title withResourceNamed:(NSString*)resourceName inBundle:(NSBundle*)parentBundle;

@end
