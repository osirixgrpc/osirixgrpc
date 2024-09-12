#import "gRPCTask.h"

@implementation gRPCTask

@synthesize executable, name, blocking, type, arguments;

- (BOOL) isEqualToTask:(gRPCTask *) task
{
    BOOL isEqual = FALSE;
    if ([name isEqualToString:[task name]] && type == [task type])
    {
        isEqual = TRUE;
    }
    return isEqual;
}

- (id) initWithExecutableURL:(NSURL *)url_ name:(NSString *)name_ type:(gRPCTaskType)type_ arguments:(NSString *)arguments_ blocking:(BOOL) blocking_
{
    if ((self = [super init]))
    {
        executable = [url_ retain];
        name = [name_ retain];
        type = type_;
        blocking = blocking_;
        arguments = [arguments_ retain];
    }
    return self;
}

- (void)dealloc
{
    [name release];
    [executable release];
    [arguments release];
    [super dealloc];
}

# pragma mark -
# pragma mark NSCoding

- (void)encodeWithCoder:(nonnull NSCoder *)coder {
    [coder encodeObject:executable forKey:@"url"];
    [coder encodeObject:name forKey:@"name"];
    [coder encodeInteger:type forKey:@"type"];
    [coder encodeBool:blocking forKey:@"blocking"];
    [coder encodeObject:arguments forKey:@"arguments"];
}

- (nullable instancetype)initWithCoder:(nonnull NSCoder *)coder {
    [super init];
    executable = [[coder decodeObjectOfClass:[NSURL class] forKey:@"url"] retain];
    name = [[coder decodeObjectOfClass:[NSString class] forKey:@"name"] retain];
    type = (int)[coder decodeIntegerForKey:@"type"];
    blocking = [coder decodeBoolForKey:@"blocking"];
    arguments = [[coder decodeObjectOfClass:[NSString class] forKey:@"arguments"] retain];
    return self;
}

+ (BOOL)supportsSecureCoding {
    return YES;
}

@end
