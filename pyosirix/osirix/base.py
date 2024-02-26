""" The core functionality of pyOsiriX (base class and service class).

"""

from __future__ import annotations

from typing import Union

import grpc  # noqa

from osirixgrpc import osirix_pb2_grpc
from osirixgrpc import types_pb2

from osirix.exceptions import GrpcException

# Define the OsiriXgrpc types allowed.
Pb2Type = Union[types_pb2.DicomStudy, types_pb2.DicomSeries, types_pb2.DicomImage, types_pb2.ROI,
                types_pb2.ROIVolume, types_pb2.DCMPix, types_pb2.BrowserController,
                types_pb2.ViewerController, types_pb2.VRController, None]


class OsirixService(object):
    """ Create and manage an OsiriX gRPC service (stub).

    Attributes:
        domain (str): The domain with which to establish the connection.  Currently, only
            "127.0.0.1" is supported (localhost). Default is "127.0.0.1".
        port (str): The port number with which to establish the connection. Default is "50051".
        max_send_message_length (int): The maximum number of bytes permitted in a send message.
            Default is 500000000 (500 MB).
        max_receive_message_length (int): The maximum number of bytes permitted in a receive
            message. Default is 500000000 (500 MB).
        osirix_service_stub (osirix_pb2_grpc.OsiriXServiceStub): The service stub used to send gRPC
            messages to the OsiriXgrpc server. None if no connection established.
        channel (grpc._channel.Channel): An insecure gRPC channel configuration.

    """
    def __init__(self, domain: str = "127.0.0.1", port: int = 50051,
                 max_send_message_length: int = 500000000,
                 max_receive_message_length: int = 500000000):
        self.port = port
        self.domain = domain
        self.server_url = domain + ":" + str(self.port)
        self.max_send_message_length = max_send_message_length
        self.max_receive_message_length = max_receive_message_length
        self.osirix_service_stub = None
        self.channel = None

    def start_service(self):
        """ Start the insecure client service.

        Raises:
            GrpcException: Occurs when something goes wrong trying to set up the connection.

        """
        try:
            self.channel = grpc.insecure_channel(self.server_url,
                                                 options=[("max_receive_message_length",
                                                           self.max_receive_message_length),
                                                          ("max_send_message_length",
                                                           self.max_send_message_length)])
            self.osirix_service_stub = osirix_pb2_grpc.OsiriXServiceStub(self.channel)
        except Exception as exc:
            raise GrpcException("Could not establish a connection with OsiriX.") from exc


class OsirixBase:
    """ A base class to be used for all pyOsiriX classes.

    Attributes:
        osirix_service (OsirixService): A service instance created with appropriate configuration.
        pb2_object (Pb2Type): The object messages passed by OsiriXgrpc (as defined in types.proto).
            Importantly, each object contains the unique identity of an instance within OsiriX,
            accessible via `osirixrpc_uid`.  Please do not modify its value!  The only time this
            should be passed as `None` is when creating an `Osirix` instance.
    """
    def __init__(self, osirix_service: OsirixService, pb2_object: Pb2Type = None):
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
            raise GrpcException(grpc_response.status.message)
        else:
            raise GrpcException("Bad response. Please contact developer.")
