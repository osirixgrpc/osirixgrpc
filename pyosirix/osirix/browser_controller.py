""" Provides access to core functionality of the OsiriX database.

There should only ever be one, but it is OK to create multiple pyOsiriX instances, they will
just contiain the same `osirixrpc_uid`.

Example usage:
    ```python
    import osirix

    database = osirix.current_browser()  # Get the current browser instance
    images_path = "/path/to/dicoms"  # Define the location of the images
    database.copy_files_into_database(images_path)  # Load the images (on separate process).
    ```
"""

from __future__ import annotations
from typing import Tuple, List

import numpy as np
from numpy.typing import NDArray

import osirixgrpc.browsercontroller_pb2 as browsercontroller_pb2

import osirix
from osirix.base import pyosirix_connection_check


class BrowserController(osirix.base.OsirixBase):
    def __repr__(self):
        return "BrowserController"

    @pyosirix_connection_check
    def copy_files_into_database(self, files: List[str]) -> None:
        """ Copy files into the Osirix database.

        Note that this will always copy files, rather than copy by link, therefore doubling the
        memory requirements. It is safe to delete the source Dicom data after import, if you wish
        to do so.

        Args:
            files (List[str]): The list of files to copy, as absolute paths.
        """
        request = browsercontroller_pb2.BrowserControllerCopyFilesIfNeededRequest(
            browser=self.pb2_object, paths=files)
        response = self.osirix_service_stub.BrowserControllerCopyFilesIfNeeded(request)
        self.response_check(response)

    @pyosirix_connection_check
    def database_selection(self) -> Tuple[List[osirix.dicom.DicomStudy],
                                          List[osirix.dicom.DicomSeries]]:
        """ Queries the user selection of Dicom images.

        Returns:
            The selected Dicom study instances
            The selected Dicom series instances
        """
        response = self.osirix_service_stub.BrowserControllerDatabaseSelection(self.pb2_object)
        self.response_check(response)

        selected_studies = []
        for study in response.studies:
            selected_studies.append(osirix.dicom.DicomStudy(self.osirix_service, study))

        selected_series = []
        for series in response.series:
            selected_series.append(osirix.dicom.DicomSeries(self.osirix_service, series))

        return selected_studies, selected_series

    @pyosirix_connection_check
    def open_viewer_2d(self, dicom_images: NDArray) -> osirix.viewer_controller.ViewerController:
        """ Open a 2D viewer for an array of osirix.dicom.DicomImage instances.

        Note that images will be loaded in the order in which they are presented as input here.
        Use the properties of DicomImage to ensure that they are loaded in order (e.g. sorted by
        the `slice_location` or `instance_number` properties).

        Args:
            dicom_images (NDArray): The array of images to display. Must be one dimensional and
                have at least one element.

        Returns:
            The resulting new viewer controller.

        Raises:
            ValueError: When the number of images in `dicom_images` is less than 1.
            ValueError: When `dicom_images` is multidimensional.
            ValueError: When instances other than DicomImage are provided in `dicom_images`.
        """
        dicom_images = np.array(dicom_images)
        if len(dicom_images) <= 0:
            raise ValueError("The number of input images must be one or greater.")
        if not dicom_images.ndim == 1:
            raise ValueError("The input array must be one dimensional.")
        for dicom_image in dicom_images:
            if not isinstance(dicom_image, osirix.dicom.DicomImage):
                raise ValueError("Only instances of DicomImage are permitted as input.")

        dicom_images = [dicom_image.pb2_object for dicom_image in dicom_images]
        frames = [browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest.FrameImages(
            images=dicom_images)]
        request = browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest(
            browser=self.pb2_object, frames=frames, movie=False)
        response = self.osirix_service_stub.BrowserControllerOpenViewerFromImages(request)
        self.response_check(response)
        return osirix.viewer_controller.ViewerController(self.osirix_service, response.viewer)

    @pyosirix_connection_check
    def open_viewer_4d(self, dicom_images: NDArray) -> osirix.viewer_controller.ViewerController:
        """ Open a 4D viewer for an array of arrays of osirix.dicom.DicomImage instances.

        As per the `open_viewer_2d` method, each frames will be presented in the order in which
        the DicomImage instances are presented to the function.

        Note that no pre-checks are performed to ensure OsiriX can actually display the data (e.g.
        same slice locations are provided for each frame).

        Args:
            dicom_images (NDArray): An array of shape (N_frames, N_images).

        Returns:
            The resulting new viewer controller.

        Raises:
            ValueError: When N_frames is less than 2.
            ValueError: When N_images is less than 1.
            ValueError: When `dicom_images` shape is not 2-dimensional.
            ValueError: When instances other than DicomImage are provided in the `dicom_images`.
        """
        dicom_images = np.array(dicom_images)
        if not dicom_images.ndim == 2:
            raise ValueError("The input array must be two dimensional.")

        n_frames, n_images = dicom_images.shape
        if not n_frames > 1:
            raise ValueError("Number of input frames must be > 1. "
                             "For single frame use `open_viewer_2d`.")
        if not n_images > 0:
            raise ValueError("Number of input images must be 1 or greater.")

        frames = []
        for i in range(n_frames):
            frame = []
            for j in range(n_images):
                dicom_image = dicom_images[i, j]
                if not isinstance(dicom_image, osirix.dicom.DicomImage):
                    raise ValueError("Only instances of DicomImage are permitted as input.")
                frame.append(dicom_image.pb2_object)
            frames.append(
                browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest.FrameImages(
                    images=frame))

        request = browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest(
            browser=self.pb2_object, frames=frames, movie=True)
        response = self.osirix_service_stub.BrowserControllerOpenViewerFromImages(request)
        self.response_check(response)
        return osirix.viewer_controller.ViewerController(self.osirix_service, response.viewer)
