/*
 *
 *  Copyright (C) 1997-2005, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Kuratorium OFFIS e.V.
 *    Healthcare Information and Communication Systems
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module:  dcmjpeg
 *
 *  Author:  Marco Eichelberg, Norbert Olges
 *
 *  Purpose: Codec class for encoding JPEG Lossless (8/12/16-bit)
 */

#ifndef DJENC2K_H
#define DJENC2K_H

#include "osconfig.h"
#include "djcodece.h" /* for class DJCodecEncoder */


/** Encoder class for JPEG 2K
 */
class DJEncoder2K : public DJCodecEncoder
{
public: 

  /// default constructor
  DJEncoder2K();

  /// destructor
  virtual ~DJEncoder2K();

  /** returns the transfer syntax that this particular codec
   *  is able to encode and decode.
   *  @return supported transfer syntax
   */
  virtual E_TransferSyntax supportedTransferSyntax() const;

private:

  /** returns true if the transfer syntax supported by this
   *  codec is lossless.
   *  @return lossless flag
   */
  virtual OFBool isLosslessProcess() const;

  /** creates 'derivation description' string after encoding.
   *  @param toRepParam representation parameter passed to encode()
   *  @param cp codec parameter passed to encode()
   *  @param bitsPerSample bits per sample of the original image data prior to compression
   *  @param ratio image compression ratio. This is not the "quality factor"
   *    but the real effective ratio between compressed and uncompressed image,
   *    i. e. 30 means a 30:1 lossy compression.
   *  @param imageComments image comments returned in this
   *    parameter which is initially empty
   */
  virtual void createDerivationDescription(
    const DcmRepresentationParameter * toRepParam,
    const DJCodecParameter *cp,
    Uint8 bitsPerSample,
    double ratio,
    OFString& derivationDescription) const;

  /** creates an instance of the compression library to be used
   *  for encoding/decoding.
   *  @param toRepParam representation parameter passed to encode()
   *  @param cp codec parameter passed to encode()
   *  @param bitsPerSample bits per sample for the image data
   *  @return pointer to newly allocated codec object
   */
  virtual DJEncoder *createEncoderInstance(
    const DcmRepresentationParameter * toRepParam,
    const DJCodecParameter *cp,
    Uint8 bitsPerSample) const;
    
};

/** Encoder class for JPEG 2K
 */
class DJEncoder2KLossLess : public DJCodecEncoder
{
public: 

  /// default constructor
  DJEncoder2KLossLess();

  /// destructor
  virtual ~DJEncoder2KLossLess();

  /** returns the transfer syntax that this particular codec
   *  is able to encode and decode.
   *  @return supported transfer syntax
   */
  virtual E_TransferSyntax supportedTransferSyntax() const;

private:

  /** returns true if the transfer syntax supported by this
   *  codec is lossless.
   *  @return lossless flag
   */
  virtual OFBool isLosslessProcess() const;

  /** creates 'derivation description' string after encoding.
   *  @param toRepParam representation parameter passed to encode()
   *  @param cp codec parameter passed to encode()
   *  @param bitsPerSample bits per sample of the original image data prior to compression
   *  @param ratio image compression ratio. This is not the "quality factor"
   *    but the real effective ratio between compressed and uncompressed image,
   *    i. e. 30 means a 30:1 lossy compression.
   *  @param imageComments image comments returned in this
   *    parameter which is initially empty
   */
  virtual void createDerivationDescription(
    const DcmRepresentationParameter * toRepParam,
    const DJCodecParameter *cp,
    Uint8 bitsPerSample,
    double ratio,
    OFString& derivationDescription) const;

  /** creates an instance of the compression library to be used
   *  for encoding/decoding.
   *  @param toRepParam representation parameter passed to encode()
   *  @param cp codec parameter passed to encode()
   *  @param bitsPerSample bits per sample for the image data
   *  @return pointer to newly allocated codec object
   */
  virtual DJEncoder *createEncoderInstance(
    const DcmRepresentationParameter * toRepParam,
    const DJCodecParameter *cp,
    Uint8 bitsPerSample) const;
    
};

#endif
