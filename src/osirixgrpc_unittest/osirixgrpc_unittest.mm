//
//  osirixgrpc_unittest.m
//  osirixgrpc_unittest
//
//  Created by adminmblackledge on 26/01/2024.
//

#import <XCTest/XCTest.h>

#import "gRPCCache.h"
#import "gRPCROIVolumeDelegate.h"
#import "roivolume.pb.h"
#import <OsiriXAPI/ROIVolume.h>

@interface osirixgrpc_unittest : XCTestCase

@end

@implementation osirixgrpc_unittest

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    XCTAssertEqual(1, 1, @"Expected 1 to equal 1");
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

- (void)testROIVolumeTextureWithCachedROIVolume {
    // Arrange
    osirixgrpc::ROIVolume *request;
    osirixgrpc::ROIVolumeTextureResponse *response;
    
    // Create a sample ROIVolume and add it to the cache
    gRPCCache *cache = [[gRPCCache alloc] init];
    ROIVolume *rv = [[ROIVolume alloc] init];
    [rv setTexture:TRUE];
    NSString* rv_uid = [cache addObject:rv];
    
    request->set_osirixrpc_uid([rv_uid UTF8String]);
    
    // Act
    [gRPCROIVolumeDelegate ROIVolumeTexture:request :response :cache];
    
    // Assert
    XCTAssertTrue(response->status().status() == 1, @"Status should be 1 for cached ROIVolume");
}

- (void)testROIVolumeTextureWithNoCachedROIVolume {
    // Arrange
//    osirixgrpc::ROIVolume request;
//    osirixgrpc::ROIVolumeTextureResponse response;
//    gRPCCache *cache = [[gRPCCache alloc] init];
//    
//    // Act
//    [YourClass ROIVolumeTexture:&request :&response :cache];
//    
//    // Assert
//    XCTAssertTrue(response.status().status() == 0, @"Status should be 0 for no cached ROIVolume");
//    XCTAssertEqualObjects(response.status().message(), @"No ROIVolume cached", @"Incorrect error message");
    // You may add more assertions based on your specific logic
}

@end
