""" Test the osirixgrpc functionality for OsiriX ViewerController class """

from time import time

from osirixgrpc import viewercontroller_pb2, utilities_pb2


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
    print(response)
    assert response.status.status == 1, f"Could not request blending controller"
    assert response.blending_viewer.osirixrpc_uid == viewer_controller_2d.osirixrpc_uid


def test_viewer_controller_copy_viewer_window_in_4d(grpc_stub, viewer_controller_4d):
    """ Test that a window can be copied (shut down in next test). """
    request = viewercontroller_pb2.ViewerControllerCopyViewerWindowRequest(
        viewer_controller=viewer_controller_4d, in_4d=False)
    response = grpc_stub.ViewerControllerCopyViewerWindow(request)
    assert response.status.status == 1, f"Could not request copy viewer window"


def test_viewer_controller_close_viewer(grpc_stub, viewer_controller_2d, viewer_controller_4d):
    """ Check that a viewer can be closed. """
    # Wait for the new viewer to open
    t0 = time()
    viewers = grpc_stub.OsirixDisplayed2DViewers(utilities_pb2.Empty()).viewer_controllers
    while len(viewers) == 2 and time() - t0 < 10.0:
        viewers = grpc_stub.OsirixDisplayed2DViewers(utilities_pb2.Empty()).viewer_controllers
    assert len(viewers) > 2, f"Could not establish a third viewer"

    for viewer in viewers:
        if viewer.osirixrpc_uid == viewer_controller_2d.osirixrpc_uid:
            continue
        elif viewer.osirixrpc_uid == viewer_controller_4d.osirixrpc_uid:
            continue
        else:
            response = grpc_stub.ViewerControllerCloseViewer(viewer)
            assert response.status.status == 1, f"Could not close viewer"