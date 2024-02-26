from __future__ import annotations
from typing import Tuple, Dict

from numpy import ndarray

import osirixgrpc.viewercontroller_pb2 as viewercontroller_pb2
import osirixgrpc.vrcontroller_pb2 as vrcontroller_pb2
import osirixgrpc.dcmpix_pb2 as dcmpix_pb2
import osirixgrpc.roi_pb2 as roi_pb2
from osirix.dicom import DicomSeries, DicomStudy, DicomImage
from osirix.dcm_pix import DCMPix
from osirix.roi import ROI


class ViewerController(object):
    """
    Class representing the properties and methods to communicate with the Osirix service through
    gRPC for a ViewerController
    """

    def __init__(self, osirixrpc_uid, osirix_service):
        self.osirixrpc_uid = osirixrpc_uid
        self.osirix_service = osirix_service
        self.response_processor = ResponseProcessor()

    @property
    def idx(self) -> int:
        """
          Makes a gRPC request to retrieve the idx for the ViewerController

          Returns:
            int : idx
        """
        response_viewer_idx = self.osirix_service.ViewerControllerIdx(self.osirixrpc_uid)
        self.response_processor.response_check(response_viewer_idx)
        self._idx = response_viewer_idx.idx

        return self._idx

    @idx.setter
    def idx(self, idx=int) -> None:
        """
          Makes a gRPC request to set the idx for the ViewerController

          Args:
            int : idx

          Returns:
            None
        """
        request = viewercontroller_pb2.ViewerControllerSetIdxRequest(viewer_controller=self.osirixrpc_uid, idx=idx)
        response = self.osirix_service.ViewerControllerSetIdx(request)
        self.response_processor.response_check(response)

    @property
    def modality(self) -> str:
        """
          Makes a gRPC request to retrieve the modality for the ViewerController

          Returns:
            str : modality
        """
        response_viewer_modality = self.osirix_service.ViewerControllerModality(self.osirixrpc_uid)

        self.response_processor.response_check(response_viewer_modality)

        self._modality = response_viewer_modality.modality

        return self._modality

    @property
    def movie_idx(self) -> int:
        """
          Makes a gRPC request to retrieve the movie idx for the ViewerController

          Returns:
            int : movie_idx
        """
        response_viewer_movie_idx = self.osirix_service.ViewerControllerMovieIdx(self.osirixrpc_uid)
        self.response_processor.response_check(response_viewer_movie_idx)
        return response_viewer_movie_idx.movie_idx

    @movie_idx.setter
    def movie_idx(self, movie_idx=int) -> None:
        """ Makes a gRPC request to set the movie idx for the ViewerController.

          Args:
            movie_idx (int): The frame to set the 2D viewer to.
        """
        request = viewercontroller_pb2.ViewerControllerSetMovieIdxRequest(
            viewer_controller=self.osirixrpc_uid, movie_idx=movie_idx)
        response = self.osirix_service.ViewerControllerSetMovieIdx(request)
        self.response_processor.response_check(response)

    @property
    def title(self) -> str:
        """ Makes a gRPC request to retrieve the title for the ViewerController

          Returns:
            str : title
        """
        response_viewer_title = self.osirix_service.ViewerControllerTitle(self.osirixrpc_uid)
        self.response_processor.response_check(response_viewer_title)
        self._title = response_viewer_title.title

        return self._title

    @property
    def wlww(self) -> Tuple[float, float]:
        """
          Makes a gRPC request to retrieve the wlww for the ViewerController

          Returns:
            A Tuple containing wl and ww in float
        """
        response_viewer_wlww = self.osirix_service.ViewerControllerWLWW(self.osirixrpc_uid)
        self.response_processor.response_check(response_viewer_wlww)
        self._ww = response_viewer_wlww.ww
        self._wl = response_viewer_wlww.wl
        return (self._wl, self._ww)

    @wlww.setter
    def wlww(self, wlww : Tuple[float, float]) -> None:
        """
          Makes a gRPC request to set the wlww for the ViewerController

          Args:
            Tuple[float, float] : wlww

          Returns:
            None
        """
        wl, ww = wlww
        request = viewercontroller_pb2.ViewerControllerSetWLWWRequest(viewer_controller=self.osirixrpc_uid, wl=wl, ww=ww)
        response = self.osirix_service.ViewerControllerSetWLWW(request)
        self.response_processor.response_check(response)

    def process_viewer_pix_list(self, response) -> Tuple[DCMPix, ...]:
        """
          Process gRPC response to retrieve the pix list for the ViewerController

          Args:
            response : response from ViewerControllerPixListResponse

          Returns:
            A Tuple containing DCMPix
        """
        pix_tuple: Tuple[DCMPix, ...] = ()
        for pix in response.pix:
            dcm_pix = DCMPix(pix, self.osirix_service)
            pix_tuple = pix_tuple + (dcm_pix,)

        return pix_tuple

    def process_viewer_roi_list(self, response) -> Tuple[ROI, ...]:
        """
          Process gRPC response to retrieve the roi list for the ViewerController

          Args:
            response : response from ViewerControllerROIListResponse

          Returns:
            A Tuple containing ROIs
        """
        roi_tuple: Tuple[ROI, ...] = ()
        for roi_slice in response.roi_slices:
            roi = ROI(roi_slice, self.osirix_service)
            roi_tuple = roi_tuple + (roi,)
        return roi_tuple

    def process_viewer_rois(self, response) -> Tuple[ROI, ...]:
        """
          Process gRPC response to retrieve the ROIs for the ViewerController

          Args:
            response : response from ViewerControllerROIsWithNameResponse/ViewerControllerSelectedROIsResponse

          Returns:
            A Tuple containing DCMPix
        """
        roi_tuple: Tuple[ROI, ...] = ()
        for roi in response.rois:
            roi = ROI(roi, self.osirix_service)
            roi_tuple = roi_tuple + (roi,)
        return roi_tuple

    def process_vr_controllers(self, response) -> Tuple[VRController, ...]:
        """
          Process gRPC response to retrieve the VR controllers for the ViewerController

          Args:
            response : response from ViewerControllerVRControllersResponse

          Returns:
            A Tuple containing VR Controllers`
        """
        vr_tuple: Tuple[VRController, ...] = ()
        for vr_controller in response.vr_controllers:
            vr_controller_obj = VRController(vr_controller, self.osirix_service)
            vr_tuple = vr_tuple + (vr_controller_obj,)
        return vr_tuple

    # # returns VC
    def blending_controller(self) -> ViewerController:
        """
          Process gRPC response to retrieve the blending controller for the ViewerController

          Returns:
            ViewerController
        """

        # Multiple VR Controllers case?
        vr_controller = self.osirix_service.ViewerControllerVRControllers(self.osirixrpc_uid).vr_controllers[0]
        response = self.osirix_service.VRControllerBlendingController(vr_controller)
        self.response_processor.response_check(response)
        return ViewerController(response.viewer_controller, self.osirix_service)

    def close_viewer(self) -> None:
        """
          Process gRPC request to close the ViewerController

          Returns:
            None
        """
        response = self.osirix_service.ViewerControllerCloseViewer(self.osirixrpc_uid)
        self.response_processor.response_check(response)

    # returns VC
    def copy_viewer_window(self, in_4d: bool = False) -> ViewerController:
        """
          Process gRPC request to copy the viewer window for the ViewerController

          Args:
            bool : in_4d

          Returns:
            ViewerController
        """
        request = viewercontroller_pb2.ViewerControllerCopyViewerWindowRequest(viewer_controller=self.osirixrpc_uid, in_4d=in_4d)
        response = self.osirix_service.ViewerControllerCopyViewerWindow(request)
        self.response_processor.response_check(response)

        return ViewerController(self.osirixrpc_uid,self.osirix_service)

    def cur_dcm(self) -> DCMPix:
        """
          Process gRPC request to retrieve current dicom pix for the ViewerController

          Returns:
            DCMPix: current dicom picture for ViewerController
        """
        pix = self.osirix_service.ViewerControllerCurDCM(self.osirixrpc_uid).pix
        dcm_pix = DCMPix(pix, self.osirix_service)
        return dcm_pix

    def is_data_volumic(self, in_4d: bool = False) -> bool:
        """
          Process gRPC request to retrieve the is_data_volumic flag for the ViewerController

          Args:
            bool : in_4d

          Returns:
            bool : whether data is volumic
        """
        request = viewercontroller_pb2.ViewerControllerIsDataVolumicRequest(viewer_controller=self.osirixrpc_uid, in_4d=in_4d)
        response = self.osirix_service.ViewerControllerIsDataVolumic(request)
        self.response_processor.response_check(response)
        return response.in_4d

    def max_movie_index(self) -> int:
        """
          Process gRPC request to retrieve max movie idx for the ViewerController

          Returns:
            int : max movie inde
        """
        response = self.osirix_service.ViewerControllerMaxMovieIdx(self.osirixrpc_uid)
        self.response_processor.response_check(response)
        return response.max_movie_idx

    def needs_display_update(self) -> None:
        """
          Process gRPC requqest to check whether the ViewerController needs display update

          Returns:
            None
        """
        response = self.osirix_service.ViewerControllerNeedsDisplayUpdate(self.osirixrpc_uid)
        self.response_processor.response_check(response)

    def pix_list(self, movie_idx: int) -> Tuple[DCMPix, ...]:
        """
          Process gRPC response to retrieve the VR controllers for the ViewerController

          Args:
            response : response from ViewerControllerVRControllersResponse

          Returns:
            A Tuple containing VR Controllers`
        """
        request = viewercontroller_pb2.ViewerControllerPixListRequest(viewer_controller=self.osirixrpc_uid, movie_idx=movie_idx)
        response = self.osirix_service.ViewerControllerPixList(request)
        pix_tuple = self.process_viewer_pix_list(response)

        return pix_tuple

    def resample_viewer_controller(self, vc : ViewerController) -> ViewerController:
        """
          Process gRPC request to resample the ViewerController based on another fixed ViewerController

          Args:
            ViewerController : ViewerController to resameple from

          Returns:
            ViewerController
        """
        request = viewercontroller_pb2.ViewerControllerResampleViewerControllerRequest(
                                                            viewer_controller=self.osirixrpc_uid,
                                                            fixed_viewer_controller=vc.osirixrpc_uid)

        response = self.osirix_service.ViewerControllerResampleViewerController(request)
        self.response_processor.response_check(response)
        return ViewerController(self.osirixrpc_uid, self.osirix_service)

    # Check ROISlice and ROI
    def roi_list(self, movie_idx:int) -> Tuple[ROI, ...]:
        """
          Process gRPC request to retrieve the list of ROIs based on movie_idx for the ViewerController

          Args:
            int: movie_idx

          Returns:
            A Tuple containing ROIs
        """
        request = viewercontroller_pb2.ViewerControllerROIListRequest(viewer_controller=self.osirixrpc_uid,
                                                                      movie_idx=movie_idx)
        response = self.osirix_service.ViewerControllerROIList(request)
        self.response_processor.response_check(response)
        roi_tuple = self.process_viewer_roi_list(response)

        return roi_tuple


    def rois_with_name(self, name: str, movie_idx: int, in_4d: bool = False) -> Tuple[ROI, ...]:
        """
          Process gRPC request to retrieve the list of ROIs based on movie_idx for the ViewerController

          Args:
            str: name
            int: movie_idx
            bool : in_4d

          Returns:
            A Tuple containing ROIs
        """
        request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(viewer_controller=self.osirixrpc_uid,
                                                                           name=name,
                                                                           movie_idx=movie_idx,
                                                                           in_4d=in_4d)
        response = self.osirix_service.ViewerControllerROIsWithName(request)
        self.response_processor.response_check(response)
        roi_tuple = self.process_viewer_rois(response)

        return roi_tuple

    def selected_rois(self) -> Tuple[ROI, ...]:
        """
          Process gRPC request to retrieve ROIs that are selected for the ViewerController

          Returns:
            A Tuple containing ROIs
        """
        response = self.osirix_service.ViewerControllerSelectedROIs(self.osirixrpc_uid)
        self.response_processor.response_check(response)
        roi_tuple = self.process_viewer_rois(response)

        return roi_tuple

    #TODO implement this when the TypeResponse protobuf is exposed

    # def set_roi(self, roi: ROI, position: int, movie_idx: int) -> None:
    #     #Mask
    #     buffer_array = np.random.randn(40 * 40) > 0
    #     buffer = viewercontroller_pb2.ViewerControllerNewROIRequest.Buffer(buffer=1 * buffer_array, rows=40,
    #                                                                        columns=40)
    #
    #     r, g, b = roi.color
    #     color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=r, g=g, b=b)
    #     request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.osirixrpc_uid,
    #                                                                  movie_idx=movie_idx,
    #                                                                  position=position,
    #                                                                  itype=20,
    #                                                                  buffer=buffer,
    #                                                                  color=color,
    #                                                                  opacity=roi.opacity,
    #                                                                  name=roi.name)
    #     response = self.osirix_service.ViewerControllerNewROI(request)
    #     print(response.roi)
    #
    #     # How to decide between which ROI to create
    #
    #     #Oval
    #     rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42., width=20.,
    #                                                                    height=10.)
    #     color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=100, b=200)
    #     request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
    #                                                                  movie_idx=0, position=0, itype=9,
    #                                                                  rectangle=rect, color=color, opacity=0.5,
    #                                                                  name="oval", thickness=3.0)
    #     response = self.osirix_service.ViewerControllerNewROI(request)
    #     self.assertEqual(response.status.status, 1)
    #     print(response.roi)
    #
    #     # Arrow
    #     # Points seem to go in order [head, tail]
    #     color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=0, g=255, b=0)
    #     points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=66., y=42.),
    #               viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=99., y=24.)]
    #     request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
    #                                                                  points=points, movie_idx=0, position=0,
    #                                                                  itype=14, color=color, opacity=0.5,
    #                                                                  name="arrow", thickness=3.0)
    #     response = self.osirix_service.ViewerControllerNewROI(request)
    #     print(response.roi)
    #
    #     #Point
    #     rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42., width=20.,
    #                                                                    height=10.)
    #     color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=0, g=255, b=255)
    #     request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
    #                                                                  rectangle=rect, movie_idx=0, position=0,
    #                                                                  itype=19, color=color, opacity=1.0,
    #                                                                  name="point", thickness=3.0)
    #     response = self.osirix_service.ViewerControllerNewROI(request)
    #     print(response.roi)
    #
    #     # A rectangle TROI
    #     rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42., width=20.,
    #                                                                    height=10.)
    #     color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=100, b=100)
    #     request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
    #                                                                  rectangle=rect, movie_idx=0, position=0,
    #                                                                  itype=6, color=color, opacity=1.0, name="tROI",
    #                                                                  thickness=3.0)
    #     response = self.osirix_service.ViewerControllerNewROI(request)
    #     self.assertEqual(response.status.status, 1)
    #     print(response.roi)
    #
    #     #Text
    #     rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42., width=20.,
    #                                                                    height=10.)
    #     color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=100, b=100)
    #     request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
    #                                                                  rectangle=rect, movie_idx=0, position=0,
    #                                                                  itype=13, color=color, opacity=1.0,
    #                                                                  name="Some text", thickness=3.0)
    #     response = self.osirix_service.ViewerControllerNewROI(request)
    #     print(response.roi)
    #
    #     #TTAGT
    #     points = [[50.20499802, 32.32217407], [53.27367783, 38.77323914], [64.68674469, 25.43341637],
    #               [69.71873474, 36.01180649], [41.8967247, 36.27430344], [68.91729736, 23.42099953]]
    #     points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=p[0], y=p[1]) for p in points]
    #     print(len(points))
    #     color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=250, b=220)
    #     request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
    #                                                                  points=points, movie_idx=0, position=0,
    #                                                                  itype=29, color=color, opacity=1.0,
    #                                                                  name="tTAGT", thickness=3.0)
    #     response = self.osirix_service.ViewerControllerNewROI(request)
    #     print(response.roi)
    #
    #     #Pencil
    #     points = [[50.20499802, 32.32217407], [53.27367783, 38.77323914], [64.68674469, 25.43341637],
    #               [69.71873474, 36.01180649], [41.8967247, 36.27430344], [68.91729736, 23.42099953]]
    #     points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=p[0], y=p[1]) for p in points]
    #     color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=50, b=220)
    #     request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
    #                                                                  points=points, movie_idx=0, position=0,
    #                                                                  itype=15, color=color, opacity=1.0,
    #                                                                  name="pencil", thickness=3.0)
    #     response = self.osirix_service.ViewerControllerNewROI(request)
    #     print(response.roi)
    #
    #     points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=71., y=-2.), \
    #               viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=67., y=11.), \
    #               viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=90., y=9.)]
    #     color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=50, b=220)
    #     request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
    #                                                                  points=points, movie_idx=0, position=0,
    #                                                                  itype=12, color=color, opacity=1.0,
    #                                                                  name="pencil", thickness=3.0)
    #     response = self.osirix_service.ViewerControllerNewROI(request)
    #     print(response.roi)
    #
    #     # Measure
    #     points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=71., y=-2.), \
    #               viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=67., y=11.)]
    #     color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=50, b=0)
    #     request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
    #                                                                  points=points, movie_idx=0, position=0,
    #                                                                  itype=5, color=color, opacity=1.0,
    #                                                                  name="measure", thickness=3.0)
    #     response = self.osirix_service.ViewerControllerNewROI(request)
    #     print(response.roi)

    #TODO No response in osirix.proto

    # def start_wait_progress_window(self, message: str, max: int) -> Wait:

    def vr_controllers(self) -> Tuple:
        """
          Process gRPC request to retrieve the VR Controllers for the ViewerController

          Returns:
            None
        """
        response = self.osirix_service.ViewerControllerVRControllers(self.osirixrpc_uid)
        self.response_processor.response_check(response)
        vr_tuple = self.process_vr_controllers(response)

        return vr_tuple

    @classmethod
    def name(cls):
        cls.__name__


