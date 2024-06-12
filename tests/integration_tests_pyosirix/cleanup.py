""" Close the windows that were opened and the created ROIs. """


def test_delete_rois(viewer_controller_2d, viewer_controller_4d):
    """ Delete the created ROIs. """
    def delete_rois_in_viewer(viewer_controller):
        for j in range(viewer_controller.max_movie_index):
            roi_list = viewer_controller.roi_list(j)
            for roi_slice in roi_list:
                for roi in roi_slice:
                    roi.delete()
    delete_rois_in_viewer(viewer_controller_2d)
    delete_rois_in_viewer(viewer_controller_4d)


def test_close_viewers(viewer_controller_2d, viewer_controller_4d):
    """ Close the viewers (and the associated VRControllers). """
    viewer_controller_2d.close()
    viewer_controller_4d.close()
