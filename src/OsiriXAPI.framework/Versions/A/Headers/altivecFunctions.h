/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Accelerate/Accelerate.h>

#ifdef __cplusplus
extern "C"
{
#endif /*cplusplus*/
	#if __ppc__ || __ppc64__
	// ALTIVEC FUNCTIONS
	extern void InverseLongs(register vector unsigned int *unaligned_input, register long size);
	extern void InverseShorts( register vector unsigned short *unaligned_input, register long size);
	extern void vmultiply(vector float *a, vector float *b, vector float *r, long size);
	extern void vsubtract(vector float *a, vector float *b, vector float *r, long size);
	extern void vsubtractAbs(vector float *a, vector float *b, vector float *r, long size);
	extern void vmax8(vector unsigned char *a, vector unsigned char *b, vector unsigned char *r, long size);
	extern void vmax(vector float *a, vector float *b, vector float *r, long size);
	extern void vmin(vector float *a, vector float *b, vector float *r, long size);
	extern void vmin8(vector unsigned char *a, vector unsigned char *b, vector unsigned char *r, long size);
	#else
	extern void vmax8Intel( vUInt8 *a, vUInt8 *b, vUInt8 *r, long size);
	extern void vmin8Intel( vUInt8 *a, vUInt8 *b, vUInt8 *r, long size);
	#endif
	
	extern void vmultiplyNoAltivec( float *a,  float *b,  float *r, long size);
	extern void vminNoAltivec( float *a,  float *b,  float *r, long size);
	extern void vmaxNoAltivec(float *a, float *b, float *r, long size);
	extern void vsubtractNoAltivec( float *a,  float *b,  float *r, long size);
	extern void vsubtractNoAltivecAbs( float *a,  float *b,  float *r, long size);
	
	extern short Altivec;

#ifdef __cplusplus
}
#endif /*cplusplus*/
