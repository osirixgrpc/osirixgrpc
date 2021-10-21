//
//  gRPCScript.h
//  osirixgrpc
//
//  Created by adminmblackledge on 14/04/2021.
//

#import <Foundation/Foundation.h>

/*!
 * @abstract
 * Categorizes the script types that can be run
 *
 * @constant gRPCImageTool
 * Performs image manipulation.  Script available from the ViewerController window menu.
 *
 * @constant gRPCROITool
 * Modify/create regions of interest.  Script available from the ViewerController window menu.
 *
 * @constant gRPCDatabaseTool
 * Dicom database manipulation.  Script available from the BrowserController window menu.
 *
 * @constant gRPCVolumeRenderTool
 * Volume render manipulation.  Script available from the VRController window menu.
 */
typedef enum {
    gRPCImageTool,
    gRPCROITool,
    gRPCDatabaseTool,
    gRPCVolumeRenderTool
} gRPCScriptType;

/*!
 * @abstract
 * Categorizes the script languages that are supported
 *
 * @constant gRPCPython
 * Python script that should be run with a Python interpreter
 *
 * @constant gRPCUndefined
 * Script language not yet officially supported.  If a valid interpreter is available it can be run, but at users own risk.
 *
 * @discussion
 * The script language is automatically detected when passed to the gRPC plugin.
 */
typedef enum {
    gRPCUndefined,
    gRPCPython
} gRPCScriptLanguage;

/*!
 * A data model for storage and management of scripts installed by the user. Instances of the model will be controlled by `gRPCScriptContoller`
 */
@interface gRPCScript : NSObject <NSSecureCoding>
{
    NSURL *url;
    NSURL *interpreter;
    NSString *name;
    BOOL blocking;
    gRPCScriptType type;
    gRPCScriptLanguage language;
    NSMutableArray *arguments;
}

/*!
 * @property url
 *
 * @abstract
 * The location of the script file as a URL.
 *
 * @discussion
 * This property can only be read.  The location of the script file will be managed by the plugin and thus can only be set upon initialisation.
 */
@property (readonly) NSURL *url;

/*!
 * @property interpreter
 *
 * @abstract
 * The location of the interpreter used to run the script as a URL.
 */
@property (readwrite, atomic, copy) NSURL *interpreter;

/*!
 * @property name
 *
 * @abstract
 * The display name of the script within menu items.
 */
@property (readwrite, atomic, copy) NSString *name;

/*!
 * @property blocking
 *
 * @abstract
 * Whether to run the script modally (blocking) or not.
 */
@property (readwrite, assign) BOOL blocking;

/*!
 * @property type
 *
 * @abstract
 * The type of script.  This will define the menubar within which the script will be displayed.
 *
 * @discussion
 * Will be one of the following enum values:
 *    gRPCImageTool
 *    gRPCROITool
 *    gRPCDatabaseTool
 *    gRPCVolumeRenderTool
 */
@property (readwrite, assign) gRPCScriptType type;

/*!
 * @property language
 *
 * @abstract
 * The script lanuguage
 *
 * @discussion
 * Cannot only be read.
 *
 * Will be one of the following enum values:
 *    gRPCUndefined (if no language detected)
 *    gRPCPython
 */
@property (readonly) gRPCScriptLanguage language;

/*!
 * @property arguments
 *
 * @abstract
 * An array of arguments that will be passed to the executable when run.
 */
@property (readwrite, assign) NSMutableArray *arguments;

/*!
 * @method descriptionForScriptType
 *
 * @abstract
 * Provides a NSString description of the script type
 *
 * @return
 * NSString description.
 */
+ (NSString *) descriptionForScriptType: (gRPCScriptType)type;

/*!
 * @method descriptionForScriptLanguage
 *
 * @abstract
 * Provides a NSString description of the script language
 *
 * @return
 * NSString description.
 */
+ (NSString *) descriptionForScriptLanguage: (gRPCScriptLanguage)language;

/*!
 * @method detectLanguageOfScriptAtPath
 *
 * @abstract
 * Detect the language of script at the specified location.
 *
 * @param path
 * The location of the script file as a NSString variable (absolute path).
 *
 * @return
 * gRPCScriptLanguage integer defining the detected script.  Will return `gRPCUndefined` if not detected.
 */
+ (gRPCScriptLanguage) detectLanguageOfScriptAtPath:(NSString *)path;

/*!
 * @method detectLanguageOfScriptAtURL
 *
 * @abstract
 * Detect the language of script at the specified location.
 *
 * @param path
 * The location of the script file as a NSURL variable.
 *
 * @return
 * gRPCScriptLanguage integer defining the detected script.  Will return `gRPCUndefined` if not detected.
 */
+ (gRPCScriptLanguage) detectLanguageOfScriptAtURL:(NSURL *)url;

/*!
 * @method detectNameOfScriptAtPath
 *
 * @abstract
 * Detect the name of script at the specified location (filename without extension).
 *
 * @param path
 * The location of the script file as a NSString variable (absolute path).
 *
 * @return
 * NSString for the automatically generated script name.
 */
+ (NSString *) detectNameOfScriptAtPath:(NSString *)path;

/*!
 * @method detectNameOfScriptAtURL
 *
 * @abstract
 * Detect the name of script at the specified location (filename without extension).
 *
 * @param url
 * The location of the script file as a NSURL variable.
 *
 * @return
 * NSString for the automatically generated script name.
 */
+ (NSString *) detectNameOfScriptAtURL:(NSURL *)url;

/*!
 * @method initWithURL: interpreter: name: type: isBlocking:
 *
 * @abstract
 * Intialise a new instance of gRPCScript
 *
 * @param url
 * The location of the script file.
 *
 * @param interpreter
 * The location of the interpreter.  Can be nil if not yet set-up.
 *
 * @param name
 * The display name of the script
 *
 * @param type
 * The type of the script.  One of:
 *    gRPCImageTool
 *    gRPCROITool
 *    gRPCDatabaseTool
 *    gRPCVolumeRenderTool
 *
 * @param blocking
 *
 * @return
 * NSString for the automatically generated script name.
 */
- (id) initWithURL:(NSURL *)url_ interpreter:(NSURL *)interpreter_ name:(NSString *)name_ type:(gRPCScriptType)type_ isBlocking:(BOOL) blocking_;

/*!
 * @method isEqualToScript:
 *
 * @abstract
 * Used to define equality between two scripts
 *
 * @discussion
 * Scripts will be considered equal if the following properties are equivalent: name, type
 *
 * @return
 * Boolean value indicating equality
 */
- (BOOL) isEqualToScript:(gRPCScript *) script;

@end
