""" Provides functionality for the images displayed in a 2D OsiriX viewer.

Example usage:
     ```python
     import osirix
     import matplotlib.pyplot as plt

     viewer = osirix.frontmost_viewer()  # Raises GrpcException error if no viewer is available.
     pix = viewer.cur_dcm()  # Get the currently displayed DCMPix object
     plt.imshow(pix.image, cmap = "gray")  # Display the image data (pix.image is a 2D numpy array)
     plt.show()
     ```
"""

from __future__ import annotations
from typing import Dict, Tuple

from numpy.typing import NDArray
import numpy as np

import osirixgrpc.dcmpix_pb2 as dcmpix_pb2

import osirix
from osirix.base import pyosirix_connection_check


class DCMPix(osirix.base.OsirixBase):
    def __repr__(self):
        return f"DCMPix: " \
               f"{self.slice_location:.2f} " \
               f"{self.shape}"

    @property
    @pyosirix_connection_check
    def is_rgb(self) -> bool:
        """ Is the image data red-green-blue? If `False` must be greyscale.
        """
        response = self.osirix_service_stub.DCMPixIsRGB(self.pb2_object)
        self.response_check(response)
        return response.is_rgb

    @property
    @pyosirix_connection_check
    def slice_location(self) -> float:
        """ The slice location of the image.

        NOTE: It can be more accurate to get the slice location by loading the dicom file via the
        `source_file` property (using pydicom for example), and using the ImagePositionPatient tag.
        """
        response = self.osirix_service_stub.DCMPixSliceLocation(self.pb2_object)
        self.response_check(response)
        return float(response.slice_location)

    @property
    @pyosirix_connection_check
    def orientation(self) -> NDArray:
        """ The orientation of the image.

        NOTE: It can be more accurate to get the slice location by loading the dicom file via the
        `source_file` property (using pydicom for example), and using the ImageOrientationPatient
        tag.
        """
        response = self.osirix_service_stub.DCMPixOrientation(self.pb2_object)
        self.response_check(response)
        orientation = []
        for o in response.orientation:
            orientation.append(float(o))
        return np.array(orientation)

    @property
    @pyosirix_connection_check
    def origin(self) -> Tuple[float, float, float]:
        """ The origin of the image (x, y, z).

        NOTE: It can be more accurate to get the slice location by loading the dicom file via the
        `source_file` property (using pydicom for example), and using the ImagePositionPatient tag.
        """
        response = self.osirix_service_stub.DCMPixOrigin(self.pb2_object)
        self.response_check(response)
        return (float(response.origin_x),
                float(response.origin_y),
                float(response.origin_z))

    @property
    @pyosirix_connection_check
    def pixel_spacing(self) -> Tuple[float, float]:
        """ The pixel spacing of the image (order: rows, columns)
        """
        response = self.osirix_service_stub.DCMPixSpacing(self.pb2_object)
        self.response_check(response)
        return float(response.spacing_rows), float(response.spacing_columns)

    @property
    @pyosirix_connection_check
    def shape(self) -> Tuple[int, int]:
        """ The pixel shape of the image (order: rows, columns)
        """
        response = self.osirix_service_stub.DCMPixShape(self.pb2_object)
        self.response_check(response)
        return int(response.rows), int(response.columns)

    @property
    @pyosirix_connection_check
    def source_file(self) -> str:
        """ The source file of the image on the host machine.
        """
        response = self.osirix_service_stub.DCMPixSourceFile(self.pb2_object)
        self.response_check(response)
        return response.source_file

    @property
    @pyosirix_connection_check
    def image(self) -> NDArray:
        """ The image data as a Numpy array.

        If the image is RGB format, then the shape will be (rows, columns, 4), whereas if the image
        is greyscale format it will be shape (rows, columns) (see `is_rgb` property).
        """
        response = self.osirix_service_stub.DCMPixImage(self.pb2_object)
        self.response_check(response)
        if response.is_argb:
            image_array = np.array(response.image_data_argb).reshape((response.rows,
                                                                      response.columns,
                                                                      4))
        else:
            image_array = np.array(response.image_data_float).reshape((response.rows,
                                                                       response.columns))

        return image_array

    @image.setter
    @pyosirix_connection_check
    def image(self, image_arr: NDArray):
        """ The image data as a Numpy array.

        If the image is RGB format, then the shape will be (rows, columns, 4), whereas if the image
        is greyscale format it will be shape (rows, columns) (see `is_rgb` property).
        """
        is_rgb = self.is_rgb
        if is_rgb:
            request = dcmpix_pb2.DCMPixSetImageRequest(pix=self.pb2_object,
                                                       image_data_argb=image_arr.ravel().tolist())

        else:
            request = dcmpix_pb2.DCMPixSetImageRequest(pix=self.pb2_object,
                                                       image_data_float=image_arr.ravel().tolist())

        response = self.osirix_service_stub.DCMPixSetImage(request)
        self.response_check(response)

    @pyosirix_connection_check
    def compute_roi(self, roi: osirix.roi.ROI) -> Dict:
        """ Compute some statistics from an ROI contained within the image.

        Note that these are calculated internally by OsiriX.  For more refinement on how statistics
        are calculated we suggest that it is better to create your own tools (based on the
        `scipy.stats` library for example).

        Args:
            roi (osirix.roi.ROI): The region of interest from which to compute the statistics.

        Returns:
            A dictionary containing the following key-value pairs: "mean", "std", "min", "max",
                "skewness", "kurtosis"
        """
        request = dcmpix_pb2.DCMPixComputeROIRequest(pix=self.pb2_object, roi=roi.pb2_object)
        response = self.osirix_service_stub.DCMPixComputeROI(request)
        self.response_check(response)
        roi_dict = {
            "mean": response.mean,
            "total": response.total,
            "std_dev": response.std_dev,
            "min": response.min,
            "max": response.max,
            "skewness": response.skewness,
            "kurtosis": response.kurtosis
        }
        return roi_dict

    @pyosirix_connection_check
    def convert_to_bw(self, mode: int = 3) -> None:
        """ Convert the image to greyscale.

        Args:
            mode (int): 0 = use red channel, 1 = use green channel, 2 = use blue channel, and
                3 = merge.
        """
        if mode not in [0, 1, 2, 3]:
            raise ValueError("Mode must 0, 1, 2, or 3")
        request = dcmpix_pb2.DCMPixConvertToBWRequest(pix=self.pb2_object,
                                                      bw_channel=mode)
        response = self.osirix_service_stub.DCMPixConvertToBW(request)
        self.response_check(response)

    @pyosirix_connection_check
    def convert_to_rgb(self, mode: int = 3) -> None:
        """ Convert the image to RGB.

        Args:
            mode (int): 0 = create red channel, 1 = create green channel, 2 = create blue channel,
                and 3 = create all channels.
        """
        request = dcmpix_pb2.DCMPixConvertToRGBRequest(pix=self.pb2_object, rgb_channel=mode)
        response = self.osirix_service_stub.DCMPixConvertToRGB(request)
        self.response_check(response)

    @pyosirix_connection_check
    def get_map_from_roi(self, roi: osirix.roi.ROI) -> NDArray:
        """ Create a mask from an input ROI based on the image.

        Args:
            roi (osirix.roi.ROI): The ROI from which to extract the mask.

        Returns:
            The mask as a 2-dimensional binary array with shape (rows, columns).
        """
        request = dcmpix_pb2.DCMPixGetMapFromROIRequest(pix=self.pb2_object,
                                                        roi=roi.pb2_object)
        response = self.osirix_service_stub.DCMPixGetMapFromROI(request)
        self.response_check(response)
        mask = np.array(response.map).reshape(response.rows, response.columns)
        return mask

    @pyosirix_connection_check
    def get_roi_values(self, roi: osirix.roi.ROI) -> Tuple[NDArray, NDArray, NDArray]:
        """ Extract the pixel values within a region of interest.

        Args:
            roi (osirix.roi.ROI): The ROI from which to extract values.

        Returns:
            The row indices of the extracted values.
            The columns indices of the extracted values.
            The extracted pixel values.
        """
        request = dcmpix_pb2.DCMPixROIValuesRequest(pix=self.pb2_object, roi=roi.pb2_object)
        response = self.osirix_service_stub.DCMPixROIValues(request)
        self.response_check(response)
        rows = np.array(response.row_indices)
        columns = np.array(response.column_indices)
        values = np.array(response.values)
        return rows, columns, values

    @pyosirix_connection_check
    def image_obj(self) -> osirix.dicom.DicomImage:
        """ The `DicomImage` instance from which the image was derived.

        Returns:
            The image instance.
        """
        response = self.osirix_service_stub.DCMPixDicomImage(self.pb2_object)
        self.response_check(response)
        return osirix.dicom.DicomImage(self.osirix_service, response.dicom_image)

    @pyosirix_connection_check
    def series_obj(self) -> osirix.dicom.DicomSeries:
        """ The `DicomSeries` instance from which the image was derived.

        Returns:
            The series instance.
        """
        response = self.osirix_service_stub.DCMPixDicomSeries(self.pb2_object)
        self.response_check(response)
        return osirix.dicom.DicomSeries(self.osirix_service, response.dicom_series)

    @pyosirix_connection_check
    def study_obj(self) -> osirix.dicom.DicomStudy:
        """ The `DicomStudy` instance from which the image was derived.

        Returns:
            The study instance.
        """
        response = self.osirix_service_stub.DCMPixDicomStudy(self.pb2_object)
        self.response_check(response)
        return osirix.dicom.DicomStudy(self.osirix_service, response.dicom_study)
