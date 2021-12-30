//
//  gRPCScriptControllerBlockingCellView.h
//  osirixgrpc
//
//  Created by adminmblackledge on 07/06/2021.
//

#import <Cocoa/Cocoa.h>

@interface gRPCScriptControllerBlockingCellView : NSTableCellView

{
    IBOutlet NSButton *checkBox;
}

@property (readonly) NSButton *checkBox;

@end
