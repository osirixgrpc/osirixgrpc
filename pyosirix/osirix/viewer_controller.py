""" Functionality for the 2D viewer.

"""

from __future__ import annotations
from typing import Tuple, List
import warnings

from numpy.typing import NDArray
import numpy as np

import osirixgrpc.viewercontroller_pb2 as viewercontroller_pb2

import osirix


class ViewerController(osirix.base.OsirixBase):
    """ Represents one of the displayed volume render windows.

    """
    @property
    def idx(self) -> int:
        """ The slice index currently being displayed to the viewer (starting at 0).

        Note that the index displayed on the viewer is this value plus one.
        """
        response = self.osirix_service_stub.ViewerControllerIdx(self.pb2_object)
        self.response_check(response)
        return int(response.idx)

    @idx.setter
    def idx(self, idx: int) -> None:
        """ The slice index currently being displayed to the viewer (starting at 0).

        Note that the index displayed on the viewer is this value plus one.
        """
        request = viewercontroller_pb2.ViewerControllerSetIdxRequest(
            viewer_controller=self.pb2_object, idx=idx)
        response = self.osirix_service_stub.ViewerControllerSetIdx(request)
        self.response_check(response)

    @property
    def modality(self) -> str:
        """ The modality of the displayed data.
        """
        response = self.osirix_service_stub.ViewerControllerModality(self.pb2_object)
        self.response_check(response)
        return response.modality

    @property
    def movie_idx(self) -> int:
        """ The frame currently being displayed by the viewer.
        """
        response = self.osirix_service_stub.ViewerControllerMovieIdx(self.pb2_object)
        self.response_check(response)
        return response.movie_idx

    @movie_idx.setter
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
    def title(self) -> str:
        """ The title of the 2D viewing window.
        """
        response = self.osirix_service_stub.ViewerControllerTitle(self.pb2_object)
        self.response_check(response)
        return response.title

    @property
    def wlww(self) -> Tuple[float, float]:
        """The window level and window width of the viewer.
        """
        response = self.osirix_service_stub.ViewerControllerWLWW(self.pb2_object)
        self.response_check(response)
        return response.wl, response.ww

    @wlww.setter
    def wlww(self, wlww: Tuple[float, float]) -> None:
        """The window level and window width of the viewer.
        """
        request = viewercontroller_pb2.ViewerControllerSetWLWWRequest(vr_controller=self.pb2_object,
                                                                      wl=wlww[0],
                                                                      ww=wlww[1])
        response = self.osirix_service_stub.ViewerControllerSetWLWW(request)
        self.response_check(response)

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

    def vr_controllers(self) -> List[osirix.vr_controller.VRController]:
        """ Return the list of currently displayed 3D viewers associates with this 2D window.
        """
        response = self.osirix_service_stub.ViewerControllerVRControllers(self.pb2_object)
        self.response_check(response)
        vrs = []
        for vr_controller in response.vr_controllers:
            vrs.append(osirix.vr_controller.VRController(self.osirix_service, vr_controller))
        return vrs

    def blending_controller(self) -> ViewerController:
        # TODO: What happens if there isn't one. Does it return None?
        """ Return the viewer controller instance that is being fused with this one.

        Returns:
            The ViewerController instance.
        """
        response = self.osirix_service_stub.ViewerControllerVRControllers(self.pb2_object)
        self.response_check(response)
        return ViewerController(self.osirix_service, response.viewer_controller)

    def close_viewer(self) -> None:
        """ Close the viewer
        """
        response = self.osirix_service_stub.ViewerControllerCloseViewer(self.pb2_object)
        self.response_check(response)

    def copy_viewer_window(self, in_4d: bool = False) -> None:
        # TODO: Is it just the first frame if in_4d is False?
        # TODO: Currently this does not return a reference to the new window.  This would be nice!
        """ Create a copy of this 2D viewer.

        This can be useful for image processing when you want to keep a copy of the original and
        a processed version.

        Args:
            in_4d (bool): Whether to copy the entire 4D dataset. Default is False.
        """
        request = viewercontroller_pb2.ViewerControllerCopyViewerWindowRequest(
            viewer_controller=self.pb2_object, in_4d=in_4d)
        response = self.osirix_service_stub.ViewerControllerCopyViewerWindow(request)
        self.response_check(response)

    def cur_dcm(self) -> osirix.dcm_pix.DCMPix:
        """ Return the currently displayed DCMPix instance.

        Returns:
            the currently displayed DCMPix instance.
        """
        response = self.osirix_service_stub.ViewerControllerCurDCM(self.pb2_object)
        self.response_check(response)
        return osirix.dcm_pix.DCMPix(self.osirix_service, response.pix)

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

    def max_movie_index(self) -> int:
        """ The maximum movie index in the viewer.

        Note this equals the number of frames minus 1.

        Returns:
            The maximum frame index.
        """
        response = self.osirix_service_stub.ViewerControllerMaxMovieIdx(self.pb2_object)
        self.response_check(response)
        return response.max_movie_idx

    def needs_display_update(self) -> None:
        """ Tell the viewer it should update its display.

        This is particularly important if you want to see changes to pixel values in real time.
        """
        response = self.osirix_service_stub.ViewerControllerNeedsDisplayUpdate(self.pb2_object)
        self.response_check(response)

    def resample_viewer_controller(self, vc: ViewerController):
        """ Resample this (moving) ViewerController based on another (fixed) ViewerController.

        Args:
            vc (osirix.viewer_controller.ViewerController): The fixed viewer.
        """
        request = viewercontroller_pb2.ViewerControllerResampleViewerControllerRequest(
            viewer_controller=self.pb2_object, fixed_viewer_controller=vc.pb2_object)
        response = self.osirix_service_stub.ViewerControllerResampleViewerController(request)
        self.response_check(response)

    def new_roi(self, itype: int = 15, name: str = "", position: idx = 0, movie_idx: int = 0,
                buffer_position_column: int = 0, buffer_position_row: int = 0,
                color: Tuple[float, float, float] = (0, 255, 0), thickness: float = 1.0,
                opacity: float = 1.0, buffer: NDArray = None, rect: NDArray = None,
                points: NDArray = None) -> osirix.roi.ROI:
        """ Create a new ROI within the viewer.

        Important: It is safer to create a new ROI using one of the utility functions as they
        provide better checking on input parameters in certain contexts, and ensure the right ROI
        type is created. This is meant as a parent function that performs the heavy lifting. It is
        made public for transparency.

        Args:
            itype (int): The index of the roi type (see `osirix.roi.ROI.itypes` for details).
                Default is 15 (tPencil).
            name (str): The name of the ROI.
            position (int): The slice index on which to create the new ROI.
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
            ValueError: When both `buffer` and `points` is None.
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
                buffer=buffer, rows=rows, columns=columns)
            request = viewercontroller_pb2.ViewerControllerNewROIRequest(
                viewer_controller=self.pb2_object, position=position, movie_idx=movie_idx,
                buffer_position_column=buffer_position_column, color=color_request,
                buffer_position_row=buffer_position_row, opacity=opacity, name=name,
                buffer=buffer_request, itype=itype)
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
                viewer_controller=self.pb2_object, position=position, movie_idx=movie_idx,
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
                viewer_controller=self.pb2_object, position=position, movie_idx=movie_idx,
                color=color_request, opacity=opacity, name=name, points=points_request,
                thickness=thickness, itype=itype)
        response = self.osirix_service_stub.ViewerControllerNewROI(request)
        self.response_check(response)
        return osirix.roi.ROI(self.osirix_service, response.roi)
