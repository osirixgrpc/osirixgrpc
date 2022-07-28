/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/




#import <Foundation/Foundation.h>

// Import Carbon.h, and add an ivar to your class's .h:
// You could roll this into the Mail class as presented above

#import <Carbon/Carbon.h>
/** \brief Sends email */
@interface Mailer : NSObject {

}

- (void)runScript:(NSString *)txt;
- (BOOL)sendMail:(NSString *)richBody to:(NSString *)to subject:(NSString *)subject isMIME:(BOOL)isMIME name:(NSString *)client sendNow:(BOOL)sendWithoutUserReview image:(NSString*) imagePath;
@end
