#import "gRPCTaskController.h"
#import "gRPCTaskControllerInterpreterCellView.h"
#import "gRPCTaskControllerBlockingCellView.h"
#import "gRPCTaskControllerTypeCellView.h"
#import "gRPCLog.h"

@implementation gRPCTaskController

@synthesize tasks, storageURL;

+ (NSString *) gRPCTaskControllerErrorDomain
{
    return [NSString stringWithFormat:@"%@.taskControllerErrorDomain", [gRPCPluginFilter pluginIdentifier]];
}

#pragma mark -
#pragma mark Initializer

- (id)initWithStorageURL:(NSURL *)url
{
    self = [super initWithWindowNibName:@"gRPCTaskWindow"];
    if (!self) {
        gRPCLogError(@"Could not initialize task controller");
        return  nil;
    }
    
    storageURL = [url copy];
    NSFileManager *manager = [NSFileManager defaultManager];
    BOOL isDirectory;
    BOOL fileExists = [manager fileExistsAtPath:[storageURL path] isDirectory:&isDirectory];
    if (!fileExists || !isDirectory)
    {
        gRPCLogError(@"storageURL not available");
        return nil;
    }
    
    tasks = [self loadTasks];
    
    return self;
}

- (void)dealloc
{
    [tasks release];
    [storageURL release];
    [super dealloc];
}

#pragma mark -
#pragma mark Storage/retrieval

- (NSString *) tasksConfigurationPath
{
    return [[storageURL path] stringByAppendingPathComponent:@"tasks_configs.json"];
}

// Create a representation object of the task array that can be converted to JSON
- (NSArray *) jsonTaskRepresentation
{
    NSMutableArray *jsonArray = [[NSMutableArray alloc] init];
    for (gRPCTask *task in tasks)
    {
        NSString *executableString = [[task executable] path];
        NSString *name = [task name];
        BOOL blocking = [task blocking];
        gRPCTaskType type = [task type];
        NSString *argumentsString = [[task arguments] componentsJoinedByString:@"/"];
        
        NSString *blockingString = @"NO";
        if (blocking)
        {
            blockingString = @"YES";
        }
        
        NSString *typeString = nil;
        switch (type){
            case gRPCImageTask:
                typeString = @"gRPCImageTask";
                break;
            case gRPCROITask:
                typeString = @"gRPCROITask";
                break;
            case gRPCDatabaseTask:
                typeString = @"gRPCDatabaseTask";
                break;
            case gRPCVolumeRenderTask:
                typeString = @"gRPCVolumeRenderTask";
                break;
            default:
                gRPCLogError(@"No valid type found");
        }
        
        NSDictionary *taskRepresentation = [NSDictionary dictionaryWithObjectsAndKeys:executableString, @"executable", name, @"name", typeString, @"type", blockingString, @"blocking", argumentsString, @"arguments", nil];
        
        [jsonArray addObject:taskRepresentation];
    }
    return jsonArray;
}

- (void) saveTasks:(NSArray *) tasks
{
    NSString *configPath = [self tasksConfigurationPath];
    NSArray *tasksRepresentations = [self jsonTaskRepresentation];
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:tasksRepresentations options:NSJSONWritingPrettyPrinted error:nil];
    [jsonData writeToFile:configPath atomically:YES];
    [tasksRepresentations release];
}

- (NSMutableArray *) loadTasks
{
    NSString *configPath = [self tasksConfigurationPath];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSMutableArray *tasks_ = [[NSMutableArray alloc] init];
    if ([fileManager fileExistsAtPath:configPath])
    {
        NSData *jsonData = [NSData dataWithContentsOfFile:configPath];
        NSArray *taskRepresentations = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:nil];
        for (NSDictionary *taskRepresentation in taskRepresentations)
        {
            NSString *executableString = [taskRepresentation objectForKey:@"executable"];
            NSString *name = [taskRepresentation objectForKey:@"name"];
            NSString *blockingString = [taskRepresentation objectForKey:@"blocking"];
            NSString *typeString = [taskRepresentation objectForKey:@"type"];
            NSString *argumentsString = [taskRepresentation objectForKey:@"arguments"];
            
            BOOL blocking = NO;
            if ([blockingString isEqualToString:@"YES"])
            {
                blocking = YES;
            }
            
            gRPCTaskType taskType;
            if ([typeString isEqualToString:@"gRPCImageTool"])
            {
                taskType = gRPCImageTask;
            }
            else if ([typeString isEqualToString:@"gRPCROITool"])
            {
                taskType = gRPCROITask;
            }
            else if ([typeString isEqualToString:@"gRPCDatabaseTool"])
            {
                taskType = gRPCDatabaseTask;
            }
            else
            {
                taskType = gRPCVolumeRenderTask;
            }
            
            NSArray *arguments = [argumentsString componentsSeparatedByString:@" "];
            
            gRPCTask *task = [[gRPCTask alloc] initWithExecutableURL:[NSURL fileURLWithPath:executableString] name:name type:taskType arguments:arguments blocking:blocking];
            [tasks_ addObject:task];
        }
    }
    return tasks_;
}

#pragma mark -
#pragma mark Accessors

- (gRPCTask *)taskWithName:(NSString *)name
{
    for (gRPCTask *task in tasks)
    {
        if ([task.name isEqualToString:name])
        {
            return task;
        }
    }
    return nil;
}

- (BOOL)taskPresentWithName:(NSString *)name
{
    for (gRPCTask *task in tasks)
    {
        if ([task.name isEqualToString:name])
        {
            return TRUE;
        }
    }
    return FALSE;
}

- (NSArray *) taskNamesForType:(gRPCTaskType)type
{
    
    NSMutableArray *taskNames = [NSMutableArray array];
    for (gRPCTask *task in tasks)
    {
        if ([task type] == type)
        {
            [taskNames addObject:[task name]];
        }
    }
    return taskNames;
}

- (NSArray *) taskNames
{
    NSMutableArray *taskNames = [NSMutableArray array];
    for (gRPCTask *task in tasks)
        [taskNames addObject:[task name]];
    return taskNames;
}

# pragma mark -
# pragma mark Register/unregister

- (void) unregisterTask: (gRPCTask *)task
{
    if (![tasks containsObject:task])
    {
        gRPCLogDefault(@"Tried to remove invalid task");
        return;
    }
    [tasks removeObject:task];
    [self saveTasks:tasks];
}

- (void) unregisterTasks:(NSArray *)tasks
{
    for (gRPCTask *task in tasks)
    {
        [self unregisterTask: task];
    }
}

# pragma mark -
# pragma mark Task window methods

- (IBAction)executableChanged:(id)sender
{
    NSOpenPanel *openPanel = [NSOpenPanel openPanel];
    [openPanel setTitle:@"Select the executable"];
    [openPanel setCanChooseFiles:YES];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanCreateDirectories:NO];
    if ([openPanel runModal] == NSModalResponseOK)
    {
        NSURL *url = [openPanel URL];
        long row = [taskTable rowForView:sender];
        gRPCTask *task = [tasks objectAtIndex:row];
        [task setExecutable:url];
        [self saveTasks:tasks];
        [taskTable reloadData];
    }
}

- (IBAction)blockingChanged:(id)sender
{
    int value = [(NSButton *)sender intValue];
    long row = [taskTable rowForView:sender];
    gRPCTask *task = [tasks objectAtIndex:row];
    [task setBlocking:value>0?YES:NO];
    [self saveTasks:tasks];
    [taskTable reloadData];
}

- (IBAction)typeChanged:(id)sender
{
    long value = [(NSPopUpButton *)sender indexOfSelectedItem];
    long row = [taskTable rowForView:sender];
    gRPCTask *task = [tasks objectAtIndex:row];
    switch (value) {
        case 0:
            [task setType:gRPCImageTask];
            break;
        case 1:
            [task setType:gRPCROITask];
            break;
        case 2:
            [task setType:gRPCVolumeRenderTask];
            break;
        case 3:
            [task setType:gRPCDatabaseTask];
            break;
        default:
            gRPCLogError(@"Incorrect button value encountered.");
    }
    [self saveTasks:tasks];
    [taskTable reloadData];
}

- (IBAction) nameChanged:(id)sender
{
    NSString *name = [(NSTextField *)sender stringValue];
    long row = [taskTable rowForView:sender];
    gRPCTask *task = [tasks objectAtIndex:row];
    [task setName:name];
    [self saveTasks:tasks];
    [taskTable reloadData];
}

- (NSInteger) numberOfRowsInTableView:(NSTableView *)tableView
{
    return [tasks count];
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    NSString *identifier = [tableColumn identifier];
    gRPCTask *task = (gRPCTask *)[tasks objectAtIndex:row];
    
    if ([identifier isEqualToString:@"executable"])
    {
        gRPCTaskControllerInterpreterCellView *view = [tableView makeViewWithIdentifier:@"executable" owner:self];
        [[view textField] setStringValue: [[task executable] path]];
        [[view textField] setToolTip:[[task executable] path]];
        return view;
    }
    else if ([identifier isEqualToString:@"blocking"])
    {
        gRPCTaskControllerBlockingCellView *view = [tableView makeViewWithIdentifier:@"blocking" owner:self];
        [[view checkBox] setIntValue:[task blocking]?1:0];
        return view;
    }
    else if ([identifier isEqualToString:@"name"])
    {
        NSTableCellView *view = [tableView makeViewWithIdentifier:@"name" owner:self];
        [[view textField] setStringValue:[task name]];
        return view;
    }
    else if ([identifier isEqualToString:@"type"])
    {
        gRPCTaskControllerTypeCellView *view = [tableView makeViewWithIdentifier:@"type" owner:self];
        [[view popUpButton] addItemsWithTitles:@[@"Image", @"ROI", @"VR", @"Database"]];
        switch ([task type]) {
            case gRPCImageTask:
                [[view popUpButton] selectItemAtIndex:0];
                break;
            case gRPCROITask:
                [[view popUpButton] selectItemAtIndex:1];
                break;
            case gRPCVolumeRenderTask:
                [[view popUpButton] selectItemAtIndex:2];
                break;
            case gRPCDatabaseTask:
                [[view popUpButton] selectItemAtIndex:3];
                break;
            default:
                break;
        }
        return view;
    }
    else
    {
        return nil;
    }
}

// Used by the IBAction for user requests to register a task
- (void) registerTaskAction
{
    NSOpenPanel *openPanel = [NSOpenPanel openPanel];
    [openPanel setTitle:@"Select the task file location"];
    [openPanel setCanChooseFiles:YES];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanCreateDirectories:NO];
    if ([openPanel runModal] == NSModalResponseOK)
    {
        NSURL *url = [openPanel URL];
        [self registerTaskAtURL:url];
    }
    [taskTable reloadData];
}

// Used by the IBAction for user requests to unregister a task
- (void) unregisterTaskAction
{
    NSInteger row = [taskTable selectedRow];
    gRPCTask *task = [tasks objectAtIndex:row];
    [self unregisterTask:task];
    [taskTable reloadData];
}

- (IBAction)addRemoveTask:(id)sender
{
    NSSegmentedCell *cell = (NSSegmentedCell *)sender;
    switch ([cell selectedSegment]) {
        case 0:
            [self unregisterTaskAction];
            break;
        case 1:
            [self registerTaskAction];
            break;
        default:
            break;
    }
}

@end
