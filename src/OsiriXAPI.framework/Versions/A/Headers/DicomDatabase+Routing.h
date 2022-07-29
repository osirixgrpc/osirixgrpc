/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "DicomDatabase.h"


@interface DicomDatabase (Routing)

- (void) emptyQueue;
- (void) initRouting;
- (void) deallocRouting;

- (void) addImages:(NSArray*)_dicomImages toSendQueueForRoutingRule:(NSDictionary*)routingRule;
- (void) applyRoutingRules:(NSArray*)routingRules toImages:(NSArray*)images;
- (void) addImagesToRouting:(NSArray*)images;
- (void) initiateRoutingUnlessAlreadyRouting;
- (void) routing;
- (NSRecursiveLock*) routingLock;
- (int) queueSize;
- (void) saveRoutingToFile;

@end
