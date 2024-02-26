""" Functionality for the regions of interest in 2D (`ROI`) and 3D (`ROIVolume`) viewers.

"""

from __future__ import annotations

import warnings
from typing import Tuple

import numpy as np
from numpy.typing import NDArray

import osirixgrpc.roi_pb2 as roi_pb2
import osirixgrpc.roivolume_pb2 as roivolume_pb2

import osirix


class ROIVolume(osirix.base.OsirixBase):
    """ Represents a single volumetric region of interest in a 3D viewer (`VRController`)

    """
    @property
    def texture(self) -> bool:
        """ Whether the volume ROI is textured
        """
        response = self.osirix_service_stub.ROIVolumeTexture(self.pb2_object)
        self.response_check(response)
        return response.texture

    @texture.setter
    def texture(self, texture: bool):
        """ Whether the volume ROI is textured
        """
        request = roivolume_pb2.ROIVolumeSetTextureRequest(roi=self.pb2_object,
                                                           texture=texture)
        response = self.osirix_service_stub.ROIVolumeSetTexture(request)
        self.response_check(response)

    @property
    # TODO: Can we define a set_visible method?
    def visible(self) -> bool:
        """ Whether the volume ROI is visible in the 3D viewer
        """
        response = self.osirix_service_stub.ROIVolumeVisible(self.pb2_object)
        self.response_check(response)
        return response.visible

    @property
    def name(self) -> str:
        """ The name of the ROI volume.
        """
        response = self.osirix_service_stub.ROIVolumeName(self.pb2_object)
        self.response_check(response)
        return response.name

    @property
    def color(self) -> Tuple[float, float, float]:
        """ The color of the volume ROI as a (r, g, b) tuple (each channel in range 0-1)
        """
        response = self.osirix_service_stub.ROIVolumeColor(self.pb2_object)
        self.response_check(response)
        return response.r, response.g, response.b

    @color.setter
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
    def opacity(self) -> float:
        """ The opacity of the ROI volume in the range 0-1
        """
        response = self.osirix_service_stub.ROIVolumeOpacity(self.pb2_object)
        self.response_check(response)
        return float(response.opacity)

    @opacity.setter
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
    def factor(self) -> float:
        """ The factor of the ROI volume in the range 0-1
        """
        response = self.osirix_service_stub.ROIVolumeFactor(self.pb2_object)
        self.response_check(response)
        return float(response.factor)

    @factor.setter
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
    @property
    def color(self) -> Tuple[int, int, int]:
        """ The color of the volume ROI as a (r, g, b) tuple (each channel in range 0-255)
        """
        response = self.osirix_service_stub.ROIColor(self.pb2_object)
        self.response_check(response)
        return response.r, response.g, response.b

    @color.setter
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
    def name(self) -> str:
        """ The name of the ROI
        """
        response = self.osirix_service_stub.ROIName(self.pb2_object)
        self.response_check(response)
        return response.name

    @name.setter
    def name(self, name: str) -> None:
        """ The name of the ROI
        """
        request = roi_pb2.ROISetNameRequest(roi=self.pb2_object, name=name)
        response = self.osirix_service_stub.ROISetName(request)
        self.response_check(response)

    @property
    def opacity(self) -> float:
        """ The opacity of the ROI, ranging from 0 (transparent) to 1 (opaque)
        """
        response = self.osirix_service_stub.ROIOpacity(self.pb2_object)
        self.response_check(response)
        return response.opacity

    @opacity.setter
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
    def thickness(self) -> float:
        """ The line thickness (in points) of any polygon-based ROI.
        """
        response = self.osirix_service_stub.ROIThickness(self.pb2_object)
        self.response_check(response)
        return response.thickness

    @thickness.setter
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
    def pix(self) -> osirix.dcm_pix.DCMPix:
        """ The DCMPix instance coupled with the ROI. This should be the one on which it is drawn.
        """
        response = self.osirix_service_stub.ROIPix(self.pb2_object)
        self.response_check(response)
        return osirix.dcm_pix.DCMPix(self.osirix_service, response.pix)

    @property
    def itype(self) -> int:
        """ The ROI type
        """
        response = self.osirix_service_stub.ROIIType(self.pb2_object)
        self.response_check(response)
        return int(response.itype)

    def centroid(self) -> Tuple[float, float]:
        # TODO: Check what this is returning.  Is it image or pixel coordinates.  What order?
        """ The centroid of the ROI
        """
        response = self.osirix_service_stub.ROICentroid(self.pb2_object)
        self.response_check(response)
        return response.x, response.y

    def flip_horizontally(self) -> None:
        """ Flip the ROI horizontally
        """
        response = self.osirix_service_stub.ROIFlipHorizontally(self.pb2_object)
        self.response_check(response)

    def flip_vertically(self) -> None:
        """ Flip the ROI vertically
        """
        response = self.osirix_service_stub.ROIFlipVertically(self.pb2_object)
        self.response_check(response)

    def roi_area(self) -> float:
        # TODO: Is this in cm2?
        """ The area of the ROI in squared centimeters.
        """
        response = self.osirix_service_stub.ROIArea(self.pb2_object)
        self.response_check(response)
        return response.area

    def roi_move(self, columns: int, rows: int) -> None:
        # TODO: Ensure this is correct.
        """ Move the ROI by a specified number of columns and rows.

        Args:
            columns (int): The number of columns to move (right = positive, left = negative)
            rows (int): The number of rows to move (up = positive, down = negative)
        """
        request = roi_pb2.ROIMoveRequest(roi=self.pb2_object, columns=columns, rows=rows)
        response = self.osirix_service_stub.ROIMove(request)
        self.response_check(response)

    def rotate(self, theta: float, center: Tuple[float, float] = None) -> None:
        # TODO: Check the direction of theta is correct and that center works.
        """ Rotate the ROI by angle theta, about a given

        Args:
            theta (float): The angle by which to rotate (in degrees). Positive is clockwise.
            center (Tuple[float, float]): The position (column, row) about which to rotate.
                These can be non-integer values. If `None`, then rotation is about the centroid of
                the ROI. Default is `None`.
        """
        if center is None:
            center = self.centroid()
        column, row = center
        request = roi_pb2.ROIRotateRequest(roi=self.pb2_object, degrees=theta, x=column, y=row)
        response = self.osirix_service_stub.ROIRotate(request)
        self.response_check(response)
