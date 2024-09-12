#import <Foundation/Foundation.h>

/*!
 * @abstract
 * Categorizes the task types that can be run within OsiriX
 *
 * @constant gRPCImageTask
 * Performs image manipulation.  Task available from the ViewerController window menu.
 *
 * @constant gRPCROITask
 * Modify/create regions of interest.  Task available from the ViewerController window menu.
 *
 * @constant gRPCDatabaseTask
 * Dicom database manipulation.  Task available from the BrowserController window menu.
 *
 * @constant gRPCVolumeRenderTask
 * Volume render manipulation.  Task available from the VRController window menu.
 */
typedef enum {
    gRPCImageTask,
    gRPCROITask,
    gRPCDatabaseTask,
    gRPCVolumeRenderTask
} gRPCTaskType;

/*!
 * A data model for storage and management of tasks installed/run by the user. Instances of the model will be controlled by `gRPCTaskContoller`
 */
@interface gRPCTask : NSObject <NSSecureCoding>
{
    NSString *name;
    BOOL blocking;
    gRPCTaskType type;
    NSURL *executable;
    NSString *arguments;
}

/*!
 * @property name
 *
 * @abstract
 * The display name of the task within menu items.
 */
@property (readwrite, atomic, copy) NSString *name;

/*!
 * @property blocking
 *
 * @abstract
 * Whether to run the task modally (blocking) or not.
 */
@property (readwrite, assign) BOOL blocking;

/*!
 * @property type
 *
 * @abstract
 * The type of task.  This will define the menubar within which the task will be displayed.
 *
 * @discussion
 * Will be one of the following enum values:
 *    gRPCImageTool
 *    gRPCROITool
 *    gRPCDatabaseTool
 *    gRPCVolumeRenderTool
 */
@property (readwrite, assign) gRPCTaskType type;

/*!
 * @property executable
 *
 * @abstract
 * The location of the executable used to run the task as a URL.
 */
@property (readwrite, atomic, copy) NSURL *executable;

/*!
 * @property arguments
 *
 * @abstract
 * A string of arguments that will be passed to the executable when run.
 */
@property (readwrite, assign) NSString *arguments;

/*!
 * @method initWithExecutableURL: name: type: arguments: isBlocking:
 *
 * @abstract
 * Intialise a new instance of gRPCTask
 *
 * @param url
 * The location of the executable.
 *
 * @param name
 * The display name of the task
 *
 * @param type
 * The type of the task.  One of:
 *    gRPCImageTask
 *    gRPCROITask
 *    gRPCDatabaseTask
 *    gRPCVolumeRenderTask
 *
 * @param arguments
 * The arguments that will be passed to the task executable.
 *
 * @param blocking
 * Whether to run the task modally (blocking) or not.
 */
- (id) initWithExecutableURL:(NSURL *)url_ name:(NSString *)name_ type:(gRPCTaskType)type_ arguments:(NSString *)arguments_ blocking:(BOOL) blocking_;

/*!
 * @method isEqualToTask:
 *
 * @abstract
 * Used to define equality between two tasks
 *
 * @discussion
 * Tasks will be considered equal if the following properties are equivalent: name, type
 *
 * @return
 * Boolean value indicating equality
 */
- (BOOL) isEqualToTask:(gRPCTask *) task;

@end
