""" Test the osirixgrpc functionality for OsiriX DCMPix class """

import os

import pytest
import numpy as np

from osirixgrpc import dcmpix_pb2


def test_dcm_pix_dicom_image(grpc_stub, dcm_pix_test, image_test):
    """ Check that the correct dicom image is provided. """
    response = grpc_stub.DCMPixDicomImage(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dicom image"


def test_dcm_pix_dicom_series(grpc_stub, dcm_pix_test, series_test):
    """ Check that the correct dicom series is provided. """
    response = grpc_stub.DCMPixDicomSeries(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dicom series"


def test_dcm_pix_dicom_study(grpc_stub, dcm_pix_test, study_test):
    """ Check that the correct dicom study is provided. """
    response = grpc_stub.DCMPixDicomStudy(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dicom study"


def test_dcm_pix_shape(grpc_stub, dcm_pix_test):
    """ Check the correct shape is provided. """
    response = grpc_stub.DCMPixShape(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dcm pix shape"
    assert response.rows == 320
    assert response.columns == 320


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
    assert response.origin_x == pytest.approx(+72.0981827, abs=1e-5), f"Bad origin x"
    assert response.origin_y == pytest.approx(-106.164879, abs=1e-5), f"Bad origin y"
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
    assert response.slice_location == pytest.approx(+72.0981827, abs=1e-5), f"Bad slice location"


def test_dcm_pix_source_file(grpc_stub, dcm_pix_test):
    """ Check a valid source file is provided. """
    response = grpc_stub.DCMPixSourceFile(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dcm pix source file"
    assert os.path.exists(response.source_file), f"Source file does not exist"


def test_dcm_pix_compute_roi(grpc_stub, dcm_pix_test, roi_mask_test):
    """ Check that correct ROI statistics are provided. """
    request = dcmpix_pb2.DCMPixComputeROIRequest(pix=dcm_pix_test, roi=roi_mask_test)
    response = grpc_stub.DCMPixComputeROI(request)
    assert response.status.status == 1, f"Could not request compute ROI"
    assert response.mean == pytest.approx(0.525, abs=1e-5), f"Bad mean value for ROI"
    assert response.total == pytest.approx(840, abs=1e-5), f"Bad total value for ROI"
    assert response.std_dev == pytest.approx(0.60467, abs=1e-5), f"Bad std-dev value for ROI"
    assert response.max == pytest.approx(3, abs=1e-5), f"Bad max value for ROI"
    assert response.skewness == pytest.approx(0.77747, abs=1e-5), f"Bad skewness value for ROI"
    assert response.kurtosis == pytest.approx(0.06178, abs=1e-5), f"Bad kurtosis value for ROI"


def test_dcm_pix_roi_values(grpc_stub, dcm_pix_test, roi_mask_test):
    """ Check that correct values are obtained from an ROI. """
    request = dcmpix_pb2.DCMPixROIValuesRequest(pix=dcm_pix_test, roi=roi_mask_test)
    response = grpc_stub.DCMPixROIValues(request)
    assert response.status.status == 1, f"Could not request ROI values"
    assert np.mean(response.values) == pytest.approx(0.525, abs=1e-5), f"Bad mean value for ROI"
    assert np.sum(response.values) == pytest.approx(840, abs=1e-5), f"Bad total value for ROI"
    assert np.max(response.values) == pytest.approx(3, abs=1e-5), f"Bad max value for ROI"
    assert np.std(response.values) == pytest.approx(0.60467, abs=1e-5), f"Bad std-dev value for ROI"
    assert np.min(response.row_indices) == 0, f"Bad minimum row index"
    assert np.max(response.row_indices) == 39, f"Bad maximum row index"
    assert np.min(response.column_indices) == 0, f"Bad minimum column index"
    assert np.max(response.column_indices) == 39, f"Bad maximum column index"


def test_dcm_get_map_from_roi(grpc_stub, dcm_pix_test, roi_mask_test):
    """ Check that an ROI mask can be obtained """
    request = dcmpix_pb2.DCMPixGetMapFromROIRequest(pix=dcm_pix_test, roi=roi_mask_test)
    response = grpc_stub.DCMPixGetMapFromROI(request)
    assert response.status.status == 1, f"Could not request map from ROI"
    assert response.rows == 320, f"Bad number of map rows {response.rows}"
    assert response.columns == 320, f"Bad number of map columns {response.columns}"
    assert len(response.map) == 320 * 320, f"Bad number of map pixels {len(response.map)}"
    assert np.sum(response.map) == 40 * 40, f"Bad number of map True values {np.sum(response.map)}"


def test_dcm_pix_image_greyscale(grpc_stub, dcm_pix_test):
    """ Check that a valid image is provided. """
    response = grpc_stub.DCMPixImage(dcm_pix_test)
    assert response.status.status == 1, f"Could not request dcm pix image"
    assert response.rows == 320, f"Bad number of image rows"
    assert response.columns == 320, f"Bad number of image columns"
    assert response.is_argb is False, f"Image should be greyscale"
    array = np.array(response.image_data_float).reshape(response.rows, response.columns)
    assert np.mean(array) == pytest.approx(201.55313, abs=1e-5), f"Bad greyscale image average"
    assert np.std(array) == pytest.approx(228.00445, abs=1e-5), f"Bad greyscale image std-dev"


def test_dcm_pix_set_image_greyscale(grpc_stub, dcm_pix_test):
    """ Check that a DCMPix image can be manipulated (and return to original values). """
    response = grpc_stub.DCMPixImage(dcm_pix_test)
    values = response.image_data_float
    new_values = [v * 2 for v in values]
    request = dcmpix_pb2.DCMPixSetImageRequest(pix=dcm_pix_test, image_data_float=new_values)
    response = grpc_stub.DCMPixSetImage(request)
    assert response.status.status == 1, f"Could not request set image values"
    response = grpc_stub.DCMPixImage(dcm_pix_test)
    assert np.mean(response.image_data_float) == pytest.approx(201.55313 * 2, abs=1e-5), \
        f"Bad greyscale image average"

    # Return to original values
    request = dcmpix_pb2.DCMPixSetImageRequest(pix=dcm_pix_test, image_data_float=values)
    response = grpc_stub.DCMPixSetImage(request)
    assert response.status.status == 1, f"Could not reset image values"


def test_dcm_pix_is_greyscale(grpc_stub, dcm_pix_test):
    """ Check the correct channel setting (greyscale) is provided. """
    response = grpc_stub.DCMPixIsRGB(dcm_pix_test)
    assert response.status.status == 1, f"Could not request is RGB"
    assert response.is_rgb is False, f"Should have greyscale data here"


def test_dcm_pix_convert_to_rgb(grpc_stub, dcm_pix_test):
    """ Check that DCMPix can be converted to RGB (red in this case). """
    request = dcmpix_pb2.DCMPixConvertToRGBRequest(pix=dcm_pix_test, rgb_channel=0)
    response = grpc_stub.DCMPixConvertToRGB(request)
    assert response.status.status == 1, f"Could not convert to RGB"


def test_dcm_pix_is_rgb(grpc_stub, dcm_pix_test):
    """ Check the correct channel setting (RGB) is provided. """
    response = grpc_stub.DCMPixIsRGB(dcm_pix_test)
    assert response.status.status == 1, f"Could not request is RGB"
    assert response.is_rgb is True, f"Should have RGB data here"


def test_dcm_pix_compute_roi_rgb(grpc_stub, dcm_pix_test, roi_mask_test):
    """ Check error raised when ROI stats are obtained from an RGB image. """
    request = dcmpix_pb2.DCMPixComputeROIRequest(pix=dcm_pix_test, roi=roi_mask_test)
    response = grpc_stub.DCMPixComputeROI(request)
    assert response.status.status == 0, f"Should not be able to access ROI statistics"


def test_dcm_pix_roi_values_rgb(grpc_stub, dcm_pix_test, roi_mask_test):
    """ Check error raised when ROI values are obtained from an RGB image. """
    request = dcmpix_pb2.DCMPixROIValuesRequest(pix=dcm_pix_test, roi=roi_mask_test)
    response = grpc_stub.DCMPixROIValues(request)
    assert response.status.status == 0, f"Should not be able to access ROI values"


def test_dcm_pix_image_argb(grpc_stub, dcm_pix_test):
    """ Check that a DCMPix image can be obtained in ARGB format. """
    response = grpc_stub.DCMPixImage(dcm_pix_test)
    assert response.status.status == 1, f"Could not request get ARGB image values"
    assert response.rows == 320, f"Bad number of rows"
    assert response.columns == 320, f"Bad number of columns"
    assert len(response.image_data_argb) == 320 * 320 * 4, f"Bad number of image values"


def test_dcm_pix_set_image_rgb(grpc_stub, dcm_pix_test):
    """ Check that DCMPix image values can be set in ARGB format. """
    response = grpc_stub.DCMPixImage(dcm_pix_test)
    assert response.status.status == 1, f"Could not request get ARGB image values"
    argb = np.array(response.image_data_argb).reshape((response.rows, response.columns, 4))
    argb[:, :, 2] = 255
    argb = argb.astype("uint8").ravel().tolist()
    request = dcmpix_pb2.DCMPixSetImageRequest(pix=dcm_pix_test, image_data_argb=argb)
    response = grpc_stub.DCMPixSetImage(request)
    assert response.status.status == 1, f"Could not set ARGB values"


def test_dcm_convert_to_bw(grpc_stub, dcm_pix_test):
    """ Check DCMPix can be converted back to greyscale. """
    request = dcmpix_pb2.DCMPixConvertToBWRequest(pix=dcm_pix_test, bw_channel=0)
    response = grpc_stub.DCMPixConvertToBW(request)
    assert response.status.status == 1, f"Could not convert back to greyscale."
    assert grpc_stub.DCMPixIsRGB(dcm_pix_test).is_rgb is False, f"Image not in greyscale"
