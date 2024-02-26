""" Provides functionality for the images displayed in a 2D OsiriX viewer.

"""

from __future__ import annotations
from typing import Dict, Tuple

from numpy.typing import NDArray
import numpy as np

import osirixgrpc.dcmpix_pb2 as dcmpix_pb2

import osirix


class DCMPix(osirix.base.OsirixBase):
    """ Represents a single image displayed within a 2D OsiriX viewer (`ViewerController`)

    """

    @property
    def is_rgb(self) -> bool:
        """ Is the image data red-green-blue? If `False` must be greyscale.
        """
        response = self.osirix_service_stub.DCMPixIsRGB(self.pb2_object)
        self.response_check(response)
        return response.is_rgb

    @property
    def slice_location(self) -> float:
        """ The slice location of the image.

        NOTE: It can be more accurate to get the slice location by loading the dicom file via the
        `source_file` property (using pydicom for example), and using the ImagePositionPatient tag.
        """
        response = self.osirix_service_stub.DCMPixSliceLocation(self.pb2_object)
        self.response_check(response)
        return float(response.slice_location)

    @property
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
    def origin(self) -> Tuple[float, float, float]:
        """ The origin of the image.

        NOTE: It can be more accurate to get the slice location by loading the dicom file via the
        `source_file` property (using pydicom for example), and using the ImagePositionPatient tag.
        """
        response = self.osirix_service_stub.DCMPixOrigin(self.pb2_object)
        self.response_check(response)
        return float(response.origin[0]), float(response.origin[1]), float(response.origin[2])

    @property
    def pixel_spacing(self) -> Tuple[float, float]:
        """ The pixel spacing of the image (order: rows, columns)
        """
        response = self.osirix_service_stub.DCMPixSpacing(self.pb2_object)
        self.response_check(response)
        return float(response.spacing_rows), float(response.spacing_columns)

    @property
    def shape(self) -> Tuple[int, int]:
        """ The pixel shape of the image (order: rows, columns)
        """
        response = self.osirix_service_stub.DCMPixShape(self.pb2_object)
        self.response_check(response)
        return int(response.rows), int(response.columns)

    @property
    def source_file(self) -> str:
        """ The source file of the image on the host machine.
        """
        response = self.osirix_service_stub.DCMPixSourceFile(self.pb2_object)
        self.response_check(response)
        return response.source_file

    @property
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

    def set_image(self, image: NDArray, is_argb: bool) -> None:
        """ Set the pixel data of an image.

        Note that care must be taken the shape of the input data matches that of the current image.

        Args:
             image (NDArray): The pixel data with shape (rows, columns, 4) if `is_argb` is `True`,
                (rows, columns) otherwise.
             is_argb (bool): Whether the data is in ARGB format or not.
        """
        if is_argb:
            request = dcmpix_pb2.DCMPixSetImageRequest(pix=self.pb2_object,
                                                       image_data_argb=image.ravel().tolist())

        else:
            request = dcmpix_pb2.DCMPixSetImageRequest(pix=self.pb2_object,
                                                       image_data_float=image.ravel().tolist())
        response = self.osirix_service_stub.DCMPixSetImage(request)
        self.response_check(response)

    def compute_roi(self, roi: osirix.roi.ROI) -> Dict:
        """ Compute some statistics from an ROI contained within the image.

        Note that these are calculated internally by OsiriX.  For more refinement on how statistics
        are calculated we suggest that it is better to create your own tools (based on the
        `scipy.stats` library for example).

        Args:
            roi (osirix.roi.ROI): The region of interest from which to compute the statistics.

        Returns:
            The following statistics:
                - "mean"
                - "total"
                - "std_dev"
                - "min"
                - "max"
                - "skewness"
                - "kurtosis"
        """
        request = dcmpix_pb2.DCMPixComputeROIRequest(pix=self.pb2_object, roi=roi.pb2_object)
        response = self.osirix_service_stub.DCMPixComputeROI(request)
        self.response_check(response)
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

    def convert_to_bw(self, mode: int = 3) -> None:
        """ Convert the image to greyscale.

        Args:
            mode (int): 0 = use red channel, 1 = use green channel, 2 = use blue channel, and
                3 = merge.
        """
        if mode not in [0, 1, 2, 3]:
            raise ValueError('Mode must 0, 1, 2, or 3')
        request = dcmpix_pb2.DCMPixConvertToBWRequest(pix=self.pb2_object,
                                                      bw_channel=mode)
        response = self.osirix_service_stub.DCMPixConvertToBW(request)
        self.response_check(response)

    def convert_to_rgb(self, mode: int = 3) -> None:
        """ Convert the image to RGB.

        Args:
            mode (int): 0 = create red channel, 1 = create green channel, 2 = create blue channel,
                and 3 = create all channels.
        """
        request = dcmpix_pb2.DCMPixConvertToRGBRequest(pix=self.pb2_object, rgb_channel=mode)
        response = self.osirix_service_stub.DCMPixConvertToRGB(request)
        self.response_check(response)

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

    def image_obj(self) -> osirix.dicom.DicomImage:
        """ The `DicomImage` instance from which the image was derived.

        Returns:
            The image instance.
        """
        response = self.osirix_service_stub.DCMPixDicomImage(self.pb2_object)
        self.response_check(response)
        return osirix.dicom.DicomImage(self.osirix_service, response.dicom_image)

    def series_obj(self) -> osirix.dicom.DicomSeries:
        """ The `DicomSeries` instance from which the image was derived.

        Returns:
            The series instance.
        """
        response = self.osirix_service_stub.DCMPixDicomSeries(self.pb2_object)
        self.response_check(response)
        return osirix.dicom.DicomSeries(self.osirix_service, response.dicom_series)

    def study_object(self) -> osirix.dicom.DicomStudy:
        """ The `DicomStudy` instance from which the image was derived.

        Returns:
            The study instance.
        """
        response = self.osirix_service_stub.DCMPixDicomStudy(self.pb2_object)
        self.response_check(response)
        return osirix.dicom.DicomStudy(self.osirix_service, response.dicom_study)
