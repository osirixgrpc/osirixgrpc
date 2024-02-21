from __future__ import annotations

import datetime
import sys
# sys.path.append("./pb2")
import osirixgrpc.osirix_pb2_grpc as osirix_pb2_grpc
from typing import Tuple
from osirix.response_processor import ResponseProcessor

class DicomStudy(object):
    '''
    Class representing the properties and methods to communicate with the Osirix service through
    gRPC for a study
    '''

    def __init__(self,
                 osirixrpc_uid : str,
                 osirix_service : osirix_pb2_grpc.OsiriXServiceStub,
                 ):
        self.response_processor = ResponseProcessor()
        self.osirixrpc_uid = osirixrpc_uid
        self.osirix_service = osirix_service

    @property
    def date(self) -> datetime.datetime:
        """
        Provides the datetime associated with the DicomStudy
        Returns:
            datetime: date and time for the study
        """
        response_study_date = self.osirix_service.DicomStudyDate(self.osirixrpc_uid)

        self.response_processor.response_check(response_study_date)

        datetime_output: datetime.datetime = datetime.datetime(response_study_date.year,
                                                               response_study_date.month,
                                                               response_study_date.day,
                                                               response_study_date.hour,
                                                               response_study_date.minute,
                                                               response_study_date.second
                                                               )

        study_date = datetime_output
        return study_date

    # @date.setter
    # def date(self, response):
    #     self._date = response

    @property
    def date_added(self) -> datetime.datetime:
        """
        Provides date added associated with the DicomStudy
        Returns:
            datetime: date added of the study
        """
        response_study_date_added = self.osirix_service.DicomStudyDateAdded(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_date_added)

        datetime_output: datetime.datetime = datetime.datetime(response_study_date_added.year,
                                                               response_study_date_added.month,
                                                               response_study_date_added.day,
                                                               response_study_date_added.hour,
                                                               response_study_date_added.minute,
                                                               response_study_date_added.second
                                                               )

        self._date_added = datetime_output
        return self._date_added

    # @date_added.setter
    # def date_added(self, response):
    #     self._date_added = response

    @property
    def date_of_birth(self) -> datetime.datetime:
        """
        Provides the date of the birth for the patient associated with the DicomStudy
        Returns:
            datetime : study patient's date of birth
        """
        response_study_date_of_birth = self.osirix_service.DicomStudyDateOfBirth(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_date_of_birth)
        datetime_output: datetime.datetime = datetime.datetime(response_study_date_of_birth.year,
                                                               response_study_date_of_birth.month,
                                                               response_study_date_of_birth.day
                                                               )

        self._date_of_birth = datetime_output
        return self._date_of_birth

    @property
    def institution_name(self) -> str:
        """
        Provides institution name associated with the DicomStudy
        Returns:
            str : name of the institution for the study
        """
        response_study_institution_name = self.osirix_service.DicomStudyInstitutionName(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_institution_name)
        self._institution_name = response_study_institution_name.institution_name

        return self._institution_name

    # @institution_name.setter
    # def institution_name(self, response) -> None:
    #     self._institution_name = response

    @property
    def modalities(self) -> str:
        """
        Provides the modalities associated with the DicomStudy
        Returns:
            str : modalities for the study
        """
        response_study_modalities = self.osirix_service.DicomStudyModalities(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_modalities)
        self._modalities = response_study_modalities.modalities

        return self._modalities

    @property
    def name(self) -> str:
        """
        Provides name associated with the DicomStudy
        Returns:
            str : name of the study
        """
        response_study_name = self.osirix_service.DicomStudyName(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_name)
        self._name = response_study_name.name

        return self._name

    @property
    def number_of_images(self) -> int:
        """
        Provides number of images associated with the DicomStudy
        Returns:
            int : number of image for the study
        """
        response_study_no_of_images = self.osirix_service.DicomStudyNumberOfImages(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_no_of_images)
        self._study_number_of_images = response_study_no_of_images.no_images

        return self._study_number_of_images

    @property
    def patient_id(self) -> str:
        """
        Provides id of the patient associated with the DicomStudy
        Returns:
            str : patient's id
        """
        response_study_patient_id = self.osirix_service.DicomStudyPatientID(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_patient_id)
        self._patient_id = response_study_patient_id.patient_id

        return self._patient_id

    @property
    def patient_sex(self) -> str:
        """
        Provides sex of the patient associated with the DicomStudy
        Returns:
            str : patient's sex
        """
        response_study_patient_sex = self.osirix_service.DicomStudyPatientSex(self.osirixrpc_uid)
        self.response_processor.process_check(response_study_patient_sex)
        self._patient_sex = response_study_patient_sex.patient_sex

        return self._patient_sex

    @property
    def patient_uid(self) -> str:
        """
        Provides uid of the patient associated with the DicomStudy
        Returns:
            str : patient uid
        """
        response_study_patient_uid = self.osirix_service.DicomStudyPatientUID(self.osirixrpc_uid)
        self.response_processor.process_check(response_study_patient_uid)
        self._patient_uid = response_study_patient_uid.patient_uid

        return self._patient_uid

    #TODO
    @property
    def performing_physician(self) -> str:
        """
        Provides the performing physician associated with the DicomStudy
        Returns:
            str : performing physician
        """
        response_study_performing_physician = self.osirix_service.DicomStudyPerformingPhysician(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_performing_physician)
        self._performing_physician = response_study_performing_physician.performing_physician

        return self._performing_physician

    #TODO
    @property
    def referring_physician(self) -> str:
        """
        Provides referring physician associated with the DicomStudy
        Returns:
            str : referrring physician
        """
        response_study_referring_physician = self.osirix_service.DicomStudyPerformingPhysician(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_referring_physician)
        self._referring_physician = response_study_referring_physician.referring_physician

        return self._referring_physician

    #TODO
    @property
    def series(self) -> Tuple[DicomSeries, ...]:
        """
        Provides all the series associated with the DicomStudy
        Returns:
            Tuple containing all the DicomSeries for the study
        """
        response_study_series = self.osirix_service.DicomStudySeries(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_series)
        dicom_series_tuple : Tuple[DicomSeries, ...] = ()

        for series in response_study_series.series:
            # print(series.osirixrpc_uid)
            # series_tuple = series_tuple + (series.osirixrpc_uid,)
            dicom_series = DicomSeries(series, self.osirix_service)
            dicom_series_tuple = dicom_series_tuple + (dicom_series,)

        self._series = dicom_series_tuple

        return self._series

    @property
    def study_instance_uid(self) -> str:
        """
        Provides study instance uid associated with the DicomStudy
        Returns:
            str : study instance uid
        """
        response_study_study_instance_uid = self.osirix_service.DicomStudyStudyInstanceUID(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_study_instance_uid)
        self._study_instance_uid = response_study_study_instance_uid.study_instance_uid

        return self._study_instance_uid

    @property
    def study_name(self) -> str:
        """
        Provides the study name associated with the DicomStudy
        Returns:
            str : study name
        """
        response_study_study_name = self.osirix_service.DicomStudyStudyName(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_study_name)
        self._study_study_name = response_study_study_name.study_name

        return self._study_study_name


    def no_files(self) -> int:
        """
        Provides number of files associated with the DicomStudy
        Returns:
            int: number of files for the study
        """
        response_study_no_of_files = self.osirix_service.DicomStudyNoFiles(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_no_of_files)
        study_no_of_files = response_study_no_of_files.no_files

        return study_no_of_files

    def images(self) -> Tuple[DicomImage, ...]:
        """
        Provides all the images associated with the DicomStudy
        Returns:
            Tuple containing all the DicomImage for the study
        """

        response_study_images = self.osirix_service.DicomStudyImages(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_images)

        dicom_image_tuple : Tuple[DicomImage, ...] = ()

        for image in response_study_images.images:
            dicom_image = DicomImage(image, self.osirix_service)
            dicom_image_tuple = dicom_image_tuple + (dicom_image,)

        return dicom_image_tuple

    def image_series(self) -> Tuple[DicomSeries, ...]:
        """
        Provides all the series associated with the DicomStudy
        Returns:
            Tuple containing all the DicomSeries for the study
        """
        response_study_series = self.osirix_service.DicomStudySeries(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_series)

        dicom_series_tuple : Tuple[DicomSeries, ...] = ()

        for series in response_study_series.series:
            dicom_series = DicomSeries(series, self.osirix_service)
            dicom_series_tuple = dicom_series_tuple + (dicom_series,)

        return dicom_series_tuple

    def no_files_excluding_multframes(self) -> int:
        """
        Provides number of files excluding multiple frames associated with the DicomStudy
        Returns:
            int : name of files without multiple frames
        """
        response_study_no_of_files_excl_multiframes = self.osirix_service.DicomStudyNoFilesExcludingMultiFrames(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_no_of_files_excl_multiframes)

        study_no_of_files_excl_multiframes = response_study_no_of_files_excl_multiframes.no_files

        return study_no_of_files_excl_multiframes

    def paths(self) -> Tuple[str, ...]:
        """
        Provides the paths associated with the DicomStudy
        Returns:
            Tuple containing the paths for the study
        """

        response_study_paths = self.osirix_service.DicomStudyPaths(self.osirixrpc_uid)
        self.response_processor.response_check(response_study_paths)
        study_paths = tuple(response_study_paths.paths)

        return study_paths

    def raw_no_files(self) -> int:
        """
        Provides the raw number of files associated with the DicomStudy
        Returns:
            int : raw number of the files for the study
        """
        response_study_raw_no_of_files = self.osirix_service.DicomStudyRawNoFiles(self.osirixrpc_uid)

        study_raw_no_of_files = response_study_raw_no_of_files.no_files

        return study_raw_no_of_files

class DicomSeries(object):
    '''
    Class representing the properties and methods to communicate with the Osirix service through
    gRPC for a series
    '''

    def __init__(self,
                 osirixrpc_uid: str,
                 osirix_service: osirix_pb2_grpc.OsiriXServiceStub
                 ):
        self.response_processor = ResponseProcessor()
        self.osirixrpc_uid = osirixrpc_uid
        self.osirix_service = osirix_service

    @property
    def date(self) -> datetime.datetime:
        """
        Provides the date associated with the DicomSeries
        Returns:
            datetime : date of the series
        """
        response_series_date = self.osirix_service.DicomSeriesDate(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_date)
        datetime_output : datetime.datetime = datetime.datetime(response_series_date.year,
                                   response_series_date.month,
                                   response_series_date.day,
                                   response_series_date.hour,
                                   response_series_date.minute,
                                   response_series_date.second
                               )
        self._date = datetime_output
        return self._date

    # @date.setter
    # def date(self, response):
    #     self._date = response

    @property
    def images(self) -> Tuple[DicomImage, ...]:
        """
        Provides the images associated with the DicomSeries
        Returns:
            A Tuple containing the DicomImages in the series
        """
        response_series_images = self.osirix_service.DicomSeriesImages(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_images)

        dicom_image_tuple : Tuple[DicomImage, ...] = ()

        for image in response_series_images.images:
            dicom_image = DicomImage(image, self.osirix_service)
            dicom_image_tuple = dicom_image_tuple + (dicom_image,)

        self._images = dicom_image_tuple

        return self._images

    @property
    def modality(self) -> str:
        response_series_modality = self.osirix_service.DicomSeriesModality(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_modality)
        self._modality = response_series_modality.modality

        return self._modality

    @property
    def name(self) -> str:
        """
        Provides thename associated with the DicomSeries
        Returns:
            string : name of the series
        """
        response_series_name = self.osirix_service.DicomSeriesName(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_name)
        self._name = response_series_name.name

        return self._name

    #TODO
    #No number of images for Dicom Series response
    @property
    def number_of_images(self) -> int:
        """
        Provides the number of images in the the DicomSeries
        Returns:
           int : number of images in the series
        """
        response_series_no_of_images = self.osirix_service.DicomSeriesNumberOfImages(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_no_of_images)
        self._number_of_images = response_series_no_of_images.number_of_images

        return self._number_of_images

    @property
    def series_description(self) -> str:
        """
        Provides the description of the DicomSeries
        Returns:
           string : the description for the series
        """
        response_series_series_description = self.osirix_service.DicomSeriesSeriesDescription(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_series_description)
        self._series_description = response_series_series_description.series_description

        return self._series_description

    @property
    def series_instance_uid(self) -> str:
        """
        Provides the series instance uid associated with the DicomSeries
        Returns:
            string : series instance uid of the series
        """
        response_series_instance_uid = self.osirix_service.DicomSeriesSeriesInstanceUID(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_instance_uid)
        self._series_instance_uid = response_series_instance_uid.series_instance_uid

        return self._series_instance_uid

    @property
    def sop_class_uid(self) -> str:
        """
        Provides the sop class uid associated with the DicomSeries
        Returns:
           str : sop class uid of the series
        """
        response_series_sop_class_uid = self.osirix_service.DicomSeriesSeriesSOPClassUID(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_sop_class_uid)
        self._sop_class_uid = response_series_sop_class_uid.series_sop_class_uid
        return self._sop_class_uid

    @property
    def study(self) -> DicomStudy:
        """
        Provides the study associated with the series
        Returns:
           DicomStudy : study related to the series
        """
        response_series_study = self.osirix_service.DicomSeriesStudy(self.osirixrpc_uid)
        self.response_processor.process_basic_response(response_series_study)
        study_series = response_series_study.study

        self._study = DicomStudy(study_series, self.osirix_service)

        return self._study

    def next_series(self) -> DicomSeries:
        """
        Provides the next series in the study
        Returns:
           DicomSeries : the next series in the study
        """

        response_series_next_series = self.osirix_service.DicomSeriesNextSeries(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_next_series)
        series_next_series = response_series_next_series.next_series

        series_next_series_obj = DicomSeries(series_next_series, self.osirix_service)

        return series_next_series_obj

    def paths(self) -> Tuple[str, ...]:
        """
        Provides the paths for the series
        Returns:
           A Tuple containing string paths of the series
        """

        response_series_paths = self.osirix_service.DicomSeriesPaths(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_paths)
        series_paths = tuple(response_series_paths.paths)

        return series_paths

    def previous_series(self) -> DicomSeries:
        """
        Provides the previous series in the study
        Returns:
           Returns DicomSeries of a previous series
        """

        response_series_previous_series = self.osirix_service.DicomSeriesPreviousSeries(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_previous_series)
        series_previous_series = response_series_previous_series.previous_series

        series_previous_series_obj = DicomSeries(series_previous_series, self.osirix_service)

        return series_previous_series_obj

    def sorted_images(self) -> Tuple[DicomImage, ...]:
        """
        Provides the sorted images associated with the DicomSeries
        Returns:
           A Tuple containing DicomImage that are sorted
        """
        response_series_sorted_images = self.osirix_service.DicomSeriesSortedImages(self.osirixrpc_uid)
        self.response_processor.response_check(response_series_sorted_images)

        dicom_image_tuple : Tuple[DicomImage, ...] = ()

        for sorted_image in response_series_sorted_images.sorted_images:
            dicom_image = DicomImage(sorted_image, self.osirix_service)
            dicom_image_tuple = dicom_image_tuple + (dicom_image,)

        return dicom_image_tuple

class DicomImage(object):
    '''
    Class representing the properties and methods to communicate with the Osirix service through
    gRPC for an image
    '''

    def __init__(self,
                 osirixrpc_uid : str,
                 osirix_service : osirix_pb2_grpc.OsiriXServiceStub
                 ):
        self.response_processor = ResponseProcessor()
        self.osirixrpc_uid = osirixrpc_uid
        self.osirix_service = osirix_service

    @property
    def date(self) -> datetime.datetime:
        """
        Provides the datetime for the DicomImage
        Returns:
            datetime : the datetime of the DicomImage
        """
        response_image_date = self.osirix_service.DicomImageDate(self.osirixrpc_uid)
        self.response_processor.response_check(response_image_date)

        datetime_output: datetime.datetime = datetime.datetime(response_image_date.year,
                                                               response_image_date.month,
                                                               response_image_date.day,
                                                               response_image_date.hour,
                                                               response_image_date.minute,
                                                               response_image_date.second
                                                               )
        self._date = datetime_output
        return self._date

    @property
    def instance_number(self) -> int:
        """
        Provides the instance number for the DicomImage
        Returns:
           int : the instance number of the DicomImage
        """
        response_image_instance_number = self.osirix_service.DicomImageInstanceNumber(self.osirixrpc_uid)
        self.response_processor.response_check(response_image_instance_number)
        self._instance_number = response_image_instance_number.instance_number
        return self._instance_number

    @property
    def modality(self) -> str:
        """
        Provides the modality for the DicomImage
        Returns:
           str : the modality of the DicomImage
        """
        response_image_modality = self.osirix_service.DicomImageModality(self.osirixrpc_uid)
        self.response_processor.response_check(response_image_modality)
        self._modality = response_image_modality.modality
        return self._modality

    @property
    def number_of_frames(self) -> int:
        """
        Provides the number of frames for the DicomImage
        Returns:
           int : the number of frames of the DicomImage
        """
        response_image_no_of_frames = self.osirix_service.DicomImageNumberOfFrames(self.osirixrpc_uid)
        self.response_processor.response_check(response_image_no_of_frames)
        self._number_of_frames = response_image_no_of_frames.number_of_frames
        return self._number_of_frames

    @property
    def series(self) -> DicomSeries:
        """
        Provides the series that the DicomImage is associated with
        Returns:
           the DicomSeries of the DicomImage
        """
        response_image_series = self.osirix_service.DicomImageSeries(self.osirixrpc_uid)

        self.response_processor.response_check(response_image_series)

        image_series = response_image_series.series

        print("Image Series : " + str(image_series))
        self._series = DicomSeries(image_series, self.osirix_service)
        return self._series

    @property
    def slice_location(self) -> float:
        """
        Provides the instance number for the DicomImage
        Returns:
           float : the instance number of the DicomImage
        """
        response_image_slice_location = self.osirix_service.DicomImageSliceLocation(self.osirixrpc_uid)

        self.response_processor.response_check(response_image_slice_location)

        self._slice_location = response_image_slice_location.slice_locations

        return self._slice_location

    def complete_path(self) -> str:
        """
        Provides the complete path for the DicomImage
        Returns:
           str : the complete path of the DicomImage
        """

        response_image_complete_path = self.osirix_service.DicomImageCompletePath(self.osirixrpc_uid)

        self.response_processor.response_check(response_image_complete_path)

        image_complete_path = response_image_complete_path.path_name

        return image_complete_path

    def height(self) -> int:
        """
        Provides the height for the DicomImage
        Returns:
           int : the height of the DicomImage
        """

        response_image_height = self.osirix_service.DicomImageHeight(self.osirixrpc_uid)

        self.response_processor.response_check(response_image_height)

        image_height = response_image_height.height

        return image_height

    def sop_instance_uid(self) -> str:
        """
        Provides the sop_instance_uid for the DicomImage
        Returns:
           str: the sop_instance_uid of the DicomImage
        """

        response_image_sop_instance_uid = self.osirix_service.DicomImageSOPInstanceUID(self.osirixrpc_uid)

        self.response_processor.response_check(response_image_sop_instance_uid)

        image_sop_instance_uid = response_image_sop_instance_uid.sop_instance_uid

        return image_sop_instance_uid

    def width(self) -> int:
        """
        Provides the width for the DicomImage
        Returns:
           int: the width of the DicomImage
        """

        response_image_width = self.osirix_service.DicomImageWidth(self.osirixrpc_uid)

        self.response_processor.response_check(response_image_width)
        image_width = response_image_width.width

        return image_width