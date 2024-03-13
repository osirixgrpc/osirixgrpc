""" Close the windows that were opened. """


def test_close_viewers(grpc_stub, viewer_controller_2d, viewer_controller_4d):
    """ Close the 4D viewer (and the associated VRController). """
    response = grpc_stub.ViewerControllerCloseViewer(viewer_controller_2d)
    assert response.status.status == 1, f"Could not close 2D viewer"
    response = grpc_stub.ViewerControllerCloseViewer(viewer_controller_4d)
    assert response.status.status == 1, f"Could not close 4D viewer"
