/*
 *
 *  Copyright (C) 1997-2012, OFFIS e.V.
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *    OFFIS e.V.
 *    R&D Division Health
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *
 *  Module:  dcmjpls
 *
 *  Author:  Uli Schlachter
 *
 *  Purpose: Helper function than converts between CharLS and dcmjpgls errors
 *
 */

#ifndef DJERROR_H
#define DJERROR_H

#include "osconfig.h"
#include "djlsutil.h" /* For the OFCondition codes */
#include "charls.h" /* CharLS include */

/** Helper class for converting between dcmjpls and CharLS error codes
 */
class DJLSError
{
private:
    /// private undefined constructor
    DJLSError();
    
public:
    
    /** This method converts a CharLS error code into a dcmjpls OFCondition
     *  @param error The CharLS error code
     *  @return The OFCondition
     */
    static const OFCondition convert(charls::ApiResult error)
    {
        if( error == charls::ApiResult::OK)
            return EC_Normal;
        else if( error == charls::ApiResult::UncompressedBufferTooSmall)
            return EC_JLSUncompressedBufferTooSmall;
        else if( error == charls::ApiResult::CompressedBufferTooSmall)
            return EC_JLSCompressedBufferTooSmall;
        else if( error == charls::ApiResult::InvalidJlsParameters)
            return EC_JLSCodecInvalidParameters;
        else if( error == charls::ApiResult::ParameterValueNotSupported)
            return EC_JLSCodecUnsupportedValue;
        else if( error == charls::ApiResult::InvalidCompressedData)
            return EC_JLSInvalidCompressedData;
        else if( error == charls::ApiResult::bit_depth_for_transform_not_supported)
            return EC_JLSUnsupportedBitDepthForTransform;
        else if( error == charls::ApiResult::UnsupportedColorTransform)
            return EC_JLSUnsupportedColorTransform;
        else if( error == charls::ApiResult::TooMuchCompressedData)
            return EC_JLSTooMuchCompressedData;
        else
            return EC_IllegalParameter;
    }
};

#endif
