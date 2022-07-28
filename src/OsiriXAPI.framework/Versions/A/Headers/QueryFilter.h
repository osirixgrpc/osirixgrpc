/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Foundation/Foundation.h>

enum searchTypes {searchContains = 0, searchStartsWith, searchEndsWith, searchExactMatch};
enum dateSearchTypes {searchToday = 4, searchYesterday, searchBefore, searchAfter, searchWithin, searchExactDate};
enum dateWithinSearch {searchWithinToday = 10, searchWithinLast2Days, searchWithinLastWeek, searchWithinLast2Weeks, searchWithinLastMonth,searchWithinLast2Months, searchWithinLast3Months, searchWithinLastYear};
enum modalities {osiCR = 0,osiCT,osiDX,osiES,osiMG,osiMR,osiNM,osiOT,osiPT,osiRF,osiSC,osiUS,osiXA};


/** \brief Query Filter */
@interface QueryFilter : NSObject {
	id _key;
	id _object;
	int _searchType;

}
+ (id)queryFilter;
+ (id)queryFilterWithObject:(id)object ofSearchType:(int)searchType forKey:(id)key;
- (id) initWithObject:(id)object ofSearchType:(int)searchType forKey:(id)key;

- (id) key;
- (id) object;
- (int) searchType;
- (NSString *)filteredValue;

- (void)setKey:(id)key;
- (void)setObject:(id)object;
- (void)setSearchType:(int)searchType;

- (NSString *)withinDateString;


@end
