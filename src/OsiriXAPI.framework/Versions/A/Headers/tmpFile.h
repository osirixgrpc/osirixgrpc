/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#ifndef tmpFile_h
#define tmpFile_h

#include <stdio.h>
#include <string.h>

#ifdef  __cplusplus
extern "C" {
#endif
    
    void resetTmpFile( const char* filename);
    unsigned int isTmpFileActivated( const char* filename);
    void activateTmpFile( const char* filename);
    
    extern unsigned int tmpFileLock;

#ifdef  __cplusplus
}
#endif
    
#endif /* tmpFile_h */
