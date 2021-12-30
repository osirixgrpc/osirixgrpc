#import <Cocoa/Cocoa.h>

#import "gRPCScript.h"
#import "gRPCScriptManager.h"

@interface gRPCScriptController : NSWindowController <NSWindowDelegate, NSTableViewDataSource, NSTableViewDelegate>
{
    gRPCScriptManager *scriptManager;
    
    IBOutlet NSTableView *scriptTable;
}

# pragma mark -
# pragma mark initializer
/*!
 * @abstract
 * Initialise the class with the plugin script manager.
 *
 * @param scriptManager
 * The manager to act as the data source for the table view. 
 *
 * @return
 * A reference to the create instance of the gRPCScriptController.
 */
- (id)initWithScriptManager: (gRPCScriptManager *) scriptManager;

# pragma mark -
# pragma mark Script window methods

- (IBAction)addRemoveScript:(id)sender;

+ (NSString *) gRPCScriptControllerErrorDomain;

@end
