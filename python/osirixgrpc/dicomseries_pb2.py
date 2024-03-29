# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: dicomseries.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import utilities_pb2 as utilities__pb2
import types_pb2 as types__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x11\x64icomseries.proto\x12\nosirixgrpc\x1a\x0futilities.proto\x1a\x0btypes.proto\"M\n\x18\x44icomSeriesPathsResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\r\n\x05paths\x18\x02 \x03(\t\"y\n!DicomSeriesPreviousSeriesResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x30\n\x0fprevious_series\x18\x02 \x01(\x0b\x32\x17.osirixgrpc.DicomSeries\"q\n\x1d\x44icomSeriesNextSeriesResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12,\n\x0bnext_series\x18\x02 \x01(\x0b\x32\x17.osirixgrpc.DicomSeries\"t\n\x1f\x44icomSeriesSortedImagesResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12-\n\rsorted_images\x18\x02 \x03(\x0b\x32\x16.osirixgrpc.DicomImage\"e\n\x18\x44icomSeriesStudyResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12%\n\x05study\x18\x02 \x01(\x0b\x32\x16.osirixgrpc.DicomStudy\"g\n\x19\x44icomSeriesImagesResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12&\n\x06images\x18\x02 \x03(\x0b\x32\x16.osirixgrpc.DicomImage\"g\n$DicomSeriesSeriesInstanceUIDResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x1b\n\x13series_instance_uid\x18\x02 \x01(\t\"h\n$DicomSeriesSeriesSOPClassUIDResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x1c\n\x14series_sop_class_uid\x18\x02 \x01(\t\"f\n$DicomSeriesSeriesDescriptionResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x1a\n\x12series_description\x18\x02 \x01(\t\"S\n\x1b\x44icomSeriesModalityResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x10\n\x08modality\x18\x02 \x01(\t\"K\n\x17\x44icomSeriesNameResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0c\n\x04name\x18\x02 \x01(\t\"a\n!DicomSeriesNumberOfImagesResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x18\n\x10number_of_images\x18\x02 \x01(\x05\"\xaa\x01\n\x17\x44icomSeriesDateResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0c\n\x04year\x18\x02 \x01(\x05\x12\r\n\x05month\x18\x03 \x01(\x05\x12\x0b\n\x03\x64\x61y\x18\x04 \x01(\x05\x12\x0c\n\x04hour\x18\x05 \x01(\x05\x12\x0e\n\x06minute\x18\x06 \x01(\x05\x12\x0e\n\x06second\x18\x07 \x01(\x05\x12\x13\n\x0bmillisecond\x18\x08 \x01(\x05\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'dicomseries_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _globals['_DICOMSERIESPATHSRESPONSE']._serialized_start=63
  _globals['_DICOMSERIESPATHSRESPONSE']._serialized_end=140
  _globals['_DICOMSERIESPREVIOUSSERIESRESPONSE']._serialized_start=142
  _globals['_DICOMSERIESPREVIOUSSERIESRESPONSE']._serialized_end=263
  _globals['_DICOMSERIESNEXTSERIESRESPONSE']._serialized_start=265
  _globals['_DICOMSERIESNEXTSERIESRESPONSE']._serialized_end=378
  _globals['_DICOMSERIESSORTEDIMAGESRESPONSE']._serialized_start=380
  _globals['_DICOMSERIESSORTEDIMAGESRESPONSE']._serialized_end=496
  _globals['_DICOMSERIESSTUDYRESPONSE']._serialized_start=498
  _globals['_DICOMSERIESSTUDYRESPONSE']._serialized_end=599
  _globals['_DICOMSERIESIMAGESRESPONSE']._serialized_start=601
  _globals['_DICOMSERIESIMAGESRESPONSE']._serialized_end=704
  _globals['_DICOMSERIESSERIESINSTANCEUIDRESPONSE']._serialized_start=706
  _globals['_DICOMSERIESSERIESINSTANCEUIDRESPONSE']._serialized_end=809
  _globals['_DICOMSERIESSERIESSOPCLASSUIDRESPONSE']._serialized_start=811
  _globals['_DICOMSERIESSERIESSOPCLASSUIDRESPONSE']._serialized_end=915
  _globals['_DICOMSERIESSERIESDESCRIPTIONRESPONSE']._serialized_start=917
  _globals['_DICOMSERIESSERIESDESCRIPTIONRESPONSE']._serialized_end=1019
  _globals['_DICOMSERIESMODALITYRESPONSE']._serialized_start=1021
  _globals['_DICOMSERIESMODALITYRESPONSE']._serialized_end=1104
  _globals['_DICOMSERIESNAMERESPONSE']._serialized_start=1106
  _globals['_DICOMSERIESNAMERESPONSE']._serialized_end=1181
  _globals['_DICOMSERIESNUMBEROFIMAGESRESPONSE']._serialized_start=1183
  _globals['_DICOMSERIESNUMBEROFIMAGESRESPONSE']._serialized_end=1280
  _globals['_DICOMSERIESDATERESPONSE']._serialized_start=1283
  _globals['_DICOMSERIESDATERESPONSE']._serialized_end=1453
# @@protoc_insertion_point(module_scope)
