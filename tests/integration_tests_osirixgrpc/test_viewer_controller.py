""" Test the osirixgrpc functionality for OsiriX ViewerController class """

import numpy as np

from osirixgrpc import viewercontroller_pb2


def test_viewer_controller_2d_viewer(viewer_controller_2d):
    """ Check that a 2D viewer was found. """
    assert viewer_controller_2d is not None


def test_viewer_controller_4d_viewer(viewer_controller_4d):
    """ Check that a 4D viewer was found. """
    assert viewer_controller_4d is not None


def test_viewer_controller_max_movie_idx_2d(grpc_stub, viewer_controller_2d):
    """ Check that the correct max movie index is provided. """
    response = grpc_stub.ViewerControllerMaxMovieIdx(viewer_controller_2d)
    assert response.status.status == 1, f"Could not request 2D max movie index"
    assert response.max_movie_idx == 1, f"Bad max movie index {response.max_movie_idx}"


def test_viewer_controller_max_movie_idx_4d(grpc_stub, viewer_controller_4d):
    """ Check that the correct max movie index is provided. """
    response = grpc_stub.ViewerControllerMaxMovieIdx(viewer_controller_4d)
    assert response.status.status == 1, f"Could not request 4D max movie index"
    assert response.max_movie_idx == 2, f"Bad max movie index {response.max_movie_idx}"


def test_viewer_controller_set_idx(grpc_stub, viewer_controller_4d):
    """ Check the slice index can be set (start index = 0). """
    request = viewercontroller_pb2.ViewerControllerSetIdxRequest(
        viewer_controller=viewer_controller_4d, idx=10)
    response = grpc_stub.ViewerControllerSetIdx(request)
    assert response.status.status == 1, f"Could not set slice index"


def test_viewer_controller_get_idx(grpc_stub, viewer_controller_4d):
    """ Check the correct slice index is provided. """
    response = grpc_stub.ViewerControllerIdx(viewer_controller_4d)
    assert response.status.status == 1, f"Could not request slice index"
    assert response.idx == 10, f"Bad slice index {response.idx}"


def test_viewer_controller_set_movie_idx(grpc_stub, viewer_controller_4d):
    """ Check the movie index can be set. """
    request = viewercontroller_pb2.ViewerControllerSetMovieIdxRequest(
        viewer_controller=viewer_controller_4d, movie_idx=1)
    response = grpc_stub.ViewerControllerSetMovieIdx(request)
    assert response.status.status == 1, f"Could not set movie index"


def test_viewer_controller_get_movie_idx(grpc_stub, viewer_controller_4d):
    """ Check the correct movie index is provided. """
    response = grpc_stub.ViewerControllerMovieIdx(viewer_controller_4d)
    assert response.status.status == 1, f"Could not request movie index"
    assert response.movie_idx == 1, f"Bad movie index {response.movie_idx}"


def test_viewer_controller_needs_display_update(grpc_stub, viewer_controller_4d):
    """ Check the viewer can be updated. """
    response = grpc_stub.ViewerControllerNeedsDisplayUpdate(viewer_controller_4d)
    assert response.status.status == 1, f"Could not update viewer"


def test_viewer_controller_modality(grpc_stub, viewer_controller_4d):
    """ Check the correct modality is provided. """
    response = grpc_stub.ViewerControllerModality(viewer_controller_4d)
    assert response.status.status == 1, f"Could not request modality"
    assert response.modality == "MR"


def test_viewer_controller_set_wlww(grpc_stub, viewer_controller_4d):
    """ Check that the window level and width can be set. """
    request = viewercontroller_pb2.ViewerControllerSetWLWWRequest(
        viewer_controller=viewer_controller_4d, wl=100, ww=50)
    response = grpc_stub.ViewerControllerSetWLWW(request)
    assert response.status.status == 1, f"Could not set WLWW"


def test_viewer_controller_wlww(grpc_stub, viewer_controller_4d):
    """ Check that the correct window level and width are provided. """
    response = grpc_stub.ViewerControllerWLWW(viewer_controller_4d)
    assert response.status.status == 1, f"Could not request WLWW"
    assert response.wl == 100, f"Bad window level {response.wl}"
    assert response.ww == 50, f"Bad window level {response.ww}"


def test_viewer_controller_title(grpc_stub, viewer_controller_4d):
    """ Check that correct title is provided. """
    response = grpc_stub.ViewerControllerTitle(viewer_controller_4d)
    assert response.status.status == 1, f"Could not request title"
    assert "t2_tse_sag AP" in response.title


def test_viewer_controller_is_volumic_4d(grpc_stub, viewer_controller_4d):
    """ Check the data is volumic in 4d (in each frame individually). """
    request = viewercontroller_pb2.ViewerControllerIsDataVolumicRequest(
        viewer_controller=viewer_controller_4d, in_4d=True)
    response = grpc_stub.ViewerControllerIsDataVolumic(request)
    assert response.status.status == 1, f"Could not request is volumic"
    assert response.is_volumic, f"Data should be volumic"


def test_viewer_controller_is_volumic_2d(grpc_stub, viewer_controller_4d):
    """ Check the data is volumic in 2d (first frame?). """
    request = viewercontroller_pb2.ViewerControllerIsDataVolumicRequest(
        viewer_controller=viewer_controller_4d, in_4d=False)
    response = grpc_stub.ViewerControllerIsDataVolumic(request)
    assert response.status.status == 1, f"Could not request is volumic"
    assert response.is_volumic, f"Data should be volumic"


def test_viewer_controller_cur_dcm(grpc_stub, viewer_controller_4d):
    """ Check we can access the current DCMPix shown. """
    response = grpc_stub.ViewerControllerCurDCM(viewer_controller_4d)
    assert response.status.status == 1, f"Could not access current DCMPix"


def test_viewer_controller_pix_list(grpc_stub, viewer_controller_4d):
    """ Check we can access the complete set of DCMPix from the first and second frames. """
    request = viewercontroller_pb2.ViewerControllerPixListRequest(
        viewer_controller=viewer_controller_4d, movie_idx=0)
    response = grpc_stub.ViewerControllerPixList(request)
    assert response.status.status == 1, f"Could not obtain pix list for first frame"
    assert len(response.pix) == 40, f"Bad number of pix {len(response.pix)}"

    request = viewercontroller_pb2.ViewerControllerPixListRequest(
        viewer_controller=viewer_controller_4d, movie_idx=1)
    response = grpc_stub.ViewerControllerPixList(request)
    assert response.status.status == 1, f"Could not obtain pix list for second frame"
    assert len(response.pix) == 40, f"Bad number of pix {len(response.pix)}"


def test_viewer_controller_fuse_with_viewer(grpc_stub, viewer_controller_2d, viewer_controller_4d):
    """ Check that the 2D viewer can be fused on top of the 4D viewer. """
    request = viewercontroller_pb2.ViewerControllerFuseWithViewerRequest(
        viewer_controller=viewer_controller_4d, fusion_viewer_controller=viewer_controller_2d)
    response = grpc_stub.ViewerControllerFuseWithViewer(request)
    assert response.status.status == 1, f"Could not fuse viewers"


def test_viewer_controller_blending_controller(grpc_stub, viewer_controller_4d,
                                               viewer_controller_2d):
    """ Check the correct fusion viewer is provided. """
    response = grpc_stub.ViewerControllerBlendingController(viewer_controller_4d)
    assert response.status.status == 1, f"Could not request blending controller"
    assert response.blending_viewer.osirixrpc_uid == viewer_controller_2d.osirixrpc_uid


def test_viewer_controller_copy_viewer_window_and_close_4d(grpc_stub, viewer_controller_4d):
    """ Test that a 4D window can be copied (then shut it down!). """
    response = grpc_stub.ViewerControllerCopyViewerWindow(viewer_controller_4d)
    assert response.status.status == 1, f"Could not request copy viewer window"
    new_viewer = response.viewer_controller
    response = grpc_stub.ViewerControllerCloseViewer(new_viewer)
    assert response.status.status == 1, f"Could not close the new viewer"


def test_viewer_controller_copy_viewer_window_and_close_2d(grpc_stub, viewer_controller_2d):
    """ Test that a 4D window can be copied (then shut it down!). """
    response = grpc_stub.ViewerControllerCopyViewerWindow(viewer_controller_2d)
    assert response.status.status == 1, f"Could not request copy viewer window"
    new_viewer = response.viewer_controller
    response = grpc_stub.ViewerControllerCloseViewer(new_viewer)
    assert response.status.status == 1, f"Could not close the new viewer"


def test_viewer_controller_resample_viewer_window(grpc_stub, viewer_controller_2d):
    """ Try to resample the 2D viewer to itself (and close the result). """
    response = grpc_stub.ViewerControllerCopyViewerWindow(viewer_controller_2d)
    assert response.status.status == 1, f"Could not request copy viewer window"
    new_viewer = response.viewer_controller
    request = viewercontroller_pb2.ViewerControllerResampleViewerControllerRequest(
        viewer_controller=new_viewer, fixed_viewer_controller=viewer_controller_2d)
    response = grpc_stub.ViewerControllerResampleViewerController(request)
    assert response.status.status == 1, f"Could not resample data"
    new_viewer = response.resampled_viewer
    response = grpc_stub.ViewerControllerCloseViewer(new_viewer)
    assert response.status.status == 1, f"Could not close the new viewer"


def test_viewer_controller_new_roi_mask(grpc_stub, viewer_controller_4d):
    """ Check a new mask ROI can be created. Will create the same ROI on multiple slices. """
    rows = 40
    columns = 40
    slices = 10
    buffer_array = np.ones((rows, columns)).ravel().astype("int").tolist()
    for i in range(slices):
        buffer = viewercontroller_pb2.ViewerControllerNewROIRequest.Buffer(buffer=buffer_array,
                                                                           rows=rows,
                                                                           columns=columns)
        color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=0, b=200)
        request = viewercontroller_pb2.ViewerControllerNewROIRequest(
            viewer_controller=viewer_controller_4d, movie_idx=0, idx=i, itype=20,
            buffer=buffer, color=color, opacity=0.5, name="mask", buffer_position_x=i*3,
            buffer_position_y=i*5)
        response = grpc_stub.ViewerControllerNewROI(request)
        assert response.status.status == 1, f"Could not create new mask ROI"


def test_viewer_controller_new_roi_mask_2d(grpc_stub, viewer_controller_2d):
    """ Check a new mask ROI can be created in 2D viewer. Same ROI on multiple slices. """
    rows = 40
    columns = 40
    slices = 10
    buffer_array = np.ones((rows, columns)).ravel().astype("int").tolist()
    for i in range(slices):
        buffer = viewercontroller_pb2.ViewerControllerNewROIRequest.Buffer(buffer=buffer_array,
                                                                           rows=rows,
                                                                           columns=columns)
        color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=0, b=200)
        request = viewercontroller_pb2.ViewerControllerNewROIRequest(
            viewer_controller=viewer_controller_2d, movie_idx=0, idx=i, itype=20,
            buffer=buffer, color=color, opacity=0.5, name="mask", buffer_position_x=i*3,
            buffer_position_y=i*5)
        response = grpc_stub.ViewerControllerNewROI(request)
        assert response.status.status == 1, f"Could not create new mask ROI"


def test_viewer_controller_new_roi_oval(grpc_stub, viewer_controller_4d):
    """ Check that a new oval ROI can be created. """
    rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66.,
                                                                   origin_y=42.,
                                                                   width=20.,
                                                                   height=10.)
    color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=100, b=200)
    request = viewercontroller_pb2.ViewerControllerNewROIRequest(
        viewer_controller=viewer_controller_4d, movie_idx=1, idx=0, itype=9, rectangle=rect,
        color=color, opacity=0.5, name="oval", thickness=3.0)
    response = grpc_stub.ViewerControllerNewROI(request)
    assert response.status.status == 1, f"Could not create oval ROI"


def test_viewer_controller_new_roi_arrow(grpc_stub, viewer_controller_4d):
    """ Check that a new arrow ROI (points = [head, tail]) can be created. """
    points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=66., y=42.),
              viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=99., y=24.)]
    color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=0, g=255, b=0)
    request = viewercontroller_pb2.ViewerControllerNewROIRequest(
        viewer_controller=viewer_controller_4d, points=points, movie_idx=1, idx=0, itype=14,
        color=color, opacity=0.5, name="arrow", thickness=3.0)
    response = grpc_stub.ViewerControllerNewROI(request)
    assert response.status.status == 1, f"Could not create arrow ROI"


def test_viewer_controller_new_roi_point(grpc_stub, viewer_controller_4d):
    """ Check that a new 2D point ROI can be created. """
    rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42.,
                                                                   width=20., height=10.)
    color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=0, g=255, b=255)
    request = viewercontroller_pb2.ViewerControllerNewROIRequest(
        viewer_controller=viewer_controller_4d, rectangle=rect, movie_idx=1, idx=0, itype=19,
        color=color, opacity=1.0, name="2D point", thickness=3.0)
    response = grpc_stub.ViewerControllerNewROI(request)
    assert response.status.status == 1, f"Could not create oval ROI"


def test_viewer_controller_new_roi_troi(grpc_stub, viewer_controller_4d):
    """ Check that a new rectangle ROI can be created. """
    rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42.,
                                                                   width=20., height=10.)
    color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=100, b=100)
    request = viewercontroller_pb2.ViewerControllerNewROIRequest(
        viewer_controller=viewer_controller_4d, rectangle=rect, movie_idx=1, idx=0, itype=6,
        color=color, opacity=1.0, name="tROI (rectangle)", thickness=3.0)
    response = grpc_stub.ViewerControllerNewROI(request)
    assert response.status.status == 1, f"Could not create rectangle ROI (tROI)"


def test_viewer_controller_new_roi_text(grpc_stub, viewer_controller_4d):
    """ Check that a new text ROI can be created. """
    rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42.,
                                                                   width=20., height=10.)
    color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=100, b=100)
    request = viewercontroller_pb2.ViewerControllerNewROIRequest(
        viewer_controller=viewer_controller_4d, rectangle=rect, movie_idx=1, idx=0, itype=13,
        color=color, opacity=1.0, name="text", thickness=3.0)
    response = grpc_stub.ViewerControllerNewROI(request)
    assert response.status.status == 1, f"Could not create text ROI"


def test_viewer_controller_new_roi_ttagt(grpc_stub, viewer_controller_4d):
    """ Check that a new TTAGT ROI can be created. """
    points = [[50.20499802, 32.32217407], [53.27367783, 38.77323914], [64.68674469, 25.43341637],
              [69.71873474, 36.01180649], [41.8967247, 36.27430344], [68.91729736, 23.42099953]]
    points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=p[0], y=p[1]) for p in
              points]
    color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=250, b=220)
    request = viewercontroller_pb2.ViewerControllerNewROIRequest(
        viewer_controller=viewer_controller_4d, points=points, movie_idx=1, idx=0, itype=29,
        color=color, opacity=1.0, name="tTAGT", thickness=3.0)
    response = grpc_stub.ViewerControllerNewROI(request)
    assert response.status.status == 1, f"Could not create tTAGT ROI"


def test_viewer_controller_new_roi_pencil(grpc_stub, viewer_controller_4d):
    """ Check that a new pencil ROI can be created. """
    verts = [[50.20499802, 32.32217407], [53.27367783, 38.77323914], [64.68674469, 25.43341637],
             [69.71873474, 36.01180649], [41.8967247, 36.27430344], [68.91729736, 23.42099953]]
    for i in range(30, 40):
        points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=v[0], y=v[1])
                  for v in verts]
        color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=50, b=220)
        request = viewercontroller_pb2.ViewerControllerNewROIRequest(
            viewer_controller=viewer_controller_4d, points=points, movie_idx=0, idx=i,
            itype=15, color=color, opacity=1.0, name="pencil", thickness=3.0)
        response = grpc_stub.ViewerControllerNewROI(request)
        assert response.status.status == 1, f"Could not create pencil ROI"


def test_viewer_controller_new_roi_angle(grpc_stub, viewer_controller_4d):
    """ Check that a new angle ROI can be created. """
    points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=71., y=-2.),
              viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=67., y=11.),
              viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=90., y=9.)]
    color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=50, b=220)
    request = viewercontroller_pb2.ViewerControllerNewROIRequest(
        viewer_controller=viewer_controller_4d, points=points, movie_idx=1, idx=0, itype=12,
        color=color, opacity=1.0, name="angle", thickness=3.0)
    response = grpc_stub.ViewerControllerNewROI(request)
    assert response.status.status == 1, f"Could not create angle ROI"


def test_viewer_controller_new_roi_measure(grpc_stub, viewer_controller_4d):
    """ Check that a new measure ROI can be created. """
    points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=71., y=-2.),
              viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=67., y=11.)]
    color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=50, b=0)
    request = viewercontroller_pb2.ViewerControllerNewROIRequest(
        viewer_controller=viewer_controller_4d, points=points, movie_idx=1, idx=0, itype=5,
        color=color, opacity=1.0, name="measure", thickness=3.0)
    response = grpc_stub.ViewerControllerNewROI(request)
    assert response.status.status == 1, f"Could not create measure ROI"


def test_viewer_controller_roi_list(grpc_stub, viewer_controller_4d):
    """ Check that the list of ROIs can be returned. """
    request = viewercontroller_pb2.ViewerControllerROIListRequest(
        viewer_controller=viewer_controller_4d, movie_idx=1)
    response = grpc_stub.ViewerControllerROIList(request)
    assert response.status.status == 1, "Could not request ROI list"
    assert len(response.roi_slices) == 40, f"Incorrect number of slices {len(response.roi_slices)}"
    assert len(response.roi_slices[0].rois) == 8, f"There should be 8 new ROIs"


def test_viewer_controller_selected_rois(grpc_stub, viewer_controller_4d):
    """ Check the selected ROIs are returned. """
    response = grpc_stub.ViewerControllerSelectedROIs(viewer_controller_4d)
    assert response.status.status == 1, f"Could not request selected ROIs"


def test_viewer_controller_rois_with_name(grpc_stub, viewer_controller_4d):
    """ Check ROIs with name are provided. """
    request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(
        viewer_controller=viewer_controller_4d, name="mask", movie_idx=1, in_4d=True)
    response = grpc_stub.ViewerControllerROIsWithName(request)
    assert len(response.rois) == 10, f"Bad number of ROIs with name mask {len(response.rois)}"


def test_viewer_controller_open_vr_viewer_for_mode_vr_4d(grpc_stub, viewer_controller_4d):
    """ Check that we can open up a MIP viewer. """
    request = viewercontroller_pb2.ViewerControllerOpenVRViewerForModeRequest(
        viewer_controller=viewer_controller_4d, mode="VR")
    response = grpc_stub.ViewerControllerOpenVRViewerForMode(request)
    assert response.status.status == 1, f"Could not open VR viewer"


def test_viewer_controller_open_vr_viewer_for_mode_mip_2d(grpc_stub, viewer_controller_2d):
    """ Check that we can open up a MIP viewer. """
    request = viewercontroller_pb2.ViewerControllerOpenVRViewerForModeRequest(
        viewer_controller=viewer_controller_2d, mode="MIP")
    response = grpc_stub.ViewerControllerOpenVRViewerForMode(request)
    assert response.status.status == 1, f"Could not open MIP viewer"


def test_viewer_controller_4d(grpc_stub, viewer_controller_4d):
    response = grpc_stub.ViewerControllerVRControllers(viewer_controller_4d)
    assert response.status.status == 1, f"Could not find any open VRControllers for 4D viewer"


def test_viewer_controller_2d(grpc_stub, viewer_controller_2d):
    response = grpc_stub.ViewerControllerVRControllers(viewer_controller_2d)
    assert response.status.status == 1, f"Could not find any open VRControllers for 2D viewer"
