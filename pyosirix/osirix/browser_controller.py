""" Provides access to core functionality of the OsiriX database.

At present this includes operations:

 - Copy files into the database.
 - Interrogating the user selection of Dicom objects.

 Example usage:
     ```python
     import os
     import osirix

     database = osirix.current_browser()  # Get the current browser instance
     images_path = "/path/to/dicoms"  # Define the location of your images
     database.copy_files_into_database(images_path)  # Load the images (on separate process).
     ```
"""

from typing import Tuple, List

import osirixgrpc.browsercontroller_pb2 as browsercontroller_pb2

from osirix.dicom import DicomSeries, DicomStudy
from osirix.base import OsirixBase


class BrowserController(OsirixBase):
    """ The main OsiriX Dicom database window.

    There should only ever be one, but it is OK to create multiple pyOsiriX instances, they will
    just contiain the same `osirixrpc_uid`.
    """

    def copy_files_into_database(self, files: List[str]) -> None:
        """ Copy files into the Osirix database.

        Note that this will always copy files, rather than copy by link, therefore doubling the
        memory requirements. It is safe to delete the source Dicom data after import, if you wish
        to do so.

        Args:
            files (List[str]): The list of files to copy, as absolute paths.
        """
        request = browsercontroller_pb2.BrowserControllerCopyFilesIfNeededRequest(
            browser=self.osirix_type, paths=files)
        response = self.osirix_service_stub.BrowserControllerCopyFilesIfNeeded(request)
        self.response_check(response)

    def database_selection(self) -> Tuple[List[DicomStudy], List[DicomSeries]]:
        """ Queries the user selection of Dicom images.

        Returns:
            The selected Dicom study instances
            The selected Dicom series instances
        """
        response = self.osirix_service_stub.BrowserControllerDatabaseSelection(self.pb2_object)
        self.response_check(response)

        selected_studies = []
        for study in response.studies:
            selected_studies.append(DicomStudy(self.osirix_service, study))

        selected_series = []
        for series in response.series:
            selected_series.append(DicomSeries(self.osirix_service, series))

        return selected_studies, selected_series
