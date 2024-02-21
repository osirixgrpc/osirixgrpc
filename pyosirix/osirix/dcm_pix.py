from __future__ import annotations
from typing import Tuple, Dict
import sys

from numpy import ndarray
import numpy as np

# sys.path.append("./pb2")
# sys.path.append("/Users/admintmun/dev/pyosirix/osirix/pb2")
import osirixgrpc.viewercontroller_pb2 as viewercontroller_pb2
import osirixgrpc.vrcontroller_pb2 as vrcontroller_pb2
import osirixgrpc.dcmpix_pb2 as dcmpix_pb2
import osirixgrpc.roi_pb2 as roi_pb2
from osirix.dicom import DicomSeries, DicomStudy, DicomImage
from osirix.response_processor import ResponseProcessor

class DCMPix(object):
    '''
    Class representing the properties and methods to communicate with the Osirix service through
    gRPC for DCMPix
    '''

    def __init__(self,
                 osirixrpc_uid,
                 osirix_service):
        self.response_processor = ResponseProcessor()
        self.osirixrpc_uid = osirixrpc_uid
        self.osirix_service = osirix_service

    @property
    def is_rgb(self) -> bool:
        """
        Provides boolean value whether the DCMPix is rgb
        Returns:
            bool: rgb
        """
        response_is_rgb = self.osirix_service.DCMPixIsRGB(self.osirixrpc_uid)

        self.response_processor.response_check(response_is_rgb)

        self._is_rgb = response_is_rgb.is_rgb

        return self._is_rgb

    @property
    def slice_location(self) -> float:
        """
        Provides slice location associated with the DCMPix
        Returns:
            bool: slice location
        """
        response_slice_location = self.osirix_service.DCMPixSliceLocation(self.osirixrpc_uid)

        self.response_processor.response_check(response_slice_location)
        self._slice_location = response_slice_location.slice_location

        return self._slice_location

    @property
    def orientation(self) -> Tuple[float]:
        """
        Provides orientation associated with the DCMPix
        Returns:
            Tuple containing orientations in float
        """
        response_orientation = self.osirix_service.DCMPixOrientation(self.osirixrpc_uid)

        self.response_processor.response_check(response_orientation)

        tuple: Tuple[float, ...] = ()
        for orientation in response_orientation.orientation:
            tuple = tuple + (orientation,)

        self._orientation = tuple

        return self._orientation

    @property
    def origin(self) -> Tuple[float]:
        """
        Provides origin (rows, columns, slices) associated with the DCMPix
        Returns:
            A Tuple containing the origin values (rows, columns, slices) in float
        """
        response_origin = self.osirix_service.DCMPixOrigin(self.osirixrpc_uid)

        self.response_processor.response_check(response_origin)

        self._origin = (response_origin.origin_rows, response_origin.origin_columns, response_origin.origin_slices)

        return self._origin

    @property
    def pixel_spacing(self) -> Tuple[float]:
        """
        Provides pixel spacing in rows and columns associated with the DCMPix
        Returns:
            A tuple containing pixel spacings (rows and columns) in float
        """
        response_spacing = self.osirix_service.DCMPixSpacing(self.osirixrpc_uid)

        self.response_processor.response_check(response_spacing)
        self._pixel_spacing = (response_spacing.spacing_rows, response_spacing.spacing_columns)

        return self._pixel_spacing

    @property
    def shape(self) -> Tuple[int]:
        """
        Provides shape (rows, columns) associated with the DCMPix
        Returns:
            Tuple containing shape (rows, columns) in float
        """
        response_pix_shape = self.osirix_service.DCMPixShape(self.osirixrpc_uid)

        self.response_processor.response_check(response_pix_shape)
        self._shape = (response_pix_shape.rows, response_pix_shape.columns)
        return self._shape

    @property
    def source_file(self) -> str:
        """
         Provides source file associated with the DCMPix
         Returns:
            str: source file for DCMPix
        """
        response_pix_source_file = self.osirix_service.DCMPixSourceFile(self.osirixrpc_uid)

        self.response_processor.response_check(response_pix_source_file)
        self._source_file = response_pix_source_file.source_file

        return self._source_file

    @property
    def image(self) -> ndarray:
        """
          Provides underlying image associated with the DCMPix
          Returns:
            ndarray: image data for DCMPix
        """
        response_pix_image = self.osirix_service.DCMPixImage(self.osirixrpc_uid)

        self.response_processor.response_check(response_pix_image)

        if response_pix_image.is_argb:
            image_array = np.array(response_pix_image.image_data_argb).reshape(response_pix_image.rows, response_pix_image.columns, 4)
            return image_array
        else:
            image_array = np.array(response_pix_image.image_data_float).reshape(response_pix_image.rows, response_pix_image.columns)
            return image_array

        return self._image

    # @image.setter - setter only allows one value so switch to using a method
    def set_image(self, image: ndarray, is_argb: bool) -> None:
        if is_argb:
            request = dcmpix_pb2.DCMPixSetImageRequest(pix=self.osirixrpc_uid, image_data_argb=image)

        else:
            request = dcmpix_pb2.DCMPixSetImageRequest(pix=self.osirixrpc_uid, image_data_float=image)

        response = self.osirix_service.DCMPixSetImage(request)
        print(response)
        self.response_processor.response_check(response)


    def compute_roi(self, roi : ROI) -> Dict[str, float]:
        """
          Makes a gRPC request to compute ROIs of DCMPix and retrieves the statistics for the ROI in a dictionary.

          Examples:

           roi_dict = {
                'mean': ...,
                'total': ...,
                'std_dev': ...,
                'min': ...,
                'max': ...,
                'skewness': ...,
                'kurtosis': ...
            }

          Args:
            ROI: osirixrpc_uid of a ROI

          Returns:
            Dict containing the statistics of the ROI

        """
        request = dcmpix_pb2.DCMPixComputeROIRequest(pix=self.osirixrpc_uid, roi=roi.osirixrpc_uid)
        response = self.osirix_service.DCMPixComputeROI(request)

        self.response_processor.response_check(response)

        roi_dict = {
            'mean': response.mean,
            'total': response.total,
            'std_dev': response.std_dev,
            'min': response.min,
            'max': response.max,
            'skewness': response.skewness,
            'kurtosis': response.kurtosis
        }

        return roi_dict

    def convert_to_bw(self) -> None:
        """
          Makes a gRPC request to convert DCMPix to black-white
          Returns:
            None
        """
        request = dcmpix_pb2.DCMPixConvertToBWRequest(pix = self.osirixrpc_uid, bw_channel = 3)
        response = self.osirix_service.DCMPixConvertToBW(request)
        self.response_processor.response_check(response)

        if (response.status.status == 1):
            pass
        elif (response.status.status == 0):
            # 0 response code is the current overall failure code so there could be many reasons for failures.
            # In this case, if the image is already rgb/bw, it would be 0
            print("Image is already RGB or BW")
        else:
            raise GrpcException("No response")

    def convert_to_rgb(self) -> None:
        """
          Makes a gRPC request to convert DCMPix to red-green-blue
          Returns:
            None
        """
        request = dcmpix_pb2.DCMPixConvertToRGBRequest(pix = self.osirixrpc_uid, rgb_channel = 3)
        response = self.osirix_service.DCMPixConvertToRGB(request)
        self.response_processor.response_check(response)

        if (response.status.status == 1):
            pass
        elif (response.status.status == 0):
            # 0 response code is the current overall failure code so there could be many reasons for failures.
            # In this case, if the image is already rgb/bw, it would be 0
            print("Image is already RGB or BW")
        else:
            raise GrpcException("No response")

    def get_map_from_roi(self, roi : ROI) -> ndarray:
        """
          Makes a gRPC request to retrieve the ROI map for the DCMPix
          Args:
            ROI: osirixrpc_uid of a ROI

          Returns:
            ndarray: ROI map
        """
        request = dcmpix_pb2.DCMPixGetMapFromROIRequest(pix=self.osirixrpc_uid, roi=roi.osirixrpc_uid)
        response = self.osirix_service.DCMPixGetMapFromROI(request)
        self.response_processor.response_check(response)

        roi_map_array = np.array(response.map).reshape(response.rows, response.columns)

        return roi_map_array

    def get_roi_values(self, roi : ROI) -> Tuple[ndarray]:
        """
          Makes a gRPC request to get the ROI values for the DCMPix

          Args:
            ROI: osirixrpc_uid of a ROI

          Returns:
            Tuple containing the ROI values (rows, columns, values) in ndarray
        """
        request = dcmpix_pb2.DCMPixROIValuesRequest(pix=self.osirixrpc_uid, roi=roi.osirixrpc_uid)
        response = self.osirix_service.DCMPixROIValues(request)
        self.response_processor.response_check(response)
        rows = np.array(response.row_indices)
        columns = np.array(response.column_indices)
        values = np.array(response.values)
        roi_values = (rows, columns, values)
        return roi_values
    #TODO
    # Don't see their RPC in osirix.proto but can see response in dcmpix.prot
    def image_obj(self) -> DicomImage:
        """
          Makes a gRPC request to to retrieve the image obj for the DCMPix
          Returns:
              DicomImage: image for DCMPix
        """
        response_pix_dicom_image = self.osirix_service.DCMPixDicomImage(self.osirixrpc_uid)
        return DicomImage(response_pix_dicom_image, self.osirix_service)

    #TODO
    # Don't see their RPC in osirix.proto but can see response in dcmpix.prot
    def series_obj(self) -> DicomSeries:
        """
          Makes a gRPC request to to retrieve the series obj for the DCMPix
          Returns:
              DicomSeries: series for DCMPix
        """
        response_pix_dicom_series = self.osirix_service.DCMPixDicomSeries(self.osirixrpc_uid)
        return DicomSeries(response_pix_dicom_series, self.osirix_service)

    #TODO
    # Don't see their RPC in osirix.proto but can see response in dcmpix.prot
    def study_object(self) -> DicomStudy:
        """
          Makes a gRPC request to to retrieve the study obj for the DCMPix
          Returns:
              DicomStudy: study for DCMPix
        """
        response_pix_dicom_study = self.osirix_service.DCMPixDicomStudy(self.osirixrpc_uid)
        return DicomStudy(response_pix_dicom_study, self.osirix_service)


