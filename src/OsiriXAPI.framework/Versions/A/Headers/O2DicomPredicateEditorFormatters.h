/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/
#import <Foundation/Foundation.h>

@interface O2DicomPredicateEditorAgeStringFormatter : NSFormatter

@end


@interface O2DicomPredicateEditorMultiplicityFormatter : NSFormatter {
    NSFormatter* _monoFormatter;
}

@property(retain) NSFormatter* monoFormatter;

@end
