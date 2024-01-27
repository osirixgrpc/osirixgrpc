# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: dicomimage.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import utilities_pb2 as utilities__pb2
import types_pb2 as types__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x10\x64icomimage.proto\x12\nosirixgrpc\x1a\x0futilities.proto\x1a\x0btypes.proto\"L\n\x17\x44icomImageWidthResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\r\n\x05width\x18\x02 \x01(\r\"N\n\x18\x44icomImageHeightResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0e\n\x06height\x18\x02 \x01(\r\"`\n DicomImageSOPInstanceUIDResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x18\n\x10sop_instance_uid\x18\x02 \x01(\t\"W\n\x1e\x44icomImageCompletePathResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x11\n\tpath_name\x18\x02 \x01(\t\"\xa9\x01\n\x16\x44icomImageDateResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0c\n\x04year\x18\x02 \x01(\x05\x12\r\n\x05month\x18\x03 \x01(\x05\x12\x0b\n\x03\x64\x61y\x18\x04 \x01(\x05\x12\x0c\n\x04hour\x18\x05 \x01(\x05\x12\x0e\n\x06minute\x18\x06 \x01(\x05\x12\x0e\n\x06second\x18\x07 \x01(\x05\x12\x13\n\x0bmillisecond\x18\x08 \x01(\x05\"`\n DicomImageNumberOfFramesResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x18\n\x10number_of_frames\x18\x02 \x01(\r\"R\n\x1a\x44icomImageModalityResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x10\n\x08modality\x18\x02 \x01(\t\"g\n\x18\x44icomImageSeriesResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\'\n\x06series\x18\x02 \x01(\x0b\x32\x17.osirixgrpc.DicomSeries\"^\n\x1f\x44icomImageSliceLocationResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x17\n\x0fslice_locations\x18\x02 \x01(\x02\"_\n DicomImageInstanceNumberResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x17\n\x0finstance_number\x18\x02 \x01(\rb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'dicomimage_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _globals['_DICOMIMAGEWIDTHRESPONSE']._serialized_start=62
  _globals['_DICOMIMAGEWIDTHRESPONSE']._serialized_end=138
  _globals['_DICOMIMAGEHEIGHTRESPONSE']._serialized_start=140
  _globals['_DICOMIMAGEHEIGHTRESPONSE']._serialized_end=218
  _globals['_DICOMIMAGESOPINSTANCEUIDRESPONSE']._serialized_start=220
  _globals['_DICOMIMAGESOPINSTANCEUIDRESPONSE']._serialized_end=316
  _globals['_DICOMIMAGECOMPLETEPATHRESPONSE']._serialized_start=318
  _globals['_DICOMIMAGECOMPLETEPATHRESPONSE']._serialized_end=405
  _globals['_DICOMIMAGEDATERESPONSE']._serialized_start=408
  _globals['_DICOMIMAGEDATERESPONSE']._serialized_end=577
  _globals['_DICOMIMAGENUMBEROFFRAMESRESPONSE']._serialized_start=579
  _globals['_DICOMIMAGENUMBEROFFRAMESRESPONSE']._serialized_end=675
  _globals['_DICOMIMAGEMODALITYRESPONSE']._serialized_start=677
  _globals['_DICOMIMAGEMODALITYRESPONSE']._serialized_end=759
  _globals['_DICOMIMAGESERIESRESPONSE']._serialized_start=761
  _globals['_DICOMIMAGESERIESRESPONSE']._serialized_end=864
  _globals['_DICOMIMAGESLICELOCATIONRESPONSE']._serialized_start=866
  _globals['_DICOMIMAGESLICELOCATIONRESPONSE']._serialized_end=960
  _globals['_DICOMIMAGEINSTANCENUMBERRESPONSE']._serialized_start=962
  _globals['_DICOMIMAGEINSTANCENUMBERRESPONSE']._serialized_end=1057
# @@protoc_insertion_point(module_scope)
