#import "gRPCScript.h"

@implementation gRPCScript

@synthesize url, interpreter, name, blocking, type, language, arguments;

+ (NSString *) descriptionForScriptType: (gRPCScriptType)type
{
    NSString *description = @"Undefined";
    switch (type) {
        case gRPCImageTool:
            description = @"Image";
            break;
        case gRPCVolumeRenderTool:
            description = @"VR";
            break;
        case gRPCROITool:
            description = @"ROI";
            break;
        case gRPCDatabaseTool:
            description = @"Database";
            break;
        default:
            break;
    }
    return description;
}

+ (NSString *) descriptionForScriptLanguage: (gRPCScriptLanguage)language
{
    NSString *description = @"Undefined";
    switch (language) {
        case gRPCPython:
            description = @"Python";
            break;
        default:
            break;
    }
    return description;
}

+ (gRPCScriptLanguage) detectLanguageOfScriptAtPath:(NSString *)path
{
    NSString *fileExtension = [path pathExtension];
    if ([fileExtension isEqualToString:@"py"])
    {
        return gRPCPython;
    }
    else
    {
        return gRPCUndefined;
    }
}

+ (gRPCScriptLanguage) detectLanguageOfScriptAtURL:(NSURL *)url
{
    NSString *path = [url absoluteString];
    return [gRPCScript detectLanguageOfScriptAtPath:path];
}

+ (NSString *) detectNameOfScriptAtPath:(NSString *)path
{
    return [[path lastPathComponent] stringByDeletingPathExtension];
}

+ (NSString *) detectNameOfScriptAtURL:(NSURL *)url
{
    NSString *path = [url absoluteString];
    return [gRPCScript detectNameOfScriptAtPath:path];
}

- (BOOL) isEqualToScript:(gRPCScript *) script
{
    BOOL isEqual = FALSE;
    if ([name isEqualToString:[script name]] && type == [script type])
    {
        isEqual = TRUE;
    }
    return isEqual;
}

- (id) initWithURL:(NSURL *)url_ interpreter:(NSURL *)interpreter_ name:(NSString *)name_ type:(gRPCScriptType)type_ isBlocking:(BOOL) blocking_
{
    if ((self = [super init]))
    {
        url = [url_ retain];
        interpreter = [interpreter_ retain];
        name = [name_ retain];
        type = type_;
        blocking = blocking_;
        language = [gRPCScript detectLanguageOfScriptAtURL:url_];
    }
    return self;
}

- (void)dealloc
{
    [name release];
    [url release];
    [interpreter release];
    [arguments release];
    [super dealloc];
}

# pragma mark -
# pragma mark NSCoding

- (void)encodeWithCoder:(nonnull NSCoder *)coder {
    [coder encodeObject:url forKey:@"url"];
    [coder encodeObject:interpreter forKey:@"interpreter"];
    [coder encodeObject:name forKey:@"name"];
    [coder encodeInteger:type forKey:@"type"];
    [coder encodeBool:blocking forKey:@"blocking"];
    [coder encodeObject:arguments forKey:@"arguments"];
}

- (nullable instancetype)initWithCoder:(nonnull NSCoder *)coder {
    [super init];
    url = [[coder decodeObjectOfClass:[NSURL class] forKey:@"url"] retain];
    interpreter = [[coder decodeObjectOfClass:[NSURL class] forKey:@"interpreter"] retain];
    name = [[coder decodeObjectOfClass:[NSString class] forKey:@"name"] retain];
    type = (int)[coder decodeIntegerForKey:@"type"];
    blocking = [coder decodeBoolForKey:@"blocking"];
    language = [gRPCScript detectLanguageOfScriptAtURL:[self url]];
    arguments = [[coder decodeObjectOfClass:[NSMutableArray class] forKey:@"arguments"] retain];
    return self;
}

+ (BOOL)supportsSecureCoding {
    return YES;
}

@end
