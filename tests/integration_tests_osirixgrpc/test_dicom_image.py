""" Test the  osirixgrpc functionality for OsiriX DicomImage class """

import os

import pytest


def test_dicom_image_sop_instance_uid(grpc_stub, series_test):
    """ Check that a SOP instance is obtainable from the dicom images. """
    image = grpc_stub.DicomSeriesImages(series_test).images[0]
    response = grpc_stub.DicomImageSOPInstanceUID(image)
    assert response.status.status == 1


def test_image_available(image_test):
    """ Check the intended test image available. """
    assert image_test is not None


def test_width(grpc_stub, image_test):
    """ Check the image has the intended width. """
    response = grpc_stub.DicomImageWidth(image_test)
    assert response.status.status == 1, f"Could not request width"
    assert response.width == 320, "Bad image width identified"


def test_height(grpc_stub, image_test):
    """ Check the image has the intended height. """
    response = grpc_stub.DicomImageHeight(image_test)
    assert response.status.status == 1, f"Could not request height"
    assert response.height == 320, "Bad image width identified"


def test_complete_path(grpc_stub, image_test):
    """ Check that a complete path is provided. """
    response = grpc_stub.DicomImageCompletePath(image_test)
    assert response.status.status == 1, f"Could not request complete path"
    assert os.path.exists(response.path_name), f"Bad path provided"


def test_date(grpc_stub, image_test):
    """ Check that the correct date is provided. """
    response = grpc_stub.DicomImageDate(image_test)
    assert response.status.status == 1, f"Could not request date"
    assert response.year == 2022, f"Bad year"
    assert response.month == 8, f"Bad month"
    assert response.day == 3, f"Bad day"
    assert response.hour == 19, f"Bad hour"
    assert response.minute == 3, f"Bad minute"
    assert response.second == 11, f"Bad second"
    assert response.millisecond == 1718993592, f"Bad millisecond"


def test_number_of_frames(grpc_stub, image_test):
    """ Check that the correct number of frames are provided. """
    response = grpc_stub.DicomImageNumberOfFrames(image_test)
    assert response.status.status == 1, f"Could not request number of frames"
    assert response.number_of_frames == 1, f"Bad number_of_frames"


def test_modality(grpc_stub, image_test):
    """ Check the modality is correct. """
    response = grpc_stub.DicomImageModality(image_test)
    assert response.status.status == 1, f"Could not request modality"
    assert response.modality == "MR", f"Bad modality"


def test_series(grpc_stub, image_test, series_test):
    """ Check the correct series is provided. """
    response = grpc_stub.DicomImageSeries(image_test)
    assert response.status.status == 1, f"Could not request series"
    assert response.series.osirixrpc_uid == series_test.osirixrpc_uid, f"Bad series"


def test_slice_location(grpc_stub, image_test):
    """ Check the correct slice location is available. """
    response = grpc_stub.DicomImageSliceLocation(image_test)
    assert response.status.status == 1, f"Could not request slice location"
    assert response.slice_location == pytest.approx(-56.6018, abs=1e-4), f"Bad slice location"


def test_instance_number(grpc_stub, image_test):
    """ Check the instance number is available. """
    response = grpc_stub.DicomImageInstanceNumber(image_test)
    assert response.status.status == 1, f"Could not request instance number"
    assert response.instance_number == 1, f"Bad instance number"
