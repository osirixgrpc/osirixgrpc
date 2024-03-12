""" Configuration and fixtures for pytest """

import os

import pytest
import grpc

from osirixgrpc import osirix_pb2_grpc, utilities_pb2, viewercontroller_pb2


class GrpcTestException(Exception):
    """Exception raised when connection to OsiriX cannot be established

    Attributes:
        message (str): explanation of the error
    """
    def __init__(self, message=""):
        self.message = message
        super().__init__(self.message)


@pytest.fixture(scope="function")
def grpc_stub():
    try:
        port = 50001
        server_url_localhost = 'localhost:' + str(port)
        channel_opt = [('grpc.max_send_message_length', 512 * 1024 * 1024),
                       ('grpc.max_receive_message_length', 512 * 1024 * 1024)]
        channel = grpc.insecure_channel(server_url_localhost, options=channel_opt)
        stub = osirix_pb2_grpc.OsiriXServiceStub(channel)
    except Exception as exc:
        raise GrpcTestException(f"No connection to OsiriX can be established: {exc}")

    yield stub
    channel.close()


@pytest.fixture(scope="function")
def dicom_paths():
    directory = os.path.abspath("../data/MR phantom")
    paths = [os.path.join(directory, path) for path in os.listdir(directory) if "dcm" in path]
    yield paths


@pytest.fixture(scope="function")
def browser_controller(grpc_stub):
    browser_controller = grpc_stub.OsirixCurrentBrowser(utilities_pb2.Empty()).browser_controller
    yield browser_controller


@pytest.fixture(scope="function")
def viewer_controller_2d(grpc_stub):
    viewers = grpc_stub.OsirixDisplayed2DViewers(utilities_pb2.Empty()).viewer_controllers
    viewer_controller = None
    for viewer in viewers:
        response = grpc_stub.ViewerControllerMaxMovieIdx(viewer)
        max_movie_idx = response.max_movie_idx
        if max_movie_idx == 1:
            viewer_controller = viewer
    yield viewer_controller


@pytest.fixture(scope="function")
def viewer_controller_4d(grpc_stub):
    viewers = grpc_stub.OsirixDisplayed2DViewers(utilities_pb2.Empty()).viewer_controllers
    viewer_controller = None
    for viewer in viewers:
        response = grpc_stub.ViewerControllerMaxMovieIdx(viewer)
        max_movie_idx = response.max_movie_idx
        if max_movie_idx > 1:
            viewer_controller = viewer
    yield viewer_controller


@pytest.fixture(scope="function")
def study_uid_test():
    """ The test study UID """
    yield "1.2.840.846310145.17.1.1.4515953"


@pytest.fixture(scope="function")
def series_uid_test():
    """ The core test series UID for 2D testing. """
    yield "1.3.12.2.1107.5.2.18.41171.2022080319011374970780396.0.0.0 TE-98"


@pytest.fixture(scope="function")
def image_uid_test():
    """ An image SOP instance UID used for testing """
    yield "1.3.12.2.1107.5.2.18.41171.2022080319050545343380519"


@pytest.fixture(scope="function")
def study_test(grpc_stub, browser_controller, study_uid_test):
    """ Return the DicomStudy used during testing purposes """
    studies = grpc_stub.BrowserControllerDatabaseStudies(browser_controller).studies
    test_study = None
    for study in studies:
        response = grpc_stub.DicomStudyStudyInstanceUID(study)
        study_uid = response.study_instance_uid
        if study_uid == study_uid_test:
            test_study = study
    yield test_study


@pytest.fixture(scope="function")
def series_test(grpc_stub, study_test, series_uid_test):
    """ Return the DicomSeries used during testing purposes """
    series = grpc_stub.DicomStudySeries(study_test).series
    test_series = None
    for serie in series:
        response = grpc_stub.DicomSeriesSeriesInstanceUID(serie)
        series_uid = response.series_instance_uid
        if series_uid == series_uid_test:
            test_series = serie
    yield test_series


@pytest.fixture(scope="function")
def image_test(grpc_stub, series_test, image_uid_test):
    images = grpc_stub.DicomSeriesImages(series_test).images
    test_image = None
    for image in images:
        response = grpc_stub.DicomImageSOPInstanceUID(image)
        sop_instance_uid = response.sop_instance_uid
        if sop_instance_uid == image_uid_test:
            test_image = image
    yield test_image


@pytest.fixture(scope="function")
def dcm_pix_test(grpc_stub, viewer_controller_2d, image_test):
    request = viewercontroller_pb2.ViewerControllerPixListRequest(
        viewer_controller=viewer_controller_2d, movie_idx=0)
    response = grpc_stub.ViewerControllerPixList(request)
    yield response.pix[0]


@pytest.fixture(scope="function")
def roi_mask_test(grpc_stub, viewer_controller_4d):
    request = viewercontroller_pb2.ViewerControllerROIListRequest(
        viewer_controller=viewer_controller_4d, movie_idx=0)
    response = grpc_stub.ViewerControllerROIList(request)
    roi = response.roi_slices[0].rois[0]
    assert grpc_stub.ROIName(roi).name == "mask"
    yield roi
