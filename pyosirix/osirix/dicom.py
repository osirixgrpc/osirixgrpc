""" Classes that represent the core objects within the OsiriX database.

Example usage:
    ```python
    import osirix
    from osirix.dicom import DicomStudy, DicomSeries

    database = osirix.current_browser()  # Get the current browser instance
    studies, series = database.database_selection()  # Get the current selection by the user
    for study in studies:
        print(f"This is a DicomStudy instance with name {obj.study_name}")
    for serie in series:
        print(f"This is a DicomSeries instance with description {obj.series_description}")
    ```
"""

from __future__ import annotations

import datetime
from typing import List

import osirix
from osirix.base import pyosirix_connection_check


class DicomStudy(osirix.base.OsirixBase):
    """ An instance representing a Dicom study within the OsiriX database.

    All attributes for this instance are immutable.
    """
    def __repr__(self):
        return f"DicomStudy: " \
               f"patient_id = {self.patient_id}, " \
               f"date = {self.date.strftime('%d/%m/%Y - %H:%M')}, " \
               f"uid = {self.pb2_object.osirixrpc_uid}"

    @property
    @pyosirix_connection_check
    def date(self) -> datetime.datetime:
        """ The date in which the Dicom data were acquired.
        """
        response = self.osirix_service_stub.DicomStudyDate(self.pb2_object)
        self.response_check(response)
        study_date = datetime.datetime(response.year,
                                       response.month,
                                       response.day,
                                       response.hour,
                                       response.minute,
                                       response.second)
        return study_date

    @property
    @pyosirix_connection_check
    def date_added(self) -> datetime.datetime:
        """ The date in which the Dicom data were added to the OsiriX database.
        """
        response = self.osirix_service_stub.DicomStudyDateAdded(self.pb2_object)
        self.response_check(response)
        date_added = datetime.datetime(response.year,
                                       response.month,
                                       response.day,
                                       response.hour,
                                       response.minute,
                                       response.second)
        return date_added

    @property
    @pyosirix_connection_check
    def date_of_birth(self) -> datetime.datetime:
        """ The patient date of birth for the Dicom study.
        """
        response = self.osirix_service_stub.DicomStudyDateOfBirth(self.pb2_object)
        self.response_check(response)
        date_of_birth = datetime.datetime(response.year,
                                          response.month,
                                          response.day)
        return date_of_birth

    @property
    @pyosirix_connection_check
    def institution_name(self) -> str:
        """ The name of the institution where the Dicom study was performed.
        """
        response = self.osirix_service_stub.DicomStudyInstitutionName(self.pb2_object)
        self.response_check(response)
        return response.institution_name

    @property
    @pyosirix_connection_check
    def patient_name(self) -> str:
        """ The patient name of the Dicom study
        """
        response = self.osirix_service_stub.DicomStudyName(self.pb2_object)
        self.response_check(response)
        return response.name

    @property
    @pyosirix_connection_check
    def number_of_images(self) -> int:
        """ The number of images within the Dicom study.
        """
        response = self.osirix_service_stub.DicomStudyNumberOfImages(self.pb2_object)
        self.response_check(response)
        return response.no_images

    @property
    @pyosirix_connection_check
    def patient_id(self) -> str:
        """ The patient ID of the Dicom study.
        """
        response = self.osirix_service_stub.DicomStudyPatientID(self.pb2_object)
        self.response_check(response)
        return response.patient_id

    @property
    @pyosirix_connection_check
    def patient_sex(self) -> str:
        """ The patient sex of the Dicom study.
        """
        response = self.osirix_service_stub.DicomStudyPatientSex(self.pb2_object)
        self.response_check(response)
        return response.patient_sex

    @property
    @pyosirix_connection_check
    def patient_uid(self) -> str:
        """ The patient UID of the Dicom study.
        """
        response = self.osirix_service_stub.DicomStudyPatientUID(self.pb2_object)
        self.response_check(response)
        return response.patient_uid

    @property
    @pyosirix_connection_check
    def performing_physician(self) -> str:
        """ The performing physician name for the Dicom study.
        """
        response = self.osirix_service_stub.DicomStudyPerformingPhysician(self.pb2_object)
        self.response_check(response)
        return response.performing_physician

    @property
    @pyosirix_connection_check
    def referring_physician(self) -> str:
        """ The referring physician name for the Dicom study.
        """
        response = self.osirix_service_stub.DicomStudyReferringPhysician(self.pb2_object)
        self.response_check(response)
        return response.referring_physician

    @property
    @pyosirix_connection_check
    def study_instance_uid(self) -> str:
        """ The study instance UID for the Dicom series.
        """
        response = self.osirix_service_stub.DicomStudyStudyInstanceUID(self.pb2_object)
        self.response_check(response)
        return response.study_instance_uid

    @property
    @pyosirix_connection_check
    def study_name(self) -> str:
        """ The study name for the Dicom series.
        """
        response = self.osirix_service_stub.DicomStudyStudyName(self.pb2_object)
        self.response_check(response)
        return response.study_name

    @pyosirix_connection_check
    def modalities(self) -> str:
        """ The modalities available within the Dicom study.

        Returns:
            The modalities of the study seperated by a double backslash.
        """
        response = self.osirix_service_stub.DicomStudyModalities(self.pb2_object)
        self.response_check(response)
        return response.modalities

    @pyosirix_connection_check
    def series(self) -> List[DicomSeries]:
        """ The Dicom Series instances associated with the study.

        Returns:
            A list of the DicomSeries instances associated with the study.
        """
        response = self.osirix_service_stub.DicomStudySeries(self.pb2_object)
        self.response_check(response)
        series = []
        for serie in response.series:
            series.append(DicomSeries(self.osirix_service, serie))
        return series

    @pyosirix_connection_check
    def images(self) -> List[DicomImage]:
        """ The Dicom Image instances associated with the study.

        Returns:
            A list of the DicomImage instances associated with the study.
        """
        response = self.osirix_service_stub.DicomStudyImages(self.pb2_object)
        self.response_check(response)
        images = []
        for image in response.images:
            images.append(DicomImage(self.osirix_service, image))
        return images

    @pyosirix_connection_check
    def paths(self) -> List[str]:
        """ The Dicom file paths associated with the study.

        Returns:
            A list of absolute paths.
        """
        response = self.osirix_service_stub.DicomStudyPaths(self.pb2_object)
        self.response_check(response)
        paths = [path for path in response.paths]
        return paths

    @pyosirix_connection_check
    def no_files(self) -> int:
        """ The number of files comprising the Dicom study.

        Returns:
            The integer number of files contained in the study.
        """
        response = self.osirix_service_stub.DicomStudyNoFiles(self.pb2_object)
        self.response_check(response)
        return response.no_files

    @pyosirix_connection_check
    def raw_no_files(self) -> int:
        """ he number of raw image files within the Dicom study.

        Returns:
            The number of files.
        """
        response = self.osirix_service_stub.DicomStudyRawNoFiles(self.pb2_object)
        self.response_check(response)
        return response.no_files


class DicomSeries(osirix.base.OsirixBase):
    """ An instance representing a Dicom series within the OsiriX database.

    All attributes for this instance are immutable.
    """
    def __repr__(self):
        return f"DicomSeries: " \
               f"modality = {self.modality}, "\
               f"series_description = {self.series_description}, " \
               f"uid = {self.pb2_object.osirixrpc_uid}" \
               f"\n     {self.study.__repr__()}"

    @property
    @pyosirix_connection_check
    def date(self) -> datetime.datetime:
        """ The date in which the series was acquired.
        """
        response = self.osirix_service_stub.DicomSeriesDate(self.pb2_object)
        self.response_check(response)
        series_date = datetime.datetime(response.year,
                                        response.month,
                                        response.day,
                                        response.hour,
                                        response.minute,
                                        response.second)
        return series_date

    @property
    @pyosirix_connection_check
    def images(self) -> List[DicomImage]:
        """ The Dicom Image instances associated with the series.
        """
        response = self.osirix_service_stub.DicomSeriesImages(self.pb2_object)
        self.response_check(response)
        images = []
        for image in response.images:
            images.append(DicomImage(self.osirix_service, image))
        return images

    @property
    @pyosirix_connection_check
    def modality(self) -> str:
        """ The modality of the Dicom series.
        """
        response = self.osirix_service_stub.DicomSeriesModality(self.pb2_object)
        self.response_check(response)
        return response.modality

    @property
    @pyosirix_connection_check
    def patient_name(self) -> str:
        """ The patient name of the Dicom series
        """
        response = self.osirix_service_stub.DicomSeriesName(self.pb2_object)
        self.response_check(response)
        return response.name

    @property
    @pyosirix_connection_check
    def number_of_images(self) -> int:
        """ The number of images within the Dicom series.
        """
        response = self.osirix_service_stub.DicomSeriesNumberOfImages(self.pb2_object)
        self.response_check(response)
        return response.number_of_images

    @property
    @pyosirix_connection_check
    def series_description(self) -> str:
        """ The series description.
        """
        response = self.osirix_service_stub.DicomSeriesSeriesDescription(self.pb2_object)
        self.response_check(response)
        return response.series_description

    @property
    @pyosirix_connection_check
    def series_instance_uid(self) -> int:
        """ The series instance UID.

        Warning: This seems to generate some unexpected results. It is better to access directly
            by reading the dicom files (via DicomSeries.paths) with pydicom.
        """
        response = self.osirix_service_stub.DicomSeriesSeriesInstanceUID(self.pb2_object)
        self.response_check(response)
        return response.series_instance_uid

    @property
    @pyosirix_connection_check
    def sop_class_uid(self) -> int:
        """ The series SOP class UID.
        """
        response = self.osirix_service_stub.DicomSeriesSeriesSOPClassUID(self.pb2_object)
        self.response_check(response)
        return response.series_sop_class_uid

    @property
    @pyosirix_connection_check
    def study(self) -> DicomStudy:
        """ The Dicom Study containing the series.
        """
        response = self.osirix_service_stub.DicomSeriesStudy(self.pb2_object)
        self.response_check(response)
        return DicomStudy(self.osirix_service, response.study)

    @pyosirix_connection_check
    def next_series(self) -> DicomSeries:
        """ The next Dicom Series in the OsiriX database.

        Returns:
            The next DicomSeries instance.
        """
        response = self.osirix_service_stub.DicomSeriesNextSeries(self.pb2_object)
        self.response_check(response)
        return DicomSeries(self.osirix_service, response.series)

    @pyosirix_connection_check
    def previous_series(self) -> DicomSeries:
        """ The previous Dicom Series in the OsiriX database.

        Returns:
            The previous DicomSeries instance.
        """
        response = self.osirix_service_stub.DicomSeriesPreviousSeries(self.pb2_object)
        self.response_check(response)
        return DicomSeries(self.osirix_service, response.series)

    @pyosirix_connection_check
    def paths(self) -> List[str]:
        """ The Dicom file paths associated with the series.

        Returns:
            A list of absolute paths.
        """
        response = self.osirix_service_stub.DicomSeriesPaths(self.pb2_object)
        self.response_check(response)
        paths = [path for path in response.paths]
        return paths

    @pyosirix_connection_check
    def sorted_images(self) -> List[DicomImage]:
        """ Dicom image instances sorted by OsiriX user preferences.

        These preferences are determined in OsiriX Preferences / Database / Sorting.

        Returns:
           A list of sorted DicomImage instances.
        """
        response = self.osirix_service_stub.DicomSeriesSortedImages(self.pb2_object)
        self.response_check(response)
        sorted_images = []
        for sorted_image in response.sorted_images:
            sorted_images.append(DicomImage(self.osirix_service, sorted_image))
        return sorted_images


class DicomImage(osirix.base.OsirixBase):
    """ An instance representing a Dicom image within the OsiriX database.

    All attributes for this instance are immutable.
    """
    def __repr__(self):
        return f"DicomImage: " \
               f"instance_number = {self.instance_number}, "\
               f"slice_location = {self.slice_location:.2f}, " \
               f"uid = {self.pb2_object.osirixrpc_uid}" \
               f"\n     {self.series.__repr__()}"

    @property
    @pyosirix_connection_check
    def date(self) -> datetime.datetime:
        """ The date in which the Dicom image were acquired.
        """
        response = self.osirix_service_stub.DicomImageDate(self.pb2_object)
        self.response_check(response)
        image_date = datetime.datetime(response.year,
                                       response.month,
                                       response.day,
                                       response.hour,
                                       response.minute,
                                       response.second)
        return image_date

    @property
    @pyosirix_connection_check
    def instance_number(self) -> int:
        """ The instance number for the Dicom image.
        """
        response = self.osirix_service_stub.DicomImageInstanceNumber(self.pb2_object)
        self.response_check(response)
        return response.instance_number

    @property
    @pyosirix_connection_check
    def modality(self) -> str:
        """ The modality of the Dicom image.
        """
        response = self.osirix_service_stub.DicomImageModality(self.pb2_object)
        self.response_check(response)
        return response.modality

    @property
    @pyosirix_connection_check
    def number_of_frames(self) -> int:
        """ The number of frames within the Dicom image.
        """
        response = self.osirix_service_stub.DicomImageNumberOfFrames(self.pb2_object)
        self.response_check(response)
        return response.number_of_frames

    @property
    @pyosirix_connection_check
    def series(self) -> DicomSeries:
        """ The DicomSeries instance in which the image is contained.
        """
        response = self.osirix_service_stub.DicomImageSeries(self.pb2_object)
        self.response_check(response)
        return DicomSeries(self.osirix_service, response.series)

    @property
    @pyosirix_connection_check
    def slice_location(self) -> float:
        """ The slice location of the image.

        Note that this is never perfect; it can be better to read the source dicom instance and use
            the ImagePositionPatient parameter.
        """
        response = self.osirix_service_stub.DicomImageSliceLocation(self.pb2_object)
        self.response_check(response)
        return response.slice_location

    @pyosirix_connection_check
    def complete_path(self) -> str:
        """ The path of the source Dicom file.

        Returns:
           The complete path of the Dicom file containing the information contained by the image.
        """
        response = self.osirix_service_stub.DicomImageCompletePath(self.pb2_object)
        self.response_check(response)
        return response.path_name

    @pyosirix_connection_check
    def height(self) -> int:
        """ The number of rows in the image
        Returns:
           The height (number of rows) of the image.
        """
        response = self.osirix_service_stub.DicomImageHeight(self.pb2_object)
        self.response_check(response)
        return response.height

    @pyosirix_connection_check
    def width(self) -> int:
        """ The number of columns in the image
        Returns:
           The width (number of columns) of the image.
        """
        response = self.osirix_service_stub.DicomImageWidth(self.pb2_object)
        self.response_check(response)
        return response.width

    @pyosirix_connection_check
    def sop_instance_uid(self) -> str:
        """ The SOP instance UID for the image.

        Returns:
           The SOP instance UID, a unique Dicom identifier for the image.
        """
        response = self.osirix_service_stub.DicomImageSOPInstanceUID(self.pb2_object)
        self.response_check(response)
        return response.sop_instance_uid
