#import <Cocoa/Cocoa.h>

#import "gRPCTask.h"

/**
 * Manages the location, properties and runtime of installed tasks.
 * There should only ever be one instance of this class created within the osirixgrpc runtime, and it should be
 * managed by the gRPCPluginFilter at the top level of the plugin.
 *
 * It contains a NSMutableArray of `gRPCTask` instances that contain information about the tasks
 * that have been installed; dictionary keys match the name of the task.
 *
 * Utility methods are provided for adding and removing tasks.
 */

@interface gRPCTaskController : NSWindowController <NSWindowDelegate, NSTableViewDataSource, NSTableViewDelegate>
{
    IBOutlet NSTableView *taskTable;
    NSURL *storageURL;
    NSMutableArray *tasks;
}

# pragma mark -
# pragma mark properties

/*!
 * @property storageURL
 *
 * @abstract
 * The URL that has been requested by the user to store the task file information.
 */
@property (readonly) NSURL *storageURL;

/*!
 * @property tasks
 *
 * @abstract
 * NSMutableArray of gRPCTask instances.
 */
@property (readonly) NSMutableArray *tasks;

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
 * A reference to the create instance of the gRPCTaskController.
 */
- (id)initWithStorageURL:(NSURL *)url;

# pragma mark -
# pragma mark Task accessors
/*!
 * @abstract
 * Access the `gRPCTask` instance associated with a specific name.
 *
 * @param name
 * The name of the task.
 *
 * @return
 * The `gRPCTask` instance with the requested name
 */
- (gRPCTask *) taskWithName: (NSString *)name;

/*!
 * @abstract
 * Check whether a task with a given name exists in the database.
 *
 * @param name
 * The name of the task.
 *
 * @return
 * Whether a task with the specified name is present.
 */
- (BOOL) taskPresentWithName:(NSString *)name;

/*!
 * @abstract
 * The names of all contained tasks with a particular task type.
 *
 * @param type
 * The type of task requested.
 * One of:
 *    gRPCImageTask
 *    gRPCROITask
 *    gRPCDatabaseTask
 *    gRPCVolumeRenderTask
 */
- (NSArray *) taskNamesForType:(gRPCTaskType)type;

# pragma mark -
# pragma mark Task register/unregister

/*!
 * @abstract
 * Register a task from a given URL
 *
 * @param url
 * The URL of the task that needs registration.
 */
- (void) registerTaskAtURL:(NSURL *)url;

/*!
 * @abstract
 * Unregister tasks
 *
 * @param tasks
 * An array of gRPCTask instances to remove. Any that are not contained will be ignored.
 */
- (void) unregisterTasks:(NSArray *)tasks;

/*!
 * @abstract
 * Unregister task
 *
 * @param task
 * The gRPCTask instance to remove. If not contained will be ignored.
 */
- (void) unregisterTask:(gRPCTask *)task;

/*!
 * @abstract
 * Save current tasks to file
 *
 * @param tasks
 * An NSArray of gRPCTask instances
 */
- (void) saveTasks:(NSArray *) tasks;

# pragma mark -
# pragma mark Task window methods

- (IBAction)addRemoveTask:(id)sender;

+ (NSString *) gRPCTaskControllerErrorDomain;

@end
