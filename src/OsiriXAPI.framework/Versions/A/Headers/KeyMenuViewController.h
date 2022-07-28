//
//  KeyMenuView.h
//  OsiriXMDInstaller
//
//  Created by antoinerosset on 10.04.19.
//

#import <Cocoa/Cocoa.h>

@interface KeyMenuViewController : NSViewController
{
    IBOutlet NSTextField *product;
	IBOutlet NSTextField *purchaseDate;
    IBOutlet NSTextField *key;
    IBOutlet NSImageView *computer;
    IBOutlet NSTextField *installedOn;
}
@property (readonly) NSTextField  *product, *purchaseDate, *key;

- (id)initWithDictonary: (NSDictionary*) d;
+ (id)keyMenuItemWithDictionary: (NSDictionary*) d;
@end
