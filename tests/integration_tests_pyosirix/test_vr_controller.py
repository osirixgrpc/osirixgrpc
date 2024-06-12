""" Test the osirixgrpc functionality for pyOsiriX VRController class """

import numpy as np


def test_vr_controller_style_2d(vr_controller_2d):
    """ Check the correct style is provided. """
    assert vr_controller_2d.style == "standard", f"Bad vr controller style {vr_controller_2d.style}"


def test_vr_controller_style_4d(vr_controller_4d):
    """ Check the correct style is provided. """
    assert vr_controller_4d.style == "standard", f"Bad vr controller style {vr_controller_4d.style}"


def test_vr_controller_title_2d(vr_controller_2d):
    """ Check the title is provided for 2D VRController. """
    assert "3D Reconstruction:" in vr_controller_2d.title,\
        f"Bad title provided {vr_controller_2d.title}"
    assert "t2_tse_sag AP" in vr_controller_2d.title,\
        f"Bad title provided {vr_controller_2d.title}"


def test_vr_controller_title_4d(vr_controller_4d):
    """ Check the title is provided for 4D VRController. """
    assert "3D Reconstruction:" in vr_controller_4d.title, \
        f"Bad title provided {vr_controller_4d.title}"
    assert "t2_tse_sag AP" in vr_controller_4d.title, f"Bad title provided {vr_controller_4d.title}"
    assert "4D" in vr_controller_4d.title, f"Bad title provided {vr_controller_4d.title}"


def test_vr_controller_needs_display_update(vr_controller_4d):
    """ Check the VRController display can be updated. """
    vr_controller_4d.needs_display_update()


def test_vr_controller_viewer_2d(vr_controller_2d, viewer_controller_2d):
    """ Check the correct ViewerController is linked to the volume display. """
    assert vr_controller_2d.viewer_2d().pb2_object.osirixrpc_uid ==\
           viewer_controller_2d.pb2_object.osirixrpc_uid, f"Bad 2D viewer found"


def test_vr_controller_blending_viewer(vr_controller_4d, viewer_controller_2d):
    """ Check the correct blending ViewerController is linked to the volume display. """
    assert vr_controller_4d.blending_controller().pb2_object.osirixrpc_uid ==\
           viewer_controller_2d.pb2_object.osirixrpc_uid, f"Bad blending viewer found"


def test_vr_controller_set_get_wlww(vr_controller_2d):
    """ Check the window level and width can be set (and get). """
    vr_controller_2d.wlww = (200, 400)
    assert np.allclose(vr_controller_2d.wlww, (200, 400)), f"Could not set WLWW"


def test_vr_controller_set_get_rendering_mode_mip(vr_controller_2d):
    """ Check the rendering mode can be set (and get) to MIP (max intensity projection). """
    vr_controller_2d.rendering_mode = "MIP"
    assert vr_controller_2d.rendering_mode == "MIP", f"Could not set rendering mode to MIP"


def test_vr_controller_set_rendering_mode_vr(vr_controller_2d):
    """ Check the rendering mode can be set (and get) to VR (volume render). """
    vr_controller_2d.rendering_mode = "VR"
    assert vr_controller_2d.rendering_mode == "VR", f"Could not set rendering mode to VR"


def test_vr_controller_roi_volumes(vr_controller_2d):
    """ Check ROIVolume instances can be accessed. """
    assert len(vr_controller_2d.roi_volumes()) >= 1,\
        f"Bad number of ROIVolumes {len(vr_controller_2d.roi_volumes())}"


def test_vr_controller_display_roi_volume(vr_controller_2d, roi_volume_test):
    """ Check that a contained ROIVolume can be displayed. """
    vr_controller_2d.display_roi_volume(roi_volume_test)


def test_vr_controller_hide_roi_volume(vr_controller_2d, roi_volume_test):
    """ Check that a contained ROIVolume can be displayed. """
    vr_controller_2d.hide_roi_volume(roi_volume_test)
    vr_controller_2d.display_roi_volume(roi_volume_test)  # Display again for subsequent tests
