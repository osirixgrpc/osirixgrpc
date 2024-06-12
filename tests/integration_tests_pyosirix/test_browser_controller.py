""" Test the pyosirix functionality for OsiriX BrowserController class """

from time import time

import numpy as np
import pytest

import osirix  # noqa


def test_browser_studies_status(browser_controller):
    """ Check that the number of studies is 1. """
    studies, series = browser_controller.database_selection()
    assert len(studies) == 1, f"Bad number of studies {len(studies)}"
    assert len(series) == 0, f"Bad number of series {len(series)}"


def test_wait_for_database_studies(browser_controller):
    """ Check data is imported. Wait for it to become available. """
    now = time()
    time_limit = 5.0
    studies = None
    while studies is None and time() - now < time_limit:
        studies_, series_ = browser_controller.database_selection()
        if len(studies_) > 0:
            studies = studies_

    assert len(studies) == 1, f"There should only be one test study in the database."
    assert studies is not None, f"Data not loaded within {time_limit} seconds."


def test_study_available(study_test):
    """ Check the test study is loaded """
    assert study_test is not None


def test_series_available(series_test):
    """ Check the test study is loaded """
    assert series_test is not None


def test_open_viewer_2d_error_bad_frames(browser_controller):
    """ Test a 2D viewer cannot be opened with multiframe input. """
    bad_dicom_images = np.array([np.ones(20), np.ones(20)])
    with pytest.raises(ValueError) as exc:
        browser_controller.open_viewer_2d(bad_dicom_images)
    assert str(exc.value) == "The input array must be one dimensional.", \
        f"Bad error message for multi-frame input for open 2D viewer"


def test_open_viewer_2d_error_bad_type(browser_controller):
    """ Test a 2D viewer cannot be opened with bad input data type. """
    bad_dicom_images = np.ones(20)
    with pytest.raises(ValueError) as exc:
        browser_controller.open_viewer_2d(bad_dicom_images)
    assert str(exc.value) == "Only instances of DicomImage are permitted as input.", \
        f"Bad error message for bad input types for open 2D viewer"


def test_open_viewer_2d_error_bad_number(browser_controller):
    """ Test a 2D viewer cannot be opened with no images. """
    bad_dicom_images = np.array([])
    with pytest.raises(ValueError) as exc:
        browser_controller.open_viewer_2d(bad_dicom_images)
    assert str(exc.value) == "The number of input images must be one or greater.", \
        f"Bad error message for 0-length input for open 2D viewer"


def test_open_viewer_2d(browser_controller, series_test):
    """ Test a 2D viewer can be opened with good input. """
    dicom_images = np.array(series_test.images)
    sorted_idx = np.argsort([image.slice_location for image in dicom_images])
    dicom_images = dicom_images[sorted_idx]
    viewer_controller = browser_controller.open_viewer_2d(dicom_images)
    assert isinstance(viewer_controller, osirix.viewer_controller.ViewerController), \
        f"Bad viewer instance {type(viewer_controller)}"


def test_open_viewer_4d_error_bad_frames(browser_controller):
    """ Test a 4D viewer cannot be opened with single frame input. """
    bad_dicom_images = [np.ones(20)]
    with pytest.raises(ValueError) as exc:
        browser_controller.open_viewer_4d(bad_dicom_images)
    err_str = f"Number of input frames must be > 1. For single frame use `open_viewer_2d`."
    assert str(exc.value) == err_str, \
        f"Bad error message for single frame input for open 4D viewer"


def test_open_viewer_4d_error_bad_type(browser_controller):
    """ Test a 4D viewer cannot be opened with bad input data type. """
    bad_dicom_images = np.ones((2, 20))
    with pytest.raises(ValueError) as exc:
        browser_controller.open_viewer_4d(bad_dicom_images)
    assert str(exc.value) == "Only instances of DicomImage are permitted as input.", \
        f"Bad error message for bad input types for open 4D viewer"


def test_open_viewer_4d_error_bad_number(browser_controller):
    """ Test a 4D viewer cannot be opened with no images. """
    bad_dicom_images = [[], []]
    with pytest.raises(ValueError) as exc:
        browser_controller.open_viewer_4d(bad_dicom_images)
    assert str(exc.value) == "Number of input images must be 1 or greater.", \
        f"Bad error message for 0-length input images for open 4D viewer"


def test_open_viewer_4d_error_bad_dimensions(browser_controller):
    """ Test a 4D viewer cannot be opened with bad input dimensions. """
    bad_dicom_images = np.ones(20)
    with pytest.raises(ValueError) as exc:
        browser_controller.open_viewer_4d(bad_dicom_images)
    assert str(exc.value) == "The input array must be two dimensional.", \
        f"Bad error message for bad input dimensions for open 4D viewer"


def test_open_viewer_4d(browser_controller, series_test):
    """ Test a 4D viewer can be opened with good input. """
    dicom_images = np.array(series_test.images)
    sorted_idx = np.argsort([image.slice_location for image in dicom_images])
    dicom_images = [dicom_images[sorted_idx], dicom_images[sorted_idx]]
    viewer_controller = browser_controller.open_viewer_4d(dicom_images)
    assert isinstance(viewer_controller, osirix.viewer_controller.ViewerController), \
        f"Bad viewer instance {type(viewer_controller)}"
