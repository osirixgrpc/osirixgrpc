""" Test the osirixgrpc functionality for pyOsiriX DicomSeries class """

import os
from datetime import datetime, timedelta

import pytest

import osirix  # noqa


def test_dicom_series_paths(series_test):
    """ Check valid paths are returned """
    paths = series_test.paths
    assert len(paths) == 40, f"Incorrect number of paths ({len(paths)})"
    for path in paths:
        assert os.path.exists(path), f"Path {path} does not exist"


def test_dicom_series_next_series(series_test):
    """ Check there is no next series. """
    with pytest.raises(osirix.exceptions.GrpcException) as exc:
        _ = series_test.next_series
    assert str(exc.value) == "No next series", f"Bad error message for no next series"


def test_dicom_series_previous_series(series_test):
    """ Check there is no previous series. """
    with pytest.raises(osirix.exceptions.GrpcException) as exc:
        _ = series_test.previous_series
    assert str(exc.value) == "No previous series", f"Bad error message for no previous series"


def test_dicom_series_sorted_images(series_test):
    """ Check that sorted images are provided. """
    images = series_test.sorted_images()
    assert len(images) == 40, f"Bad number of sorted images {len(images)}"


def test_dicom_series_study(series_test, study_test):
    """ Check the correct study instance is obtainable. """
    study = series_test.study
    assert isinstance(study, osirix.dicom.DicomStudy), f"Bad type returned"
    assert study.pb2_object.osirixrpc_uid == study_test.pb2_object.osirixrpc_uid, f"Bad study found"


def test_dicom_series_images(series_test):
    """ Check that images are provided. """
    images = series_test.images
    for image in images:
        assert isinstance(image, osirix.dicom.DicomImage)
    assert len(images) == 40, f"Bad number of images ({len(images)})"


def test_dicom_series_series_instance_uid(series_test, series_uid_test):
    assert series_test.series_instance_uid == series_uid_test,\
        f"Bad series instance UID {series_test.series_instance_uid}"


def test_dicom_series_sop_class_uid(series_test):
    """ Check that the correct SOP class UID is returned. """
    assert series_test.sop_class_uid == "1.2.840.10008.5.1.4.1.1.4",\
        f"Bad sop class UID {series_test.sop_class_uid}"


def test_dicom_series_series_description(series_test):
    assert series_test.series_description == "t2_tse_sag AP",\
        f"Bad series description {series_test.series_description}"


def test_dicom_series_modality(series_test):
    """ Check the correct modality is returned. """
    assert series_test.modality == "MR", f"Bad modality {series_test.modality}"


def test_dicom_series_patient_name(series_test):
    """ Check the correct patient name is returned. """
    assert series_test.patient_name == "t2_tse_sag AP", \
        f"Bad series patient name {series_test.patient_name}"


def test_dicom_series_date(series_test):
    """ Check the correct series date is returned. """
    date = datetime.strptime("20220803190123", "%Y%m%d%H%M%S")
    assert abs(date - series_test.date) <= timedelta(seconds=1.0)


def test_dicom_series_number_of_images(series_test):
    """ Check correct number of images returned """
    assert series_test.number_of_images == 40, \
        f"Bad number of images {series_test.number_of_images}"
