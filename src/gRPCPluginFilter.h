#import <Foundation/Foundation.h>
#import <OsiriXAPI/PluginFilter.h>

#import "gRPCServerController.h"
#import "gRPCToolbarController.h"
#import "gRPCScriptController.h"

/*
 The core class for the plugin, and used to interface with OsiriX.
 
 This will be responsible for:
    1. Initialising and deallocating all created plugin controllers (ServerController, ScriptController, TaskController, ToolbarController) during runtime.
    2. Redirecting requests from the toolbar controller.
    3. Managing the support directory and plugin identifier string.
 
 */

@interface gRPCPluginFilter : PluginFilter {
    
    gRPCServerController *serverController;
    gRPCToolbarController *toolbarController;
    gRPCScriptController *scriptController;
    
}

/*!
 * @method pluginSupportDirectory
 *
 * @abstract
 * The filepath of the support directory (currently in "~/Library/Application Support/OsiriXGRPC").
 *
 * @return
 * NSString for the filepath
 */
+(NSString *) pluginSupportDirectory;

/*!
 * @method pluginIdentifier
 *
 * @abstract
 * The plugin identifier (currently "com.instituteofcancerresearch.osirixgrpc")
 *
 * @return
 * NSString for identifier
 */
+(NSString *) pluginIdentifier;

-(long)filterImage:(NSString*) menuName;

@end
