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
 * Select a file URL with a particular extension
 *
 * @param extension The allowed extension to use.  If NULL then any file extension is allowed
 *
 * @param allowDirs Whether to allow selection of directories.
 *
 * @param allowFiles Whether to allow selection of files.
 *
 * @return The file URL
 */
+ (NSURL *)selectURLWithExtension:(nullable NSString *)extension allowingDirectories:(BOOL)allowDirs allowingFiles:(BOOL)allowFiles;

/**
 * Select a file path with a particular extension
 *
 * @param extension The allowed extension to use.  If NULL then any file extension is allowed
 *
 * @param allowDirs Whether to allow selection of directories.
 *
 * @param allowFiles Whether to allow selection of files.
 *
 * @return The file path
 */
+ (NSString *)selectFilePathWithExtension:(nullable NSString *)extension allowingDirectories:(BOOL)allowDirs allowingFiles:(BOOL)allowFiles;

/**
 * Read the contents of file at a specified file path
 *
 * @param filePath The file path to read
 *
 * @return An NSString representing the contents of the file
 */
+ (NSString *)readFileContentsAtPath:(NSString *)filePath;

/**
 * Read the contents of file at a specified URL
 *
 * @param url The url to use
 *
 * @return An NSString representing the contents of the file
 */
+ (NSString *)readFileContentsAtURL:(NSURL *)url;

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
