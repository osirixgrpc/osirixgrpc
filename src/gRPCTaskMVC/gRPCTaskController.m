#import "gRPCTaskController.h"
#import "gRPCLog.h"
#import "gRPCUtilities.h"

@implementation gRPCTaskController

@synthesize tasks, storageURL, taskConsole;

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
    
    configPanel = [[gRPCTaskConfigurationController alloc] init];
    [configPanel setDelegate:self];
    
    taskConsole = [[gRPCTaskConsoleController alloc] init];
    
    tasks = [self loadTasks];
    
    return self;
}

- (void)dealloc
{
    [tasks release];
    [storageURL release];
    [configPanel release];
    [taskConsole release];
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
        NSString *argumentsString = [task arguments];
        
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
            if ([typeString isEqualToString:@"gRPCImageTask"])
            {
                taskType = gRPCImageTask;
            }
            else if ([typeString isEqualToString:@"gRPCROITask"])
            {
                taskType = gRPCROITask;
            }
            else if ([typeString isEqualToString:@"gRPCDatabaseTask"])
            {
                taskType = gRPCDatabaseTask;
            }
            else
            {
                taskType = gRPCVolumeRenderTask;
            }
            
            gRPCTask *task = [[gRPCTask alloc] initWithExecutableURL:[NSURL fileURLWithPath:executableString] name:name type:taskType arguments:argumentsString blocking:blocking];
            [tasks_ addObject:task];
        }
    }
    return tasks_;
}

#pragma mark -
#pragma mark Accessors

- (gRPCTask *)taskWithName:(NSString *)name andType: (gRPCTaskType) type
{
    for (gRPCTask *task in tasks)
    {
        if ([task.name isEqualToString:name] && task.type == type)
        {
            return task;
        }
    }
    return nil;
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

# pragma mark -
# pragma mark Register/unregister

- (BOOL) registerTask:(gRPCTask *)task
{
    for (gRPCTask *task_ in tasks)
    {
        if ([task isEqualToTask:task_])
            return FALSE;
    }
    [tasks addObject:task];
    [self saveTasks:tasks];
    return TRUE;
}

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
# pragma mark Task panel delegate methods

- (void)didPressOK {
    NSLog(@"User pressed OK");
    // Handle OK action
}

- (void)didPressCancel {
    [configPanel close];
}

# pragma mark -
# pragma mark Task window methods

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    NSString *identifier = [tableColumn identifier];
    gRPCTask *task = (gRPCTask *)[tasks objectAtIndex:row];
    
    if ([identifier isEqualToString:@"blocking"])
    {
        NSTableCellView *view = [tableView makeViewWithIdentifier:@"blocking" owner:self];
        [[view textField] setStringValue:[task blocking]?@"Y":@"N"];
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
        NSTableCellView *view = [tableView makeViewWithIdentifier:@"type" owner:self];
        switch ([task type]) {
            case gRPCImageTask:
                [[view textField] setStringValue:@"Image"];
                break;
            case gRPCROITask:
                [[view textField] setStringValue:@"ROI"];
                break;
            case gRPCVolumeRenderTask:
                [[view textField] setStringValue:@"VR"];
                break;
            case gRPCDatabaseTask:
                [[view textField] setStringValue:@"Database"];
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
    // Load the window
    [self.window beginSheet:configPanel.window completionHandler:^(NSModalResponse returnCode) {
            if (returnCode == NSModalResponseOK) {
                NSLog(@"Tool added.");
            } else {
                NSLog(@"Operation cancelled.");
            }
        }];
}

// Used by the IBAction for user requests to unregister a task
- (void) unregisterTaskAction
{
    NSInteger row = [taskTable selectedRow];
    gRPCTask *task = [tasks objectAtIndex:row];
    [self unregisterTask:task];
    [taskTable reloadData];
}

- (void) editTaskAction
{
    NSLog(@"Editing task");
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
        case 2:
            [self editTaskAction];
            break;
        default:
            break;
    }
}

# pragma mark -
# pragma mark Run Task
- (void) runTask:(gRPCTask *)task
{
    // Get all relevant paramters for the task
    NSURL *executableURL = [task executable];
    BOOL blocking = [task blocking];
    NSMutableArray *arguments = [[[task arguments] componentsSeparatedByString:@" "] mutableCopy];
    
    // Set up a task handle and pipe for stderr/stdout
    NSTask *taskHandle = [[[NSTask alloc] init] autorelease];
    NSPipe *pipeStdErr = [[[NSPipe alloc] init] autorelease];
    NSPipe *pipeStdOut = [[[NSPipe alloc] init] autorelease];
    
    // Set task variables
    [taskHandle setExecutableURL:executableURL];
    [taskHandle setStandardOutput:pipeStdOut];
    [taskHandle setStandardError:pipeStdErr];
    [taskHandle setEnvironment:@{@"HOME": NSHomeDirectory()}];
    
    // Perform a case-insensitive search for "python"
    NSRange range = [[executableURL lastPathComponent] rangeOfString:@"python" options:NSCaseInsensitiveSearch];
    if (range.location != NSNotFound) {
        [arguments insertObject:@"-u" atIndex:0]; // Don't buffer stdout/stderr
    }
    [taskHandle setArguments:arguments];

    // Set up the stdout to print to screen
    NSFileHandle *fileHandleStdOut = [pipeStdOut fileHandleForReading];
    [fileHandleStdOut waitForDataInBackgroundAndNotify];
    [[NSNotificationCenter defaultCenter] addObserver:[self taskConsole] selector:@selector(stdOutDataAvailable:) name:NSFileHandleDataAvailableNotification object:fileHandleStdOut];
    
    // Set up the stderr to print to screen
    NSFileHandle *fileHandleStdErr = [pipeStdErr fileHandleForReading];
    [fileHandleStdErr waitForDataInBackgroundAndNotify];
    [[NSNotificationCenter defaultCenter] addObserver:[self taskConsole] selector:@selector(stdErrDataAvailable:) name:NSFileHandleDataAvailableNotification object:fileHandleStdErr];
    
    // Listen for when the task terminates
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(taskTerminated:) name:NSTaskDidTerminateNotification object:task];
    
    // Launch the task and wait if required.
    NSError *error = nil;
    bool bOK = [taskHandle launchAndReturnError:&error];
    if (!bOK) {
        [[self taskConsole] appendTextToView:[NSString stringWithFormat:@"Could not start script: %@", [error localizedDescription]]];
    }
    else {
        // Append text to the view so we know this is a new session
        [[self taskConsole] appendTextToView:[NSString stringWithFormat:@"Starting task with executable: %@\n%@\n", [executableURL path], [gRPCUtilities currentTimeString]]];

        
        if (blocking)
        {
            [taskHandle waitUntilExit];
        }
    }
}

- (void) taskTerminated:(id) sender
{
    [[self taskConsole] appendTextToView:[NSString stringWithFormat:@"Task finished: %@\n\n", [gRPCUtilities currentTimeString]]];
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
