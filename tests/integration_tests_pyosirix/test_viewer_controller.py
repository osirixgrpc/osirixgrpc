""" Test the osirixgrpc functionality for pyOsiriX ViewerController class """

import numpy as np

import osirix  # noqa


def test_viewer_controller_2d_viewer(viewer_controller_2d):
    """ Check that a 2D viewer was found. """
    assert viewer_controller_2d is not None


def test_viewer_controller_4d_viewer(viewer_controller_4d):
    """ Check that a 4D viewer was found. """
    assert viewer_controller_4d is not None


def test_viewer_controller_max_movie_index_2d(viewer_controller_2d):
    """ Check that the correct max movie index is provided. """
    assert viewer_controller_2d.max_movie_index == 1, \
        f"Bad max movie index {viewer_controller_2d.max_movie_index}"


def test_viewer_controller_max_movie_index_4d(viewer_controller_4d):
    """ Check that the correct max movie index is provided. """
    assert viewer_controller_4d.max_movie_index == 2, \
        f"Bad max movie index {viewer_controller_4d.max_movie_index}"


def test_viewer_controller_set_get_idx(viewer_controller_4d):
    """ Check the slice index can be set and obtained. """
    viewer_controller_4d.idx = 10
    assert viewer_controller_4d.idx == 10, f"The idx property should be updated to 10."


def test_viewer_controller_set_get_movie_idx(viewer_controller_4d):
    """ Check the movie index can be set and obtained. """
    viewer_controller_4d.movie_idx = 1
    assert viewer_controller_4d.movie_idx == 1,  f"Bad movie index {viewer_controller_4d.movie_idx}"


def test_viewer_controller_needs_display_update(viewer_controller_4d):
    """ Check the viewer can be updated. """
    viewer_controller_4d.needs_display_update()


def test_viewer_controller_modality(viewer_controller_4d):
    """ Check the correct modality is provided. """
    assert viewer_controller_4d.modality == "MR"


def test_viewer_controller_set_get_wlww(viewer_controller_4d):
    """ Check that the window level and width can be set. """
    new_wlww = (100, 50)
    viewer_controller_4d.wlww = new_wlww
    assert np.allclose(viewer_controller_4d.wlww, new_wlww)


def test_viewer_controller_title(viewer_controller_4d):
    """ Check that correct title is provided. """
    assert "t2_tse_sag AP" in viewer_controller_4d.title


def test_viewer_controller_is_volumic_4d(viewer_controller_4d):
    """ Check the data is volumic in 4d (in each frame individually). """
    assert viewer_controller_4d.is_data_volumic(in_4d=True), f"Data should be volumic"


def test_viewer_controller_is_volumic_2d(viewer_controller_4d):
    """ Check the data is volumic in 2d (first frame). """
    assert viewer_controller_4d.is_data_volumic(in_4d=False), f"Data should be volumic"


def test_viewer_controller_cur_dcm(viewer_controller_4d):
    """ Check we can access the current DCMPix shown. """
    pix = viewer_controller_4d.cur_dcm()
    assert isinstance(pix, osirix.dcm_pix.DCMPix), f"Bad instance returned"


def test_viewer_controller_pix_list(viewer_controller_4d):
    """ Check we can access the complete set of DCMPix from the first and second frames. """
    assert len(viewer_controller_4d.pix_list(0)) == 40, \
        f"Bad number of pix {len(viewer_controller_4d.pix_list(0))} in first frame"
    assert len(viewer_controller_4d.pix_list(1)) == 40, \
        f"Bad number of pix {len(viewer_controller_4d.pix_list(0))} in second frame"


def test_viewer_controller_fuse_with_viewer(viewer_controller_2d, viewer_controller_4d):
    """ Check that the 2D viewer can be fused on top of the 4D viewer. """
    viewer_controller_4d.fuse_with_viewer(viewer_controller_2d)


def test_viewer_controller_blending_controller(viewer_controller_4d, viewer_controller_2d):
    """ Check the correct fusion viewer is provided. """
    assert viewer_controller_4d.blending_controller().pb2_object.osirixrpc_uid ==\
           viewer_controller_2d.pb2_object.osirixrpc_uid, f"Bad blending controller"


def test_viewer_controller_copy_viewer_window_and_close_4d(viewer_controller_4d):
    """ Test that a 4D window can be copied (then shut it down). """
    new_viewer = viewer_controller_4d.copy_viewer_window()
    assert isinstance(new_viewer, osirix.viewer_controller.ViewerController)
    new_viewer.close_viewer()


def test_viewer_controller_resample_viewer_window(viewer_controller_2d):
    """ Try to resample the 2D viewer to itself (and close the result). """
    new_viewer = viewer_controller_2d.copy_viewer_window()
    new_viewer = new_viewer.resample_viewer_controller(viewer_controller_2d)
    new_viewer.close_viewer()


def test_viewer_controller_new_roi_mask(viewer_controller_4d):
    """ Check a new mask ROI can be created. Will create the same ROI on multiple slices. """
    rows = 40
    columns = 40
    slices = 10
    buffer_array = np.ones((rows, columns)) > 0
    for i in range(slices):
        roi = viewer_controller_4d.new_mask_roi(buffer=buffer_array,
                                                name="pyosirix_mask",
                                                idx=i,
                                                movie_idx=0,
                                                buffer_position_column=i*3,
                                                buffer_position_row=i*5,
                                                color=(255, 255, 0),
                                                opacity=0.5)
        assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_mask_2d(viewer_controller_2d):
    """ Check a new mask ROI can be created in 2D viewer. Same ROI on multiple slices. """
    rows = 40
    columns = 40
    slices = 10
    buffer_array = np.ones((rows, columns)) > 0
    for i in range(slices):
        roi = viewer_controller_2d.new_mask_roi(buffer=buffer_array,
                                                name="pyosirix_mask",
                                                idx=i,
                                                movie_idx=0,
                                                buffer_position_column=i * 3,
                                                buffer_position_row=i * 5,
                                                color=(255, 255, 0),
                                                opacity=0.5)
        assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_oval(viewer_controller_4d):
    """ Check that a new oval ROI can be created. """
    roi = viewer_controller_4d.new_oval_roi(center=(66., 42.),
                                            width=40.,
                                            height=20.,
                                            name="pyosirix_oval",
                                            idx=0,
                                            movie_idx=1,
                                            thickness=3.0,
                                            color=(255, 100, 200),
                                            opacity=0.5)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_oval_angle(viewer_controller_4d):
    """ Check that a new oval angle ROI can be created. """
    roi = viewer_controller_4d.new_oval_angle_roi(center=(76., 52.),
                                                  width=40.,
                                                  height=20.,
                                                  name="pyosirix_oval_angle",
                                                  idx=0,
                                                  movie_idx=1,
                                                  thickness=3.0,
                                                  color=(200, 100, 0),
                                                  opacity=0.5)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_rectangle(viewer_controller_4d):
    """ Check that a new rectangle ROI can be created. """
    roi = viewer_controller_4d.new_rectangle_roi(center=(66., 42.),
                                                 width=40.,
                                                 height=20.,
                                                 name="pyosirix_rect",
                                                 idx=0,
                                                 movie_idx=1,
                                                 thickness=3.0,
                                                 color=(0, 200, 200),
                                                 opacity=0.5)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_arrow(viewer_controller_4d):
    """ Check that a new arrow ROI can be created. """
    roi = viewer_controller_4d.new_arrow_roi(tail=(50., 50.),
                                             head=(155.5, 100.5),
                                             name="pyosirix_arrow",
                                             idx=0,
                                             movie_idx=1,
                                             thickness=3.0,
                                             color=(0, 255, 0),
                                             opacity=0.5)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_point(viewer_controller_4d):
    """ Check that a new point ROI can be created. """
    roi = viewer_controller_4d.new_point_roi(column=200.,
                                             row=255.5,
                                             name="pyosirix_point",
                                             idx=0,
                                             movie_idx=1,
                                             thickness=3.0,
                                             color=(255, 0, 255),
                                             opacity=0.5)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_text(viewer_controller_4d):
    """ Check that a new point ROI can be created. """
    roi = viewer_controller_4d.new_text_roi(column=100.,
                                            row=255.5,
                                            name="pyosirix_text",
                                            idx=0,
                                            movie_idx=1,
                                            thickness=3.0,
                                            color=(255, 255, 255),
                                            opacity=0.5)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_ttagt(viewer_controller_4d):
    """ Check that a new TTAGT ROI can be created. """
    a = (100., 100.)
    d = (200., 200.)
    b = (100., 200.)
    c = (150., 200.)
    roi = viewer_controller_4d.new_tagt_roi(a=a,
                                            b=b,
                                            c=c,
                                            d=d,
                                            name="pyosirix_tagt",
                                            idx=0,
                                            movie_idx=1,
                                            thickness=3.0,
                                            color=(0, 255, 0),
                                            opacity=0.75)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_angle(viewer_controller_4d):
    """ Check that a new angle ROI can be created. """
    p1 = (71., -2.)
    p2 = (67., 11.)
    p3 = (90., 9.)
    roi = viewer_controller_4d.new_angle_roi(p1=p1,
                                             p2=p2,
                                             p3=p3,
                                             name="pyosirix_angle",
                                             idx=0,
                                             movie_idx=1,
                                             thickness=3.0,
                                             color=(255, 0, 0),
                                             opacity=0.75)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_measure(viewer_controller_4d):
    """ Check that a new measure ROI can be created. """
    roi = viewer_controller_4d.new_measurement_roi(start=(71., -2.),
                                                   end=(67., 11.),
                                                   name="pyosirix_measurement",
                                                   idx=0,
                                                   movie_idx=1,
                                                   thickness=3.0,
                                                   color=(255, 255, 0),
                                                   opacity=1.0)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_dynamic_angle(viewer_controller_4d):
    """ Check that a new dynamic angle ROI can be created. """
    roi = viewer_controller_4d.new_dynamic_angle_roi(p1=(100., 100.),
                                                     p2=(150., 100.),
                                                     p3=(100., 150.),
                                                     p4=(100., 200.),
                                                     name="pyosirix_dynangle",
                                                     idx=0,
                                                     movie_idx=1,
                                                     thickness=3.0,
                                                     color=(255, 255, 0),
                                                     opacity=1.0)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_axis(viewer_controller_4d):
    """ Check that a new axis ROI can be created. """
    roi = viewer_controller_4d.new_axis_roi(p1=(180., 190.),
                                            p2=(150., 100.),
                                            p3=(100., 150.),
                                            p4=(100., 200.),
                                            name="pyosirix_axis",
                                            idx=0,
                                            movie_idx=1,
                                            thickness=3.0,
                                            color=(0, 255, 0),
                                            opacity=1.0)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_closed_polygon(viewer_controller_4d):
    """ Check that a new closed polygon ROI can be created. """
    new_points = np.array([[10.5, 10.5],
                           [50.5, 10.5],
                           [50.5, 50.5],
                           [10.5, 50.5]])
    roi = viewer_controller_4d.new_polygon_roi(points=new_points,
                                               closed=True,
                                               name="pyosirix_closed_polygon",
                                               idx=39,
                                               movie_idx=0,
                                               thickness=3.0,
                                               color=(0, 255, 0),
                                               opacity=1.0)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_new_roi_open_polygon(viewer_controller_4d):
    """ Check that a new open polygon ROI can be created. """
    new_points = np.array([[10.5, 10.5],
                           [50.5, 10.5],
                           [50.5, 50.5],
                           [10.5, 50.5]])
    roi = viewer_controller_4d.new_polygon_roi(points=new_points,
                                               closed=False,
                                               name="pyosirix_open_polygon",
                                               idx=38,
                                               movie_idx=0,
                                               thickness=3.0,
                                               color=(255, 255, 0),
                                               opacity=1.0)
    assert isinstance(roi, osirix.roi.ROI), f"Did not return ROI instance"


def test_viewer_controller_roi_list(viewer_controller_4d):
    """ Check that the list of ROIs can be returned. """
    roi_slices = viewer_controller_4d.roi_list(1)
    assert len(roi_slices) == 40, f"Incorrect number of slices {len(roi_slices)}"
    assert len(roi_slices[0]) >= 11, f"There should be at least 11 new ROIs"


def test_viewer_controller_selected_rois(viewer_controller_4d):
    """ Check the selected ROIs are returned. """
    selected_rois = viewer_controller_4d.selected_rois()
    assert len(selected_rois) == 0


def test_viewer_controller_rois_with_name(viewer_controller_4d):
    """ Check ROIs with name are provided. """
    rois = viewer_controller_4d.rois_with_name("pyosirix_mask")
    assert len(rois) == 10, f"Bad number of ROIs with name mask {len(rois)}"


def test_viewer_controller_open_vr_viewer_for_mode_vr_4d(viewer_controller_4d):
    """ Check that we can open up a MIP viewer. """
    vr_controller = viewer_controller_4d.open_vr_viewer(mode="VR")
    assert isinstance(vr_controller, osirix.vr_controller.VRController)


def test_viewer_controller_open_vr_viewer_for_mode_mip_2d(viewer_controller_2d):
    """ Check that we can open up a MIP viewer. """
    vr_controller = viewer_controller_2d.open_vr_viewer(mode="MIP")
    assert isinstance(vr_controller, osirix.vr_controller.VRController)


def test_viewer_controller_vr_controllers_4d(viewer_controller_4d):
    vr_controllers = viewer_controller_4d.vr_controllers()
    assert len(vr_controllers) == 1, f"Bad number of associated VR controllers"


def test_viewer_controller_vr_controllers_2d(viewer_controller_2d):
    vr_controllers = viewer_controller_2d.vr_controllers()
    assert len(vr_controllers) == 1, f"Bad number of associated VR controllers"
