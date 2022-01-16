#import <Foundation/Foundation.h>

@interface gRPCUtilities : NSObject

/**
 * Check whether a given string conforms to IPV4 or IPV6
 *
 * @param ipAddress
 *
 * @return Boolean value
 */
+ (BOOL)isValidIPAddress:(nonnull NSString *)ipAddress;

/**
 * Check whether a given string conforms to IPV4 or IPV6
 *
 * @param ipAddress
 *
 * @return Boolean value
 */
+ (NSURL *)selectURLWithExtension:(nullable NSString *)extension allowingDirectories:(BOOL)allowDirs allowingFiles:(BOOL)allowFiles;

/**
 * Check whether a given string conforms to IPV4 or IPV6
 *
 * @param ipAddress
 *
 * @return Boolean value
 */
+ (NSString *)selectFilePathWithExtension:(nullable NSString *)extension allowingDirectories:(BOOL)allowDirs allowingFiles:(BOOL)allowFiles;


/**
 * Alert the user with a pop-up window with a given message and button options.
 *
 * @param message What you want to display to the reader as primary message.
 *
 * @param firstButton String for the first (and default) button.
 *
 * @param secondButton String for the second button (if required).
 *
 * @param thirdButton String for the third button (if required).
 *
 * @param informativeTextWithFormat Format string for the remaining parameters
 *
 * @warning message and firstButton must be defined.
 */
+ (NSInteger)alertWithMessageText:(nonnull NSString *)message :(nonnull NSString *)firstButton :(nullable NSString *)secondButton :(nullable NSString *)thirdButton :(nullable NSString *)informativeTextWithFormat, ...;

@end
