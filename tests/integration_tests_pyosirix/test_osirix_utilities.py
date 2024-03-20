import pytest

import osirix


def test_global_osirix_instance(global_osirix_instance):
    assert global_osirix_instance is not None


def test_check_connection(global_osirix_instance):
    assert global_osirix_instance.osirix_service.check_connection() is True, \
        f"Failed to start the OsiriX service. OsiriX may be closed."


def test_new_service_creation(secondary_service, secondary_port):
    assert secondary_service.check_connection() is True, f"Could not establish secondary connection"
    assert secondary_service.port == secondary_port, f"Bad port number {secondary_service.port}"


def test_current_browser(global_osirix_instance):
    assert global_osirix_instance.current_browser(), f"Could not establish current browser"


def test_viewer_controller_is_closed(global_osirix_instance):
    # There should be no viewer controller open yet.
    with pytest.raises(osirix.exceptions.GrpcException) as exc:
        global_osirix_instance.frontmost_viewer()
    assert str(exc.value) == "No ViewerController active", \
        f"Bad error message for no frontmost viewer controller"


def test_vr_controller_is_closed(global_osirix_instance):
    # There should be no vr controller open yet.
    with pytest.raises(osirix.exceptions.GrpcException) as exc:
        global_osirix_instance.frontmost_vr_controller()
    assert str(exc.value) == "No VRController active", \
        f"Bad error message for no frontmost VR controller"


def test_displayed_2d_viewers_is_zero(global_osirix_instance):
    vcs = global_osirix_instance.displayed_2d_viewers()
    assert len(vcs) == 0, f"There are one or more ViewerControllers open"


def test_displayed_vr_controllers_is_zero(global_osirix_instance):
    vcs = global_osirix_instance.displayed_vr_controllers()
    assert len(vcs) == 0, f"There are one or more VRControllers open"
