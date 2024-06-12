""" The core functionality of pyOsiriX (base class and service class).

"""

from __future__ import annotations

from typing import Union

import osirixgrpc
from osirixgrpc import types_pb2

import osirix
from osirix.exceptions import GrpcException

# Define the OsiriXgrpc types allowed.
Pb2Type = Union[types_pb2.DicomStudy, types_pb2.DicomSeries, types_pb2.DicomImage, types_pb2.ROI,
                types_pb2.ROIVolume, types_pb2.DCMPix, types_pb2.BrowserController,
                types_pb2.ViewerController, types_pb2.VRController, None]


def pyosirix_connection_check(func):
    """ A decorator function that checks an OsiriX connection is established.  """
    def wrapper(self, *args, **kwargs):
        if self.osirix_service.check_connection():
            return func(self, *args, **kwargs)
        else:
            raise GrpcException("No connection with OsiriX available.")
    return wrapper


class OsirixBase:
    """ A base class to be used for all pyOsiriX classes. Only subclasses must be created.

    """
    def __init__(self, osirix_service: osirix.osirix_utilities.OsirixService,
                 pb2_object: Pb2Type = None):
        self._osirix_service = osirix_service
        self._osirix_service_stub = osirix_service.osirix_service_stub
        self.pb2_object = pb2_object  # The protobuf object created using osirixgrpc (private)

    @property
    def osirix_service(self) -> osirix.osirix_utilities.OsirixService:
        """ The OsiriX service from which the instance was created.
        """
        return self._osirix_service

    @property
    def osirix_service_stub(self) -> osirixgrpc.osirix_pb2_grpc.OsiriXServiceStub:
        """ The service stub contained with service. Provided for convenient/fast access.
        """
        return self._osirix_service_stub

    @staticmethod
    def response_check(grpc_response) -> None:
        """ Checks whether the status of a response and raises an appropriate error.

        Args:
            grpc_response: Response returned by Osirix service. All returned OsiriXgrpc messages
                contain a `status` (1 for success, 0 otherwise).  Where the status is 0, an
                additional `message` is provided, outlining what went wrong.
        """
        if grpc_response.status.status == 1:
            pass
        elif grpc_response.status.message != "":
            raise osirix.exceptions.GrpcException(grpc_response.status.message)
        else:
            raise osirix.exceptions.GrpcException("Bad response. Please contact developer.")
