#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>

#define FONTGLSIZE 65535

@interface NSFont (withay_OpenGL)

- (void) drawUnicodeString:(unichar*) str length:(NSUInteger) l withFontType: (int) fontType glList: (GLuint) glList scaling:(float) scaling;
+ (void) setOpenGLLogging:(BOOL)logEnabled;
+ (void) resetFont: (int) preview;
- (void) initFontImage:(unichar)first count:(int)count fontType:(int) preview  scaling: (float) scaling;
- (void) makeGLDisplayListBase:(GLint)base :(long*) charSizeArrayIn :(int) fontType : (float) scaling;
+ (unsigned char*) createCharacterWithImage:(NSBitmapImageRep *)bitmap;
@end
