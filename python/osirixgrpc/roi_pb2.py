# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: roi.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import utilities_pb2 as utilities__pb2
import types_pb2 as types__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\troi.proto\x12\nosirixgrpc\x1a\x0futilities.proto\x1a\x0btypes.proto\"C\n\x0fROIAreaResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0c\n\x04\x61rea\x18\x02 \x01(\x02\"O\n\x13ROICentroidResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\t\n\x01x\x18\x02 \x01(\x02\x12\t\n\x01y\x18\x03 \x01(\x02\"U\n\x0eROIPixResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x1f\n\x03pix\x18\x02 \x01(\x0b\x32\x12.osirixgrpc.DCMPix\"C\n\x0fROINameResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0c\n\x04name\x18\x02 \x01(\t\"W\n\x10ROIColorResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\t\n\x01r\x18\x02 \x01(\x05\x12\t\n\x01g\x18\x03 \x01(\x05\x12\t\n\x01\x62\x18\x04 \x01(\x05\"I\n\x12ROIOpacityResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x0f\n\x07opacity\x18\x02 \x01(\x02\"M\n\x14ROIThicknessResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x11\n\tthickness\x18\x02 \x01(\x02\"\x8f\x01\n\x11ROIPointsResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\x35\n\x06points\x18\x02 \x03(\x0b\x32%.osirixgrpc.ROIPointsResponse.Point2D\x1a\x1f\n\x07Point2D\x12\t\n\x01x\x18\x01 \x01(\x02\x12\t\n\x01y\x18\x02 \x01(\x02\"E\n\x10ROIITypeResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.osirixgrpc.Status\x12\r\n\x05itype\x18\x02 \x01(\x05\"W\n\x10ROIRotateRequest\x12\x1c\n\x03roi\x18\x01 \x01(\x0b\x32\x0f.osirixgrpc.ROI\x12\x0f\n\x07\x64\x65grees\x18\x02 \x01(\x02\x12\t\n\x01x\x18\x03 \x01(\x02\x12\t\n\x01y\x18\x04 \x01(\x02\"M\n\x0eROIMoveRequest\x12\x1c\n\x03roi\x18\x01 \x01(\x0b\x32\x0f.osirixgrpc.ROI\x12\x0f\n\x07\x63olumns\x18\x02 \x01(\x05\x12\x0c\n\x04rows\x18\x03 \x01(\x05\"?\n\x11ROISetNameRequest\x12\x1c\n\x03roi\x18\x01 \x01(\x0b\x32\x0f.osirixgrpc.ROI\x12\x0c\n\x04name\x18\x02 \x01(\t\"S\n\x12ROISetColorRequest\x12\x1c\n\x03roi\x18\x01 \x01(\x0b\x32\x0f.osirixgrpc.ROI\x12\t\n\x01r\x18\x02 \x01(\x05\x12\t\n\x01g\x18\x03 \x01(\x05\x12\t\n\x01\x62\x18\x04 \x01(\x05\"E\n\x14ROISetOpacityRequest\x12\x1c\n\x03roi\x18\x01 \x01(\x0b\x32\x0f.osirixgrpc.ROI\x12\x0f\n\x07opacity\x18\x02 \x01(\x02\"I\n\x16ROISetThicknessRequest\x12\x1c\n\x03roi\x18\x01 \x01(\x0b\x32\x0f.osirixgrpc.ROI\x12\x11\n\tthickness\x18\x02 \x01(\x02\"\x8d\x01\n\x13ROISetPointsRequest\x12\x1c\n\x03roi\x18\x01 \x01(\x0b\x32\x0f.osirixgrpc.ROI\x12\x37\n\x06points\x18\x02 \x03(\x0b\x32\'.osirixgrpc.ROISetPointsRequest.Point2D\x1a\x1f\n\x07Point2D\x12\t\n\x01x\x18\x01 \x01(\x02\x12\t\n\x01y\x18\x02 \x01(\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'roi_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _globals['_ROIAREARESPONSE']._serialized_start=55
  _globals['_ROIAREARESPONSE']._serialized_end=122
  _globals['_ROICENTROIDRESPONSE']._serialized_start=124
  _globals['_ROICENTROIDRESPONSE']._serialized_end=203
  _globals['_ROIPIXRESPONSE']._serialized_start=205
  _globals['_ROIPIXRESPONSE']._serialized_end=290
  _globals['_ROINAMERESPONSE']._serialized_start=292
  _globals['_ROINAMERESPONSE']._serialized_end=359
  _globals['_ROICOLORRESPONSE']._serialized_start=361
  _globals['_ROICOLORRESPONSE']._serialized_end=448
  _globals['_ROIOPACITYRESPONSE']._serialized_start=450
  _globals['_ROIOPACITYRESPONSE']._serialized_end=523
  _globals['_ROITHICKNESSRESPONSE']._serialized_start=525
  _globals['_ROITHICKNESSRESPONSE']._serialized_end=602
  _globals['_ROIPOINTSRESPONSE']._serialized_start=605
  _globals['_ROIPOINTSRESPONSE']._serialized_end=748
  _globals['_ROIPOINTSRESPONSE_POINT2D']._serialized_start=717
  _globals['_ROIPOINTSRESPONSE_POINT2D']._serialized_end=748
  _globals['_ROIITYPERESPONSE']._serialized_start=750
  _globals['_ROIITYPERESPONSE']._serialized_end=819
  _globals['_ROIROTATEREQUEST']._serialized_start=821
  _globals['_ROIROTATEREQUEST']._serialized_end=908
  _globals['_ROIMOVEREQUEST']._serialized_start=910
  _globals['_ROIMOVEREQUEST']._serialized_end=987
  _globals['_ROISETNAMEREQUEST']._serialized_start=989
  _globals['_ROISETNAMEREQUEST']._serialized_end=1052
  _globals['_ROISETCOLORREQUEST']._serialized_start=1054
  _globals['_ROISETCOLORREQUEST']._serialized_end=1137
  _globals['_ROISETOPACITYREQUEST']._serialized_start=1139
  _globals['_ROISETOPACITYREQUEST']._serialized_end=1208
  _globals['_ROISETTHICKNESSREQUEST']._serialized_start=1210
  _globals['_ROISETTHICKNESSREQUEST']._serialized_end=1283
  _globals['_ROISETPOINTSREQUEST']._serialized_start=1286
  _globals['_ROISETPOINTSREQUEST']._serialized_end=1427
  _globals['_ROISETPOINTSREQUEST_POINT2D']._serialized_start=717
  _globals['_ROISETPOINTSREQUEST_POINT2D']._serialized_end=748
# @@protoc_insertion_point(module_scope)
