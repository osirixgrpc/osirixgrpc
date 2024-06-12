""" Test the osirixgrpc functionality for OsiriX DCMPix class """

import os

import pytest
import numpy as np

import osirix  # noqa


def test_dcm_pix_dicom_image(dcm_pix_test):
    """ Check that the correct dicom image is provided. """
    assert isinstance(dcm_pix_test.image_obj(), osirix.dicom.DicomImage), f"Bad DCMPix return type"


def test_dcm_pix_dicom_series(dcm_pix_test, series_test):
    """ Check that the correct dicom series is provided. """
    series = dcm_pix_test.series_obj()
    assert series.pb2_object.osirixrpc_uid == series_test.pb2_object.osirixrpc_uid,\
        f"Bad dicom series"


def test_dcm_pix_dicom_study(dcm_pix_test, study_test):
    """ Check that the correct dicom study is provided. """
    study = dcm_pix_test.study_obj()
    assert study.pb2_object.osirixrpc_uid == study_test.pb2_object.osirixrpc_uid, \
        f"Bad dicom study"


def test_dcm_pix_shape(dcm_pix_test):
    """ Check the correct shape is provided. """
    assert dcm_pix_test.shape[0] == 320, f"Bad number of columns"
    assert dcm_pix_test.shape[1] == 320, f"Bad number of rows"


def test_dcm_pix_spacing(dcm_pix_test):
    """ Check the correct spacing is provided. """
    assert dcm_pix_test.pixel_spacing[0] == pytest.approx(0.78125, abs=1e-5), f"Bad spacing rows"
    assert dcm_pix_test.pixel_spacing[1] == pytest.approx(0.78125, abs=1e-5), f"Bad spacing columns"


def test_dcm_pix_origin(dcm_pix_test):
    """ Check the correct origin is provided. """
    assert dcm_pix_test.origin[0] == pytest.approx(+72.0981827, abs=1e-5), f"Bad origin x"
    assert dcm_pix_test.origin[1] == pytest.approx(-106.164879, abs=1e-5), f"Bad origin y"
    assert dcm_pix_test.origin[2] == pytest.approx(+124.136139, abs=1e-5), f"Bad origin z"


def test_dcm_pix_orientation(dcm_pix_test):
    """ Check the correct orientation is provided. """
    assert np.allclose(dcm_pix_test.orientation, [0.0, 1.0, 0.0,
                                                  0.0, 0.0, -1.0,
                                                  -1.0, 0.0, 0.0], atol=1e-2), f"Bad orientation"


def test_dcm_pix_slice_location(dcm_pix_test):
    """ Check the correct slice location is provided. """
    assert dcm_pix_test.slice_location == pytest.approx(+72.0981827, abs=1e-5), \
        f"Bad slice location"


def test_dcm_pix_source_file(dcm_pix_test):
    """ Check a valid source file is provided. """
    assert os.path.exists(dcm_pix_test.source_file), f"Source file does not exist"


def test_dcm_pix_compute_roi(dcm_pix_test, roi_mask_test):
    """ Check that correct ROI statistics are provided. """
    stats = dcm_pix_test.compute_roi(roi_mask_test)
    assert isinstance(stats, dict), f"Bad ROI stats type"
    assert stats["mean"] == pytest.approx(0.525, abs=1e-5), f"Bad mean value for ROI"
    assert stats["total"] == pytest.approx(840, abs=1e-5), f"Bad total value for ROI"
    assert stats["std_dev"] == pytest.approx(0.60467, abs=1e-5), f"Bad std-dev value for ROI"
    assert stats["max"] == pytest.approx(3, abs=1e-5), f"Bad max value for ROI"
    assert stats["skewness"] == pytest.approx(0.77747, abs=1e-5), f"Bad skewness value for ROI"
    assert stats["kurtosis"] == pytest.approx(0.06178, abs=1e-5), f"Bad kurtosis value for ROI"


def test_dcm_pix_roi_values(dcm_pix_test, roi_mask_test):
    """ Check that correct values are obtained from an ROI. """
    rows, columns, values = dcm_pix_test.get_roi_values(roi_mask_test)
    assert np.mean(values) == pytest.approx(0.525, abs=1e-5), f"Bad mean value for ROI"
    assert np.sum(values) == pytest.approx(840, abs=1e-5), f"Bad total value for ROI"
    assert np.max(values) == pytest.approx(3, abs=1e-5), f"Bad max value for ROI"
    assert np.std(values) == pytest.approx(0.60467, abs=1e-5), f"Bad std-dev value for ROI"
    assert np.min(rows) == 0, f"Bad minimum row index"
    assert np.max(rows) == 39, f"Bad maximum row index"
    assert np.min(columns) == 0, f"Bad minimum column index"
    assert np.max(columns) == 39, f"Bad maximum column index"


def test_dcm_get_map_from_roi(dcm_pix_test, roi_mask_test):
    """ Check that an ROI mask can be obtained """
    mask = dcm_pix_test.get_map_from_roi(roi_mask_test)
    assert mask.shape[0] == 320, f"Bad number of rows {mask.shape[0]}"
    assert mask.shape[1] == 320, f"Bad number of rows {mask.shape[1]}"
    assert np.sum(mask) == 40 * 40, f"Bad number of map True values {np.sum(mask)}"


def test_dcm_pix_image_greyscale(dcm_pix_test):
    """ Check that a valid image is provided. """
    array = dcm_pix_test.image
    assert array.shape[0] == 320, f"Bad number of image columns"
    assert array.shape[1] == 320, f"Bad number of image rows"
    assert array.ndim == 2, f"Image should be greyscale"
    assert np.mean(array) == pytest.approx(201.55313, abs=1e-5), f"Bad greyscale image average"
    assert np.std(array) == pytest.approx(228.00445, abs=1e-5), f"Bad greyscale image std-dev"


def test_dcm_pix_set_image_greyscale(dcm_pix_test):
    """ Check that a DCMPix image can be manipulated (and return to original values). """
    dcm_pix_test.image = dcm_pix_test.image * 2
    assert np.mean(dcm_pix_test.image) == pytest.approx(201.55313 * 2, abs=1e-5), \
        f"Bad greyscale image average"
    dcm_pix_test.image = dcm_pix_test.image / 2  # Return to original values


def test_dcm_pix_is_greyscale(dcm_pix_test):
    """ Check the correct channel setting (greyscale) is provided. """
    assert dcm_pix_test.is_rgb is False, f"Should have greyscale data here"


def test_dcm_pix_is_rgb(dcm_pix_test):
    """ Check the correct channel setting (RGB) is provided. """
    dcm_pix_test.convert_to_rgb(mode=2)
    assert dcm_pix_test.is_rgb is True, f"Should have RGB data here"


def test_dcm_pix_compute_roi_rgb(dcm_pix_test, roi_mask_test):
    """ Check error raised when ROI stats are obtained from an RGB image. """
    with pytest.raises(osirix.exceptions.GrpcException) as exc:
        _ = dcm_pix_test.compute_roi(roi_mask_test)
    assert str(exc.value) == "No values provided for RGB pix", \
        f"Bad error message for RGB ROI stats"


def test_dcm_pix_roi_values_rgb(dcm_pix_test, roi_mask_test):
    """ Check error raised when ROI values are obtained from an RGB image. """
    with pytest.raises(osirix.exceptions.GrpcException) as exc:
        _ = dcm_pix_test.get_roi_values(roi_mask_test)
    assert str(exc.value) == "No values provided for RGB pix", \
        f"Bad error message for RGB ROI values"


def test_dcm_pix_image_argb(dcm_pix_test):
    """ Check that a DCMPix image can be obtained in ARGB format. """
    argb_array = dcm_pix_test.image
    assert argb_array.ndim == 3, f"ARGB image should have 3 dimensions"
    assert argb_array.shape[0] == 320, f"Bad number of rows"
    assert argb_array.shape[1] == 320, f"Bad number of columns"
    assert argb_array.shape[2] == 4, f"Bad number of channels"


def test_dcm_pix_set_image_rgb(dcm_pix_test):
    """ Check that DCMPix image values can be set in ARGB format. """
    argb_array = dcm_pix_test.image
    argb_array[:, :, 1] = 255
    dcm_pix_test.image = argb_array
    assert np.all(dcm_pix_test.image[:, :, 1] == 255), f"Could not set ARGB image"


def test_dcm_convert_to_bw(dcm_pix_test):
    """ Check DCMPix can be converted back to greyscale. """
    dcm_pix_test.convert_to_bw(mode=0)
    assert dcm_pix_test.image.ndim == 2, f"Converted image is not greyscale"
    assert np.all(dcm_pix_test.image == 255), f"Did not convert properly to greyscale"
