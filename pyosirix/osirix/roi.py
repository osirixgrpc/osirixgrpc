from __future__ import annotations
from typing import Tuple, Dict
import sys

from numpy import ndarray
import numpy as np

import osirixgrpc.viewercontroller_pb2 as viewercontroller_pb2
import osirixgrpc.vrcontroller_pb2 as vrcontroller_pb2
import osirixgrpc.dcmpix_pb2 as dcmpix_pb2
import osirixgrpc.roi_pb2 as roi_pb2
import osirixgrpc.roivolume_pb2 as roivolume_pb2
from osirix.dicom import DicomSeries, DicomStudy, DicomImage
from osirix.response_processor import ResponseProcessor
from osirix.dcm_pix import DCMPix

class ROIVolume:
    """
    A class representing the 3D volume ROI contained within a 3D render window.
    """
    def __init__(self,
                 pb2_object: roivolume_pb2,
                 osirix_service):
        self.pb2_object = pb2_object
        self.osirix_service = osirix_service

    @property
    def texture(self) -> bool:
        """ The texture of the ROI volume as a bool.
        """
        response = self.osirix_service.ROIVolumeTexture(self.pb2_object)
        if response.status == 0:
            warnings.warn("Invalid ROI Volume")
            return None
        return response.texture

    @texture.setter
    def texture(self, texture: bool):
        """ The texture of the ROI volume as a bool.
        """
        request = roivolume_pb2.ROIVolumeSetTextureRequest(roi=self.pb2_object,
                                                           texture=texture)
        response = self.osirix_service.ROIVolumeSetTexture(request)
        if not response.status == 1:
            warnings.warn("Could not set ROIVolume texture")

    @property
    def visible(self) -> bool:
        """ The visibility of the ROI volume as a bool.
        """
        response = self.osirix_service.ROIVolumeVisible(self.pb2_object)
        if response.status == 0:
            warnings.warn("Invalid ROI Volume")
            return None
        return response.visible

    @property
    def name(self) -> str:
        """ The name of the ROI volume.
        """
        response = self.osirix_service.ROIVolumeName(self.pb2_object)
        if response.status == 0:
            warnings.warn("Invalid ROI Volume")
            return None
        return response.name

    @property
    def color(self) -> Tuple[float, float, float]:
        """ The color of the ROI volume as a (r, g, b) tuple (each channel in range 0-1)
        """
        response = self.osirix_service.ROIVolumeColor(self.pb2_object)
        if response.status == 0:
            warnings.warn("Invalid ROI Volume")
            return None
        return response.r, response.g, response.b

    @color.setter
    def color(self, color: Tuple[int, int, int]):
        """ The color of the ROI volume as a (r, g, b) tuple (each channel in range 0-1)
        """
        # Check the input
        if not len(color) == 3:
            raise ValueError("Color must have 3 elements")
        if numpy.any(numpy.array(color) < 0):
            raise ValueError("RGB values must be >= 0")
        if numpy.any(numpy.array(color) > 1):
            raise ValueError("RGB values must be <= 1")

        request = roivolume_pb2.ROIVolumeSetColorRequest(roi=self.pb2_object,
                                                         r=color[0],
                                                         g=color[1],
                                                         b=color[2])
        response = self.osirix_service.ROIVolumeSetColor(request)
        if not response.status == 1:
            warnings.warn("Could not set ROIVolume color")

    def volume(self) -> float:
        """ The volume of the ROI volume

        Returns:
            volume: float
        """
        response = self.osirix_service.ROIVolumeVolume(self.pb2_object)
        if response.status == 0:
            warnings.warn("Invalid ROI Volume")
            return None
        return response.volume

    @property
    def opacity(self) -> float:
        """ The opacity of the ROI volume in the range 0-1
        """
        response = self.osirix_service.ROIVolumeOpacity(self.pb2_object)
        if response.status == 0:
            warnings.warn("Invalid ROI Volume")
            return None
        return response.opacity

    @opacity.setter
    def opacity(self, opacity: float):
        """ The opacity of the ROI volume in the range 0-1
        """
        if opacity < 0 or opacity > 1:
            raise ValueError("Opacity must be in range 0-1")
        request = roivolume_pb2.ROIVolumeSetOpacityRequest(roi=self.pb2_object,
                                                           opacity=opacity)
        response = self.osirix_service.ROIVolumeSetOpacity(request)
        if not response.status == 1:
            warnings.warn("Could not set ROIVolume opacity")

    @property
    def factor(self) -> float:
        """ The factor of the ROI volume in the range 0-1
        """
        response = self.osirix_service.ROIVolumeFactor(self.pb2_object)
        if response.status == 0:
            warnings.warn("Invalid ROI Volume")
            return None
        return response.factor

    @opacity.setter
    def factor(self, factor: float):
        """ The factor of the ROI volume in the range 0-1
        """
        if factor < 0 or factor > 1:
            raise ValueError("Factor must be in range 0-1")
        request = roivolume_pb2.ROIVolumeSetFactorRequest(roi=self.pb2_object,
                                                          factor=factor)
        response = self.osirix_service.ROIVolumeSetFactor(request)
        if not response.status == 1:
            warnings.warn("Could not set ROIVolume factor")

class ROI(object):
    '''
    Class representing the properties and methods to communicate with the Osirix service through
    gRPC for the ROIs in Osirix
    '''
    # osirixrpc_uid = None
    # response_processor = None
    # osirix_service = None

    def __init__(self,
                 osirixrpc_uid,
                 osirix_service):
        self.response_processor = ResponseProcessor()
        self.osirixrpc_uid = osirixrpc_uid
        self.osirix_service = osirix_service


    @property
    def color(self) -> Tuple[int, int, int]:
        """
          Makes a gRPC request to retrieve the color (r, g, b) for the ROI
          Returns:
              Tuple containing the color values (r, g, b) in int
        """
        response_roi_color = self.osirix_service.ROIColor(self.osirixrpc_uid)
        self.response_processor.response_check(response_roi_color)
        self._color = (response_roi_color.r, response_roi_color.g, response_roi_color.b)
        return self._color

    @color.setter
    def color(self, color: Tuple[int, int, int]) -> None:
        """
          Makes a gRPC request to set the color (r, g, b) for the ROI

          Args:
            A Tuple containing the red, green, blue values for color

          Returns:
            None
        """
        r, g, b = color
        request = roi_pb2.ROISetColorRequest(roi=self.osirixrpc_uid, r=r, g=g, b=b)
        response_roi_color = self.osirix_service.ROISetColor(request)
        self.response_processor.response_check(response_roi_color)

    @property
    def name(self) -> str:
        """
          Makes a gRPC request to get the name for the ROI
          Returns:
            str: name
        """
        response_roi_name = self.osirix_service.ROIName(self.osirixrpc_uid)
        self._name = response_roi_name.name
        return self._name

    @name.setter
    def name(self, name : str) -> None:
        """
          Makes a gRPC request to set the name for the ROI

          Args:
            str : name

          Returns:
            None
        """
        request = roi_pb2.ROISetNameRequest(roi=self.osirixrpc_uid, name=name)
        response_roi_name = self.osirix_service.ROISetName(request)
        self.response_processor.response_check(response_roi_name)

    @property
    def opacity(self) -> float:
        """
          Makes a gRPC request to retrieve the opacity for the ROI

          Returns:
            float: opacity
        """

        response_roi_opacity = self.osirix_service.ROIOpacity(self.osirixrpc_uid)
        self._opacity = response_roi_opacity.opacity
        return self._opacity

    @opacity.setter
    def opacity(self, opacity : float) -> None:
        """
          Makes a gRPC request to set the opacity for the ROI

          Args:
            float : opacity

          Returns:
            None
        """
        request = roi_pb2.ROISetOpacityRequest(roi=self.osirixrpc_uid, opacity=opacity)
        response = self.osirix_service.ROISetOpacity(request)
        self.response_processor.response_check(response)

    @property
    def points(self) -> ndarray:
        """
          Makes a gRPC request to retrieve the points for the ROI

          Returns:
            ndarray: points
        """
        response_roi_points = self.osirix_service.ROIPoints(self.osirixrpc_uid)

        points = []
        for i in range(len(response_roi_points.points)):
            points.append([response_roi_points.points[i].x, response_roi_points.points[i].y])
        self._points = np.array(points)

        return self._points

    # TODO
    # @points.setter
    # def points(self, points : ndarray) -> None:
    #     request = roi_pb2.ROISetPointsRequest(roi=self.osirixrpc_uid, point=points)
    #     response = self.osirix_service.SetROIPoints(request)
    #     self.response_processor.process_basic_response(response)

    @property
    def thickness(self) -> float:
        """
          Makes a gRPC request to retrieve the thickness for the ROI

          Returns:
            float: thickness
        """
        response_roi_thickness = self.osirix_service.ROIThickness(self.osirixrpc_uid)
        self._thickness = response_roi_thickness.thickness
        return self._thickness

    @thickness.setter
    def thickness(self, thickness : float) -> None:
        """
          Makes a gRPC request to set the thickness for the ROI

          Args:
            float : thickness

          Returns:
            None
        """
        request = roi_pb2.ROISetThicknessRequest(roi=self.osirixrpc_uid, thickness=thickness)
        response = self.osirix_service.ROISetThickness(request)
        self.response_processor.response_check(response)

    @property
    def pix(self) -> DCMPix:
        """
          Makes a gRPC request to retrieve the DCMPix for the ROI

          Returns:
            DCMPix : pix that ROI is drawn on
        """
        response_roi_pix = self.osirix_service.ROIPix(self.osirixrpc_uid)
        roi_pix = response_roi_pix.pix
        self._pix = DCMPix(roi_pix, self.osirix_service)
        return self._pix

    #TODO Can't see proto message for type
    @property
    # def type(self) -> str:
    #     return self._type

    def centroid(self) -> Tuple[float, float]:
        """
          Makes a gRPC request to retrieve the centroid (x, y) for the ROI

          Returns:
            A Tuple containing centroid information (x, y)
        """
        response = self.osirix_service.ROICentroid(self.osirixrpc_uid)
        return (response.x , response.y)

    def flip_horizontally(self) -> None:
        """
          Makes a gRPC request to flip the ROI horizontally

          Returns:
            None
        """
        response = self.osirix_service.ROIFlipHorizontally(self.osirixrpc_uid)
        self.response_processor.response_check(response)

    def flip_vertically(self) -> None:
        """
          Makes a gRPC request to flip the ROI vertically
          Returns:
            None
        """
        response = self.osirix_service.ROIFlipVertically(self.osirixrpc_uid)
        self.response_processor.response_check(response)

    def roi_area(self) -> float :
        """
          Makes a gRPC request to retrieve the area for the ROI

          Returns:
            float : area of ROI
        """
        response = self.osirix_service.ROIArea(self.osirixrpc_uid)
        return response.area

    def roi_move(self, columns:float, rows:float) -> None:
        """
          Makes a gRPC request to move the ROI by rows and columns

          Args:
            float : columns
            float : rows

          Returns:
            None
        """
        request = roi_pb2.ROIMoveRequest(roi=self.osirixrpc_uid, columns=columns, rows=rows)
        response = self.osirix_service.ROIMove(request)
        self.response_processor.response_check(response)

    def rotate(self, theta:float, center: Tuple[int, int]) -> None:
        """
          Makes a gRPC request to rotate the ROI using theta and center (x, y_

          Args:
            float : theta
            Tuple[int, int]: center

          Returns:
            None
        """
        # centroid_response = self.osirix_service.ROICentroid(self.osirixrpc_uid)
        x, y = center
        request = roi_pb2.ROIRotateRequest(roi=self.osirixrpc_uid, degrees=theta, x=x, y=y)
        response = self.osirix_service.ROIRotate(request)
        self.response_processor.response_check(response)


