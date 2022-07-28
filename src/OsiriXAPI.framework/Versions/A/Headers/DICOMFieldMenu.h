/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Foundation/Foundation.h>

@interface DICOMFieldMenu : NSObject <NSTableViewDataSource>
{
    IBOutlet NSPopover *popOver;
    IBOutlet NSArrayController *dicomFieldsArrayController;
    IBOutlet NSTextField *fieldDescriptionTextField;
    IBOutlet NSTableView *dicomFieldsTableView;
    
    int group, element;
    NSString *groupString, *elementString, *dicomFile;
    
    BOOL onlyInDICOMFile;
    
    NSMutableArray *orderedDICOMFieldsArray;
    
    void (^block)(void);
}

@property (copy) void (^block)(void);
@property (assign) IBOutlet NSArrayController *dicomFieldsArrayController;
@property (readonly) NSPopover *popOver;
@property (retain, nonatomic) NSString *groupString, *elementString, *dicomFile;
@property (retain) NSMutableArray *orderedDICOMFieldsArray;
@property (nonatomic) int group, element;
@property (nonatomic) BOOL onlyInDICOMFile;

+ (id) displayRelativeToRect: (NSRect) r ofView: (NSView*) view withGroup: (int) g andElement: (int) e performOnClose: (void (^)(void))block;
+ (id) menuWithGroup: (int) g andElement: (int) e;
- (IBAction) close:(id)sender;
- (NSString*) string;

@end
