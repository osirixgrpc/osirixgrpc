""" Test the osirixgrpc functionality for pyOsiriX DicomStudy class """

import os
from datetime import datetime, timedelta

import pytest

import osirix  # noqa


def test_dicom_study_paths(study_test):
    """ Check valid paths are returned """
    paths = study_test.paths
    assert len(paths) == 40, f"Incorrect number of paths ({len(paths)})"
    for path in paths:
        assert os.path.exists(path), f"Path {path} does not exist"


def test_dicom_study_images(study_test):
    """ Check that images are provided. """
    images = study_test.images
    assert len(images) >= 40, f"Bad number of images ({len(images)})"


def test_dicom_study_modalities(study_test):
    """ Check correct modalities are provided. """
    assert study_test.modalities == "MR", f"Bad modalities {study_test.modalities}"


def test_dicom_study_no_files(study_test):
    """ Check no files is correctly provided. """
    assert study_test.no_files == 40, f"Bad no files {study_test.no_files}"


def test_dicom_study_raw_no_files(study_test):
    """ Check raw no files is correctly provided. """
    assert study_test.no_files >= 40, f"Bad raw no files {study_test.no_files}"


def test_dicom_study_series(study_test, series_test):
    """ Check the correct series instances are provided. """
    series = study_test.series
    assert len(series) == 1, f"Bad number of series {len(series)}"
    assert series[0].pb2_object.osirixrpc_uid == series_test.pb2_object.osirixrpc_uid, \
        f"Bad series found"


def test_dicom_study_name(study_test):
    """ Check the correct patient name is provided. """
    assert study_test.patient_name.lower() == "osirixgrpc test patient", \
        f"Bad name {study_test.patient_name}"


def test_dicom_study_date(study_test):
    """ Check the correct study date is provided. """
    date = datetime.strptime("20220803190119", "%Y%m%d%H%M%S")
    assert abs(date - study_test.date) <= timedelta(seconds=1.0)


def test_dicom_study_date_added(study_test):
    """ Check the correct study date added is provided. """
    now = datetime.now()
    assert abs(now - study_test.date_added) <= timedelta(hours=1.0)


def test_dicom_study_dob(study_test):
    """ Check the correct date of birth is provided. """
    dob = datetime.strptime("19000101", "%Y%m%d")
    assert abs(dob - study_test.date_of_birth) <= timedelta(days=1.0)


def test_dicoms_study_institution_name(study_test):
    assert study_test.institution_name.lower() == "osirixgrpc test institution",\
        f"Bad institution name {study_test.institution_name}"


def test_dicom_study_patient_id(study_test):
    """ Check the correct patient ID is provided. """
    assert study_test.patient_id.lower() == "osirixgrpc test patient id", \
        f"Bad patient ID {study_test.patient_id}"


def test_dicom_study_patient_uid(study_test):
    """ Check the correct patient UID is provided. """
    assert study_test.patient_uid ==\
           "OSIRIXGRPC TEST PATIENT-OSIRIXGRPC TEST PATIENT ID-19000101", \
           f"Bad patient UID {study_test.patient_uid}"


def test_dicom_study_patient_sex(study_test):
    """ Check the correct patient sex is provided. """
    assert study_test.patient_sex == "O", f"Bad patient sex {study_test.patient_sex}"


def test_dicom_study_performing_physician(study_test):
    """ Check the correct performing physician is provided. """
    with pytest.raises(osirix.exceptions.GrpcException) as exc:
        _ = study_test.performing_physician
    assert str(exc.value) == "Performing physician not available", \
        f"Bad error message for no performing physician"


def test_dicom_study_referring_physician(study_test):
    """ Check the correct referring physician is provided. """
    assert study_test.referring_physician.lower() == "osirixgrpc test physician name", \
        f"Bad referring physician {study_test.referring_physician}"


def test_dicom_study_study_instance_uid(study_test):
    """ Check the correct study instance UID is provided. """
    assert study_test.study_instance_uid == "1.2.840.846310145.17.1.1.4515953", \
        f"Bad study instance UID {study_test.study_instance_uid}"


def test_dicom_study_study_name(study_test):
    """ Check the correct study name is provided. """
    assert study_test.study_name.lower() == "osirixgrpc test study", \
        f"Bad study name {study_test.study_name}"
