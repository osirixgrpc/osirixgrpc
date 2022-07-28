/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/




#import <Cocoa/Cocoa.h>
#import "Camera.h"
#import "Interpolation3D.h"

/** \brief Manages 3D flythrus
*/

@interface FlyThru : NSObject {
	NSMutableArray	*stepCameras, *pathCameras, *stepsPositionInPath;
	int				numberOfFrames;
	int				interpolationMethod; // 1: spline / 2: piecewise
	BOOL			constantSpeed, loop;
	
}

@property (readwrite, retain) NSMutableArray *steps;
@property (readwrite, retain) NSMutableArray *pathCameras;
@property (readwrite, retain) NSMutableArray *stepsPositionInPath;
@property int numberOfFrames;
@property int interpolationMethod;

@property BOOL constantSpeed;
@property BOOL loop;


// steps (cameras choosed by the user)
-(id) initWithFirstCamera: (Camera*) sCamera;
-(void) addCamera: (Camera*) aCamera;
-(void) addCamera: (Camera*) aCamera atIndex: (int) index;
-(void) removeCameraAtIndex: (int) index;
-(void) removeAllCamera;



-(void) computePath; // interpollation of the path for every parameters
-(NSMutableArray*) path: (NSMutableArray*) pts : (int) interpolMeth : (BOOL) computeStepsPositions; // interpollation for 1 parameter

-(NSMutableDictionary*) exportToXML;
-(void) setFromDictionary: (NSDictionary*) xml;

@end
