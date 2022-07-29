/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@class ViewerController;

/** \brief Window Controller for DICOM printing */
@interface DCMPrintSCUWindowController : NSWindowController <NSWindowDelegate> {
    NSMutableDictionary *printer;
    NSArray *printers, *printersMenu;
    int selectedPrinter;
    NSString *printerDescription;
    
    NSRect windowFrameToRestore;
    ViewerController *viewer;
    BOOL scaleFitToRestore;
    int pages, from, to, interval, numberOfImages, modalMode;
    NSString *pagesTextfield;
    IBOutlet NSSlider *fromSlider;
    IBOutlet NSSlider *toSlider;
    
    BOOL saveAsPreferredSettings;
    
    NSString *printFolder;
}
@property (retain) ViewerController *viewer;
@property (retain) NSArray *printers, *printersMenu;
@property (nonatomic) int selectedPrinter;
@property (retain) NSString *printerDescription, *pagesTextfield, *printFolder;
@property (retain) NSMutableDictionary *printer;
@property (nonatomic) int pages, from, to, interval, numberOfImages;
@property BOOL saveAsPreferredSettings;

- (IBAction) cancel: (id) sender;
- (IBAction) printImages: (id) sender;
@end
