""" Test the osirixgrpc functionality for OsiriX ROIVolume class """

import pytest
import numpy as np


def test_roi_volume_name(roi_volume_test):
    """ Check the correct ROIVolume name is provided. """
    assert roi_volume_test.name == "pyosirix_mask", f"Bad roi volume name {roi_volume_test.name}"


def test_roi_volume_volume(roi_volume_test):
    """ Check the correct ROIVolume volume is provided.  Note this appears quite buggy? """
    assert roi_volume_test.volume() == pytest.approx(-29.0039, abs=1e-4)


def test_roi_volume_visible(roi_volume_test):
    """ Check the ROIVolume is visible. """
    assert roi_volume_test.visible is True, f"ROIVolume not visible"


def test_roi_volume_set_texture(roi_volume_test):
    """ Check that the ROIVolume texture can be set (and get). """
    roi_volume_test.texture = False
    assert roi_volume_test.texture is False, f"Could not set roi volume texture"


def test_roi_volume_set_factor(roi_volume_test):
    """ Check that the ROIVolume factor can be set (and get). """
    roi_volume_test.factor = 1.0
    assert roi_volume_test.factor == pytest.approx(1.0, 1e-1), \
        f"Bad roi volume factor {roi_volume_test.factor}"


def test_roi_volume_set_opacity(roi_volume_test):
    """ Check that the ROIVolume opacity can be set (and get). """
    roi_volume_test.opacity = 0.5
    assert roi_volume_test.opacity == pytest.approx(0.5, 1e-1), \
        f"Bad roi volume factor {roi_volume_test.opacity}"


def test_roi_volume_set_color(roi_volume_test):
    """ Check that the ROIVolume color can be set (and get). """
    roi_volume_test.color = (1., 1., 0.)
    assert np.allclose(roi_volume_test.color, (1., 1., 0.), atol=1e-2), \
        f"Bad roi volume color {roi_volume_test.color}"
