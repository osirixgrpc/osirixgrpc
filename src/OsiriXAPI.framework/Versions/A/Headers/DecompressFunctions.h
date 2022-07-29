
#if !TARGET_OS_IOS
#import "DCM Framework/DCMFramework.h"
#import "AppController.h"
#else
enum compressionTechniqueType {
    compression_sameAsDefault = 0,
    compression_none = 1,
    compression_JPEG = 2,
    compression_JPEG2000 = 3,
    compression_JPEGLS = 4,
    compression_undefined = 255
};
typedef enum compressionTechniqueType compressionTechniqueType;

typedef enum DCM_CompressionQuality_ {DCMLosslessQuality = 0, DCMHighQuality, DCMMediumQuality, DCMLowQuality} DCM_CompressionQuality;
#endif

@interface DecompressFunctions : NSObject
{
}

+(void) compressPaths:(NSArray*) paths destination:(NSString*) destination settings: (id) dict;
+(void) compressPaths:(NSArray*) paths destination:(NSString*) destination;

+(void) compressPaths:(NSArray*) paths destination:(NSString*) destination compression: (compressionTechniqueType) compression quality: (DCM_CompressionQuality) quality settings: (id) dict;
+(void) compressPaths:(NSArray*) paths destination:(NSString*) destination compression: (compressionTechniqueType) compression quality: (DCM_CompressionQuality) quality;

+(void) compressPaths:(NSArray*) paths compression: (compressionTechniqueType) compression quality: (DCM_CompressionQuality) quality settings: (id) dict;
+(void) compressPaths:(NSArray*) paths compression: (compressionTechniqueType) compression quality: (DCM_CompressionQuality) quality;

+(void) compressConcurrentlyPaths:(NSArray*)allPaths compression: (compressionTechniqueType) compression quality: (DCM_CompressionQuality) quality;
+(void) compressConcurrentlyPaths:(NSArray*)allPaths destination:(NSString*)dest compression: (compressionTechniqueType) compression quality: (DCM_CompressionQuality) quality;

+ (compressionTechniqueType) compressionForModality: (NSString*) mod quality:(DCM_CompressionQuality*) quality resolution: (int) resolution;
+ (compressionTechniqueType) compressionForModality: (NSString*) mod quality:(DCM_CompressionQuality*) quality resolution: (int) resolution settings: (id) dict;

@end
