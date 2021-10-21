#import <Foundation/Foundation.h>
#import <OsiriXAPI/PluginFilter.h>

#import "gRPCServerController.h"
#import "gRPCToolbarController.h"
#import "gRPCScriptManager.h"

@interface gRPCPluginFilter : PluginFilter {
    
    gRPCServerController *serverController;
    gRPCToolbarController *toolbarController;
    gRPCScriptManager *scriptManager;
    
}

+(NSString *) pluginSupportDirectory;
+(NSString *) pluginIdentifier;

-(long)filterImage:(NSString*) menuName;

@end
