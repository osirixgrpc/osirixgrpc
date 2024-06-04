import os
import pytest

import osirix  # noqa


@pytest.fixture(scope="function")
def global_osirix_instance():
    yield osirix.global_osirix_instance()


@pytest.fixture(scope="function")
def secondary_port():
    yield 50003


@pytest.fixture(scope="function")
def secondary_service(secondary_port):
    service = osirix.osirix_utilities.OsirixService(domain="127.0.0.1",
                                                    port=secondary_port,
                                                    max_send_message_length=500000000,
                                                    max_receive_message_length=500000000)
    service.start_service()
    yield service
    service.stop_service()


@pytest.fixture(scope="function")
def browser_controller():
    yield osirix.current_browser()


@pytest.fixture(scope="function")
def dicom_paths():
    directory = os.path.abspath("../data/MR phantom")
    paths = [os.path.join(directory, path) for path in os.listdir(directory) if "dcm" in path]
    yield paths


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
def study_test(browser_controller, study_uid_test):
    """ Return the DicomStudy used during testing purposes """
    studies, series = browser_controller.database_selection()
    test_study = None
    for study in studies:
        study_uid = study.study_instance_uid
        if study_uid == study_uid_test:
            test_study = study
    yield test_study


@pytest.fixture(scope="function")
def series_test(study_test, series_uid_test):
    """ Return the DicomSeries used during testing purposes """
    series = study_test.series
    test_series = None
    for serie in series:
        series_uid = serie.series_instance_uid
        if series_uid == series_uid_test:
            test_series = serie
    yield test_series


@pytest.fixture(scope="function")
def image_test(series_test, image_uid_test):
    test_image = None
    for image in series_test.images:
        sop_instance_uid = image.sop_instance_uid
        if sop_instance_uid == image_uid_test:
            test_image = image
    yield test_image


@pytest.fixture(scope="function")
def viewer_controller_2d():
    viewers = osirix.displayed_2d_viewers()
    viewer_controller = None
    for viewer in viewers:
        if viewer.max_movie_index == 1:
            viewer_controller = viewer
    yield viewer_controller


@pytest.fixture(scope="function")
def viewer_controller_4d():
    viewers = osirix.displayed_2d_viewers()
    viewer_controller = None
    for viewer in viewers:
        if viewer.max_movie_index > 1:
            viewer_controller = viewer
    yield viewer_controller


@pytest.fixture(scope="function")
def dcm_pix_test(viewer_controller_2d):
    yield viewer_controller_2d.pix_list(0)[0]


@pytest.fixture(scope="function")
def roi_mask_test(viewer_controller_4d):
    rois = viewer_controller_4d.rois_with_name("pyosirix_mask", movie_idx=0)
    assert len(rois) > 0, \
        f"Could not find an roi with name 'pyosirix_mask'"
    yield rois[0]


@pytest.fixture(scope="function")
def roi_closed_polygon_test(viewer_controller_4d):
    rois = viewer_controller_4d.rois_with_name("pyosirix_closed_polygon", movie_idx=0)
    assert len(rois) > 0, \
        f"Could not find a pencil roi with name 'pyosirix_closed_polygon'"
    yield rois[0]


@pytest.fixture(scope="function")
def roi_open_polygon_test(viewer_controller_4d):
    rois = viewer_controller_4d.rois_with_name("pyosirix_open_polygon", movie_idx=0)
    assert len(rois) > 0, \
        f"Could not find a pencil roi with name 'pyosirix_open_polygon'"
    yield rois[0]


@pytest.fixture(scope="function")
def vr_controller_4d(viewer_controller_4d):
    yield viewer_controller_4d.vr_controllers()[0]


@pytest.fixture(scope="function")
def vr_controller_2d(viewer_controller_2d):
    yield viewer_controller_2d.vr_controllers()[0]


@pytest.fixture(scope="function")
def roi_volume_test(vr_controller_2d):
    roi_volume = None
    for rv in vr_controller_2d.roi_volumes():
        if rv.name == "pyosirix_mask":
            roi_volume = rv
    assert roi_volume is not None, f"Could not find correctly named ROI"
    yield roi_volume
