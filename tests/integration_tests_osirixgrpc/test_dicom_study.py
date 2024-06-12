""" Test the osirixgrpc functionality for OsiriX DicomStudy class """

import os
from datetime import datetime


def test_dicom_study_paths(grpc_stub, study_test):
    """ Check valid paths are returned """
    response = grpc_stub.DicomStudyPaths(study_test)
    assert response.status.status == 1, f"Could not request paths"
    paths = response.paths
    assert len(paths) == 40, f"Incorrect number of paths ({len(paths)})"
    for path in paths:
        assert os.path.exists(path), f"Path {path} does not exist"


def test_dicom_study_images(grpc_stub, study_test):
    """ Check that images are provided. """
    response = grpc_stub.DicomStudyImages(study_test)
    assert response.status.status == 1, f"Could not request images"
    images = response.images
    assert len(images) == 40, f"Bad number of images ({len(images)})"


def test_dicom_study_modalities(grpc_stub, study_test):
    """ Check correct modalities are provided. """
    response = grpc_stub.DicomStudyModalities(study_test)
    assert response.status.status == 1, f"Could not request modalities"
    assert response.modalities == "MR", f"Bad modalities {response.modalities}"


def test_dicom_study_modality(grpc_stub, study_test):
    """ Check correct modality is provided. """
    response = grpc_stub.DicomStudyModality(study_test)
    assert response.status.status == 1, f"Could not request modality"
    assert response.modality == "MR", f"Bad modalities {response.modality}"


def test_dicom_study_no_files(grpc_stub, study_test):
    """ Check no files is correctly provided. """
    response = grpc_stub.DicomStudyNoFiles(study_test)
    assert response.status.status == 1, f"Could not request no files"
    assert response.no_files == 40, f"Bad no files {response.no_files}"


def test_dicom_study_raw_no_files(grpc_stub, study_test):
    """ Check raw no files is correctly provided. """
    response = grpc_stub.DicomStudyRawNoFiles(study_test)
    assert response.status.status == 1, f"Could not request raw no files"
    assert response.no_files == 40, f"Bad raw no files {response.no_files}"


def test_dicom_study_number_of_images(grpc_stub, study_test):
    """ Check number of images is correctly provided. """
    response = grpc_stub.DicomStudyNumberOfImages(study_test)
    assert response.status.status == 1, f"Could not request number of images"
    assert response.no_images == 40, f"Bad raw no files {response.no_images}"


def test_dicom_study_series(grpc_stub, study_test, series_test):
    """ Check the correct series instances are provided. """
    response = grpc_stub.DicomStudySeries(study_test)
    assert response.status.status == 1, f"Could not request series"
    series = response.series
    assert len(series) == 1, f"Bad number of series {len(series)}"
    assert series[0].osirixrpc_uid == series_test.osirixrpc_uid, f"Bad study found"


def test_dicom_study_name(grpc_stub, study_test):
    """ Check the correct patient name is provided. """
    response = grpc_stub.DicomStudyName(study_test)
    assert response.status.status == 1, f"Could not request study name"
    assert response.name.lower() == "osirixgrpc test patient", f"Bad name {response.name}"


def test_dicom_study_date(grpc_stub, study_test):
    """ Check the correct study date is provided. """
    response = grpc_stub.DicomStudyDate(study_test)
    assert response.status.status == 1, f"Could not request study date"  # noqa: duplicate lines
    assert response.year == 2022, f"Bad year {response.year}"
    assert response.month == 8, f"Bad month {response.month}"
    assert response.day == 3, f"Bad day {response.day}"
    assert response.hour == 19, f"Bad hour {response.hour}"
    assert response.minute == 1, f"Bad minute {response.minute}"
    assert response.second == 19, f"Bad second {response.second}"
    assert response.millisecond == 1718993592, f"Bad millisecond {response.millisecond}"


def test_dicom_study_date_added(grpc_stub, study_test):
    """ Check the correct study date added is provided. """
    response = grpc_stub.DicomStudyDateAdded(study_test)
    assert response.status.status == 1, f"Could not request study date added"
    now = datetime.now()
    assert response.year == int(now.strftime("%Y")), f"Bad year added"
    assert response.month == int(now.strftime("%m")), f"Bad month added"
    assert response.day == int(now.strftime("%d")), f"Bad day added"


def test_dicom_study_dob(grpc_stub, study_test):
    """ Check the correct date of birth is provided. """
    response = grpc_stub.DicomStudyDateOfBirth(study_test)
    assert response.status.status == 1, f"Could not request study date of birth"
    assert response.year == 1900, f"Bad DOB year {response.year}"
    assert response.month == 1, f"Bad DOB month {response.month}"
    assert response.day == 1, f"Bad DOB day {response.day}"


def test_dicoms_study_institution_name(grpc_stub, study_test):
    """ Check the correct study institution name is provided. """
    response = grpc_stub.DicomStudyInstitutionName(study_test)
    assert response.status.status == 1, f"Could not request study institution name"
    assert response.institution_name.lower() == "osirixgrpc test institution",\
        f"Bad institution name {response.institution_name}"


def test_dicom_study_patient_id(grpc_stub, study_test):
    """ Check the correct patient ID is provided. """
    response = grpc_stub.DicomStudyPatientID(study_test)
    assert response.status.status == 1, f"Could not request study patient ID"
    assert response.patient_id == "osirixgrpc test patient id", \
        f"Bad patient ID {response.patient_id}"


def test_dicom_study_patient_uid(grpc_stub, study_test):
    """ Check the correct patient UID is provided. """
    response = grpc_stub.DicomStudyPatientUID(study_test)
    assert response.status.status == 1, f"Could not request study patient UID"
    assert response.patient_uid == "OSIRIXGRPC TEST PATIENT-OSIRIXGRPC TEST PATIENT ID-19000101", \
        f"Bad patient UID {response.patient_uid}"


def test_dicom_study_patient_sex(grpc_stub, study_test):
    """ Check the correct patient sex is provided. """
    response = grpc_stub.DicomStudyPatientSex(study_test)
    assert response.status.status == 1, f"Could not request study patient sex"
    assert response.patient_sex == "O", f"Bad patient sex {response.patient_sex}"


def test_dicom_study_performing_physician(grpc_stub, study_test):
    """ Check the correct performing physician is provided. """
    response = grpc_stub.DicomStudyPerformingPhysician(study_test)
    assert response.status.status == 0, f"There should be no performing physician"


def test_dicom_study_referring_physician(grpc_stub, study_test):
    """ Check the correct referring physician is provided. """
    response = grpc_stub.DicomStudyReferringPhysician(study_test)
    assert response.status.status == 1, f"TCould not request referring physician"
    assert response.referring_physician.lower() == "osirixgrpc test physician name", \
        f"Bad referring physician {response.referring_physician}"


def test_dicom_study_study_instance_uid(grpc_stub, study_test):
    """ Check the correct study instance UID is provided. """
    response = grpc_stub.DicomStudyStudyInstanceUID(study_test)
    assert response.status.status == 1, f"Could not request study instance UID"
    assert response.study_instance_uid == "1.2.840.846310145.17.1.1.4515953", \
        f"Bad study instance UID {response.study_instance_uid}"


def test_dicom_study_study_name(grpc_stub, study_test):
    """ Check the correct study name is provided. """
    response = grpc_stub.DicomStudyStudyName(study_test)
    assert response.status.status == 1, f"Could not request study name"
    assert response.study_name == "Osirixgrpc Test Study", f"Bad study name {response.study_name}"
