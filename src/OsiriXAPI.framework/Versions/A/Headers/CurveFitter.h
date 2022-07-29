/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

// Curve fitting class based on the Simplex method described in the article "Fitting Curves to Data" in the May 1984 issue of Byte magazine, pages 340-362.

#import <Cocoa/Cocoa.h>

@interface CurveFitter : NSObject
{
    int fit;                // Number of curve type to fit
    double *xData, *yData;  // x,y data to fit
    int numPoints;          // number of data points
    int numParams;          // number of parametres
    int numVertices;        // numParams+1 (includes sumLocalResiduaalsSqrd)
    int worst;          // worst current parametre estimates
    int nextWorst;      // 2nd worst current parametre estimates
    int best;           // best current parametre estimates
    double	**simp;        // the simplex (the last element of the array at each vertice is the sum of the square of the residuals)
    double	*next;      // new vertex to be tested
    int numIter;        // number of iterations so far
    int maxIter;    // maximum number of iterations per restart
    int restarts;   // number of times to restart simplex after first soln.
    double maxError;     // maximum error tolerance
}

- (double) sqr:(double) d;
- (void) doFit: (int) fitType;
- (void) initialize;
- (void) restart: (int) n;
- (int) getNumParams;
- (double) f:(int) f :(double *)p :(double) x;
- (double*) getParams;
- (double*) getResiduals;
- (double) getSumResidualsSqr;
- (double) getSD;
- (double) getFitGoodness;
- (void) sumResiduals: (double*) x;
- (void) newVertex;
- (void) order;
- (int) getIterations;
- (int) getMaxIterations;
- (void) setMaxIterations:(int) x;
- (int) getRestarts;
- (void) setRestarts:(int) x;
- (int) getMax:(double*) array;

@end
