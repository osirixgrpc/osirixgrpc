//
//  KeyMenuView.h
//  OsiriXMDInstaller
//
//  Created by antoinerosset on 10.04.19.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface KeyMenuView : NSView
{
    IBOutlet NSTextField *product;
	IBOutlet NSTextField *purchaseDate;
	IBOutlet NSTextField *purchaseDateLabel;
    IBOutlet NSTextField *key;
	IBOutlet NSTextField *keyLabel;
    IBOutlet NSTextField *installedOn;
	IBOutlet NSTextField *installedOnLabel;
    
    BOOL highlighted;
}
@end

NS_ASSUME_NONNULL_END
