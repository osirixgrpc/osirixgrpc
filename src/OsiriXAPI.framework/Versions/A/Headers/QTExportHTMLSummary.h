/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


/** \brief Used for html export for disk burning*/
@interface QTExportHTMLSummary : NSObject
{
	NSString *patientsListTemplate, *examsListTemplate, *seriesTemplate; // whole template
	NSDictionary *patientsDictionary;
	NSMutableDictionary* imagePathsDictionary;
	NSString *rootPath, *footerString;
	int uniqueSeriesID;
	NSDateFormatter	*dateFormat, *timeFormat;
}

@property(retain) NSMutableDictionary* imagePathsDictionary;

+(NSString*)nonNilString:(NSString*)aString;
+ (void) getMovieWidth: (int*) width height: (int*) height imagesArray: (NSArray*) imagesArray;

+(NSString*)kindOfPath:(NSString*)path forSeriesId:(int)seriesId inSeriesPaths:(NSDictionary*)seriesPaths;

#pragma mark-
#pragma mark HTML template
- (void)readTemplates;
- (NSString*)fillPatientsListTemplates;
- (NSString*)fillStudiesListTemplatesForSeries:(NSArray*) series;
- (NSString*)fillSeriesTemplatesForSeries:(NSManagedObject*)series numberOfImages:(int)imagesCount;

#pragma mark-
#pragma mark HTML file creation
- (void)createHTMLfiles;
- (void)createHTMLPatientsList;
- (void)createHTMLStudiesList;
- (void)createHTMLExtraDirectory;
- (void)createHTMLSeriesPage:(NSManagedObject*)series numberOfImages:(int)imagesCount outPutFileName:(NSString*)fileName;

#pragma mark-
#pragma mark setters
- (void)setPath:(NSString*)path;
- (void)setPatientsDictionary:(NSDictionary*)dictionary;

@end
