//
//  RadviseWebViewerController.h
//  OsiriX_Lion
//
//  Created by antoinerosset on 27.11.17.
//  Copyright © 2017 OsiriX Team. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>

@interface RadviseWebViewerController : NSWindowController <NSWindowDelegate, WKNavigationDelegate, WKHTTPCookieStoreObserver>
{
    IBOutlet WKWebView *web;
}
-(void) loadWebPage;

+(id) instantiate;
+(NSString*) gtoken;

@end
