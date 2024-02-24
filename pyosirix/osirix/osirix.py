""" Core pyOsiriX functionality classes. """

from __future__ import annotations
from typing import List

import grpc  # noqa

import osirixgrpc.osirix_pb2_grpc as osirix_pb2_grpc
import osirixgrpc.utilities_pb2 as utilities_pb2

from osirix.viewer_controller import ViewerController
from osirix.vr_controller import VRController
from osirix.browser_controller import BrowserController
from osirix.exceptions import GrpcException


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
        osirix_service (osirix_pb2_grpc.OsiriXServiceStub): The service client used to send gRPC
            messages to the OsiriXgrpc server. None if no connection established.
        channel (grpc._channel.Channel): An insecure gRPC channel configuration.

    """
    def __init__(self, domain: str = "127.0.0.1", port: int = 50051,
                 max_send_message_length: int = 500000000,
                 max_receive_message_length: int = 500000000):
        self.port = port
        self.domain = domain
        self.server_url = domain + str(self.port)
        self.max_send_message_length = max_send_message_length
        self.max_receive_message_length = max_receive_message_length
        self.osirix_service = None
        self.channel = None

    def start_service(self):
        """ Start the insecure client service.

        """
        self.channel = grpc.insecure_channel(self.server_url,
                                             options=[("max_receive_message_length",
                                                       self.max_receive_message_length),
                                                      ("max_send_message_length",
                                                       self.max_send_message_length)])
        self.osirix_service = osirix_pb2_grpc.OsiriXServiceStub(self.channel)


class OsirixBase:
    """ A base class to use for all wrapper classes. Provides all shared capabilities

    """

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


class Osirix(OsirixBase):
    """ Provides access functionality to core OsiriX objects (viewers and Dicom browser).

    Attributes:
        osirix_service: The `OsirixService` to assign to the instance (required). This is passed
            to all child instances create from this object.

    """

    def __init__(self, osirix_service: osirix_pb2_grpc.OsiriXServiceStub) -> None:
        self.osirix_service = osirix_service

    def current_browser(self) -> BrowserController:
        """ The main Dicom browser instance.

        Returns:
            osirix.browser_controller.BrowserController
        """
        current_browser_response = self.osirix_service.OsirixCurrentBrowser(utilities_pb2.Empty())
        self.response_check(current_browser_response)
        browser_controller = current_browser_response.browser_controller
        browser_controller_obj = BrowserController(browser_controller, self.osirix_service)
        return browser_controller_obj

    def frontmost_viewer(self) -> ViewerController:
        """ The front-most 2D viewer.

        Returns:
            osirix.viewer_controller.ViewerController
        """
        viewer_response = self.osirix_service.OsirixFrontmostViewer(utilities_pb2.Empty())
        self.response_check(viewer_response)
        viewer_controller = viewer_response.viewer_controller
        viewer_controller_obj = ViewerController(viewer_controller, self.osirix_service)
        return viewer_controller_obj

    def displayed_2d_viewers(self) -> List[ViewerController, ...]:
        """ All currently active 2D viewers.

        Returns:
            List
        """
        viewers_response = self.osirix_service.OsirixDisplayed2DViewers(utilities_pb2.Empty())
        self.response_check(viewers_response)
        viewer_controller_objs = []
        for viewer_controller in viewers_response.viewer_controllers:
            viewer_controller_obj = ViewerController(viewer_controller, self.osirix_service)
            viewer_controller_objs.append(viewer_controller_obj)
        return viewer_controller_objs

    def frontmost_vr_controller(self) -> VRController:
        """ The front-most 3D viewer.

        Returns:
            osirix.vr_controller.VRController
        """
        vr_response = self.osirix_service.OsirixFrontmostVRController(utilities_pb2.Empty())
        self.response_check(vr_response)
        vr_controller = vr_response.vr_controller
        vr_controller_obj = VRController(vr_controller, self.osirix_service)
        return vr_controller_obj

    def displayed_vr_controllers(self) -> List[VRController, ...]:
        """ All currently active 3D viewers.

        Returns:
            List
        """
        vrs_response = self.osirix_service.OsirixDisplayedVRControllers(utilities_pb2.Empty())
        self.response_check(vrs_response)
        vr_controller_objs = []
        for vr_controller in vrs_response.vr_controllers:
            vr_controller_obj = VRController(vr_controller, self.osirix_service)
            vr_controller_objs.append(vr_controller_obj)
        return vr_controller_objs
