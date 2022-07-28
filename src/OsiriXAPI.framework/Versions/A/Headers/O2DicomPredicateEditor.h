/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

@class O2DicomPredicateEditorRowTemplate;

@interface O2DicomPredicateEditor : NSPredicateEditor {
@private
    BOOL _inited, _inValidateEditing, _dbMode, _backbinding, _setting;
    O2DicomPredicateEditorRowTemplate* _dpert;
}

@property(nonatomic) BOOL dbMode, inited;

- (BOOL)matchForPredicate:(NSPredicate*)p;
- (BOOL)reallyMatchForPredicate:(NSPredicate*)predicate;

@end

