""" Functionality for the 3D viewer.

Example usage:
    ```python
    import osirix

    vr_controller = osirix.frontmost_vr_controller()  # Raises GrpcException if not available.
    vr_controller.wlww = (50, 100)  # Set the window level and width
    print(f"This window has {len(vr_controller.roi_volumes())} ROI volumes")
    ```
"""

from __future__ import annotations
from typing import Tuple, List

import osirixgrpc.vrcontroller_pb2 as vrcontroller_pb2

import osirix
from osirix.base import pyosirix_connection_check


class VRController(osirix.base.OsirixBase):
    """ Represents one of the displayed volume render windows.

    """
    def __repr__(self):
        return f"VRController: " \
               f"{self.title} " \
               f"({self.rendering_mode})"

    @property
    @pyosirix_connection_check
    def rendering_mode(self) -> str:
        """ The rendering mode: "VR" for volume render, "MIP" for maximum intensity projection.
        """
        response = self.osirix_service_stub.VRControllerRenderingMode(self.pb2_object)
        self.response_check(response)
        return response.rendering_mode

    @rendering_mode.setter
    @pyosirix_connection_check
    def rendering_mode(self, rendering_mode: str) -> None:
        """ The rendering mode: "VR" for volume render, "MIP" for maximum intensity projection.
        """
        if rendering_mode not in ["VR", "MIP"]:
            raise ValueError("Bad rendering_mode. Must be 'VR' or 'MIP'")
        request = vrcontroller_pb2.VRControllerSetRenderingModeRequest(
            vr_controller=self.pb2_object, rendering_mode=rendering_mode)
        response = self.osirix_service_stub.VRControllerSetRenderingMode(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def style(self) -> str:
        """ The style of the volume render window.
        """
        response = self.osirix_service_stub.VRControllerStyle(self.pb2_object)
        self.response_check(response)
        return response.style

    @property
    @pyosirix_connection_check
    def title(self) -> str:
        """ The title of the volume render window.
        """
        response = self.osirix_service_stub.VRControllerTitle(self.pb2_object)
        self.response_check(response)
        return response.title

    @property
    @pyosirix_connection_check
    def wlww(self) -> Tuple[float, float]:
        """ The window level and window width of the viewer.
        """
        response = self.osirix_service_stub.VRControllerWLWW(self.pb2_object)
        self.response_check(response)
        return response.wl, response.ww

    @wlww.setter
    @pyosirix_connection_check
    def wlww(self, wlww: Tuple[float, float]) -> None:
        """The window level and window width of the viewer.
        """
        request = vrcontroller_pb2.VRControllerSetWLWWRequest(vr_controller=self.pb2_object,
                                                              wl=wlww[0],
                                                              ww=wlww[1])
        response = self.osirix_service_stub.VRControllerSetWLWW(request)
        self.response_check(response)

    @pyosirix_connection_check
    def blending_controller(self) -> osirix.viewer_controller.ViewerController:
        """ The 2D ViewerController instance currently being blended (fused).

        Example usage:
             ```python
                vr_controllers = frontmost_viewer.vr_controllers()
                vr_controller = vr_controllers[0]
                viewer_controller = vr_controller.blending_controller()
             ```
        """
        response = self.osirix_service_stub.VRControllerBlendingController(self.pb2_object)
        self.response_check(response)
        return osirix.viewer_controller.ViewerController(self.osirix_service,
                                                         response.viewer_controller)

    @pyosirix_connection_check
    def viewer_2d(self) -> osirix.viewer_controller.ViewerController:
        """ The 2D ViewerController instance from which the 3D viewer was started.

        Example usage:
             ```python
                vr_controllers = frontmost_viewer.vr_controllers()
                vr_controller = vr_controllers[0]
                viewer_controller = vr_controller.viewer_2d()
             ```
        """
        response = self.osirix_service_stub.VRControllerViewer2D(self.pb2_object)
        self.response_check(response)
        return osirix.viewer_controller.ViewerController(self.osirix_service,
                                                         response.viewer_controller)

    @pyosirix_connection_check
    def roi_volumes(self) -> List[osirix.roi.ROIVolume]:
        """ Obtain references to all volumetric ROIs.

        Returns:
            A list of ROIVolume instances.

        Example usage:
             ```python
                vr_controllers = frontmost_viewer.vr_controllers()  # Get a list of currently open ones.
                if len(vr_controllers) == 0:
                    print("No open VR Controller.  Creating one.")
                    vr_controller = frontmost_viewer.open_vr_viewer(mode="MIP")  # Only other alternative is "VR"
                else:
                    vr_controller = vr_controllers[0]
                roi_volumes = vr_controller.roi_volumes()
                if len(roi_volumes) == 0:
                    print("No valid ROI volumes available")  # Note that ROIs defined on a single slice do not count!

                for roi_volume in roi_volumes:
                    print(f"Displaying ROI volume with name {roi_volume.name}
             ```
        """
        response = self.osirix_service_stub.VRControllerROIVolumes(self.pb2_object)
        self.response_check(response)
        roi_volumes = []
        for roi_volume in response.roi_volumes:
            roi_volumes.append(osirix.roi.ROIVolume(self, self.osirix_service, roi_volume))
        return roi_volumes

    @pyosirix_connection_check
    def hide_roi_volume(self, roi_volume: osirix.roi.ROIVolume):
        """ Ensure that an input ROI is hidden on the 3D display.

        Args:
            roi_volume (osirix.roi.ROIVolume): The ROI volume to hide.

        Example usage:
             ```python
                vr_controllers = frontmost_viewer.vr_controllers()  # Get a list of currently open ones.
                if len(vr_controllers) == 0:
                    print("No open VR Controller.  Creating one.")
                    vr_controller = frontmost_viewer.open_vr_viewer(mode="MIP")  # Only other alternative is "VR"
                else:
                    vr_controller = vr_controllers[0]
                roi_volumes = vr_controller.roi_volumes()
                roi_volume = vr_controller.roi_volumes()[0]
                vr_controller.hide_roi_volume(roi_volume)
             ```
        """
        request = vrcontroller_pb2.VRControllerHideROIVolumeRequest(
            vr_controller=self.pb2_object, roi_volume=roi_volume.pb2_object)
        response = self.osirix_service_stub.VRControllerHideROIVolume(request)
        self.response_check(response)

    @pyosirix_connection_check
    def display_roi_volume(self, roi_volume: osirix.roi.ROIVolume):
        """ Ensure that an input ROI is visible on the 3D display.

        Args:
            roi_volume (osirix.roi.ROIVolume): The ROI volume to make visible.

        Example usage:
             ```python
                vr_controllers = frontmost_viewer.vr_controllers()  # Get a list of currently open ones.
                if len(vr_controllers) == 0:
                    print("No open VR Controller.  Creating one.")
                    vr_controller = frontmost_viewer.open_vr_viewer(mode="MIP")  # Only other alternative is "VR"
                else:
                    vr_controller = vr_controllers[0]
                roi_volumes = vr_controller.roi_volumes()
                roi_volume = vr_controller.roi_volumes()[0]
                vr_controller.display_roi_volume(roi_volume)
             ```
        """
        request = vrcontroller_pb2.VRControllerDisplayROIVolumeRequest(
            vr_controller=self.pb2_object, roi_volume=roi_volume.pb2_object)
        response = self.osirix_service_stub.VRControllerDisplayROIVolume(request)
        self.response_check(response)

    @pyosirix_connection_check
    def needs_display_update(self):
        """ Tell the VRController that it should update its display.

        This is particularly important if you want to see changes to pixel values in real time.

        Example usage:
             ```python
                vr_controllers = frontmost_viewer.vr_controllers()
                vr_controller = vr_controllers[0]
                vr_controller.needs_display_update()
             ```
        """

        response = self.osirix_service_stub.VRControllerNeedsDisplayUpdate(self.pb2_object)
        self.response_check(response)
