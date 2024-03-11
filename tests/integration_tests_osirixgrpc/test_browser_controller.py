""" Test the osirixgrpc functionality for OsiriX BrowserController class """

from time import time

import numpy as np

from osirixgrpc import browsercontroller_pb2


def test_browser_studies_status(grpc_stub, browser_controller):
    """ Check that the studies can be accessed """
    response = grpc_stub.BrowserControllerDatabaseStudies(browser_controller)
    assert response.status.status == 1,\
           f"Could not access browser studies. Status is {response.status.status}"


def test_browser_is_empty(grpc_stub, browser_controller):
    """ This ensures that the browser is empty as a first test """
    response = grpc_stub.BrowserControllerDatabaseStudies(browser_controller)
    assert len(response.studies) == 0,\
           f"There appear to be existing studies in the browser. Please start an empty database."


def test_browser_import(grpc_stub, browser_controller, dicom_paths):
    """ Try to import the test data """
    request = browsercontroller_pb2.BrowserControllerCopyFilesIfNeededRequest(
        browser=browser_controller, paths=dicom_paths)
    response = grpc_stub.BrowserControllerCopyFilesIfNeeded(request)
    assert response.status.status == 1,\
           f"Could not import the data. Status is {response.status.status}"


def test_wait_for_database_studies(grpc_stub, browser_controller):
    """ Try to find the appropriate test study """
    # Wait until it become available from thread.
    now = time()
    time_limit = 5.0
    studies = None
    while studies is None and time() - now < time_limit:
        response = grpc_stub.BrowserControllerDatabaseStudies(browser_controller)
        if len(response.studies) > 0:
            studies = response.studies

    assert studies is not None, f"Data not loaded within {time_limit} seconds."


def test_database_selection(grpc_stub, browser_controller):
    """ Check that a database selection can be obtained """
    response = grpc_stub.BrowserControllerDatabaseSelection(browser_controller)
    assert response.status.status == 1


def test_study_available(study_test):
    """ Check the test study is loaded """
    assert study_test is not None


def test_series_available(series_test):
    """ Check the test study is loaded """
    assert series_test is not None


def test_open_viewer_2d(grpc_stub, browser_controller, study_test, series_test):
    """ Check that the database can be traversed and a series opened in 2D """
    # Sort the DicomImage instances by slice location.
    dicom_images = np.array(grpc_stub.DicomSeriesImages(series_test).images)
    sorted_idx = np.argsort([grpc_stub.DicomImageSliceLocation(image).slice_location
                             for image in dicom_images])
    dicom_images = dicom_images[sorted_idx].tolist()

    # Generate the request and start.
    frames = [browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest.FrameImages(
        images=dicom_images)]
    request = browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest(
        browser=browser_controller, frames=frames, movie=False)
    response = grpc_stub.BrowserControllerOpenViewerFromImages(request)
    assert response.status.status == 1


def test_open_viewer_4d(grpc_stub, browser_controller, study_test, series_test):
    """ Check that the database can be traversed and a series opened in 4D """
    # Sort the DicomImage instances by slice location.
    dicom_images = np.array(grpc_stub.DicomSeriesImages(series_test).images)
    sorted_idx = np.argsort([grpc_stub.DicomImageSliceLocation(image).slice_location
                             for image in dicom_images])
    dicom_images = dicom_images[sorted_idx].tolist()

    # Generate the request and start.
    frames = [browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest.FrameImages(
                  images=dicom_images),
              browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest.FrameImages(
                  images=dicom_images)]
    request = browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest(
        browser=browser_controller, frames=frames, movie=True)
    response = grpc_stub.BrowserControllerOpenViewerFromImages(request)
    assert response.status.status == 1
