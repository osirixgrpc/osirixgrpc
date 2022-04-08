//
//  gRPCScriptControllerInterpreterCellView.h
//  osirixgrpc
//
//  Created by adminmblackledge on 06/06/2021.
//

#import <Cocoa/Cocoa.h>

@interface gRPCScriptControllerInterpreterCellView : NSTableCellView
{
    IBOutlet NSButton *openButton;
    IBOutlet NSTextField *textField;
}

@property (readonly) NSButton *openButton;
@property (readwrite, assign) NSTextField *textField;

@end
