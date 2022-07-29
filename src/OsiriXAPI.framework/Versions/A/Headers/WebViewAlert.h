/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>

@interface WebViewAlert : NSWindowController <WebPolicyDelegate, WebFrameLoadDelegate>
{
    BOOL displayCancel, displayEnterRegKey, showDontShowAgain, dontShowAgain;
    NSURL *url;
    NSString *signature, *authorization;
    int modalResponse;
    IBOutlet WebView *webView;
    unsigned long crc32result;
    NSMutableDictionary *preferences;
    NSTimer *quitAfterInterval;
}

+ (NSInteger) alertWithURL: (NSURL*) u;
+ (NSInteger) alertWithURL: (NSURL*) u quitTimer: (BOOL) quitTimer;

+ (NSInteger) alertWithDictionary: (NSDictionary*) d;
+ (NSInteger) alertWithDictionary: (NSDictionary*) u quitTimer: (BOOL) quitTimer;

- (id) initWithDictionary: (NSDictionary*) d;

@property (readonly) int modalResponse;
@property BOOL displayCancel, displayEnterRegKey, showDontShowAgain, dontShowAgain, doNotShow;
@property (retain) NSURL *url;
@property (retain) NSString *signature, *authorization;
@property (retain) NSMutableDictionary *preferences;
@property (retain) NSTimer *quitAfterInterval;

@end
