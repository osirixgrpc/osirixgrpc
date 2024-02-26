""" Functionality for the 3D viewer.

"""

from __future__ import annotations
from typing import Tuple

import osirixgrpc.vrcontroller_pb2 as vrcontroller_pb2

import osirix


class VRController(osirix.base.OsirixBase):
    """ Represents one of the displayed volume render windows.

    """
    @property
    def rendering_mode(self) -> str:
        """ The rendering mode: "VR" for volume render, "MIP" for maximum intensity projection.
        """
        response = self.osirix_service_stub.VRControllerRenderingMode(self.pb2_object)
        self.response_check(response)
        return response.rendering_mode

    @rendering_mode.setter
    def rendering_mode(self, rendering_mode: str) -> None:
        """ The rendering mode: "VR" for volume render, "MIP" for maximum intensity projection.
        """
        if not rendering_mode == "VR" or rendering_mode == "MIP":
            raise ValueError("Bad rendering_mode. Must be 'VR' or 'MIP'")
        request = vrcontroller_pb2.VRControllerSetRenderingModeRequest(
            vr_controller=self.pb2_object, rendering_mode=rendering_mode)
        response = self.osirix_service_stub.VRControllerSetRenderingMode(request)
        self.response_check(response)

    @property
    def style(self) -> str:
        """ The style of the volume render window.
        """
        response = self.osirix_service_stub.VRControllerStyle(self.pb2_object)
        self.response_check(response)
        return response.style

    @property
    def title(self) -> str:
        """ The title of the volume render window.
        """
        response = self.osirix_service_stub.VRControllerTitle(self.pb2_object)
        self.response_check(response)
        return response.title

    @property
    def wlww(self) -> Tuple[float, float]:
        """ The window level and window width of the viewer.
        """
        response = self.osirix_service_stub.VRControllerWLWW(self.pb2_object)
        self.response_check(response)
        return response.wl, response.ww

    @wlww.setter
    def wlww(self, wlww: Tuple[float, float]) -> None:
        # TODO: Do I need to set a tolerance on the WW?
        """The window level and window width of the viewer.
        """
        request = vrcontroller_pb2.VRControllerSetWLWWRequest(vr_controller=self.pb2_object,
                                                              wl=wlww[0],
                                                              ww=wlww[1])
        response = self.osirix_service_stub.VRControllerSetWLWW(request)
        self.response_check(response)

    def blending_controller(self) -> osirix.viewer_controller.ViewerController:
        """ The 2D ViewerController instance currently being blended (fused).
        """
        response = self.osirix_service_stub.VRControllerBlendingController(self.pb2_object)
        self.response_check(response)
        return osirix.viewer_controller.ViewerController(self.osirix_service,
                                                         response.viewer_controller)

    def viewer_2d(self) -> osirix.viewer_controller.ViewerController:
        """ The 2D ViewerController instance from which the 3D viewer was started.
        """
        response = self.osirix_service_stub.VRControllerViewer2D(self.pb2_object)
        self.response_check(response)
        return osirix.viewer_controller.ViewerController(self.osirix_service,
                                                         response.viewer_controller)
