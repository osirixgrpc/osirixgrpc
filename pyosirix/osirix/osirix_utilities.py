""" Provide access to the core OsiriX objects: 2D/3D viewers and the database (browser).

"""

from __future__ import annotations
from typing import List

import grpc  # noqa

from osirixgrpc import osirix_pb2_grpc
import osirixgrpc.utilities_pb2 as utilities_pb2

import osirix


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
            raise osirix.exceptions.GrpcException(
                "Could not establish a connection with OsiriX.") from exc


class Osirix(osirix.base.OsirixBase):
    """ Provides access functionality to core OsiriX objects (2D/3D viewers and Dicom browser).

    Note that it is better not to use this class directly, unless you know what you are doing.
    There is a global instance of this class, set-up according to the OsiriXgrpc plugin
    configuration, as described in the main `__init__.py` module.
    """

    def current_browser(self) -> osirix.browser_controller.BrowserController:
        """ Return an instance of the current Dicom database browser.

        Note that it is better not use this method directly. Use the following instead:

        ```python
        import osirix
        browser = osirix.current_browser()
        ```

        Returns:
            The main Dicom browser instance.
        """
        request = utilities_pb2.Empty()
        response = self.osirix_service_stub.OsirixCurrentBrowser(request)
        self.response_check(response)
        browser_controller = response.browser_controller
        browser_controller_obj = osirix.browser_controller.BrowserController(self.osirix_service,
                                                                             browser_controller)
        return browser_controller_obj

    def frontmost_viewer(self) -> osirix.viewer_controller.ViewerController:
        """ Return an instance of the front-most 2D viewer.

        If there are more than one, look for the viewer highlighted by a red boundary.
        Note that it is better not use this method directly. Use the following instead:

        ```python
        import osirix
        viewer = osirix.frontmost_viewer()
        ```

        Returns:
            The front-most 2D viewer.
        """
        request = utilities_pb2.Empty()
        response = self.osirix_service_stub.OsirixFrontmostViewer(request)
        self.response_check(response)
        viewer_controller = response.viewer_controller
        viewer_controller_obj = osirix.viewer_controller.ViewerController(self.osirix_service,
                                                                          viewer_controller)
        return viewer_controller_obj

    def displayed_2d_viewers(self) -> List[osirix.viewer_controller.ViewerController, ...]:
        """ Return all displayed 2D viewer instances.

        Note that it is better not use this method directly. Use the following instead:

        ```python
        import osirix
        viewers = osirix.displayed_2d_viewers()
        ```

        Returns:
            A list of 2D viewer instances.
        """
        request = utilities_pb2.Empty()
        response = self.osirix_service_stub.OsirixDisplayed2DViewers(request)
        self.response_check(response)
        viewer_controller_objs = []
        for viewer_controller in response.viewer_controllers:
            viewer_controller_obj = osirix.viewer_controller.ViewerController(self.osirix_service,
                                                                              viewer_controller)
            viewer_controller_objs.append(viewer_controller_obj)
        return viewer_controller_objs

    def frontmost_vr_controller(self) -> osirix.vr_controller.VRController:
        """ Return an instance of the front-most 3D viewer.

        Note that it is better not use this method directly. Use the following instead:

        ```python
        import osirix
        vr_controller = osirix.frontmost_vr_controller()
        ```

        Returns:
            The front-most 3D viewer.
        """
        request = utilities_pb2.Empty()
        response = self.osirix_service_stub.OsirixFrontmostVRController(request)
        self.response_check(response)
        vr_controller = response.vr_controller
        vr_controller_obj = osirix.vr_controller.VRController(self.osirix_service,
                                                              vr_controller)
        return vr_controller_obj

    def displayed_vr_controllers(self) -> List[osirix.vr_controller.VRController, ...]:
        """ Return all displayed 3D viewer instances.

        Note that it is better not use this method directly. Use the following instead:

        ```python
        import osirix
        vr_controllers = osirix.displayed_vr_controllers()
        ```

        Returns:
            A list of 3D viewer instances.
        """
        request = utilities_pb2.Empty()
        response = self.osirix_service_stub.OsirixDisplayedVRControllers(request)
        self.response_check(response)
        vr_controller_objs = []
        for vr_controller in response.vr_controllers:
            vr_controller_obj = osirix.vr_controller.VRController(self.osirix_service,
                                                                  vr_controller)
            vr_controller_objs.append(vr_controller_obj)
        return vr_controller_objs
