/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

/*
The WindowLayoutManager class manages the various placement of the Viewers
primarily by use of hanging proctols and Advanced hanging protocols
and keeps track of the Viewer Related Window Controllers
It is a shared class.
 */

#import <Cocoa/Cocoa.h>

@class OSIWindowController;
//@class LayoutWindowController;
@interface WindowLayoutManager : NSObject
{
	NSDictionary *_currentHangingProtocol;
}

@property( retain) NSDictionary *currentHangingProtocol;

+ (WindowLayoutManager*)sharedWindowLayoutManager;
+ (int) windowsRowsForHangingProtocol:(NSDictionary*) protocol;
+ (int) windowsColumnsForHangingProtocol:(NSDictionary*) protocol;
+ (int) windowsTilingForRows: (int) rows columns: (int) columns;
+ (int) imageTilingForRows: (int) rows columns: (int) columns;
+ (int) imagesRowsForHangingProtocol:(NSDictionary*) protocol;
+ (int) imagesColumnsForHangingProtocol:(NSDictionary*) protocol;
- (int) windowsRows;
- (int) windowsColumns;
- (int) imagesRows;
- (int) imagesColumns;

#pragma mark-
#pragma mark hanging protocol setters and getters

+ (NSArray*) hangingProtocolsForModality: (NSString*) modality;
+ (NSDictionary*) hangingProtocolForModality: (NSString*) modalities description: (NSString *) description;
- (void) setCurrentHangingProtocolForModality: (NSString*) modality description: (NSString*) description;
- (NSDictionary*) currentHangingProtocol;

@end
