//
//  gRPCScriptControllerTypeCellView.h
//  osirixgrpc
//
//  Created by adminmblackledge on 07/06/2021.
//

#import <Cocoa/Cocoa.h>

@interface gRPCScriptControllerTypeCellView : NSTableCellView
{
    IBOutlet NSPopUpButton *popUpButton;
}

@property (assign) NSPopUpButton *popUpButton;

@end
