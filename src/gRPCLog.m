#import "gRPCLog.h"

void gRPCLogWithTypeCategoryAndFormatV(int type, NSString *category, NSString *format, va_list args)
{
    NSBundle *bundle = [NSBundle bundleForClass:[gRPCPluginFilter class]];
    NSString *identifier = [[bundle infoDictionary] valueForKey:@"CFBundleIdentifier"];
    NSString *message = [[[NSString alloc] initWithFormat:format arguments:args] autorelease];
    os_log_t customLog = os_log_create([identifier UTF8String], [category UTF8String]);
    os_log_with_type(customLog, type, "%{public}@", message);
}

void gRPCLogWithTypeCategoryAndFormat(int type, NSString *category, NSString *format, ...)
{
    va_list args;
    va_start(args, format);
    gRPCLogWithTypeCategoryAndFormatV(type, category, format, args);
    va_end(args);
    
}
