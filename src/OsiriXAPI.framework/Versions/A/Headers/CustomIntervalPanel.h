/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@interface CustomIntervalPanel : NSWindowController
{
    NSDate *fromDate;
    NSDate *toDate;
    
    IBOutlet NSMatrix *matrix;
    IBOutlet NSDatePicker *fromPicker;
    IBOutlet NSDatePicker *toPicker;
    IBOutlet NSDatePicker *textualFromPicker;
    IBOutlet NSDatePicker *textualToPicker;
}

@property (nonatomic, retain) NSDate *fromDate, *toDate;

+ (CustomIntervalPanel*) sharedCustomIntervalPanel;
- (IBAction) nowFrom:(id)sender;
- (IBAction) nowTo:(id) sender;
- (void) sizeWindowAccordingToSettings;
- (void) setFormatAccordingToSettings;

@end
