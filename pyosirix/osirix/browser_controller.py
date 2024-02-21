import sys
# sys.path.append("./pb2")

# sys.path.append("/Users/admintmun/dev/pyosirix/osirix/pb2")
import osirixgrpc.browsercontroller_pb2 as browsercontroller_pb2
from osirix.exceptions import GrpcException
from typing import Tuple, List
from osirix.dicom import DicomSeries, DicomStudy
from osirix.response_processor import ResponseProcessor

class BrowserController(object):
    """
    Retrives the browser window of Osirix
    """

    def __init__(self, osirixrpc_uid, osirix_service) -> None:
        self.osirix_service = osirix_service
        self.osirixrpc_uid = osirixrpc_uid
        self.response_processor = ResponseProcessor()


    def copy_files_into_database(self, files: List[str]) -> None:
        """
        Copy files into the database of Osirix

        Args:
            files: list of files to copy into database

        Returns:
            None

        """
        request = browsercontroller_pb2.BrowserControllerCopyFilesIfNeededRequest(browser=self.osirixrpc_uid, paths = files)
        response = self.osirix_service.BrowserControllerCopyFilesIfNeeded(request)
        self.response_processor.process_basic_response(response)

    # Check return type of Tuples
    def database_selection(self) -> Tuple[Tuple[DicomStudy,...], Tuple[DicomSeries,...]]:
        """
        Queries the Osirix database for its files

        Returns:
            A Tuple containing two Tuples. The first Tuple contains all the Dicom studies and the second
            Tuple contains all the Dicom series in the database

        """
        response = self.osirix_service.BrowserControllerDatabaseSelection(self.osirixrpc_uid)
        # dicom_study_tuple, dicom_series_tuple = self.response_processor.process_browser_database_selection(response)

        if (response.status.status == 1):

            series_tuple: Tuple[DicomSeries, ...] = ()
            study_tuple: Tuple[DicomStudy, ...] = ()

            for series in response.series:
                series_obj= DicomSeries(series, self.osirix_service)
                series_tuple = series_tuple + (series_obj,)

            for study in response.studies:
                study_obj = DicomStudy(study, self.osirix_service)

                study_tuple = study_tuple + (study_obj,)

            return (study_tuple, series_tuple)
        else:
            raise GrpcException("No response")








