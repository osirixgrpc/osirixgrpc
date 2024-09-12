#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface gRPCUtilities : NSObject

/**
 * Check whether a given integer is a valid port number. This does not check whether it is open.
 *
 * @param port
 *
 * @return 0: Invalid port number, 1:Valid port number
 */
+ (NSInteger)isValidPortNumber:(NSInteger)port;

/**
 * Check whether a given string conforms to IPV4 or IPV6
 *
 * @param ipAddress
 *
 * @return 0: Invalid IP address, 1:Valid IP address
 */
+ (NSInteger)isValidIPAddress:(nonnull NSString *)ipAddress;

/**
 * Check whether a given port is open at the IP Address
 *
 * @param port An integer representing the port.  Should be 0 <= port <= 65535
 *
 * @param ipAddress The IP address. Currently this assumes a IPV4 numeric address, not another representation.
 *
 * @param error An NSError container for more information if something goes wrong.
 *
 * @return 0: Port not open, 1: Port open, -1: Error occurred.
 */
+ (NSInteger)isPort:(NSInteger) port openAtIPAddress:(NSString *)ipAddress withError:(NSError **)error;

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
 * Select a file URL to save a file
 *
 * @param title The title of the save panel
 *
 * @return The file URL.  Nil if none found or user cancelled operation
 */
+ (NSURL *)saveURLWithTitle:(nullable NSString *)title;

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

/**
 * Get the current time as a string.
 *
 * @return An NSString defining the time with format @"[dd/MM/YY - HH:mm:ss]".
 */
+ (NSString *) currentTimeString;

/**
 * Execute a bash command and return the result (e.g. `pwd` would return the working directory as a NSString instance).
 *
 * @param command The bash commend to execute.
 *
 * @return An NSString defining the output of the command.
 */
+ (NSString*)executeBashCommand: (NSString *)command;

@end

NS_ASSUME_NONNULL_END
