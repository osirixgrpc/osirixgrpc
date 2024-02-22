from __future__ import annotations
from typing import List, Tuple

import grpc
import sys
from osirix.exceptions import GrpcException
from osirix.viewer_controller import ViewerController
from osirix.vr_controller import VRController
from osirix.browser_controller import BrowserController
from osirix.response_processor import ResponseProcessor

# sys.path.append("./pb2/")

import osirixgrpc.osirix_pb2_grpc as osirix_pb2_grpc
import osirixgrpc.utilities_pb2 as utilities_pb2

import yaml

class OsirixService(object):
    """
    Class containing the Osirix gRPC service that the gRPC request and responses will be communicating through

    """
    def __init__(self,
                 channel_opt: List[Tuple[str, int]],
                 domain: str,
                 port : int = 50051):


        self.port = port
        self.domain = domain
        self.server_url = domain + str(self.port)
        self.channel_opt = channel_opt
        self.channel = grpc.insecure_channel(self.server_url, options=self.channel_opt)
        try:
            self.osirix_service = osirix_pb2_grpc.OsiriXServiceStub(self.channel)
        except:
            raise GrpcException("No connection to OsiriX can be established")

    def get_service(self) -> osirix_pb2_grpc.OsiriXServiceStub:
        """
        Gets the osirix service

        Returns:
            the gRPC OsirixServiceStub
        """
        return self.osirix_service

    @classmethod
    def name(cls) -> str:
        return cls.__name__

class Osirix(object):
    """
    Osirix class that allows interaction with the main Viewer, Browser and VR controllers of Osirix
    """
    # osirix_service = None
    # response_processor = None

    def __init__(self,
                 osirix_service: osirix_pb2_grpc.OsiriXServiceStub
                 ) -> None:
        self.osirix_service = osirix_service
        self.response_processor = ResponseProcessor()

    def current_browser(self) -> BrowserController:
        """
        Provides the Osirix browser window

        Returns:
            BrowserController
        """
        current_browser_response = self.osirix_service.OsirixCurrentBrowser(utilities_pb2.Empty())
        self.response_processor.response_check(current_browser_response)

        browser_controller = current_browser_response.browser_controller

        browser_controller_obj = BrowserController(browser_controller, self.osirix_service)
        return browser_controller_obj


    def frontmost_vr_controller(self) -> VRController:
        """
        Provides the VR Controller that is currently selected

        Returns:
            VRController

        """
        vr_controller_response = self.osirix_service.OsirixFrontmostVRController(utilities_pb2.Empty())

        self.response_processor.response_check(vr_controller_response)

        vr_controller = vr_controller_response.vr_controller
        # vr_controller_response = self.osirix_service.ViewerControllerVRControllers(viewer_controller_response).vr_controllers[0]

        # Build and return VRController
        vr_controller = VRController(vr_controller, self.osirix_service)
        return vr_controller


    def frontmost_viewer(self) -> ViewerController:
        """
        Provides the 2D viewer that is currently selected

        Returns:
            ViewerController

        """
        frontmost_viewer_response = self.osirix_service.OsirixFrontmostViewer(utilities_pb2.Empty())
        self.response_processor.response_check(frontmost_viewer_response)

        viewer_controller = frontmost_viewer_response.viewer_controller
        # Build and return ViewerController
        viewer_controller = ViewerController(viewer_controller, self.osirix_service)
        return viewer_controller


    def displayed_2d_viewers(self) -> Tuple[ViewerController, ...]:
        """
        Provides all 2D viewers that are displayed

        Returns:
            Tuple containing each 2D Viewer

        """
        response_displayed_2d_viewers = self.osirix_service.OsirixDisplayed2DViewers(utilities_pb2.Empty())

        self.response_processor.response_check(response_displayed_2d_viewers)
        viewer_controller_obj_tuple : Tuple[ViewerController, ...]= ()

        for viewer_controller in response_displayed_2d_viewers.viewer_controllers:
            viewer_obj: ViewerController = ViewerController(viewer_controller, self.osirix_service)
            viewer_controller_obj_tuple = viewer_controller_obj_tuple + (viewer_obj,)

        return viewer_controller_obj_tuple

    def displayed_vr_controllers(self) -> Tuple[VRController, ...]:
        """
        Provides all VR controllers that are displayed

        Returns:
            Tuple containing each VRController
        """
        response_displayed_vr_controllers = self.osirix_service.OsirixDisplayedVRControllers(utilities_pb2.Empty())
        self.response_processor.response_check(response_displayed_vr_controllers)

        vr_controller_obj_tuple: Tuple[VRController, ...] = ()

        for vr_controller in response_displayed_vr_controllers.vr_controllers:
            vr_controller_obj = VRController(vr_controller, self.osirix_service)
            vr_controller_obj_tuple = vr_controller_obj_tuple + (vr_controller_obj,)

        return vr_controller_obj_tuple

    # def run_alert_panel(self,
    #                     message: str,
    #                     information_text : str = None,
    #                     first_button: str = "OK",
    #                     second_button: str = None,
    #                     third_button: str = None):
    #
    # def select_path(self,
    #                 dirs: bool = False,
    #                 extension: str = None,
    #                 title: str = None) -> str:






