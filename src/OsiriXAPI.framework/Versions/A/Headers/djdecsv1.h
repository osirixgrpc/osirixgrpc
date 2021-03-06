/*
 *
 *  Copyright (C) 1997-2011, OFFIS e.V.
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
 *  Module:  dcmjpeg
 *
 *  Author:  Marco Eichelberg, Norbert Olges
 *
 *  Purpose: Codec class for decoding JPEG Lossless Selection Value 1 (8/12/16-bit)
 *
 */

#ifndef DJDECSV1_H
#define DJDECSV1_H

#include "osconfig.h"
#include "djcodecd.h" /* for class DJCodecDecoder */


/** Decoder class for JPEG Lossless Selection Value 1 (8/12/16-bit)
 */
class DCMTK_DCMJPEG_EXPORT DJDecoderP14SV1: public DJCodecDecoder
{
public: 

  /// default constructor
  DJDecoderP14SV1();

  /// destructor
  virtual ~DJDecoderP14SV1();

  /** returns the transfer syntax that this particular codec
   *  is able to encode and decode.
   *  @return supported transfer syntax
   */
  virtual E_TransferSyntax supportedTransferSyntax() const;

private:

  /** creates an instance of the compression library to be used for decoding.
   *  @param toRepParam representation parameter passed to decode()
   *  @param cp codec parameter passed to decode()
   *  @param bitsPerSample bits per sample for the image data
   *  @param isYBR flag indicating whether DICOM photometric interpretation is YCbCr
   *  @return pointer to newly allocated decoder object
   */
  virtual DJDecoder *createDecoderInstance(
    const DcmRepresentationParameter * toRepParam,
    const DJCodecParameter *cp,
    Uint8 bitsPerSample,
    OFBool isYBR) const;

virtual OFBool isJPEG2000() const;
};

#endif
