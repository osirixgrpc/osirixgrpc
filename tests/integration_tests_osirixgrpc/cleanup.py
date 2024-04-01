""" Close the windows that were opened. """

from osirixgrpc import viewercontroller_pb2


def test_delete_rois(grpc_stub, viewer_controller_2d, viewer_controller_4d):
    """ Delete the created ROIs. """
    def delete_rois_in_viewer(viewer_controller):
        n_frames = grpc_stub.ViewerControllerMaxMovieIdx(viewer_controller).max_movie_idx
        for j in range(n_frames):
            request = viewercontroller_pb2.ViewerControllerROIListRequest(
                viewer_controller=viewer_controller, movie_idx=j)
            roi_slices = grpc_stub.ViewerControllerROIList(request).roi_slices
            for roi_slice in roi_slices:
                for roi in roi_slice.rois:
                    grpc_stub.ROIDelete(roi)
    delete_rois_in_viewer(viewer_controller_2d)
    delete_rois_in_viewer(viewer_controller_4d)


def test_close_viewers(grpc_stub, viewer_controller_2d, viewer_controller_4d):
    """ Close the 4D viewer (and the associated VRController). """
    response = grpc_stub.ViewerControllerCloseViewer(viewer_controller_2d)
    assert response.status.status == 1, f"Could not close 2D viewer"
    response = grpc_stub.ViewerControllerCloseViewer(viewer_controller_4d)
    assert response.status.status == 1, f"Could not close 4D viewer"
