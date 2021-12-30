//
//  gRPCServerControllerActiveCellView.h
//  osirixgrpc
//
//  Created by adminmblackledge on 29/12/2021.
//

#import <Cocoa/Cocoa.h>

@interface gRPCServerControllerActiveCellView : NSTableCellView
{
    IBOutlet NSImageView *imageView;
}

@property (readwrite, assign) NSImageView *imageView;

@end
