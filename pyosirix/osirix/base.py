""" The core functionality of pyOsiriX (base class and service class).

"""

from __future__ import annotations

from typing import Union

from osirixgrpc import types_pb2

import osirix

# Define the OsiriXgrpc types allowed.
Pb2Type = Union[types_pb2.DicomStudy, types_pb2.DicomSeries, types_pb2.DicomImage, types_pb2.ROI,
                types_pb2.ROIVolume, types_pb2.DCMPix, types_pb2.BrowserController,
                types_pb2.ViewerController, types_pb2.VRController, None]


class OsirixBase:
    """ A base class to be used for all pyOsiriX classes.

    Attributes:
        osirix_service (OsirixService): A service instance created with appropriate configuration.
        pb2_object (Pb2Type): The object messages passed by OsiriXgrpc (as defined in types.proto).
            Importantly, each object contains the unique identity of an instance within OsiriX,
            accessible via `osirixrpc_uid`.  Please do not modify its value!  The only time this
            should be passed as `None` is when creating an `Osirix` instance.
    """
    def __init__(self, osirix_service: osirix.osirix_utilities.OsirixService,
                 pb2_object: Pb2Type = None):
        self.osirix_service = osirix_service
        self.osirix_service_stub = osirix_service.osirix_service_stub
        self.pb2_object = pb2_object

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
