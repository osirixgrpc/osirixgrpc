""" Test the osirixgrpc functionality for OsiriX ROIVolume class """

import pytest

from osirixgrpc import roivolume_pb2


def test_roi_volume_name(grpc_stub, roi_volume_test):
    """ Check the correct ROIVolume name is provided. """
    response = grpc_stub.ROIVolumeName(roi_volume_test)
    assert response.status.status == 1, f"Could not request roi volume name"
    assert response.name == "mask", f"Bad roi volume name {response.name}"


def test_roi_volume_volume(grpc_stub, roi_volume_test):
    """ Check the correct ROIVolume volume is provided.  Note this appears quite buggy? """
    response = grpc_stub.ROIVolumeVolume(roi_volume_test)
    assert response.status.status == 1, f"Could not request roi volume volume"
    assert response.volume == pytest.approx(-29.0039, abs=1e-4)


def test_roi_volume_visible(grpc_stub, roi_volume_test):
    """ Check the ROIVolume is visible. """
    response = grpc_stub.ROIVolumeVisible(roi_volume_test)
    assert response.status.status == 1, f"Could not request roi volume visible"
    assert response.visible is True, f"ROIVolume not visible"


def test_roi_volume_set_texture(grpc_stub, roi_volume_test):
    """ Check that the ROIVolume texture can be set. """
    request = roivolume_pb2.ROIVolumeSetTextureRequest(roi=roi_volume_test, texture=False)
    response = grpc_stub.ROIVolumeSetTexture(request)
    assert response.status.status == 1, f"Could not set roi volume texture"


def test_roi_volume_texture(grpc_stub, roi_volume_test):
    """ Check the correct ROIVolume texture status is provided. """
    response = grpc_stub.ROIVolumeTexture(roi_volume_test)
    assert response.status.status == 1, f"Could not request roi volume texture"
    assert response.texture is False, f"Texture is not False"


def test_roi_volume_set_factor(grpc_stub, roi_volume_test):
    """ Check that the ROIVolume factor can be set. """
    request = roivolume_pb2.ROIVolumeSetFactorRequest(roi=roi_volume_test, factor=1.0)
    response = grpc_stub.ROIVolumeSetFactor(request)
    assert response.status.status == 1, f"Could not set roi volume factor"


def test_roi_volume_factor(grpc_stub, roi_volume_test):
    """ Check the correct ROIVolume factor is provided. """
    response = grpc_stub.ROIVolumeFactor(roi_volume_test)
    assert response.status.status == 1, f"Could not request roi volume factor"
    assert response.factor == pytest.approx(1.0, 1e-1), f"Bad roi volume factor {response.factor}"


def test_roi_volume_set_opacity(grpc_stub, roi_volume_test):
    """ Check that the ROIVolume opacity can be set. """
    request = roivolume_pb2.ROIVolumeSetOpacityRequest(roi=roi_volume_test, opacity=0.5)
    response = grpc_stub.ROIVolumeSetOpacity(request)
    assert response.status.status == 1, f"Could not set roi volume opacity"


def test_roi_volume_opacity(grpc_stub, roi_volume_test):
    """ Check the correct ROIVolume opacity is provided. """
    response = grpc_stub.ROIVolumeOpacity(roi_volume_test)
    assert response.status.status == 1, f"Could not request roi volume opacity"
    assert response.opacity == pytest.approx(0.5, 1e-1),\
        f"Bad roi volume opacity {response.opacity}"


def test_roi_volume_set_color(grpc_stub, roi_volume_test):
    """ Check that the ROIVolume color can be set. """
    request = roivolume_pb2.ROIVolumeSetColorRequest(roi=roi_volume_test, r=1.0, g=1.0, b=0.0)
    response = grpc_stub.ROIVolumeSetColor(request)
    assert response.status.status == 1, f"Could not set roi volume color"


def test_roi_volume_color(grpc_stub, roi_volume_test):
    """ Check the correct ROIVolume color is provided. """
    response = grpc_stub.ROIVolumeColor(roi_volume_test)
    assert response.status.status == 1, f"Could not request roi volume color"
    assert response.r == pytest.approx(1.0, abs=1e-2), f"Bad roi volume red color {response.r}"
    assert response.g == pytest.approx(1.0, abs=1e-2), f"Bad roi volume green color {response.r}"
    assert response.b == pytest.approx(0.0, abs=1e-2), f"Bad roi volume blue color {response.r}"
