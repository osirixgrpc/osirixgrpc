/*=========================================================================
 Program:   OsiriX
 
 Copyright (c) Pixmeo
 All rights reserved.
 =========================================================================*/

#ifndef __vtkOsiriXFixedPointVolumeRayCastMapper_h
#define __vtkOsiriXFixedPointVolumeRayCastMapper_h

#include "vtkFixedPointVolumeRayCastMapper.h"

class VTKRENDERINGVOLUME_EXPORT vtkOsiriXFixedPointVolumeRayCastMapper : public vtkFixedPointVolumeRayCastMapper
{
public:
  static vtkOsiriXFixedPointVolumeRayCastMapper *New();
  void Render( vtkRenderer *, vtkVolume * );
    
    void ComputeRayInfo( int x, int y,
    unsigned int pos[3],
    unsigned int dir[3],
    unsigned int *numSteps );
    
protected:
	vtkOsiriXFixedPointVolumeRayCastMapper();
    void DisplayRenderedImage( vtkRenderer *ren, vtkVolume   *vol );

private:
  vtkOsiriXFixedPointVolumeRayCastMapper(const vtkOsiriXFixedPointVolumeRayCastMapper&) = delete;
  void operator=(const vtkOsiriXFixedPointVolumeRayCastMapper&);  // Not implemented.
};
#endif
