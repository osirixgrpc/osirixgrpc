//
//  gRPCScriptManager.m
//  osirixgrpc
//
//  Created by adminmblackledge on 02/06/2021.
//

#import "gRPCScriptManager.h"
#import "gRPCLog.h"

@implementation gRPCScriptManager

@synthesize scripts, storageURL;

#pragma mark -
#pragma mark Initializer

- (id)initWithStorageURL:(NSURL *)url
{
    self = [super init];
    if (!self) {
        gRPCLogError(@"Could not initialize script manager");
        return  nil;
    }
    
    storageURL = [url copy];
    NSFileManager *manager = [NSFileManager defaultManager];
    if (![manager fileExistsAtPath:[storageURL path] isDirectory:nil])
    {
        gRPCLogDefault(@"Attempting to create directory at path: %@", [storageURL path]);
        NSError *error;
        BOOL bOK = [manager createDirectoryAtPath:[storageURL path] withIntermediateDirectories:YES attributes:nil error:&error];
        if (!bOK)
        {
            gRPCLogError(@"Could not create directory: %@", error);
            return nil;
        }
    }
    
    [self loadScripts];
    
    return self;
}

- (void)dealloc
{
    [scripts release];
    [storageURL release];
    [super dealloc];
}

#pragma mark -
#pragma mark Storage/retrieval

- (NSURL *) databaseFile
{
    return [storageURL URLByAppendingPathComponent:@".scripts.db"];
}

- (BOOL) saveScripts
{
    NSError *error;
    NSData *archivedData = [NSKeyedArchiver archivedDataWithRootObject:scripts requiringSecureCoding:NO error:&error];
    if (!archivedData)
    {
        gRPCLogError(@"Could not extract archive data: %@", error);
        return NO;
    }
    [archivedData writeToURL:[self databaseFile] atomically:YES];
    return YES;
}

- (BOOL) loadScripts
{
    NSFileManager *manager = [NSFileManager defaultManager];
    
    // This happens if the file is not available yet.
    if (![manager fileExistsAtPath:[[self databaseFile] path]])
    {
        scripts = [[NSMutableArray alloc] init];
        return YES;
    }
    
    if (scripts)
        [scripts release];
    
    NSData *archivedData = [NSData dataWithContentsOfURL:[self databaseFile]];
    
    NSError *error;
    NSSet *classes = [NSSet setWithObjects:[NSMutableArray class], [gRPCScript class], nil];
    scripts = [[NSKeyedUnarchiver unarchivedObjectOfClasses:classes fromData:archivedData error:&error] retain];
    if (!scripts)
    {
        gRPCLogError(@"Could not load scripts: %@", error);
        return NO;
    }
    
    return YES;
}

#pragma mark -
#pragma mark Accessors

- (gRPCScript *)scriptWithName:(NSString *)name
{
    for (gRPCScript *script in scripts)
    {
        if ([script.name isEqualToString:name])
        {
            return script;
        }
    }
    return nil;
}

- (BOOL)scriptPresentWithName:(NSString *)name
{
    for (gRPCScript *script in scripts)
    {
        if ([script.name isEqualToString:name])
        {
            return TRUE;
        }
    }
    return FALSE;
}

- (NSArray *) scriptNamesForType:(gRPCScriptType)type
{
    
    NSMutableArray *scriptNames = [NSMutableArray array];
    for (gRPCScript *script in scripts)
    {
        if ([script type] == type)
        {
            [scriptNames addObject:[script name]];
        }
    }
    return scriptNames;
}

- (NSArray *) scriptNames
{
    NSMutableArray *scriptNames = [NSMutableArray array];
    for (gRPCScript *script in scripts)
        [scriptNames addObject:[script name]];
    return scriptNames;
}

# pragma mark -
# pragma mark Register/unregister

- (void) unregisterScript: (gRPCScript *)script
{
    [scripts removeObject:script];
    [self saveScripts];
}

- (void) unregisterScripts:(NSArray *)scripts
{
    for (gRPCScript *script in scripts)
    {
        [self unregisterScript: script];
    }
}

- (void) registerScriptAtURL:(NSURL *)url
{
    // Find the default name of the script
   NSString *name = [gRPCScript detectNameOfScriptAtURL:url];
    
    // Add to the storage - there are many defaults that can be later changed by the user.
    gRPCScript *script = [[gRPCScript alloc] initWithURL:url interpreter:[NSURL fileURLWithPath:@"/Users/adminmblackledge/opt/miniconda3/bin/python"] name:name type:gRPCImageTool isBlocking:NO];
    [scripts addObject:script];
    [self saveScripts];
}

@end
