# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: dcmpix.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import utilities_pb2 as utilities__pb2
import types_pb2 as types__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0c\x64\x63mpix.proto\x12\nosirixgrpc\x1a\x0futilities.proto\x1a\x0btypes.proto\"I\n\x13\x44\x43MPixIsRGBResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0e\n\x06is_rgb\x18\x02 \x01(\x08\"\xaa\x01\n\x18\x44\x43MPixComputeROIResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0c\n\x04mean\x18\x02 \x01(\x02\x12\r\n\x05total\x18\x03 \x01(\x02\x12\x0f\n\x07std_dev\x18\x04 \x01(\x02\x12\x0b\n\x03min\x18\x05 \x01(\x02\x12\x0b\n\x03max\x18\x06 \x01(\x02\x12\x10\n\x08skewness\x18\x07 \x01(\x02\x12\x10\n\x08kurtosis\x18\x08 \x01(\x02\"z\n\x17\x44\x43MPixROIValuesResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0e\n\x06values\x18\x02 \x03(\x02\x12\x13\n\x0brow_indices\x18\x03 \x03(\x05\x12\x16\n\x0e\x63olumn_indices\x18\x04 \x03(\x05\"k\n\x18\x44\x43MPixDicomImageResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12+\n\x0b\x64icom_image\x18\x02 \x01(\x0b\x32\x16.osirixgrpc.DicomImage\"n\n\x19\x44\x43MPixDicomSeriesResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12-\n\x0c\x64icom_series\x18\x02 \x01(\x0b\x32\x17.osirixgrpc.DicomSeries\"k\n\x18\x44\x43MPixDicomStudyResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12+\n\x0b\x64icom_study\x18\x02 \x01(\x0b\x32\x16.osirixgrpc.DicomStudy\"\x9c\x01\n\x13\x44\x43MPixImageResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0c\n\x04rows\x18\x02 \x01(\x05\x12\x0f\n\x07\x63olumns\x18\x03 \x01(\x05\x12\x0f\n\x07is_argb\x18\x04 \x01(\x08\x12\x18\n\x10image_data_float\x18\x05 \x03(\x02\x12\x17\n\x0fimage_data_argb\x18\x06 \x03(\x05\"m\n\x1b\x44\x43MPixGetMapFromROIResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0c\n\x04rows\x18\x02 \x01(\x05\x12\x0f\n\x07\x63olumns\x18\x03 \x01(\x05\x12\x0b\n\x03map\x18\x04 \x03(\x08\"X\n\x13\x44\x43MPixShapeResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0c\n\x04rows\x18\x02 \x01(\x05\x12\x0f\n\x07\x63olumns\x18\x03 \x01(\x05\"j\n\x15\x44\x43MPixSpacingResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x14\n\x0cspacing_rows\x18\x02 \x01(\x02\x12\x17\n\x0fspacing_columns\x18\x03 \x01(\x02\"~\n\x14\x44\x43MPixOriginResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x13\n\x0borigin_rows\x18\x02 \x01(\x02\x12\x16\n\x0eorigin_columns\x18\x03 \x01(\x02\x12\x15\n\rorigin_slices\x18\x04 \x01(\x02\"T\n\x19\x44\x43MPixOrientationResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x13\n\x0borientation\x18\x02 \x03(\x02\"Y\n\x1b\x44\x43MPixSliceLocationResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x16\n\x0eslice_location\x18\x02 \x01(\x02\"S\n\x18\x44\x43MPixSourceFileResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x13\n\x0bsource_file\x18\x02 \x01(\t\"Q\n\x19\x44\x43MPixConvertToRGBRequest\x12\x1f\n\x03pix\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.DCMPix\x12\x13\n\x0brgb_channel\x18\x02 \x01(\x05\"O\n\x18\x44\x43MPixConvertToBWRequest\x12\x1f\n\x03pix\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.DCMPix\x12\x12\n\nbw_channel\x18\x02 \x01(\x05\"X\n\x17\x44\x43MPixComputeROIRequest\x12\x1f\n\x03pix\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.DCMPix\x12\x1c\n\x03roi\x18\x02 \x01(\x0b\x32\x0f.osirixgrpc.ROI\"W\n\x16\x44\x43MPixROIValuesRequest\x12\x1f\n\x03pix\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.DCMPix\x12\x1c\n\x03roi\x18\x02 \x01(\x0b\x32\x0f.osirixgrpc.ROI\"k\n\x15\x44\x43MPixSetImageRequest\x12\x1f\n\x03pix\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.DCMPix\x12\x18\n\x10image_data_float\x18\x02 \x03(\x02\x12\x17\n\x0fimage_data_argb\x18\x03 \x03(\x05\"[\n\x1a\x44\x43MPixGetMapFromROIRequest\x12\x1f\n\x03pix\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.DCMPix\x12\x1c\n\x03roi\x18\x02 \x01(\x0b\x32\x0f.osirixgrpc.ROIb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'dcmpix_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _globals['_DCMPIXISRGBRESPONSE']._serialized_start=58
  _globals['_DCMPIXISRGBRESPONSE']._serialized_end=131
  _globals['_DCMPIXCOMPUTEROIRESPONSE']._serialized_start=134
  _globals['_DCMPIXCOMPUTEROIRESPONSE']._serialized_end=304
  _globals['_DCMPIXROIVALUESRESPONSE']._serialized_start=306
  _globals['_DCMPIXROIVALUESRESPONSE']._serialized_end=428
  _globals['_DCMPIXDICOMIMAGERESPONSE']._serialized_start=430
  _globals['_DCMPIXDICOMIMAGERESPONSE']._serialized_end=537
  _globals['_DCMPIXDICOMSERIESRESPONSE']._serialized_start=539
  _globals['_DCMPIXDICOMSERIESRESPONSE']._serialized_end=649
  _globals['_DCMPIXDICOMSTUDYRESPONSE']._serialized_start=651
  _globals['_DCMPIXDICOMSTUDYRESPONSE']._serialized_end=758
  _globals['_DCMPIXIMAGERESPONSE']._serialized_start=761
  _globals['_DCMPIXIMAGERESPONSE']._serialized_end=917
  _globals['_DCMPIXGETMAPFROMROIRESPONSE']._serialized_start=919
  _globals['_DCMPIXGETMAPFROMROIRESPONSE']._serialized_end=1028
  _globals['_DCMPIXSHAPERESPONSE']._serialized_start=1030
  _globals['_DCMPIXSHAPERESPONSE']._serialized_end=1118
  _globals['_DCMPIXSPACINGRESPONSE']._serialized_start=1120
  _globals['_DCMPIXSPACINGRESPONSE']._serialized_end=1226
  _globals['_DCMPIXORIGINRESPONSE']._serialized_start=1228
  _globals['_DCMPIXORIGINRESPONSE']._serialized_end=1354
  _globals['_DCMPIXORIENTATIONRESPONSE']._serialized_start=1356
  _globals['_DCMPIXORIENTATIONRESPONSE']._serialized_end=1440
  _globals['_DCMPIXSLICELOCATIONRESPONSE']._serialized_start=1442
  _globals['_DCMPIXSLICELOCATIONRESPONSE']._serialized_end=1531
  _globals['_DCMPIXSOURCEFILERESPONSE']._serialized_start=1533
  _globals['_DCMPIXSOURCEFILERESPONSE']._serialized_end=1616
  _globals['_DCMPIXCONVERTTORGBREQUEST']._serialized_start=1618
  _globals['_DCMPIXCONVERTTORGBREQUEST']._serialized_end=1699
  _globals['_DCMPIXCONVERTTOBWREQUEST']._serialized_start=1701
  _globals['_DCMPIXCONVERTTOBWREQUEST']._serialized_end=1780
  _globals['_DCMPIXCOMPUTEROIREQUEST']._serialized_start=1782
  _globals['_DCMPIXCOMPUTEROIREQUEST']._serialized_end=1870
  _globals['_DCMPIXROIVALUESREQUEST']._serialized_start=1872
  _globals['_DCMPIXROIVALUESREQUEST']._serialized_end=1959
  _globals['_DCMPIXSETIMAGEREQUEST']._serialized_start=1961
  _globals['_DCMPIXSETIMAGEREQUEST']._serialized_end=2068
  _globals['_DCMPIXGETMAPFROMROIREQUEST']._serialized_start=2070
  _globals['_DCMPIXGETMAPFROMROIREQUEST']._serialized_end=2161
# @@protoc_insertion_point(module_scope)
