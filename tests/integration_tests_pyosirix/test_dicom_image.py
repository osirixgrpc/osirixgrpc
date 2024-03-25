""" Test the functionality for pyOsiriX DicomImage class """

import os
from datetime import datetime, timedelta

import pytest


def test_dicom_image_sop_instance_uid(series_test):
    """ Check that a SOP instance is obtainable from the dicom images. """
    image = series_test.images[0]
    assert isinstance(image.sop_instance_uid, str)


def test_image_available(image_test):
    """ Check the intended test image available. """
    assert image_test is not None


def test_width(image_test):
    """ Check the image has the intended width. """
    assert image_test.width == 320, "Bad image width identified"


def test_height(image_test):
    """ Check the image has the intended height. """
    assert image_test.height == 320, "Bad image width identified"


def test_complete_path(image_test):
    """ Check that a complete path is provided. """
    assert os.path.exists(image_test.complete_path), f"Bad path provided"


def test_date(image_test):
    """ Check that the correct date is provided. """
    date = datetime.strptime("20220803190311", "%Y%m%d%H%M%S")
    assert abs(date - image_test.date) <= timedelta(seconds=1.0)


def test_number_of_frames(image_test):
    """ Check that the correct number of frames are provided. """
    assert image_test.number_of_frames == 1, f"Bad number_of_frames"


def test_modality(image_test):
    """ Check the modality is correct. """
    assert image_test.modality == "MR", f"Bad modality"


def test_series(image_test, series_test):
    """ Check the correct series is provided. """
    assert image_test.series.pb2_object.osirixrpc_uid == series_test.pb2_object.osirixrpc_uid,\
        f"Bad series"


def test_slice_location(image_test):
    """ Check the correct slice location is available. """
    assert image_test.slice_location == pytest.approx(-56.6018, abs=1e-4), f"Bad slice location"


def test_instance_number(image_test):
    """ Check the instance number is available. """
    assert image_test.instance_number == 1, f"Bad instance number"
