/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/




#import "ROI.h"
#import "MyNSTextView.h"
#import "ViewerController.h"

/** \brief  Window Controller for ROI defaults */

@interface ROIDefaultsWindow : NSWindowController <NSComboBoxDataSource>
{
	NSArray			*roiNames;
	
}
/** Set Name and closes Window */
- (IBAction)setDefaultName:(id)sender;

/** Set default name to nil */
- (IBAction)unsetDefaultName:(id)sender;

/** Default initializer */
- (id)initWithController: (ViewerController*) c;

@end
