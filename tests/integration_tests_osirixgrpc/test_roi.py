""" Test the osirixgrpc functionality for OsiriX ROI class """
import pytest
from osirixgrpc import roi_pb2, viewercontroller_pb2


def test_roi_name(grpc_stub, roi_pencil_test):
    """ Check that the ROI name is provided. """
    response = grpc_stub.ROIName(roi_pencil_test)
    assert response.status.status == 1, f"Could not request ROI name"
    assert response.name == "pencil", f"Bad ROI name {response.name}"


def test_roi_set_name(grpc_stub, roi_pencil_test):
    """ Check that the ROI name can be set (then return to original). """
    original_name = grpc_stub.ROIName(roi_pencil_test).name
    request = roi_pb2.ROISetNameRequest(roi=roi_pencil_test, name="my pencil")
    response = grpc_stub.ROISetName(request)
    assert response.status.status == 1, f"Could not set ROI name"
    assert grpc_stub.ROIName(roi_pencil_test).name == "my pencil", f"Could not confirm new ROI name"

    # Revert to original
    request = roi_pb2.ROISetNameRequest(roi=roi_pencil_test, name=original_name)
    response = grpc_stub.ROISetName(request)
    assert response.status.status == 1, f"Could not reset ROI name"


def test_roi_itype_pencil(grpc_stub, roi_pencil_test):
    """ Check the correct itype is provided (pencil ROI). """
    response = grpc_stub.ROIIType(roi_pencil_test)
    assert response.status.status == 1, f"Could not request ROI itype"
    assert response.itype == 15, f"Bad itype {response.itype}"


def test_roi_itype_mask(grpc_stub, roi_mask_test):
    """ Check the correct itype is provided (mask ROI). """
    response = grpc_stub.ROIIType(roi_mask_test)
    assert response.status.status == 1, f"Could not request ROI itype"
    assert response.itype == 20, f"Bad itype {response.itype}"


def test_roi_set_color(grpc_stub, roi_mask_test):
    """ Check the ROI color can be set (to red). """
    request = roi_pb2.ROISetColorRequest(roi=roi_mask_test, r=255, g=0, b=0)
    response = grpc_stub.ROISetColor(request)
    assert response.status.status == 1, f"Could not set ROI color"


def test_roi_color(grpc_stub, roi_mask_test):
    """ Check the correct ROI color is provided. """
    response = grpc_stub.ROIColor(roi_mask_test)
    assert response.status.status == 1, f"Could request ROI color"
    assert response.r == 255, f"Bad ROI red color {response.r}"
    assert response.g == 0, f"Bad ROI green color {response.g}"
    assert response.b == 0, f"Bad ROI blue color {response.b}"


def test_roi_set_opacity(grpc_stub, roi_mask_test):
    """ Check the ROI opacity can be set (to 0.5). """
    request = roi_pb2.ROISetOpacityRequest(roi=roi_mask_test, opacity=0.5)
    response = grpc_stub.ROISetOpacity(request)
    assert response.status.status == 1, f"Could not set ROI opacity"


def test_roi_opacity(grpc_stub, roi_mask_test):
    """ Check the correct ROI opacity is provided. """
    response = grpc_stub.ROIOpacity(roi_mask_test)
    assert response.status.status == 1, f"Could request ROI opacity"
    assert response.opacity == pytest.approx(0.5, abs=1e-2),\
        f"Bad ROI red opacity {response.opacity}"


def test_roi_set_thickness(grpc_stub, roi_pencil_test):
    """ Check the ROI thickness can be set (to 5.0). """
    request = roi_pb2.ROISetThicknessRequest(roi=roi_pencil_test, thickness=5.0)
    response = grpc_stub.ROISetThickness(request)
    assert response.status.status == 1, f"Could not set ROI thickness"


def test_roi_thickness(grpc_stub, roi_pencil_test):
    """ Check the correct ROI thickness is provided. """
    response = grpc_stub.ROIThickness(roi_pencil_test)
    assert response.status.status == 1, f"Could request ROI thickness"
    assert response.thickness == pytest.approx(5.0, abs=1e-2),\
        f"Bad ROI red thickness {response.thickness}"


def test_roi_set_points(grpc_stub, roi_pencil_test):
    """ Check that the points defining a polygonal ROI can be set. """
    points = [roi_pb2.ROISetPointsRequest.Point2D(x=10.5, y=10.5),
              roi_pb2.ROISetPointsRequest.Point2D(x=50.5, y=10.5),
              roi_pb2.ROISetPointsRequest.Point2D(x=50.5, y=50.5),
              roi_pb2.ROISetPointsRequest.Point2D(x=10.5, y=50.5)]
    request = roi_pb2.ROISetPointsRequest(roi=roi_pencil_test, points=points)
    response = grpc_stub.ROISetPoints(request)
    assert response.status.status == 1, f"Could not request set points."


def test_roi_points(grpc_stub, roi_pencil_test):
    """ Check the correct polygonal ROI points are provided. """
    response = grpc_stub.ROIPoints(roi_pencil_test)
    assert response.status.status == 1, f"Could not request ROI points"
    assert response.points[0].x == pytest.approx(10.5, abs=1e-2)
    assert response.points[0].y == pytest.approx(10.5, abs=1e-2)
    assert response.points[1].x == pytest.approx(50.5, abs=1e-2)
    assert response.points[1].y == pytest.approx(10.5, abs=1e-2)
    assert response.points[2].x == pytest.approx(50.5, abs=1e-2)
    assert response.points[2].y == pytest.approx(50.5, abs=1e-2)
    assert response.points[3].x == pytest.approx(10.5, abs=1e-2)
    assert response.points[3].y == pytest.approx(50.5, abs=1e-2)


def test_roi_area(grpc_stub, roi_pencil_test):
    """ Check the correct ROI area is provided. """
    response = grpc_stub.ROIArea(roi_pencil_test)
    assert response.status.status == 1, f"Could not request ROI area"
    assert response.area * 100 == pytest.approx(1474.59436, abs=1e-3),\
        f"Bad ROI area {response.area}"


def test_roi_centroid(grpc_stub, roi_pencil_test):
    """ Check the correct ROI centroid is provided. """
    response = grpc_stub.ROICentroid(roi_pencil_test)
    assert response.status.status == 1, f"Could not request ROI centroid"
    assert response.x == pytest.approx(30.5, abs=1e-1), f"Bad centroid x {response.x}"
    assert response.y == pytest.approx(30.5, abs=1e-1), f"Bad centroid y {response.y}"


def test_roi_flip_horizontally(grpc_stub, roi_pencil_test):
    """ Check the ROI can be flipped horizontally (and reset). """
    response = grpc_stub.ROIFlipHorizontally(roi_pencil_test)
    assert response.status.status == 1, f"Could not request ROI flip horizontally"

    points_new = grpc_stub.ROIPoints(roi_pencil_test).points
    assert points_new[0].x == pytest.approx(50.5, abs=1e-2)
    assert points_new[0].y == pytest.approx(10.5, abs=1e-2)
    assert points_new[1].x == pytest.approx(10.5, abs=1e-2)
    assert points_new[1].y == pytest.approx(10.5, abs=1e-2)
    assert points_new[2].x == pytest.approx(10.5, abs=1e-2)
    assert points_new[2].y == pytest.approx(50.5, abs=1e-2)
    assert points_new[3].x == pytest.approx(50.5, abs=1e-2)
    assert points_new[3].y == pytest.approx(50.5, abs=1e-2)

    response = grpc_stub.ROIFlipHorizontally(roi_pencil_test)
    assert response.status.status == 1, f"Could not reset ROI flip horizontally"


def test_roi_flip_vertically(grpc_stub, roi_pencil_test):
    """ Check the ROI can be flipped vertically (and reset). """
    response = grpc_stub.ROIFlipVertically(roi_pencil_test)
    assert response.status.status == 1, f"Could not request ROI flip vertically"

    points_new = grpc_stub.ROIPoints(roi_pencil_test).points
    assert points_new[0].x == pytest.approx(10.5, abs=1e-2)
    assert points_new[0].y == pytest.approx(50.5, abs=1e-2)
    assert points_new[1].x == pytest.approx(50.5, abs=1e-2)
    assert points_new[1].y == pytest.approx(50.5, abs=1e-2)
    assert points_new[2].x == pytest.approx(50.5, abs=1e-2)
    assert points_new[2].y == pytest.approx(10.5, abs=1e-2)
    assert points_new[3].x == pytest.approx(10.5, abs=1e-2)
    assert points_new[3].y == pytest.approx(10.5, abs=1e-2)

    response = grpc_stub.ROIFlipVertically(roi_pencil_test)
    assert response.status.status == 1, f"Could not reset ROI flip vertically"


def test_roi_move(grpc_stub, roi_pencil_test):
    """ Check the ROI can be moved by 10.5 columns and 5.5 rows (and reset). """
    request = roi_pb2.ROIMoveRequest(roi=roi_pencil_test, columns=10.5, rows=5.5)
    response = grpc_stub.ROIMove(request)
    assert response.status.status == 1, f"Could not request ROI move"

    points_new = grpc_stub.ROIPoints(roi_pencil_test).points
    assert points_new[0].x == pytest.approx(21.0, abs=1e-2)
    assert points_new[0].y == pytest.approx(16.0, abs=1e-2)
    assert points_new[1].x == pytest.approx(61.0, abs=1e-2)
    assert points_new[1].y == pytest.approx(16.0, abs=1e-2)
    assert points_new[2].x == pytest.approx(61.0, abs=1e-2)
    assert points_new[2].y == pytest.approx(56.0, abs=1e-2)
    assert points_new[3].x == pytest.approx(21.0, abs=1e-2)
    assert points_new[3].y == pytest.approx(56.0, abs=1e-2)

    request = roi_pb2.ROIMoveRequest(roi=roi_pencil_test, columns=-10.5, rows=-5.5)
    response = grpc_stub.ROIMove(request)
    assert response.status.status == 1, f"Could not reset ROI move"


def test_roi_rotate(grpc_stub, roi_pencil_test):
    """ Check that an ROI can be rotated by 90 degrees (and reset). """
    response = grpc_stub.ROICentroid(roi_pencil_test)
    request = roi_pb2.ROIRotateRequest(roi=roi_pencil_test, degrees=90., x=response.x, y=response.y)
    response = grpc_stub.ROIRotate(request)
    assert response.status.status == 1, f"Could not request ROI rotate"

    points_new = grpc_stub.ROIPoints(roi_pencil_test).points
    assert points_new[3].x == pytest.approx(10.5, abs=1e-2)
    assert points_new[3].y == pytest.approx(10.5, abs=1e-2)
    assert points_new[0].x == pytest.approx(50.5, abs=1e-2)
    assert points_new[0].y == pytest.approx(10.5, abs=1e-2)
    assert points_new[1].x == pytest.approx(50.5, abs=1e-2)
    assert points_new[1].y == pytest.approx(50.5, abs=1e-2)
    assert points_new[2].x == pytest.approx(10.5, abs=1e-2)
    assert points_new[2].y == pytest.approx(50.5, abs=1e-2)

    response = grpc_stub.ROICentroid(roi_pencil_test)
    request = roi_pb2.ROIRotateRequest(roi=roi_pencil_test, degrees=-90, x=response.x, y=response.y)
    response = grpc_stub.ROIRotate(request)
    assert response.status.status == 1, f"Could not reset ROI rotate"


def test_roi_pix(grpc_stub, viewer_controller_4d, roi_pencil_test):
    """ Check the correct DCMPix instance is returned. """
    request = viewercontroller_pb2.ViewerControllerPixListRequest(
        viewer_controller=viewer_controller_4d, movie_idx=0)
    pix = grpc_stub.ViewerControllerPixList(request).pix[39]
    request = viewercontroller_pb2.ViewerControllerROIListRequest(
        viewer_controller=viewer_controller_4d, movie_idx=0)
    roi = grpc_stub.ViewerControllerROIList(request).roi_slices[39].rois[0]
    response = grpc_stub.ROIPix(roi)
    assert response.status.status == 1, f"Could not request ROI DCMPix"
    assert response.pix.osirixrpc_uid == pix.osirixrpc_uid, f"Bad DCMPix returned"
