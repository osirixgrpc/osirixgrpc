""" Test the  osirixgrpc functionality for OsiriX BrowserController class """

from time import time

import pytest
import numpy as np

from osirixgrpc import utilities_pb2, browsercontroller_pb2


@pytest.fixture(scope="function")
def browser_controller(grpc_stub):
    browser_controller = grpc_stub.OsirixCurrentBrowser(utilities_pb2.Empty()).browser_controller
    yield browser_controller


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


def test_open_viewer(grpc_stub, browser_controller):
    """ Check that the database can be traversed and a series opened in 2D """
    # Search for the required study
    studies = grpc_stub.BrowserControllerDatabaseStudies(browser_controller).studies
    test_study_uid = "1.2.840.846310145.17.1.1.4515953"
    test_study = None
    for study in studies:
        response = grpc_stub.DicomStudyStudyInstanceUID(study)
        study_uid = response.study_instance_uid
        if study_uid == test_study_uid:
            test_study = study
    assert test_study is not None, f"Could not find test study data."

    # Search for the required series
    series = grpc_stub.DicomStudySeries(test_study).series
    test_series_uid = "1.3.12.2.1107.5.2.18.41171.2022080319011374970780396.0.0.0 TE-98"
    test_series = None
    for serie in series:
        response = grpc_stub.DicomSeriesSeriesInstanceUID(serie)
        series_uid = response.series_instance_uid
        if series_uid == test_series_uid:
            test_series = serie
    assert test_series is not None, f"Could not find test series data."

    # Sort the DicomImage instances be slice location.
    dicom_images = np.array(grpc_stub.DicomSeriesImages(test_series).images)
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
