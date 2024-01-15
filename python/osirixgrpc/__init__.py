__all__ = ["browsercontroller_pb2",
           "dcmpix_pb2",
           "dicomimage_pb2",
           "dicomseries_pb2",
           "dicomstudy_pb2",
           "osirix_pb2_grpc",
           "osirix_pb2",
           "roi_pb2",
           "roivolume_pb2",
           "types_pb2",
           "utilities_pb2",
           "viewercontroller_pb2",
           "vrcontroller_pb2"]

__version__ = "0.2.1-dev1"

__author__ = "Timothy Sum Hon Mun & Matthew D Blackledge"

import sys
import os
sys.path.insert(0, os.path.abspath(os.path.dirname(__file__)))

from osirixgrpc import browsercontroller_pb2
from osirixgrpc import dcmpix_pb2
from osirixgrpc import dicomimage_pb2
from osirixgrpc import dicomseries_pb2
from osirixgrpc import dicomstudy_pb2
from osirixgrpc import osirix_pb2_grpc
from osirixgrpc import osirix_pb2
from osirixgrpc import roi_pb2
from osirixgrpc import roivolume_pb2
from osirixgrpc import types_pb2
from osirixgrpc import utilities_pb2
from osirixgrpc import viewercontroller_pb2
from osirixgrpc import vrcontroller_pb2
