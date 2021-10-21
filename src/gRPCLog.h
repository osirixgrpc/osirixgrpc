#import <Foundation/Foundation.h>
#import <os/log.h>

#import "gRPCPluginFilter.h"

/**
 * Utiliy macros for logging events within the system. All logs are processed using the macOS `OSLog`
 * functionality. Instructions can be found at:
 *  https://developer.apple.com/documentation/os/logging/generating_log_messages_from_your_code
 *
 * If the macro definitions are used (preferred), the category of each message will be in the format:
 *  {Function: [name of function], Line: [lineno where log created], Version: [the version of osirixgrpc]}
 *
 * For examples of how to search for logs see https://krypted.com/mac-os-x/logs-logging-logger-oh/
 * A useful example for streaming osirixgrpc logs in the terminal is:
 *  log stream --predicate 'subsystem contains "com.instituteofcancerresearch.osirixgrpc"'
 *
 *  @warning Not that there is a heiracrchy for the log types, some of which will not be displayed.
 *  For more info, see here: https://www.iosdev.recipes/simulator/os_log/
 *  As a rule of thumb, do not use OS_LOG_TYPE_INFO or OS_LOG_TYPE_DEBUG
 */

#define gRPCLog(type, format, ...)\
{\
    NSBundle *bundle = [NSBundle bundleForClass:[gRPCPluginFilter class]];\
    NSString *version = [[bundle infoDictionary] valueForKey:@"CFBundleShortVersionString"];\
    NSString *category = [NSString stringWithFormat:@"{Function: %s, Line: %u, Version: %s}", __PRETTY_FUNCTION__, __LINE__, [version UTF8String]];\
    gRPCLogWithTypeCategoryAndFormat(type, category, format, ##__VA_ARGS__);\
}

#define gRPCLogDefault(format, ...)\
    gRPCLog(OS_LOG_TYPE_DEFAULT, format, ##__VA_ARGS__)

#define gRPCLogError(format, ...)\
    gRPCLog(OS_LOG_TYPE_ERROR, format, ##__VA_ARGS__)

#define gRPCLogFault(format, ...)\
    gRPCLog(OS_LOG_TYPE_FAULT, format, ##__VA_ARGS__)

#define gRPCLogInfo(format, ...)\
    gRPCLog(OS_LOG_TYPE_INFO, format, ##__VA_ARGS__)

#define gRPCLogDebug(format, ...)\
    gRPCLog(OS_LOG_TYPE_DEBUG, format, ##__VA_ARGS__)

/*!
 * @function gRPCLogWithTypeCategoryAndFormatV
 *
 * @abstract
 * Generate a log statement displaying the input format string and arguments
 *
 * @discussion
 * This will use the plugin identifier to act as the logging subsystem
 *
 * @param type
 * One of:
 *   OS_LOG_TYPE_ERROR
 *   OS_LOG_TYPE_DEFAULT
 *   OS_LOG_TYPE_FAULT
 *   OS_LOG_TYPE_INFO
 *   OS_LOG_TYPE_DEBUG
 *
 * @param category
 * The string representing category. This can be anything useful that should be displayed
 *
 * @param format
 * The format string for the remaining arguments in the call
 *
 * @warning
 * It is better to use the macros defined in gRPCLog.h as they will populate the category with the line number and file from which the log was raised, and also output the plugin version for better information
 *
 * @return
 * None
 *
 */
void gRPCLogWithTypeCategoryAndFormatV(int type, NSString *category, NSString *format, va_list args);

/*!
 * @function gRPCLogWithTypeCategoryAndFormat
 *
 * @abstract
 * Generate a log statement displaying the input format string and arguments
 *
 * @discussion
 * This will use the plugin identifier to act as the logging subsystem
 *
 * @param type
 * One of:
 *   OS_LOG_TYPE_ERROR
 *   OS_LOG_TYPE_DEFAULT
 *   OS_LOG_TYPE_FAULT
 *   OS_LOG_TYPE_INFO
 *   OS_LOG_TYPE_DEBUG
 *
 * @param category
 * The string representing category. This can be anything useful that should be displayed
 *
 * @param format
 * The format string for the remaining arguments in the call
 *
 * @warning
 * It is better to use the macros defined in gRPCLog.h as they will populate the category with the line number and file from which the log was raised, and also output the plugin version for better information
 *
 * @return
 * None
 *
 */
void gRPCLogWithTypeCategoryAndFormat(int type, NSString *category, NSString *format, ...);

