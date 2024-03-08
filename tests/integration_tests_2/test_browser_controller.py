""" Test the  osirixgrpc functionality for OsiriX BrowserController class """

from time import sleep

import pytest

from osirixgrpc import utilities_pb2, browsercontroller_pb2


@pytest.fixture(scope="function")
def browser_controller(grpc_stub):
    browser_controller = grpc_stub.OsirixCurrentBrowser(utilities_pb2.Empty()).browser_controller
    yield browser_controller


def test_dicom_import(grpc_stub, browser_controller, dicom_paths):
    request = browsercontroller_pb2.BrowserControllerCopyFilesIfNeededRequest(
        browser=browser_controller, paths=dicom_paths)
    response = grpc_stub.BrowserControllerCopyFilesIfNeeded(request)
    sleep(2)  # Is there a better way to do this? Import is run on a parallel osirix process.
    assert response.status.status == 1


def test_database_studies(grpc_stub, browser_controller):
    response = grpc_stub.BrowserControllerDatabaseStudies(browser_controller)
    print(response)
    assert response.status.status == 1


def test_database_selection_status(grpc_stub, browser_controller):
    response = grpc_stub.BrowserControllerDatabaseSelection(browser_controller)
    assert response.status.status == 1


def test_open_viewer(grpc_stub, browser_controller):
    database_selection = grpc_stub.BrowserControllerDatabaseSelection(browser_controller)
    study = database_selection.studies[0]
    dicom_images = grpc_stub.DicomStudyImages(study).images
    frames = [browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest.FrameImages(
        images=dicom_images)]
    request = browsercontroller_pb2.BrowserControllerOpenViewerFromImagesRequest(
        browser=browser_controller, frames=frames, movie=True)
    response = grpc_stub.BrowserControllerOpenViewerFromImages(request)
    assert response.status.status == 1
