/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "PluginFilter.h"

/** \brief  Report Plugin Filter base class */
@interface ReportPluginFilter : PluginFilter {

}

- (BOOL)createReportForStudy:(id)study;
- (BOOL)deleteReportForStudy:(id)study;
- (NSDate *)reportDateForStudy:(id)study;

@end
