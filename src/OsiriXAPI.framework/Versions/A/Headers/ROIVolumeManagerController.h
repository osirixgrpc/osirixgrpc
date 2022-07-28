/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "Window3DController.h"

/** \brief  Window Controller for managing ROIVolume collection */

@interface ROIVolumeManagerController : NSWindowController <NSTableViewDataSource>
{
		Window3DController			*viewer;
		IBOutlet NSTableView		*tableView;
		IBOutlet NSTableColumn		*columnDisplay, *columnName, *columnVolume, *columnRed, *columnGreen, *columnBlue, *columnOpacity;
		NSMutableArray				*roiVolumes;//, *displayRoiVolumes;
		IBOutlet NSArrayController	*roiVolumesController;
		IBOutlet NSObjectController	*controllerAlias;
}

- (id) initWithViewer:(Window3DController*) v;
	// Table view data source methods
- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView;
- (void) setRoiVolumes: (NSMutableArray*) volumes;
- (NSMutableArray*) roiVolumes;

@end
