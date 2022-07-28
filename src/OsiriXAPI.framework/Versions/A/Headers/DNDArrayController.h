
#import <Cocoa/Cocoa.h>
#import <SecurityInterface/SFAuthorizationView.h>


/** \brief Network destination Array Controller for  Q/R*/
@interface DNDArrayController : NSArrayController <NSMenuDelegate>
{
    IBOutlet NSTableView			*tableView;
	IBOutlet SFAuthorizationView	*_authView;
	
	NSTableColumn *sortedColumn;
    
    BOOL dontAcceptFirstRowChange;
}

@property BOOL dontAcceptFirstRowChange;

// table view drag and drop support

- (void) setAuthView:( SFAuthorizationView*) v;

- (BOOL)tableView:(NSTableView *)tv writeRows:(NSArray*)rows toPasteboard:(NSPasteboard*)pboard;
    
- (NSDragOperation)tableView:(NSTableView*)tv validateDrop:(id <NSDraggingInfo>)info proposedRow:(NSInteger)row proposedDropOperation:(NSTableViewDropOperation)op;
    
- (BOOL)tableView:(NSTableView*)tv acceptDrop:(id <NSDraggingInfo>)info row:(NSInteger)row dropOperation:(NSTableViewDropOperation)op;
    

// utility methods

-(void)moveObjectsInArrangedObjectsFromIndexes:(NSIndexSet *)indexSet toIndex:(unsigned)index;
- (void) setContextualMenuForPreferencePanel;
- (NSIndexSet *)indexSetFromRows:(NSArray *)rows;
- (int)rowsAboveRow:(int)row inIndexSet:(NSIndexSet *)indexSet;
- (void) deleteSelectedRow:(id)sender;
- (NSTableView*) tableView;
@end
