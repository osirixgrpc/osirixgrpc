/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#ifndef TeaEncrypt_h
#define TeaEncrypt_h

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
    
void encryptTEA (uint32_t* v, uint32_t* k);
void decryptTEA (uint32_t* v, uint32_t* k);
void encryptBlock(uint8_t * data, uint32_t * len, uint32_t * key);
void decryptBlock(uint8_t * data, uint32_t * len, uint32_t * key);
    
#ifdef __cplusplus
}
#endif

#endif /* TeaEncrypt_h */
