""" Test the osirixgrpc functionality for OsiriX DicomSeries class """

import os


def test_dicom_series_paths(grpc_stub, series_test):
    """ Check valid paths are returned """
    response = grpc_stub.DicomSeriesPaths(series_test)
    assert response.status.status == 1, f"Could not request paths"
    paths = response.paths
    assert len(paths) == 40, f"Incorrect number of paths ({len(paths)})"
    for path in paths:
        assert os.path.exists(path), f"Path {path} does not exist"


def test_dicom_series_next_series(grpc_stub, series_test):
    """ Check there is no next series. """
    response = grpc_stub.DicomSeriesNextSeries(series_test)
    assert response.status.status == 0, f"There should be no next series"


def test_dicom_series_previous_series(grpc_stub, series_test):
    """ Check there is no previous series. """
    response = grpc_stub.DicomSeriesPreviousSeries(series_test)
    assert response.status.status == 0, f"There should be no previous series"


def test_dicom_series_sorted_images(grpc_stub, series_test):
    """ Check that sorted images are provided. """
    response = grpc_stub.DicomSeriesSortedImages(series_test)
    assert response.status.status == 1, f"Could not request sorted images"
    images = response.sorted_images
    assert len(images) == 40, f"Bad number of sorted images {len(images)}"


def test_dicom_series_study(grpc_stub, series_test, study_test):
    """ Check the correct study instance is obtainable. """
    response = grpc_stub.DicomSeriesStudy(series_test)
    assert response.status.status == 1, f"Could not request study"
    study = response.study
    assert study.osirixrpc_uid == study_test.osirixrpc_uid, f"Bad study found"


def test_dicom_series_images(grpc_stub, series_test):
    """ Check that images are provided. """
    response = grpc_stub.DicomSeriesImages(series_test)
    assert response.status.status == 1, f"Could not request images"
    images = response.images
    assert len(images) == 40, f"Bad number of images ({len(images)})"


def test_dicom_series_series_instance_uid(grpc_stub, series_test, series_uid_test):
    """ Check that the correct series instance UID is provided. """
    response = grpc_stub.DicomSeriesSeriesInstanceUID(series_test)
    assert response.status.status == 1, f"Could not request series instance uid"
    assert response.series_instance_uid == series_uid_test,\
        f"Bad series instance UID {response.series_instance_uid}"


def test_dicom_series_series_sop_class_uid(grpc_stub, series_test):
    """ Check that the correct SOP class UID is returned. """
    response = grpc_stub.DicomSeriesSeriesSOPClassUID(series_test)
    assert response.status.status == 1, f"Could not request series sop class uid"
    assert response.series_sop_class_uid == "1.2.840.10008.5.1.4.1.1.4",\
        f"Bad sop class UID {response.series_sop_class_uid}"


def test_dicom_series_series_description(grpc_stub, series_test):
    """ Check that correct series description is returned. """
    response = grpc_stub.DicomSeriesSeriesDescription(series_test)
    assert response.status.status == 1, f"Could not request series description"
    assert response.series_description == "t2_tse_sag AP",\
        f"Bad series description {response.series_description}"


def test_dicom_series_modality(grpc_stub, series_test):
    """ Check the correct modality is returned. """
    response = grpc_stub.DicomSeriesModality(series_test)
    assert response.status.status == 1, f"Could not request series modality"
    assert response.modality == "MR", f"Bad modality {response.modality}"


def test_dicom_series_name(grpc_stub, series_test):
    """ Check the correct name ias returned. """
    response = grpc_stub.DicomSeriesName(series_test)
    assert response.status.status == 1, f"Could not request series name"
    assert response.name == "t2_tse_sag AP", f"Bad series name {response.name}"


def test_dicom_series_date(grpc_stub, series_test):
    """ Check the correct series date is returned. """
    response = grpc_stub.DicomSeriesDate(series_test)
    assert response.status.status == 1, f"Could not request series date"   # noqa: duplicate lines
    assert response.year == 2022, f"Bad year {response.year}"
    assert response.month == 8, f"Bad month {response.month}"
    assert response.day == 3, f"Bad day {response.day}"
    assert response.hour == 19, f"Bad hour {response.hour}"
    assert response.minute == 1, f"Bad minute {response.minute}"
    assert response.second == 23, f"Bad second {response.second}"
    assert response.millisecond == 1020924832, f"Bad millisecond {response.millisecond}"


def test_dicom_series_number_of_images(grpc_stub, series_test):
    """ Check correct number of images returned """
    response = grpc_stub.DicomSeriesNumberOfImages(series_test)
    assert response.status.status == 1, f"Could not request number of images"
    assert response.number_of_images == 40, f"Bad number of images {response.number_of_images}"
