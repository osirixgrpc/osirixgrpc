#import "gRPCDelegate.h"
#import "browsercontroller.pb.h"

@interface gRPCBrowserControllerDelegate : NSObject

delegateDeclaration(BrowserControllerDatabaseSelection, BrowserController, BrowserControllerDatabaseSelectionResponse)
delegateDeclaration(BrowserControllerCopyFilesIfNeeded, BrowserControllerCopyFilesIfNeededRequest, Response)

@end
