""" Close the windows that were opened. """

from osirixgrpc import viewercontroller_pb2


def __delete_rois_in_viewer__(grpc_stub, viewer_controller):
    n_frames = grpc_stub.ViewerControllerMaxMovieIdx(viewer_controller).max_movie_idx
    for j in range(n_frames):
        request = viewercontroller_pb2.ViewerControllerROIListRequest(
            viewer_controller=viewer_controller, movie_idx=j)
        response = grpc_stub.ViewerControllerROIList(request)
        for roi_slice in response.roi_slices:
            for roi in roi_slice.rois:
                grpc_stub.ROIDelete(roi)


def test_delete_rois_2d(grpc_stub, viewer_controller_2d):
    """ Delete the created ROIs. """
    __delete_rois_in_viewer__(grpc_stub, viewer_controller_2d)



def test_close_viewer_2d(grpc_stub, viewer_controller_2d):
    """ Close the 2D viewer (and the associated VRController). """
    response = grpc_stub.ViewerControllerCloseViewer(viewer_controller_2d)
    assert response.status.status == 1, f"Could not close 2D viewer"


def test_delete_rois_4d(grpc_stub, viewer_controller_4d):
    """ Delete the created ROIs. """
    __delete_rois_in_viewer__(grpc_stub, viewer_controller_4d)


def test_close_viewer_4d(grpc_stub, viewer_controller_4d):
    """ Close the 4D viewer (and the associated VRController). """
    response = grpc_stub.ViewerControllerCloseViewer(viewer_controller_4d)
    assert response.status.status == 1, f"Could not close 4D viewer"
