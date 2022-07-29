/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>

/** \brief  Window Controller for Splash Window */
@interface SplashScreen : NSWindowController <NSWindowDelegate>
{
	IBOutlet	NSButton *version;
    IBOutlet    NSTextField *regAndTransactionID;
                NSTimer	*timerIn, *timerOut;
	IBOutlet    NSImageView *view;
                int versionType;
}

+ (void) showLicense;
- (void) affiche;
- (IBAction) switchVersion:(id) sender;
@end
