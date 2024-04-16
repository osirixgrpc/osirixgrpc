""" Functionality for the 2D viewer.

"""

from __future__ import annotations
from typing import Tuple, List
import warnings

from numpy.typing import NDArray
import numpy as np

import osirixgrpc.viewercontroller_pb2 as viewercontroller_pb2

import osirix  # noqa
from osirix.base import pyosirix_connection_check  # noqa


class ViewerController(osirix.base.OsirixBase):
    """ Represents one of the displayed volume render windows.

    """
    def __repr__(self):
        return f"ViewerController: " \
               f"{self.title}"

    @property
    @pyosirix_connection_check
    def idx(self) -> int:
        """ The slice index currently being displayed to the viewer (starting at 0).

        Note that the index displayed on the viewer is this value plus one.
        """
        response = self.osirix_service_stub.ViewerControllerIdx(self.pb2_object)
        self.response_check(response)
        return int(response.idx)

    @idx.setter
    @pyosirix_connection_check
    def idx(self, idx: int) -> None:
        """ The data slice index currently being displayed to the viewer (starting at 0).

        Note that this may not be equal to the index displayed on the viewer when
            `data_flipped` is True.
        """
        request = viewercontroller_pb2.ViewerControllerSetIdxRequest(
            viewer_controller=self.pb2_object, idx=idx)
        response = self.osirix_service_stub.ViewerControllerSetIdx(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def displayed_idx(self) -> int:
        """ The data slice index currently being displayed to the viewer (starting at 0).

        Note that this may not be equal to the index displayed on the viewer when
            `data_flipped` is True.
        """
        response = self.osirix_service_stub.ViewerControllerDisplayedIdx(self.pb2_object)
        self.response_check(response)
        return int(response.displayed_idx)

    @displayed_idx.setter
    @pyosirix_connection_check
    def displayed_idx(self, idx: int) -> None:
        """ The slice index currently being displayed to the viewer (starting at 0).

        Note that the index displayed on the viewer is this value plus one.
        """
        request = viewercontroller_pb2.ViewerControllerSetDisplayedIdxRequest(
            viewer_controller=self.pb2_object, displayed_idx=idx)
        response = self.osirix_service_stub.ViewerControllerSetDisplayedIdx(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def flipped_data(self) -> int:
        """ Whether the slices data are flipped in the viewer.
        """
        response = self.osirix_service_stub.ViewerControllerFlippedData(self.pb2_object)
        self.response_check(response)
        return int(response.flipped_data)

    @property
    @pyosirix_connection_check
    def modality(self) -> str:
        """ The modality of the displayed data.
        """
        response = self.osirix_service_stub.ViewerControllerModality(self.pb2_object)
        self.response_check(response)
        return response.modality

    @property
    @pyosirix_connection_check
    def movie_idx(self) -> int:
        """ The frame currently being displayed by the viewer.
        """
        response = self.osirix_service_stub.ViewerControllerMovieIdx(self.pb2_object)
        self.response_check(response)
        return response.movie_idx

    @movie_idx.setter
    @pyosirix_connection_check
    def movie_idx(self, movie_idx: int) -> None:
        """ The frame currently being displayed by the viewer.
        """
        if movie_idx < 0:
            raise ValueError("movie_idx must be >= 0.")
        request = viewercontroller_pb2.ViewerControllerSetMovieIdxRequest(
            viewer_controller=self.pb2_object, movie_idx=movie_idx)
        response = self.osirix_service_stub.ViewerControllerSetMovieIdx(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def title(self) -> str:
        """ The title of the 2D viewing window.
        """
        response = self.osirix_service_stub.ViewerControllerTitle(self.pb2_object)
        self.response_check(response)
        return response.title

    @property
    @pyosirix_connection_check
    def wlww(self) -> Tuple[float, float]:
        """The window level and window width of the viewer.
        """
        response = self.osirix_service_stub.ViewerControllerWLWW(self.pb2_object)
        self.response_check(response)
        return response.wl, response.ww

    @wlww.setter
    @pyosirix_connection_check
    def wlww(self, wlww: Tuple[float, float]) -> None:
        """The window level and window width of the viewer.
        """
        request = viewercontroller_pb2.ViewerControllerSetWLWWRequest(
            viewer_controller=self.pb2_object, wl=wlww[0], ww=wlww[1])
        response = self.osirix_service_stub.ViewerControllerSetWLWW(request)
        self.response_check(response)

    @property
    @pyosirix_connection_check
    def max_movie_index(self) -> int:
        """ The maximum movie index in the viewer.
        """
        response = self.osirix_service_stub.ViewerControllerMaxMovieIdx(self.pb2_object)
        self.response_check(response)
        return response.max_movie_idx

    @pyosirix_connection_check
    def close(self):
        """ Close the viewer.

        Note: This will close any associated viewers (e.g. VRControllers).
        """
        response = self.osirix_service_stub.ViewerControllerCloseViewer(self.pb2_object)
        self.response_check(response)

    @pyosirix_connection_check
    def pix_list(self, movie_idx: int = None) -> List[osirix.dcm_pix.DCMPix]:
        """ Access the list of DCMPix objects contained within the 2D viewer.

        Args:
            movie_idx (int): The frame from which to extract the DCMPix instances. If `None`, then
                use the currently displayed movie_idx. Default is `None`.

        Returns:
            The list of osirix.dcm_pix.DCMPix instances requested for a particular frame.
        """
        if movie_idx is None:
            movie_idx = self.movie_idx
        request = viewercontroller_pb2.ViewerControllerPixListRequest(
            viewer_controller=self.pb2_object, movie_idx=movie_idx)
        response = self.osirix_service_stub.ViewerControllerPixList(request)
        self.response_check(response)
        return [osirix.dcm_pix.DCMPix(self.osirix_service, pix) for pix in response.pix]

    @pyosirix_connection_check
    def roi_list(self, movie_idx: int = None) -> List[List[osirix.roi.ROI]]:
        """ Access a list of lists of ROI objects contained within the 2D viewer.

        The length of the outer list is the same as the number of slices in the viewer. Note
        that some inner lists will be empty if no ROIs are drawn on that slice.

        Args:
            movie_idx (int): The frame from which to extract the ROI instances. If `None`, then
                use the currently displayed movie_idx. Default is `None`.

        Returns:
            A list of lists of osirix.roi.ROI instances requested for a particular frame.
        """
        if movie_idx is None:
            movie_idx = self.movie_idx

        # Get the response
        request = viewercontroller_pb2.ViewerControllerROIListRequest(
            viewer_controller=self.pb2_object, movie_idx=movie_idx)
        response = self.osirix_service_stub.ViewerControllerROIList(request)
        self.response_check(response)

        # Loop through all ROI slices and append a list of inner ROIs.
        rois = []
        for roi_slice in response.roi_slices:
            rois_ = []
            for roi in roi_slice.rois:
                rois_.append(osirix.roi.ROI(self.osirix_service, roi))
            rois.append(rois_)
        return rois

    @pyosirix_connection_check
    def rois_with_name(self, name: str, movie_idx: int = None, in_4d: bool = False)\
            -> List[osirix.roi.ROI]:
        """ Return a list of ROIs with a given name.
        Args:
            name (str): The name of ROIs to look for.
            movie_idx (int): The frame from which to extract the ROI instances. If `None`, then
                use the currently displayed movie_idx. Default is `None`.
            in_4d (bool): Whether to look through all frames. Default is False.

        Returns:
            A list of ROIs with the given name.
        """
        if movie_idx is None:
            movie_idx = self.movie_idx

        request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(
            viewer_controller=self.pb2_object, name=name, movie_idx=movie_idx, in_4d=in_4d)
        response = self.osirix_service_stub.ViewerControllerROIsWithName(request)
        self.response_check(response)

        rois = []
        for roi in response.rois:
            rois.append(osirix.roi.ROI(self.osirix_service, roi))
        return rois

    @pyosirix_connection_check
    def selected_rois(self) -> List[osirix.roi.ROI]:
        """ Return a list of the user-selected ROIs

        Returns:
            A list of selected ROIs.
        """
        response = self.osirix_service_stub.ViewerControllerSelectedROIs(self.pb2_object)
        self.response_check(response)
        rois = []
        for roi in response.rois:
            rois.append(osirix.roi.ROI(self.osirix_service, roi))
        return rois

    @pyosirix_connection_check
    def vr_controllers(self) -> List[osirix.vr_controller.VRController]:
        """ Return the list of currently displayed 3D viewers associates with this 2D window.
        """
        response = self.osirix_service_stub.ViewerControllerVRControllers(self.pb2_object)
        self.response_check(response)
        vrs = []
        for vr_controller in response.vr_controllers:
            vrs.append(osirix.vr_controller.VRController(self.osirix_service, vr_controller))
        return vrs

    @pyosirix_connection_check
    def blending_controller(self) -> ViewerController:
        # TODO: What happens if there isn't one. Does it return None?
        """ Return the viewer controller instance that is being fused with this one.

        Returns:
            The ViewerController instance.
        """
        response = self.osirix_service_stub.ViewerControllerBlendingController(self.pb2_object)
        self.response_check(response)
        return ViewerController(self.osirix_service, response.blending_viewer)

    @pyosirix_connection_check
    def fuse_with_viewer(self, viewer: ViewerController):
        """ Fuse another viewer onto this one.

        Args:
            viewer (osirix.viewer_controller.ViewerController): The viewer to fuse onto the present
                one.
        """
        request = viewercontroller_pb2.ViewerControllerFuseWithViewerRequest(
            viewer_controller=self.pb2_object, fusion_viewer_controller=viewer.pb2_object)
        response = self.osirix_service_stub.ViewerControllerFuseWithViewer(request)
        self.response_check(response)

    @pyosirix_connection_check
    def close_viewer(self) -> None:
        """ Close the viewer
        """
        response = self.osirix_service_stub.ViewerControllerCloseViewer(self.pb2_object)
        self.response_check(response)

    @pyosirix_connection_check
    def copy_viewer_window(self) -> ViewerController:
        """ Create a copy of the viewer.

        This can be useful for image processing when you want to keep a copy of the original and
        a processed version.

        Returns:
            The new osirix.viewer_controller.ViewerController instance.
        """
        response = self.osirix_service_stub.ViewerControllerCopyViewerWindow(self.pb2_object)
        self.response_check(response)
        return ViewerController(self.osirix_service, response.viewer_controller)

    @pyosirix_connection_check
    def cur_dcm(self) -> osirix.dcm_pix.DCMPix:
        """ Return the currently displayed DCMPix instance.

        Returns:
            the currently displayed DCMPix instance.
        """
        response = self.osirix_service_stub.ViewerControllerCurDCM(self.pb2_object)
        self.response_check(response)
        return osirix.dcm_pix.DCMPix(self.osirix_service, response.pix)

    @pyosirix_connection_check
    def is_data_volumic(self, in_4d: bool = False) -> bool:
        """ Does the underlying data have sufficient geometric properties for volume rendering.

        Args:
            in_4d (bool): Determine for all frames.

        Returns:
            Is the data volumic?
        """
        request = viewercontroller_pb2.ViewerControllerIsDataVolumicRequest(
            viewer_controller=self.pb2_object, in_4d=in_4d)
        response = self.osirix_service_stub.ViewerControllerIsDataVolumic(request)
        self.response_check(response)
        return response.is_volumic

    @pyosirix_connection_check
    def needs_display_update(self) -> None:
        """ Tell the viewer it should update its display.

        This is particularly important if you want to see changes to pixel values in real time.
        """
        response = self.osirix_service_stub.ViewerControllerNeedsDisplayUpdate(self.pb2_object)
        self.response_check(response)

    @pyosirix_connection_check
    def resample_viewer_controller(self, vc: ViewerController) -> ViewerController:
        """ Resample this (moving) ViewerController based on another (fixed) ViewerController.

        Note that the original moving viewer is closed, so a reference to the new one is returned.
        This means it is generally advised to the call the method in the following manner:

        `moving_viewer = moving_viewer.resample_viewer_controller(fixed_viewer)`

        Args:
            vc (osirix.viewer_controller.ViewerController): The fixed viewer.

        Returns:
            The resampled viewer window.
        """
        request = viewercontroller_pb2.ViewerControllerResampleViewerControllerRequest(
            viewer_controller=self.pb2_object, fixed_viewer_controller=vc.pb2_object)
        response = self.osirix_service_stub.ViewerControllerResampleViewerController(request)
        self.response_check(response)
        return ViewerController(self.osirix_service, response.resampled_viewer)

    @pyosirix_connection_check
    def open_vr_viewer(self, mode: str = "VR") -> osirix.vr_controller.VRController:
        """ Open a new 3D viewer for the enclosed data.

        Args:
            mode (str): Either 'VR' for volume render, or 'MIP' for a maximum intensity projection.

        Returns:
            A VRController instance.
        """
        if mode not in ["VR", "MIP"]:
            raise ValueError("`mode` must be either 'VR' or 'MIP'")
        request = viewercontroller_pb2.ViewerControllerOpenVRViewerForModeRequest(
            viewer_controller=self.pb2_object, mode=mode)
        response = self.osirix_service_stub.ViewerControllerOpenVRViewerForMode(request)
        self.response_check(response)
        return osirix.vr_controller.VRController(self.osirix_service, response.vr_controller)

    @pyosirix_connection_check
    def new_roi(self, itype: int = 15, name: str = "", idx: int = 0, movie_idx: int = 0,
                buffer_position_column: int = 0, buffer_position_row: int = 0,
                color: Tuple[float, float, float] = (0, 255, 0), thickness: float = 1.0,
                opacity: float = 1.0, buffer: NDArray = None, rect: NDArray = None,
                points: NDArray = None) -> osirix.roi.ROI:
        """ Create a new ROI within the viewer.

        __Important__: It is safer to create a new ROI using one of the utility functions as they
        provide better checking on input parameters in certain contexts, and ensure the right ROI
        type is created. This is meant as a parent function that performs the heavy lifting. It is
        made public for transparency.

        Args:
            itype (int): The index of the roi type (see `osirix.roi.ROI.itypes` for details).
                Default is 15 (tPencil).
            name (str): The name of the ROI.
            idx (int): The slice index on which to create the new ROI.
            movie_idx (int): The frame on which to create the new ROI.
            buffer_position_column (int): The column offset of a mask ROI in pixel coordinates.
            buffer_position_row (int): The row offset of a mask ROI in pixel coordinates.
            color (tuple): The RGB color of the ROI (values from 0-255 in each channel).
            thickness (float): The thickness of the ROI. Value between 1-20 as per OsiriX.
            opacity (float): The opacity on a scale from 0 (transparent) to 1 (opaque).
            buffer (NDArray): The buffer mask as a 2D boolean Numpy array. If `None`, then ignored.
            rect (NDArray): The rectangle defining the ROI. Must be shape (4,).
            points (NDArray): The points defining the ROI. Must be shape (N, 2) for N vertices. If
                `None` or `buffer` is not `None` or `rect` is not `None` then ignored.

        Returns:
             The created ROI instance.

        Raises:
            ValueError: When `buffer`, `points` and `rect` are all None.
            ValueError: When the input data is of invalid format.
        """
        if buffer is None and rect is None and points is None:
            raise ValueError("buffer, rect and points cannot be None at the same time.")

        if thickness < 0 or thickness > 20:
            thickness = np.clip(thickness, 0, 20)
            warnings.warn(f"Bad value for thickness. Clipping to {thickness}")

        color_request = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=color[0],
                                                                                 g=color[1],
                                                                                 b=color[2])
        if itype == 20:
            if buffer is None:
                raise ValueError("Need buffer data if creating a tPlain ROI")
            buffer = np.array(buffer)
            if buffer.ndim != 2:
                raise ValueError("`buffer` must be two-dimensional")
            rows, columns = buffer.shape
            buffer_request = viewercontroller_pb2.ViewerControllerNewROIRequest.Buffer(
                buffer=buffer.ravel().tolist(), rows=rows, columns=columns)
            request = viewercontroller_pb2.ViewerControllerNewROIRequest(
                viewer_controller=self.pb2_object, idx=idx, movie_idx=movie_idx,
                buffer_position_x=buffer_position_column, buffer_position_y=buffer_position_row,
                color=color_request, opacity=opacity, name=name, buffer=buffer_request, itype=itype)
        elif itype in [6, 9, 13, 19, 31]:
            if rect is None:
                raise ValueError("Need rect if creating a rectangle-based ROI")
            rect = np.array(rect)
            if rect.ndim != 1:
                raise ValueError("`rect` must be one-dimensional")
            if rect.shape[0] != 4:
                raise ValueError("`rect` must be shape (4,)")
            rect_request = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=rect[0],
                                                                                   origin_y=rect[1],
                                                                                   width=rect[2],
                                                                                   height=rect[3])
            request = viewercontroller_pb2.ViewerControllerNewROIRequest(
                viewer_controller=self.pb2_object, idx=idx, movie_idx=movie_idx,
                color=color_request, opacity=opacity, name=name, rectangle=rect_request,
                thickness=thickness, itype=itype)
        else:
            if points is None:
                raise ValueError("Need points if creating a point-based ROI")
            points = np.array(points)
            if points.ndim != 2:
                raise ValueError("`points` must be two-dimensional")
            points_request = [
                viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=p[0], y=p[1]) for p in
                points]
            request = viewercontroller_pb2.ViewerControllerNewROIRequest(
                viewer_controller=self.pb2_object, idx=idx, movie_idx=movie_idx,
                color=color_request, opacity=opacity, name=name, points=points_request,
                thickness=thickness, itype=itype)
        response = self.osirix_service_stub.ViewerControllerNewROI(request)
        self.response_check(response)
        return osirix.roi.ROI(self.osirix_service, response.roi)

    @pyosirix_connection_check
    def new_mask_roi(self, buffer: NDArray, **kwargs) -> osirix.roi.ROI:
        """ Create a new mask ROI within the viewer.

        Args:
            buffer (NDArray): The buffer mask as a 2D boolean Numpy array.
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        return self.new_roi(buffer=buffer, itype=20, **kwargs)

    @pyosirix_connection_check
    def new_polygon_roi(self, points: NDArray, closed: bool = True, **kwargs) -> osirix.roi.ROI:
        """ Create a new polygon ROI within the viewer.

        Args:
            points (NDArray): The vertices of the ROI.  Must have shape (N, 2).
            closed (bool): Whether the polygon is closed.
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        itype = 10
        if closed:
            itype = 11
        return self.new_roi(points=points, itype=itype, **kwargs)

    @pyosirix_connection_check
    def new_measurement_roi(self, start: Tuple[float, float], end: Tuple[float, float], **kwargs)\
            -> osirix.roi.ROI:
        """ Create a new length measurement ROI within the viewer.

        Args:
            start (float, float): The starting position of the ROI (column, row).
            end (float, float): The ending position of the ROI (column, row).
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        points = np.array([[start[0], start[1]],
                           [end[0], end[1]]])
        return self.new_roi(points=points, itype=5, **kwargs)

    @pyosirix_connection_check
    def new_point_roi(self, column: float, row: float, **kwargs) -> osirix.roi.ROI:
        """ Create a new 2D point ROI within the viewer.

        Args:
            column (float): The column position of the ROI
            row (float): The row position of the ROI
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        rect = np.array([column, row, 0, 0])
        return self.new_roi(rect=rect, itype=19, **kwargs)

    @pyosirix_connection_check
    def new_text_roi(self, column: float, row: float, name: str, **kwargs) -> osirix.roi.ROI:
        """ Create a new text-box ROI within the viewer.

        Args:
            column (float): The column position of the ROI
            row (float): The row position of the ROI
            name (str): The text to show
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        rect = np.array([column, row, 0, 0])
        return self.new_roi(rect=rect, itype=13, name=name, **kwargs)

    @pyosirix_connection_check
    def new_arrow_roi(self, tail: Tuple[float, float], head: Tuple[float, float],  **kwargs)\
            -> osirix.roi.ROI:
        """ Create a new text-box ROI within the viewer.

        Args:
            tail (float, float): The (column, row) position of the arrow tail.
            head (float, float): The (column, row) position of the arrow hear.
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        points = np.vstack([head, tail])
        return self.new_roi(points=points, itype=14, **kwargs)

    @pyosirix_connection_check
    def new_oval_roi(self, center: Tuple[float, float], width: float, height: float, **kwargs)\
            -> osirix.roi.ROI:
        """ Create a new oval ROI within the viewer.

        Args:
            center (float, float): The (column, row) center of the oval ROI.
            width (float): The width of the oval ROI.
            height (float): The height of the oval ROI.
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        rect = np.array([center[0], center[1], width / 2, height / 2])
        return self.new_roi(rect=rect, itype=9, **kwargs)

    @pyosirix_connection_check
    def new_rectangle_roi(self, center: Tuple[float, float], width: float, height: float, **kwargs)\
            -> osirix.roi.ROI:
        """ Create a new rectangle ROI within the viewer.

        Args:
            center (float, float): The (column, row) center of the rectangle ROI.
            width (float): The width of the rectangle ROI.
            height (float): The height of the rectangle ROI.
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        rect = np.array([center[0] - width / 2, center[1] - height / 2, width, height])
        return self.new_roi(rect=rect, itype=6, **kwargs)

    @pyosirix_connection_check
    def new_angle_roi(self, p1: Tuple[float, float], p2: Tuple[float, float],
                      p3: Tuple[float, float], **kwargs) -> osirix.roi.ROI:
        """ Create a new angle ROI within the viewer.

        This draws two connected vectors:
            - v = p2 -> p1
            - u = p2 -> p3

        The displayed angle is the angle between these two vectors.

        Args:
            p1 (float, float): The (column, row) position of the first angle vertex.
            p2 (float, float): The (column, row) position of the second angle vertex.
            p3 (float, float): The (column, row) position of the third angle vertex.
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        points = np.vstack([np.array(p1), np.array(p2), np.array(p3)])
        return self.new_roi(points=points, itype=12, **kwargs)

    @pyosirix_connection_check
    def new_dynamic_angle_roi(self, p1: Tuple[float, float], p2: Tuple[float, float],
                              p3: Tuple[float, float], p4: Tuple[float, float], **kwargs)\
            -> osirix.roi.ROI:
        """ Create a new dynamic angle ROI within the viewer.

        This draws two vectors:
            - v = p2 -> p1
            - u = p3 -> p4

        The displayed angle is the angle between these two vectors. The vector p2 -> p3 is also
        drawn.

        Args:
            p1 (float, float): The (column, row) position of the first angle vertex.
            p2 (float, float): The (column, row) position of the second angle vertex.
            p3 (float, float): The (column, row) position of the third angle vertex.
            p4 (float, float): The (column, row) position of the fourth angle vertex.
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        points = np.vstack([np.array(p1), np.array(p2), np.array(p3), np.array(p4)])
        return self.new_roi(points=points, itype=27, **kwargs)

    @pyosirix_connection_check
    def new_axis_roi(self, p1: Tuple[float, float], p2: Tuple[float, float],
                     p3: Tuple[float, float], p4: Tuple[float, float], **kwargs) -> osirix.roi.ROI:
        """ Create a new axis ROI within the viewer.

        Args:
            p1 (float, float): The (column, row) position of the first vertex.
            p2 (float, float): The (column, row) position of the second vertex.
            p3 (float, float): The (column, row) position of the third vertex.
            p4 (float, float): The (column, row) position of the fourth vertex.
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        points = np.vstack([np.array(p1), np.array(p2), np.array(p3), np.array(p4)])
        return self.new_roi(points=points, itype=26, **kwargs)

    @pyosirix_connection_check
    def new_tagt_roi(self, a: Tuple[float, float], b: Tuple[float, float],
                     c: Tuple[float, float], d: Tuple[float, float], **kwargs) -> osirix.roi.ROI:
        """ Create a new tTAGT ROI within the viewer.

        ROI displays:
            - The length of vector DA.
            - The perpendicular distance from B to DA
            - The perpendicular distance from C to DA
            - The distance between B and C, parallel to DA.

        Args:
            a (float, float): The (column, row) position of point A.
            b (float, float): The (column, row) position of point B.
            c (float, float): The (column, row) position of point C.
            d (float, float): The (column, row) position of point D.
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        points = np.vstack([np.array(d),
                            np.array(a),
                            np.array((0, 0)),  # Projection point of C onto AD calculated by OsiriX.
                            np.array(c),
                            np.array((0, 0)),  # Projection point of B onto AD calculated by OsiriX.
                            np.array(b)])
        return self.new_roi(points=points, itype=29, **kwargs)

    @pyosirix_connection_check
    def new_oval_angle_roi(self, center: Tuple[float, float], width: float,
                           height: float, **kwargs) -> osirix.roi.ROI:
        """ Create a new angle oval ROI within the viewer.

        Note: At present we are not aware that it is possible to pre-determine the angle part of
        this ROI. This method defines only the oval that will be drawn; the angle appears to have a
        default value of 113 degrees that can then be adapted by the user.

        Args:
            center (float, float): The (column, row) center of the oval ROI.
            width (float): The width of the oval ROI.
            height (float): The height of the oval ROI.
            **kwargs: See `new_roi` for all additional comments.

        Returns:
             The created ROI instance.
        """
        rect = np.array([center[0], center[1], width / 2, height / 2])
        return self.new_roi(rect=rect, itype=31, **kwargs)
