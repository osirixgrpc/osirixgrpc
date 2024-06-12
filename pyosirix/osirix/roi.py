""" Functionality for the regions of interest in 2D (`ROI`) and 3D (`ROIVolume`) viewers.

The following `ROI` types are available in pyOsiriX, seperated into 2 core groups:

1. Brush ROIs: Described by a 2D array of boolean values (0 = outside ROI, 1 = within ROI).

    - tPlain: The only brush ROI type.

2. Point-based ROIs: Described by a set of N 2-element vertices as a shape (N, 2) array.

    - tMeasure: A ruler measurement. N = 2.
    - tROI: A square ROI. N = 4. Created by rectangle.
    - tOval: An oval-based ROI. No limit on N. Created by rectangle.
    - tOPolygon: An open polygon. No limit on N.
    - tCPolygon: A closed polygon. No limit on N.
    - tAngle: An angle measurement. N = 3.
    - tText: A text box. Created by rectangle.
    - tArrow: An arrow. N = 2 (arrow head then tail).
    - tPencil: A closed polygon. No limit it N.
    - t2DPoint: A single point ROI. Created by rectangle.
    - tAxis: An axis-based ROI for bi-dimensional measurement. N = 4.
    - tDynAngle: The angle between two lines. N = 4.
    - tTAGT: A pair of oriented perpendicular lines for measuring distance. N = 6.
    - tBall: A circular ROI representing a slice of a 3D ball ROI. No limit on N.
        It is not possible to create a new tBall ROI with pyOsiriX.
    - tOvalAngle: An oval with an additional angle specifier. No limit on N. Created by
        rectangle.

Example usage:
    ```python
    import osirix
    import matplotlib.pyplot as plt

    viewer = osirix.frontmost_viewer()  # Raises GrpcException error if no viewer is available.
    rois = viewer.selected_rois()  # Get the currently selected ROI object.
    if len(rois) == 0:
        raise ValueError("No ROIs found.")
    roi = rois[0]
    roi_type = roi.itypes()[roi.itype]  # Get the selected ROI type.
    if roi_type == "tPlain":
        raise ValueError("Cannot plot mask (brush) ROI vertices")
    plt.plot(roi.points[:, 0], roi.points[:, 1], "ko")  # Plot the ROI vertices.
    plt.show()
    ```
"""

from __future__ import annotations

import warnings
from typing import Tuple, Dict

import numpy as np
from numpy.typing import NDArray

import osirixgrpc.roi_pb2 as roi_pb2
import osirixgrpc.roivolume_pb2 as roivolume_pb2

import osirix
from osirix.base import pyosirix_connection_check


class ROIVolume(osirix.base.OsirixBase):
    """ Represents a single volumetric region of interest in a 3D viewer (`VRController`)

    """
    def __init__(self, vr_controller: osirix.vr_controller.VRController,
                 osirix_service: osirix.osirix_utilities.OsirixService, *args, **kwargs):
        super(ROIVolume, self).__init__(osirix_service, *args, **kwargs)
        self._vr_controller = vr_controller

    def __repr__(self):
        return f"ROIVolume: " \
               f"{self.name}"

    @property
    @pyosirix_connection_check
    def vr_controller(self) -> osirix.vr_controller.VRController:
        """ The 3D volume render window in which this ROI is shown.
        """
        return self._vr_controller

    @property
    @pyosirix_connection_check
    def texture(self) -> bool:
        """ Whether the volume ROI is textured
        """
        response = self.osirix_service_stub.ROIVolumeTexture(self.pb2_object)
        self.response_check(response)
        return response.texture

    @texture.setter
    @pyosirix_connection_check
    def texture(self, texture: bool):
        """ Whether the volume ROI is textured
        """
        request = roivolume_pb2.ROIVolumeSetTextureRequest(roi=self.pb2_object,
                                                           texture=texture)
        response = self.osirix_service_stub.ROIVolumeSetTexture(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def visible(self) -> bool:
        """ Whether the volume ROI is visible in the 3D viewer
        """
        response = self.osirix_service_stub.ROIVolumeVisible(self.pb2_object)
        self.response_check(response)
        return response.visible

    @visible.setter
    @pyosirix_connection_check
    def visible(self, set_visible: bool):
        """ Whether the volume ROI is visible in the 3D viewer
        """
        if self.visible and not set_visible:
            self.vr_controller.hide_roi_volume(self)
        if not self.visible and set_visible:
            self.vr_controller.display_roi_volume(self)

    @property
    @pyosirix_connection_check
    def name(self) -> str:
        """ The name of the ROI volume.
        """
        response = self.osirix_service_stub.ROIVolumeName(self.pb2_object)
        self.response_check(response)
        return response.name

    @property
    @pyosirix_connection_check
    def color(self) -> Tuple[float, float, float]:
        """ The color of the volume ROI as a (r, g, b) tuple (each channel in range 0-1)
        """
        response = self.osirix_service_stub.ROIVolumeColor(self.pb2_object)
        self.response_check(response)
        return response.r, response.g, response.b

    @color.setter
    @pyosirix_connection_check
    def color(self, color: Tuple[float, float, float]):
        """ The color of the volume ROI as a (r, g, b) tuple (each channel in range 0-1)
        """
        r, g, b = color
        if r < 0 or r > 1:
            r = np.clip(r, 0, 1)
            warnings.warn(f"Red color outside range 0 - 1. Clipping to {r}")
        if g < 0 or g > 1:
            g = np.clip(g, 0, 1)
            warnings.warn(f"Green color outside range 0 - 1. Clipping to {g}")
        if b < 0 or b > 1:
            b = np.clip(b, 0, 1)
            warnings.warn(f"Blue color outside range 0 - 1. Clipping to {b}")
        request = roivolume_pb2.ROIVolumeSetColorRequest(roi=self.pb2_object, r=r, g=g, b=b)
        response = self.osirix_service_stub.ROIVolumeSetColor(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def opacity(self) -> float:
        """ The opacity of the ROI volume in the range 0-1
        """
        response = self.osirix_service_stub.ROIVolumeOpacity(self.pb2_object)
        self.response_check(response)
        return float(response.opacity)

    @opacity.setter
    @pyosirix_connection_check
    def opacity(self, opacity: float):
        """ The opacity of the ROI volume in the range 0-1
        """
        if opacity < 0 or opacity > 1:
            opacity = np.clip(opacity, 0, 1)
            warnings.warn(f"Opacity outside range 0 - 1. Clipping to {opacity}")
        request = roivolume_pb2.ROIVolumeSetOpacityRequest(roi=self.pb2_object,
                                                           opacity=opacity)
        response = self.osirix_service_stub.ROIVolumeSetOpacity(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def factor(self) -> float:
        """ The factor of the ROI volume in the range 0-1
        """
        response = self.osirix_service_stub.ROIVolumeFactor(self.pb2_object)
        self.response_check(response)
        return float(response.factor)

    @factor.setter
    @pyosirix_connection_check
    def factor(self, factor: float):
        """ The factor of the ROI volume in the range 0-1
        """
        if factor < 0 or factor > 1:
            factor = np.clip(factor, 0, 1)
            warnings.warn(f"Factor outside range 0 - 1. Clipping to {factor}")
        request = roivolume_pb2.ROIVolumeSetFactorRequest(roi=self.pb2_object,
                                                          factor=factor)
        response = self.osirix_service_stub.ROIVolumeSetFactor(request)
        self.response_check(response)

    @pyosirix_connection_check
    def volume(self) -> float:
        """ The volume of the ROI

        Returns:
            The volume of the 3D ROI (in millilitres).
        """
        response = self.osirix_service_stub.ROIVolumeVolume(self.pb2_object)
        self.response_check(response)
        return float(response.volume)


class ROI(osirix.base.OsirixBase):
    """ Represents a single region of interest in a 2D viewer (`ViewerController`)

    """
    def __repr__(self):
        return f"ROI: " \
               f"{self.name}"

    @classmethod
    def itypes(cls, reverse_order: bool = False) -> Dict:
        """ A map between the integer ROI type (itype) and a text descriptor.

        Args:
            reverse_order (bool): If `False` then the mapping is provided in the form
                `{itype: descriptor}` else it is returned in reverse order: `{descriptor: itype}`.

        Returns:
            A mapping between ROI itype and textual descriptor.
        """
        mapping = {5: "tMeasure",
                   6: "tROI",
                   9: "tOval",
                   10: "tOPolygon",
                   11: "tCPolygon",
                   12: "tAngle",
                   13: "tText",
                   14: "tArrow",
                   15: "tPencil",
                   19: "t2DPoint",
                   20: "tPlain",
                   26: "tAxis",
                   27: "tDynAngle",
                   29: "tTAGT",
                   30: "tBall",
                   31: "tOvalAngle"}
        if reverse_order:
            mapping = {value: key for key, value in mapping.items()}
        return mapping

    @property
    @pyosirix_connection_check
    def color(self) -> Tuple[int, int, int]:
        """ The color of the volume ROI as a (r, g, b) tuple (each channel in range 0-255)
        """
        response = self.osirix_service_stub.ROIColor(self.pb2_object)
        self.response_check(response)
        return response.r, response.g, response.b

    @color.setter
    @pyosirix_connection_check
    def color(self, color: Tuple[int, int, int]) -> None:
        """ The color of the volume ROI as a (r, g, b) tuple (each channel in range 0-255)
        """
        r, g, b = color
        if r < 0 or r > 255:
            r = np.clip(r, 0, 255)
            warnings.warn(f"Red color outside range 0 - 255. Clipping to {r}")
        if g < 0 or g > 255:
            g = np.clip(g, 0, 255)
            warnings.warn(f"Green color outside range 0 - 255. Clipping to {g}")
        if b < 0 or b > 255:
            b = np.clip(b, 0, 255)
            warnings.warn(f"Blue color outside range 0 - 255. Clipping to {b}")
        request = roi_pb2.ROISetColorRequest(roi=self.pb2_object, r=r, g=g, b=b)
        response = self.osirix_service_stub.ROISetColor(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def name(self) -> str:
        """ The name of the ROI
        """
        response = self.osirix_service_stub.ROIName(self.pb2_object)
        self.response_check(response)
        return response.name

    @name.setter
    @pyosirix_connection_check
    def name(self, name: str) -> None:
        """ The name of the ROI
        """
        request = roi_pb2.ROISetNameRequest(roi=self.pb2_object, name=name)
        response = self.osirix_service_stub.ROISetName(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def opacity(self) -> float:
        """ The opacity of the ROI, ranging from 0 (transparent) to 1 (opaque)
        """
        response = self.osirix_service_stub.ROIOpacity(self.pb2_object)
        self.response_check(response)
        return response.opacity

    @opacity.setter
    @pyosirix_connection_check
    def opacity(self, opacity: float) -> None:
        """ The opacity of the ROI, ranging from 0 (transparent) to 1 (opaque)
        """
        if opacity < 0 or opacity > 1:
            opacity = np.clip(opacity, 0, 1)
            warnings.warn(f"Opacity outside range 0 - 1. Clipping to {opacity}")
        request = roi_pb2.ROISetOpacityRequest(roi=self.pb2_object, opacity=opacity)
        response = self.osirix_service_stub.ROISetOpacity(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def points(self) -> NDArray:
        """ The vertices of any polygon-based ROI. An array with shape [N, 2].
        """
        response = self.osirix_service_stub.ROIPoints(self.pb2_object)
        self.response_check(response)
        points = []
        for i in range(len(response.points)):
            points.append([response.points[i].x, response.points[i].y])
        return np.array(points)

    @points.setter
    @pyosirix_connection_check
    def points(self, points: NDArray) -> None:
        """ The vertices of any polygon-based ROI. An array with shape [N, 2].
        """
        if points.ndim != 2:
            raise ValueError("Input points must have shape [N, 2]")
        if points.shape[1] != 2:
            raise ValueError("Input points must have shape [N, 2]")
        requested_points = []
        for i in range(points.shape[0]):
            requested_points.append(roi_pb2.ROISetPointsRequest.Point2D(x=points[i, 0],
                                                                        y=points[i, 1]))
        request = roi_pb2.ROISetPointsRequest(roi=self.pb2_object, points=requested_points)
        response = self.osirix_service_stub.ROISetPoints(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def thickness(self) -> float:
        """ The line thickness (in points) of any polygon-based ROI.
        """
        response = self.osirix_service_stub.ROIThickness(self.pb2_object)
        self.response_check(response)
        return response.thickness

    @thickness.setter
    @pyosirix_connection_check
    def thickness(self, thickness: float) -> None:
        """ The line thickness (in points) of any polygon-based ROI.
        """
        if thickness < 0:
            thickness = 0
            warnings.warn(f"Thickness < 0. Clipping to {thickness}")
        request = roi_pb2.ROISetThicknessRequest(roi=self.pb2_object, thickness=thickness)
        response = self.osirix_service_stub.ROISetThickness(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def pix(self) -> osirix.dcm_pix.DCMPix:
        """ The DCMPix instance coupled with the ROI. This should be the one on which it is drawn.
        """
        response = self.osirix_service_stub.ROIPix(self.pb2_object)
        self.response_check(response)
        return osirix.dcm_pix.DCMPix(self.osirix_service, response.pix)

    @property
    @pyosirix_connection_check
    def itype(self) -> int:
        # TODO: We need to more than provide an integer here. It should be a text description.
        """ The ROI type as an integer
        """
        response = self.osirix_service_stub.ROIIType(self.pb2_object)
        self.response_check(response)
        return int(response.itype)

    @property
    @pyosirix_connection_check
    def stype(self) -> str:
        """ The type of the ROI as a string """
        return self.itypes()[self.itype]

    @pyosirix_connection_check
    def delete(self) -> None:
        """ Delete the ROI.  This cannot be undone!
        """
        response = self.osirix_service_stub.ROIDelete(self.pb2_object)
        self.response_check(response)

    @pyosirix_connection_check
    def centroid(self) -> Tuple[float, float]:
        """ The centroid of the ROI in format (column, row). Non-integer values are permitted.
        """
        response = self.osirix_service_stub.ROICentroid(self.pb2_object)
        self.response_check(response)
        return response.x, response.y

    @pyosirix_connection_check
    def flip_horizontally(self) -> None:
        """ Flip the ROI horizontally
        """
        response = self.osirix_service_stub.ROIFlipHorizontally(self.pb2_object)
        self.response_check(response)

    @pyosirix_connection_check
    def flip_vertically(self) -> None:
        """ Flip the ROI vertically
        """
        response = self.osirix_service_stub.ROIFlipVertically(self.pb2_object)
        self.response_check(response)

    @pyosirix_connection_check
    def roi_area(self) -> float:
        """ The area of the ROI in squared centimeters.
        """
        response = self.osirix_service_stub.ROIArea(self.pb2_object)
        self.response_check(response)
        return response.area

    @pyosirix_connection_check
    def roi_move(self, columns: int, rows: int) -> None:
        # TODO: This could be float, but need to change the protocol definition.
        """ Move the ROI by a specified number of columns and rows.

        Args:
            columns (int): The number of columns to move.
                positive = left &rarr; right, negative = right &rarr; left.
            rows (int): The number of rows to move.
                positive = downwards, negative = upwards.
        """
        request = roi_pb2.ROIMoveRequest(roi=self.pb2_object, columns=columns, rows=rows)
        response = self.osirix_service_stub.ROIMove(request)
        self.response_check(response)

    @pyosirix_connection_check
    def rotate(self, theta: float, center: Tuple[float, float] = None) -> None:
        """ Rotate the ROI by angle theta, about a given

        Args:
            theta (float): The angle by which to rotate (in degrees). Positive is clockwise.
            center (Tuple[float, float]): The position (column, row) about which to rotate.
                These can be non-integer values. If `None`, then rotation is about the centroid of
                the ROI.
        """
        if center is None:
            center = self.centroid()
        column, row = center
        request = roi_pb2.ROIRotateRequest(roi=self.pb2_object, degrees=theta, x=column, y=row)
        response = self.osirix_service_stub.ROIRotate(request)
        self.response_check(response)
