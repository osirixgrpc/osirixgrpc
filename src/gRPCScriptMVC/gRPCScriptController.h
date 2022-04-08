#import <Cocoa/Cocoa.h>

#import "gRPCScript.h"

/**
 * Manages the location and properties of installed scripts, which can be anywhere on the user system.
 * There should only ever be one instance created within the osirixgrpc runtime, and it should be
 * managed by the gRPCPluginFilter at the top level of the plugin.
 *
 * It contains a NSMutableArray of `gRPCScript` instances that contain information about the scripts
 * that have been installed; dictionary keys match the name of the script.
 *
 * Utility methods are provided for adding and removing scripts.
 */

@interface gRPCScriptController : NSWindowController <NSWindowDelegate, NSTableViewDataSource, NSTableViewDelegate>
{
    IBOutlet NSTableView *scriptTable;
    NSURL *storageURL;
    NSMutableArray *scripts;
}

# pragma mark -
# pragma mark properties

/*!
 * @property storageURL
 *
 * @abstract
 * The URL that has been requested by the user to store the script file information.
 */
@property (readonly) NSURL *storageURL;

/*!
 * @property scripts
 *
 * @abstract
 * NSMutableArray of gRPCScript instances.
 */
@property (readonly) NSMutableArray *scripts;

# pragma mark -
# pragma mark initializer
/*!
 * @abstract
 * Initialise the class with a URL to which the database file will be saved.
 *
 * @param url
 * The url in which to store the database.
 *
 * @return
 * A reference to the create instance of the gRPCScriptManager.
 */
- (id)initWithStorageURL:(NSURL *)url;

# pragma mark -
# pragma mark Script accessors
/*!
 * @abstract
 * Access the `gRPCScript` instance associated with a specific name.
 *
 * @param name
 * The name of the script.
 *
 * @return
 * The `gRPCScript' instance with the requested name
 */
- (gRPCScript *) scriptWithName: (NSString *)name;

/*!
 * @abstract
 * Check whether a scriptwith a given name exists in the database.
 *
 * @param name
 * The name of the script.
 *
 * @return
 * Whether a script with the specified name is present.
 */
- (BOOL) scriptPresentWithName:(NSString *)name;

/*!
 * @abstract
 * The names of all contained scripts with a particular type.
 *
 * @param type
 * The types of script requested.
 * One of:
 *    gRPCImageTool
 *    gRPCROITool
 *    gRPCDatabaseTool
 *    gRPCVolumeRenderTool
 */
- (NSArray *) scriptNamesForType:(gRPCScriptType)type;

# pragma mark -
# pragma mark Script register/unregister

/*!
 * @abstract
 * Register a script from a given URL
 *
 * @param url
 * The URL of the script that needs registration.
 */
- (void) registerScriptAtURL:(NSURL *)url;

/*!
 * @abstract
 * Unregister scripts
 *
 * @param scripts
 * An array of gRPCScript instances to remove. Any that are not contained will be ignored.
 *
 * @return
 * A boolean indicating the success or failure of script removal.
 */
- (void) unregisterScripts:(NSArray *)scripts;

/*!
 * @abstract
 * Unregister script
 *
 * @param script
 * The gRPCScript instance to remove. If not contained will be ignored and return False.
 *
 * @return
 * A boolean indicating the success or failure of script removal.
 */
- (void) unregisterScript:(gRPCScript *)script;

/*!
 * @abstract
 * Save current scripts to file
 *
 * @param scripts
 * An NSArray of gRPCScript instances
 */
- (void) saveScripts:(NSArray *) scripts;

# pragma mark -
# pragma mark Script window methods

- (IBAction)addRemoveScript:(id)sender;

+ (NSString *) gRPCScriptControllerErrorDomain;

@end
