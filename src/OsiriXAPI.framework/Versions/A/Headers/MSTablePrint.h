//
//  MSTablePrint.h
//  Expenses
//
//  Created by Michael Swan on 7/28/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
/*
 This is exactly the same license agreement that Matt Legend Gemmell uses on his source code. I choose it because I agree with his ideas on this stuff. Feel free to use this class/code as you want. If you use this class in your software I would love acknowledgment of that in your software (such as in the about panel). Of course you can't claim that I endorse or support your software, just that I provided a class for it.
 I would also love to hear about it if you find this class useful, have ideas for improvement, and especially if you have made improvements you would like folded into the main class so others can benefit.
 If you have questions check out my tutorial _first_ (at http://themikeswan.wordpress.com/ ) then if you still need help feel free to e-mail me at mikeswan [at] themikeswan [dot]com.
 
 License Agreement for Source Code provided by Mike Swan
 
 This software is supplied to you by Mike Swan in consideration of your agreement to the following terms, and your use, installation, modification or redistribution of this software constitutes acceptance of these terms. If you do not agree with these terms, please do not use, install, modify or redistribute this software.
 
 In consideration of your agreement to abide by the following terms, and subject to these terms, Mike Swan grants you a personal, non-exclusive license, to use, reproduce, modify and redistribute the software, with or without modifications, in source and/or binary forms; provided that if you redistribute the software in its entirety and without modifications, you must retain this notice and the following text and disclaimers in all such redistributions of the software, and that in all cases attribution of Mike Swan as the original author of the source code shall be included in all such resulting software products or distributions. Neither the name, trademarks, service marks or logos of Mike Swan may be used to endorse or promote products derived from the software without specific prior written permission from Mike Swan. Except as expressly stated in this notice, no other rights or licenses, express or implied, are granted by Mike Swan herein, including but not limited to any patent rights that may be infringed by your derivative works or by other works in which the software may be incorporated.
 
 The software is provided by Mike Swan on an "AS IS" basis. MIKE SWAN MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
 
 IN NO EVENT SHALL MIKE SWAN BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF MIKE SWAN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */
#import <Cocoa/Cocoa.h>

#define LEVELPREFIX @"  "

@interface MSTablePrint : NSObject {
    NSTextTable *table;
    NSTextAlignment alignment;
    BOOL headerRow;
    BOOL headerColumn;
    BOOL alternateRows;
    BOOL alternateTextRows;
    BOOL dontAlternateColorIfLevel;
    NSColor *rowColor;
    NSColor *alternateRowColor;
    NSColor *headerColor;
    NSDictionary *headerTextStyle;
    NSDictionary *rowTextStyle;
    NSDictionary *alternateRowTextStyle;
    float maximumWidth[ 100];

}
@property (assign) NSTextTable *table;
@property (assign) NSTextAlignment alignment;
@property (assign) BOOL headerRow;
@property (assign) BOOL headerColumn;
@property (assign) BOOL alternateRows;
@property (assign) BOOL alternateTextRows;
@property (assign) BOOL dontAlternateColorIfLevel;
@property (copy) NSColor *rowColor;
@property (copy) NSColor *alternateRowColor;
@property (copy) NSColor *headerColor;
@property (copy) NSDictionary *headerTextStyle;
@property (copy) NSDictionary *rowTextStyle;
@property (copy) NSDictionary *alternateRowTextStyle;

- (NSAttributedString *)attributedStringFromItems:(NSArray *)items;
- (void) setLayout:(NSTextTableLayoutAlgorithm)layout;
- (float) maximumWidthForItems:(NSArray *)items;
@end
