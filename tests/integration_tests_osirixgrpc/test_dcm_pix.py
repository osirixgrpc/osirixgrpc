""" Test the osirixgrpc functionality for OsiriX DCMPix class """

import pytest
import numpy as np


def test_dcm_pix_dicom_image(grpc_stub, dcm_pix_test, image_test):
    """ Check that the correct dicom image is provided. """
    response = grpc_stub.DCMPixDicomImage(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dicom image"
    assert response.dicom_image.osirixrpc_uid == image_test.osirixrpc_uid, f"Bad dicom image"


def test_dcm_pix_dicom_series(grpc_stub, dcm_pix_test, series_test):
    """ Check that the correct dicom series is provided. """
    response = grpc_stub.DCMPixDicomSeries(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dicom series"
    assert response.dicom_series.osirixrpc_uid == series_test.osirixrpc_uid, f"Bad dicom series"


def test_dcm_pix_dicom_study(grpc_stub, dcm_pix_test, study_test):
    """ Check that the correct dicom study is provided. """
    response = grpc_stub.DCMPixDicomStudy(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dicom study"
    assert response.dicom_study.osirixrpc_uid == study_test.osirixrpc_uid, f"Bad dicom study"


def test_dcm_pix_spacing(grpc_stub, dcm_pix_test):
    """ Check the correct spacing is provided. """
    response = grpc_stub.DCMPixSpacing(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dcm pix spacing"
    assert response.spacing_rows == pytest.approx(0.78125, abs=1e-5), f"Bad spacing rows"
    assert response.spacing_columns == pytest.approx(0.78125, abs=1e-5), f"Bad spacing columns"


def test_dcm_pix_origin(grpc_stub, dcm_pix_test):
    """ Check the correct origin is provided. """
    response = grpc_stub.DCMPixOrigin(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dcm pix origin"
    assert response.origin_x == pytest.approx(-106.164879, abs=1e-5), f"Bad origin x"
    assert response.origin_y == pytest.approx(-56.6018143, abs=1e-5), f"Bad origin y"
    assert response.origin_z == pytest.approx(+124.136139, abs=1e-5), f"Bad origin z"


def test_dcm_pix_orientation(grpc_stub, dcm_pix_test):
    """ Check the correct orientation is provided. """
    response = grpc_stub.DCMPixOrientation(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dcm pix orientation"
    assert np.allclose(response.orientation, [0.0, 1.0, 0.0,
                                              0.0, 0.0, -1.0,
                                              -1.0, 0.0, 0.0], atol=1e-2), f"Bad orientation"


def test_dcm_pix_slice_location(grpc_stub, dcm_pix_test):
    """ Check the correct slice location is provided. """
    response = grpc_stub.DCMPixSliceLocation(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dcm pix slice location"
    assert response.slice_location == pytest.approx(-56.6018143, abs=1e-5), f"Bad slice location"

