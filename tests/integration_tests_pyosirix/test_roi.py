""" Test the osirixgrpc functionality for OsiriX ROI class """

import pytest
import numpy as np


def test_roi_name(roi_closed_polygon_test):
    """ Check that the ROI name is provided. """
    assert roi_closed_polygon_test.name == "pyosirix_closed_polygon", f"Bad ROI name {roi_pencil_test.name}"


def test_roi_set_name(roi_closed_polygon_test):
    """ Check that the ROI name can be set (then return to original). """
    roi_closed_polygon_test.name = "temp_polygon_name"
    assert roi_closed_polygon_test.name == "temp_polygon_name", f"Could not confirm new ROI name"
    roi_closed_polygon_test.name = "pyosirix_closed_polygon"
    assert roi_closed_polygon_test.name == "pyosirix_closed_polygon", f"Could not reset ROI name"


def test_roi_stype_cpolygon(roi_closed_polygon_test):
    """ Check the correct string type (and assumed itype) is provided (polygon closed ROI). """
    assert roi_closed_polygon_test.stype == "tCPolygon", f"Bad stype"


def test_roi_stype_opolygon(roi_open_polygon_test):
    """ Check the correct string type (and assumed itype) is provided (polygon open ROI). """
    assert roi_open_polygon_test.stype == "tOPolygon", f"Bad stype"


def test_roi_stype_mask(roi_mask_test):
    """ Check the correct string type (and assumed itype) is provided (mask/brush ROI). """
    assert roi_mask_test.stype == "tPlain", f"Bad stype"


def test_roi_set_get_color(roi_mask_test):
    """ Check the ROI color can be set (to red), and then obtained. """
    roi_mask_test.color = (255, 0, 0)
    assert np.allclose(roi_mask_test.color, (255, 0, 0)), f"Could not set ROI color"


def test_roi_set_get_opacity(roi_mask_test):
    """ Check the ROI opacity can be set (to 0.5). """
    roi_mask_test.opacity = 0.5
    assert roi_mask_test.opacity == pytest.approx(0.5, abs=1e-2), f"Could not set ROI opacity"


def test_roi_set_get_thickness(roi_closed_polygon_test):
    """ Check the ROI thickness can be set (to 5.0). """
    roi_closed_polygon_test.thickness = 5.0
    assert roi_closed_polygon_test.thickness == pytest.approx(5.0, abs=1e-2), \
        f"Could not set ROI thickness"


def test_roi_set_get_points(roi_closed_polygon_test):
    """ Check that the points defining a polygonal ROI can be set. """
    new_points = np.array([[10.5, 10.5],
                           [50.5, 10.5],
                           [50.5, 50.5],
                           [10.5, 50.5]])
    roi_closed_polygon_test.points = new_points
    assert np.allclose(roi_closed_polygon_test.points, new_points), f"Could not set ROI points"


def test_roi_area(roi_closed_polygon_test):
    """ Check the correct ROI area is provided. """
    assert roi_closed_polygon_test.roi_area() * 100 == pytest.approx(1474.5943, abs=1e-3),\
        f"Bad ROI area {roi_closed_polygon_test.roi_area()}"


def test_roi_centroid(roi_closed_polygon_test):
    """ Check the correct ROI centroid is provided. """
    assert np.allclose(roi_closed_polygon_test.centroid(), (30.5, 30.5)),\
        f"Bad centroid {roi_closed_polygon_test.centroid()}"


def test_roi_flip_horizontally(roi_closed_polygon_test):
    """ Check the ROI can be flipped horizontally (and reset). """
    flip_points = np.array([[50.5, 10.5],
                            [10.5, 10.5],
                            [10.5, 50.5],
                            [50.5, 50.5]])
    roi_closed_polygon_test.flip_horizontally()
    assert np.allclose(roi_closed_polygon_test.points, flip_points), \
        f"Could not ROI flip horizontally"
    roi_closed_polygon_test.flip_horizontally()


def test_roi_flip_vertically(roi_closed_polygon_test):
    """ Check the ROI can be flipped vertically (and reset). """
    flip_points = np.array([[10.5, 50.5],
                            [50.5, 50.5],
                            [50.5, 10.5],
                            [10.5, 10.5]])
    roi_closed_polygon_test.flip_vertically()
    assert np.allclose(roi_closed_polygon_test.points, flip_points), \
        f"Could not ROI flip vertically"
    roi_closed_polygon_test.flip_vertically()


def test_roi_move(roi_closed_polygon_test):
    """ Check the ROI can be moved by 10.5 columns and 5.5 rows (and reset). """
    move_points = np.array([[21.0, 16.0],
                            [61.0, 16.0],
                            [61.0, 56.0],
                            [21.0, 56.0]])
    roi_closed_polygon_test.roi_move(columns=10.5, rows=5.5)
    assert np.allclose(roi_closed_polygon_test.points, move_points), \
        f"Could not move ROI properly"
    roi_closed_polygon_test.roi_move(columns=-10.5, rows=-5.5)


def test_roi_rotate(roi_closed_polygon_test):
    """ Check that an ROI can be rotated by 90 degrees (and reset). """
    rotate_points = np.array([[50.5, 10.5],
                              [50.5, 50.5],
                              [10.5, 50.5],
                              [10.5, 10.5]])
    roi_closed_polygon_test.rotate(theta=90., center=None)  # About the centroid.
    assert np.allclose(roi_closed_polygon_test.points, rotate_points), \
        f"Could not rotate ROI properly"
    roi_closed_polygon_test.rotate(theta=-90., center=None)  # About the centroid.


def test_roi_pix(viewer_controller_4d, roi_closed_polygon_test):
    """ Check the correct DCMPix instance is returned. """
    assert viewer_controller_4d.pix_list(0)[39].pb2_object.osirixrpc_uid ==\
           roi_closed_polygon_test.pix.pb2_object.osirixrpc_uid, f"Bad DCMPix returned"
