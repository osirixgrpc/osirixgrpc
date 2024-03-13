""" Test the osirixgrpc functionality for OsiriX VRController class """

from osirixgrpc import vrcontroller_pb2


def test_vr_controller_style_2d(grpc_stub, vr_controller_2d):
    """ Check the correct style is provided. """
    response = grpc_stub.VRControllerStyle(vr_controller_2d)
    assert response.status.status == 1, f"Could not request style for 2D vr controller"
    assert response.style == "standard", f"Bad vr controller style {response.style}"


def test_vr_controller_style_4d(grpc_stub, vr_controller_4d):
    """ Check the correct style is provided. """
    response = grpc_stub.VRControllerStyle(vr_controller_4d)
    assert response.status.status == 1, f"Could not request style for 4D vr controller"
    assert response.style == "standard", f"Bad vr controller style {response.style}"


def test_vr_controller_title_2d(grpc_stub, vr_controller_2d):
    """ Check the title is provided for 2D VRController. """
    response = grpc_stub.VRControllerTitle(vr_controller_2d)
    assert response.status.status == 1, f"Could not request title for 2D vr controller"
    assert "3D Reconstruction:" in response.title, f"Bad title provided {response.title}"
    assert "t2_tse_sag AP" in response.title, f"Bad title provided {response.title}"


def test_vr_controller_title_4d(grpc_stub, vr_controller_4d):
    """ Check the title is provided for 4D VRController. """
    response = grpc_stub.VRControllerTitle(vr_controller_4d)
    assert response.status.status == 1, f"Could not request title for 4D vr controller"
    assert "3D Reconstruction:" in response.title, f"Bad title provided {response.title}"
    assert "t2_tse_sag AP" in response.title, f"Bad title provided {response.title}"
    assert "4D" in response.title, f"Bad title provided {response.title}"


def test_vr_controller_needs_display_update(grpc_stub, vr_controller_4d):
    """ Check the VRController display can be updated. """
    response = grpc_stub.VRControllerNeedsDisplayUpdate(vr_controller_4d)
    assert response.status.status == 1, f"Could not update vr controller display"


def test_vr_controller_viewer_2d(grpc_stub, vr_controller_2d, viewer_controller_2d):
    """ Check the correct ViewerController is linked to the volume display. """
    response = grpc_stub.VRControllerViewer2D(vr_controller_2d)
    assert response.status.status == 1, f"Could not request 2D viewer"
    assert response.viewer_controller.osirixrpc_uid == viewer_controller_2d.osirixrpc_uid, \
        f"Bad 2D viewer found"


def test_vr_controller_blending_viewer(grpc_stub, vr_controller_4d, viewer_controller_2d):
    """ Check the correct blending ViewerController is linked to the volume display. """
    response = grpc_stub.VRControllerBlendingController(vr_controller_4d)
    assert response.status.status == 1, f"Could not request blending viewer"
    assert response.viewer_controller.osirixrpc_uid == viewer_controller_2d.osirixrpc_uid, \
        f"Bad blending viewer found"


def test_vr_controller_set_wlww(grpc_stub, vr_controller_2d):
    """ Check the window level and width can be set. """
    request = vrcontroller_pb2.VRControllerSetWLWWRequest(vr_controller=vr_controller_2d,
                                                          wl=200,
                                                          ww=400)
    response = grpc_stub.VRControllerSetWLWW(request)
    assert response.status.status == 1, f"Could not set WLWW"


def test_vr_controller_wlww(grpc_stub, vr_controller_2d):
    """ Check the correct window level and width are provided. """
    response = grpc_stub.VRControllerWLWW(vr_controller_2d)
    assert response.status.status == 1, f"Could not request WLWW"
    assert response.wl == 200, f"Bad window level {response.wl}"
    assert response.ww == 400, f"Bad window width {response.ww}"


def test_vr_controller_set_rendering_mode_mip(grpc_stub, vr_controller_2d):
    """ Check the rendering mode can be set to MIP (max intensity projection). """
    request = vrcontroller_pb2.VRControllerSetRenderingModeRequest(vr_controller=vr_controller_2d,
                                                                   rendering_mode="MIP")
    response = grpc_stub.VRControllerSetRenderingMode(request)
    assert response.status.status == 1, f"Could not set rendering mode to MIP"


def test_vr_controller_rendering_mode_mip(grpc_stub, vr_controller_2d):
    """ Check the correct rendering mode is provided if MIP (max intensity projection). """
    response = grpc_stub.VRControllerRenderingMode(vr_controller_2d)
    assert response.status.status == 1, f"Could not request rendering mode"
    assert response.rendering_mode == "MIP", f"Bad rendering mode {response.rendering_mode}"


def test_vr_controller_set_rendering_mode_vr(grpc_stub, vr_controller_2d):
    """ Check the rendering mode can be set to VR (volume render). """
    request = vrcontroller_pb2.VRControllerSetRenderingModeRequest(vr_controller=vr_controller_2d,
                                                                   rendering_mode="VR")
    response = grpc_stub.VRControllerSetRenderingMode(request)
    assert response.status.status == 1, f"Could not set rendering mode to VR"


def test_vr_controller_rendering_mode_vr(grpc_stub, vr_controller_2d):
    """ Check the correct rendering mode is provided if VR (volume render). """
    response = grpc_stub.VRControllerRenderingMode(vr_controller_2d)
    assert response.status.status == 1, f"Could not request rendering mode"
    assert response.rendering_mode == "VR", f"Bad rendering mode {response.rendering_mode}"


def test_vr_controller_roi_volumes(grpc_stub, vr_controller_2d):
    """ Check ROIVolume instances can be accessed. """
    response = grpc_stub.VRControllerROIVolumes(vr_controller_2d)
    assert response.status.status == 1, f"Could not request VolumeROI instances"
    assert len(response.roi_volumes) == 1, f"Bad number of ROIVolumes {len(response.roi_volumes)}"


def test_vr_controller_display_roi_volume(grpc_stub, vr_controller_2d):
    """ Check that a contained ROIVolume can be displayed. """
    response = grpc_stub.VRControllerROIVolumes(vr_controller_2d)
    roi_volume = None
    for rv in response.roi_volumes:
        if grpc_stub.ROIVolumeName(rv).name == "mask":
            roi_volume = rv
    request = vrcontroller_pb2.VRControllerDisplayROIVolumeRequest(vr_controller=vr_controller_2d,
                                                                   roi_volume=roi_volume)
    response = grpc_stub.VRControllerDisplayROIVolume(request)
    assert response.status.status == 1, f"Could not display ROI volume"
