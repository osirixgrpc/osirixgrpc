from __future__ import annotations
from typing import Tuple, Dict
import sys

import numpy

import osirixgrpc.viewercontroller_pb2 as viewercontroller_pb2
import osirixgrpc.vrcontroller_pb2 as vrcontroller_pb2
from osirix.response_processor import ResponseProcessor
from osirix.viewer_controller import ViewerController
from osirix import viewer_controller
from osirix import *

class VRController(object):
    '''
    Class representing the properties and methods to communicate with the Osirix service through
    gRPC for a VRController
    '''

    def __init__(self,
                 osirixrpc_uid : str,
                 osirix_service):
        self.osirixrpc_uid = osirixrpc_uid
        self.osirix_service = osirix_service
        self.response_processor = ResponseProcessor()

    @property
    def rendering_mode(self) -> str:
        """
          Process gRPC request to retrieve the rendering mode for VRController

          Returns:
            str : rendering mode
        """
        response_vr_rendering_mode = self.osirix_service.VRControllerRenderingMode(self.osirixrpc_uid)
        self.response_processor.response_check(response_vr_rendering_mode)
        self._rendering_mode = response_vr_rendering_mode.rendering_mode

        return self._rendering_mode

    @rendering_mode.setter
    def rendering_mode(self, rendering_mode : str) -> None:
        """
          Process gRPC request to set the rendering mode for the VRController

          Args:
            str: rendering mode

          Returns:
            None
        """
        request = vrcontroller_pb2.VRControllerSetRenderingModeRequest(vr_controller=self.osirixrpc_uid, rendering_mode=rendering_mode)
        response = self.osirix_service.VRControllerSetRenderingMode(request)
        self.response_processor.response_check(response)


    @property
    def style(self) -> str:
        """
          Process gRPC request to retrieve the style for the VRController

          Returns:
            str : style
        """
        response_vr_style = self.osirix_service.VRControllerStyle(self.osirixrpc_uid)
        self.response_processor.response_check(response_vr_style)
        self._style = response_vr_style.style

        return self._style

    @property
    def title(self) -> str:
        """
          Process gRPC request to retrieve the title for the VRController

          Returns:
            str : title
        """
        response_vr_title = self.osirix_service.VRControllerTitle(self.osirixrpc_uid)
        self.response_processor.response_check(response_vr_title)
        self._title = response_vr_title.title

        return self._title

    @property
    def wlww(self) -> Tuple[float, float]:
        """
          Process gRPC request to retrive the wlww for the VRController

          Returns:
            Tuple containing wl and ww in float
        """
        response_vr_wlww = self.osirix_service.VRControllerWLWW(self.osirixrpc_uid)
        self.response_processor.response_check(response_vr_wlww)

        return (response_vr_wlww.wl, response_vr_wlww.ww)

    @wlww.setter
    def wlww(self, wlww : Tuple[float, float]) -> None:
        """
          Process gRPC request to set the wlww for the VRController

          Args:
            Tuple[float, float]: wlww

          Returns:
            None
        """
        wl, ww = wlww
        request = vrcontroller_pb2.VRControllerSetWLWWRequest(vr_controller=self.osirixrpc_uid, wl=wl, ww=ww)
        response = self.osirix_service.VRControllerSetWLWW(request)
        self.response_processor.response_check(response)

    def blending_controller(self) -> ViewerController:
        """
          Process gRPC request to retrieve the blending controller for the VRController

          Returns:
            ViewerController
        """
        response_blending_controller = self.osirix_service.VRControllerBlendingController(self.osirixrpc_uid)

        blending_controller_obj = ViewerController(response_blending_controller.viewer_controller, self.osirix_service)

        return blending_controller_obj

    def viewer_2d(self) -> ViewerController:
        """
          Process gRPC request to retrieve the 2D viewer for the VRController

          Returns:
            ViewerController
        """
        response_viewer_2d = self.osirix_service.VRControllerViewer2D(self.osirixrpc_uid)
        viewer_2d = response_viewer_2d.viewer_controller
        viewer_2d_obj = ViewerController(viewer_2d, self.osirix_service)

        return viewer_2d_obj
