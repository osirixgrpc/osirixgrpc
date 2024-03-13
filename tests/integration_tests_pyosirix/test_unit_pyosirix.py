import unittest

import sys
import os

from osirix import ViewerController

import grpc
import pytest
import numpy as np
import matplotlib.pyplot as pl
from osirix.osirix_utils import Osirix, OsirixService
from osirix.exceptions import GrpcException

import osirixgrpc.osirix_pb2 as osirix_pb2
import osirixgrpc.utilities_pb2 as utilities_pb2
import osirixgrpc.types_pb2 as types_pb2
import osirixgrpc.viewercontroller_pb2 as viewercontroller_pb2
import osirixgrpc.vrcontroller_pb2 as vrcontroller_pb2
import osirixgrpc.dcmpix_pb2 as dcmpix_pb2
import osirixgrpc.roi_pb2 as roi_pb2
import osirixgrpc.roivolume_pb2 as roivolume_pb2
import osirixgrpc.osirix_pb2_grpc as osirix_pb2_grpc

# The test defined here will require:
# ===================================
# 1) OsiriX/Horos application open with plugin installed
# 2) A single viewer controller open, with multiple frames
# 3) At least one ROI called test_grpc
# 4) A 3D renedered window open

class GrpcTest(unittest.TestCase):
	"""Base test class
	"""
	def setUp(self):
		try:
			# Check that the port and domain that your Osirix/Horos
			port = 50051
			domain = "localhost:"
			server_url_localhost = 'localhost:' + str(port)

			channel_opt = [('grpc.max_send_message_length', 512 * 1024 * 1024),
						   ('grpc.max_receive_message_length', 512 * 1024 * 1024)]

			self.osirix_service = OsirixService(channel_opt=channel_opt, domain=domain, port=port)
			self.osirix = Osirix(self.osirix_service.get_service())
			self.channel = grpc.insecure_channel(server_url_localhost, options=channel_opt)
			self.stub = osirix_pb2_grpc.OsiriXServiceStub(self.channel)
		except:
			raise GrpcException("No connection to OsiriX can be established")


class PyOsirixTestOsirix(GrpcTest):
	"""Test case for core osirix messaging

	"""

	def testOsirixCurrentBrowser(self):

		browser_controller = self.osirix.current_browser()
		response = self.stub.OsirixCurrentBrowser(utilities_pb2.Empty())
		print(type(response))
		print(response)
		print(response.status)
		print(response.status.status)
		self.assertEqual(response.status.status, 1)  # <-check for success
		self.assertEqual(response.browser_controller.osirixrpc_uid, browser_controller.osirixrpc_uid.osirixrpc_uid)

	def testOsirixFrontmostViewer(self):
		frontmost_viewer = self.osirix.frontmost_viewer()
		response = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty())
		print(response)
		print(response.status)
		print(response.status.status)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response.viewer_controller.osirixrpc_uid, frontmost_viewer.osirixrpc_uid.osirixrpc_uid)

	def testOsirixDisplayed2DViewers(self):
		displayed_2d_viewers = self.osirix.displayed_2d_viewers()
		response = self.stub.OsirixDisplayed2DViewers(utilities_pb2.Empty())
		print(response)
		print(response.status)
		print(response.status.status)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(len(response.viewer_controllers) > 0)
		self.assertTrue(len(displayed_2d_viewers) > 0)
		self.assertEqual(len(response.viewer_controllers), len(displayed_2d_viewers))

	def testOsirixFrontmostVRController(self):
		frontmost_vr_controller = self.osirix.frontmost_vr_controller()

		response = self.stub.OsirixFrontmostVRController(utilities_pb2.Empty())
		print(response)
		print(response.status)
		print(response.status.status)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response.vr_controller.osirixrpc_uid, frontmost_vr_controller.osirixrpc_uid.osirixrpc_uid)

	def testOsirixDisplayedVRControllers(self):
		displayed_vr_controllers = self.osirix.displayed_vr_controllers()
		response = self.stub.OsirixDisplayedVRControllers(utilities_pb2.Empty())
		self.assertEqual(response.status.status, 1)
		self.assertTrue(len(response.vr_controllers) > 0)
		self.assertTrue(len(displayed_vr_controllers) > 0)
		self.assertEqual(len(response.vr_controllers), len(displayed_vr_controllers))


class PyOsirixTestViewerController(GrpcTest):
	"""Test case for ViewerController messaging

	"""

	def setUp(self):
		super().setUp()
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.viewer_controller_pyosirix = self.osirix.frontmost_viewer()

	def testViewerControllerPixList(self):
		pix_list = self.viewer_controller_pyosirix.pix_list(movie_idx=0)
		request = viewercontroller_pb2.ViewerControllerPixListRequest(viewer_controller=self.viewer_controller,
																	  movie_idx=0)
		response = self.stub.ViewerControllerPixList(request)
		print(response)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(len(response.pix) > 0)
		self.assertEqual(len(response.pix), len(pix_list))

	def testViewerControllerNeedsDisplayUpdate(self):
		self.viewer_controller_pyosirix.needs_display_update() # Check for response is build in and it returns none

		response = self.stub.ViewerControllerNeedsDisplayUpdate(self.viewer_controller)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerROIList(self):
		roi_list = self.viewer_controller_pyosirix.roi_list(movie_idx=0)
		request = viewercontroller_pb2.ViewerControllerROIListRequest(viewer_controller=self.viewer_controller,
																	  movie_idx=0)
		response = self.stub.ViewerControllerROIList(request)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(len(response.roi_slices) > 0)
		self.assertEqual(len(response.roi_slices), len(roi_list))
		# print(response.roi_slices)
		for roi_slice in response.roi_slices:
			print(roi_slice)

	# TODO add tests for setting new ROIs once the Type proto messages are exposed
	def testViewerControllerNewROI_Mask(self):
		buffer_array = np.random.randn(40 * 40) > 0
		buffer = viewercontroller_pb2.ViewerControllerNewROIRequest.Buffer(buffer=1 * buffer_array, rows=40, columns=40)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=0, b=200)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
																	 movie_idx=0, position=0, itype=20, buffer=buffer,
																	 color=color, opacity=0.5, name="random")
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Oval(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42., width=20.,
																	   height=10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=100, b=200)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
																	 movie_idx=0, position=0, itype=9, rectangle=rect,
																	 color=color, opacity=0.5, name="oval",
																	 thickness=3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Arrow(self):
		# Points seem to go in order [head, tail]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=0, g=255, b=0)
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=66., y=42.),
				  viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=99., y=24.)]
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
																	 points=points, movie_idx=0, position=0, itype=14,
																	 color=color, opacity=0.5, name="arrow",
																	 thickness=3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Point(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42., width=20.,
																	   height=10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=0, g=255, b=255)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
																	 rectangle=rect, movie_idx=0, position=0, itype=19,
																	 color=color, opacity=1.0, name="point",
																	 thickness=3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)
	#
	# # A rectangle...
	def testViewerControllerNewROI_TROI(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42., width=20.,
																	   height=10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=100, b=100)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
																	 rectangle=rect, movie_idx=0, position=0, itype=6,
																	 color=color, opacity=1.0, name="tROI",
																	 thickness=3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)
	#
	def testViewerControllerNewROI_Text(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x=66., origin_y=42., width=20.,
																	   height=10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=255, g=100, b=100)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
																	 rectangle=rect, movie_idx=0, position=0, itype=13,
																	 color=color, opacity=1.0, name="Some text",
																	 thickness=3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_TTAGT(self):
		points = [[50.20499802, 32.32217407], [53.27367783, 38.77323914], [64.68674469, 25.43341637],
				  [69.71873474, 36.01180649], [41.8967247, 36.27430344], [68.91729736, 23.42099953]]
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=p[0], y=p[1]) for p in points]
		print(len(points))
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=250, b=220)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
																	 points=points, movie_idx=0, position=0, itype=29,
																	 color=color, opacity=1.0, name="tTAGT",
																	 thickness=3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Pencil(self):
		points = [[50.20499802, 32.32217407], [53.27367783, 38.77323914], [64.68674469, 25.43341637],
				  [69.71873474, 36.01180649], [41.8967247, 36.27430344], [68.91729736, 23.42099953]]
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=p[0], y=p[1]) for p in points]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=50, b=220)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
																	 points=points, movie_idx=0, position=0, itype=15,
																	 color=color, opacity=1.0, name="pencil",
																	 thickness=3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Angle(self):
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=71., y=-2.), \
				  viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=67., y=11.), \
				  viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=90., y=9.)]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=50, b=220)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
																	 points=points, movie_idx=0, position=0, itype=12,
																	 color=color, opacity=1.0, name="pencil",
																	 thickness=3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Measure(self):
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=71., y=-2.), \
				  viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=67., y=11.)]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r=100, g=50, b=0)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller=self.viewer_controller,
																	 points=points, movie_idx=0, position=0, itype=5,
																	 color=color, opacity=1.0, name="measure",
																	 thickness=3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerCurDCM(self):
		cur_dcm = self.viewer_controller_pyosirix.cur_dcm()
		response = self.stub.ViewerControllerCurDCM(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertNotEqual(response.pix.osirixrpc_uid, "")
		self.assertEqual(response.pix.osirixrpc_uid, cur_dcm.osirixrpc_uid.osirixrpc_uid)

	def testViewerControllerROIsWithName(self):
		roi_with_names = self.viewer_controller_pyosirix.rois_with_name(name="test_grpc", movie_idx=0)
		request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(viewer_controller=self.viewer_controller,
																		   name="test_grpc", movie_idx=0)
		response = self.stub.ViewerControllerROIsWithName(request)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(len(response.rois) > 0)
		self.assertNotEqual(response.rois[0].osirixrpc_uid, "")

		self.assertTrue(len(roi_with_names) > 0)
		self.assertEqual(len(response.rois), len(roi_with_names))

		request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(viewer_controller=self.viewer_controller,
																		   name="test_grpc", in_4d=True)
		response = self.stub.ViewerControllerROIsWithName(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerSelectedROIs(self):
		selected_rois = self.viewer_controller_pyosirix.selected_rois()
		response = self.stub.ViewerControllerSelectedROIs(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(len(selected_rois), len(response.rois))

	def testViewerControllerResampleViewerController(self):
		# Check that it doesn't work if bad viewer id provided.

		viewer_controller_fake = types_pb2.ViewerController(osirixrpc_uid="bad_id")
		request = viewercontroller_pb2.ViewerControllerResampleViewerControllerRequest(
			viewer_controller=viewer_controller_fake, fixed_viewer_controller=self.viewer_controller)

		#Resample by passing in the same viewer controller for testing of function
		resampled_vc =self.viewer_controller_pyosirix.resample_viewer_controller(vc=self.viewer_controller_pyosirix)
		response = self.stub.ViewerControllerResampleViewerController(request)
		print(response)
		self.assertEqual(response.status.status, 0)
		self.assertIsNotNone(resampled_vc.osirixrpc_uid)

	def testViewerControllerVRControllers(self):
		vr_controllers = self.viewer_controller_pyosirix.vr_controllers()
		response = self.stub.ViewerControllerVRControllers(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(len(vr_controllers), len(response.vr_controllers))

	def testViewerControllerTitle(self):
		title = self.viewer_controller_pyosirix.title
		response = self.stub.ViewerControllerTitle(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertFalse(response.title == "")
		self.assertEqual(response.title, title)

	def testViewerControllerModality(self):
		modality = self.viewer_controller_pyosirix.modality
		response = self.stub.ViewerControllerModality(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertFalse(response.modality == "")
		self.assertEqual(response.modality, modality)

	def testViewerControllerSetMovieIdx(self):
		request = viewercontroller_pb2.ViewerControllerSetMovieIdxRequest(viewer_controller=self.viewer_controller,
																		  movie_idx=0)
		response = self.stub.ViewerControllerSetMovieIdx(request)
		self.assertEqual(response.status.status, 1)

		self.viewer_controller_pyosirix.movie_idx = 0
		movie_idx_value = self.viewer_controller_pyosirix.movie_idx
		self.assertEqual(movie_idx_value, 0)

	# @pytest.mark.dependency(depends=['TestViewerController::testViewerControllerSetMovieIdx'])
	def testViewerControllerMovieIdx(self):
		movie_idx = self.viewer_controller_pyosirix.movie_idx
		response = self.stub.ViewerControllerMovieIdx(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.movie_idx == 0)
		self.assertEqual(response.movie_idx, movie_idx)

	def testViewerControllerIdx(self):
		idx = self.viewer_controller_pyosirix.idx
		response = self.stub.ViewerControllerIdx(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.idx == 0)
		self.assertEqual(response.idx, idx)

	def testViewerControllerSetWLWW(self):
		wlww = (100, 200)
		self.viewer_controller_pyosirix.wlww = wlww
		wlww_value = self.viewer_controller_pyosirix.wlww
		request = viewercontroller_pb2.ViewerControllerSetWLWWRequest(viewer_controller=self.viewer_controller, wl=100,
																	  ww=200)
		response = self.stub.ViewerControllerSetWLWW(request)
		response2 = self.stub.ViewerControllerWLWW(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response2.wl, wlww_value[0])
		self.assertEqual(response2.ww, wlww_value[1])

	def testViewerControllerWLWW(self):
		wl, ww = self.viewer_controller_pyosirix.wlww
		response = self.stub.ViewerControllerWLWW(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.wl == 100)
		self.assertTrue(response.ww == 200)
		self.assertEqual(response.wl, wl)
		self.assertEqual(response.ww, ww)


class PyOsirixTestDCMPix(GrpcTest):
	"""Test case for ViewerController messaging

	"""

	def setUp(self):
		super().setUp()
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.viewer_controller_pyosirix = self.osirix.frontmost_viewer()
		self.pix_pyosirix = self.viewer_controller_pyosirix.cur_dcm()
		self.pix = self.stub.ViewerControllerCurDCM(self.viewer_controller).pix
		self.pix_list_pyosirix = self.viewer_controller_pyosirix.pix_list(movie_idx=0)


		self.roi_pyosirix = self.viewer_controller_pyosirix.rois_with_name(name="test_grpc", movie_idx=0)[0]
		roi_request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(viewer_controller=self.viewer_controller,
																			   name="test_grpc", movie_idx=0)
		self.roi = self.stub.ViewerControllerROIsWithName(roi_request).rois[0]

	def testDCMPixConvertToRGB(self):
		self.pix_pyosirix.convert_to_rgb() # Catches a failed response implicityl

	def testDCMPixConvertToBW(self):
		self.pix_pyosirix.convert_to_bw() # Catches a failed response implicityl

	def testDCMPixIsRGB(self):
		is_rgb = self.pix_pyosirix.is_rgb
		response = self.stub.DCMPixIsRGB(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Is RGB: %d" % (1 * response.is_rgb))
		self.assertEqual(response.is_rgb, is_rgb)

	def testDCMPixComputeROI(self):
		roi_dict = self.pix_pyosirix.compute_roi(self.roi_pyosirix)
		request = dcmpix_pb2.DCMPixComputeROIRequest(pix=self.pix, roi=self.roi)
		response = self.stub.DCMPixComputeROI(request)
		self.assertEqual(response.status.status, 1)
		print(response)
		print(response.mean)
		self.assertEqual(response.mean, roi_dict["mean"])

	def testDCMPixROIValues(self):
		rows_py, columns_py, values_py = self.pix_pyosirix.get_roi_values(self.roi_pyosirix)
		request = dcmpix_pb2.DCMPixROIValuesRequest(pix=self.pix, roi=self.roi)
		response = self.stub.DCMPixROIValues(request)
		self.assertEqual(response.status.status, 1)
		print(response)
		rows = np.array(response.row_indices)
		columns = np.array(response.column_indices)
		values = np.array(response.values)
		print("Rows:\n", rows)
		print("Columns:\n", columns)
		print("Values:\n", values)

		self.assertTrue(np.array_equal(rows, rows_py))
		self.assertTrue(np.array_equal(columns, columns_py))
		self.assertTrue(np.array_equal(values, values_py))


	def testDCMPixShape(self):
		rows, columns = self.pix_pyosirix.shape
		response = self.stub.DCMPixShape(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Rows:%d" % response.rows)
		print("Columns: %d" % response.columns)

		self.assertEqual(response.rows, rows)
		self.assertEqual(response.columns, columns)


	def testDCMPixSpacing(self):
		rows, columns = self.pix_pyosirix.pixel_spacing
		response = self.stub.DCMPixSpacing(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Row spacing:%.2f" % response.spacing_rows)
		print("Column spacing: %.2f" % response.spacing_columns)

		self.assertEqual(response.spacing_rows, rows)
		self.assertEqual(response.spacing_columns, columns)

	def testDCMPixOrigin(self):
		rows, columns, slices = self.pix_pyosirix.origin
		response = self.stub.DCMPixOrigin(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Row origin:%.2f" % response.origin_rows)
		print("Column origin: %.2f" % response.origin_columns)
		print("Slice origin: %.2f" % response.origin_slices)

		self.assertEqual(response.origin_rows, rows)
		self.assertEqual(response.origin_columns, columns)
		self.assertEqual(response.origin_slices, slices)

	def testDCMPixOrientation(self):
		orientation = self.pix_pyosirix.orientation
		response = self.stub.DCMPixOrientation(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Orientation: ", np.array(response.orientation))

		self.assertTrue(np.array_equal(np.array(response.orientation), orientation))

	def testDCMPixSliceLocation(self):
		location = self.pix_pyosirix.slice_location
		response = self.stub.DCMPixSliceLocation(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Slice location: ", response.slice_location)
		self.assertEqual(location, response.slice_location)

	def testDCMPixSourceFile(self):
		source_file = self.pix_pyosirix.source_file
		response = self.stub.DCMPixSourceFile(self.pix)
		self.assertEqual(response.status.status, 1)
		self.assertFalse(response.source_file == "")
		print("Source file: %s" % response.source_file)
		print(type(response))

		self.assertEqual(response.source_file, source_file)

	#TODO add these tests once the RPC for them have been added to osirix.proto

	# def testDCMPixDicomImage(self):
	# 	dicom_image = self.pix_pyosirix.image_obj()
	# 	print(dicom_image.modality)
	#
	# def testDCMPixDicomSeries(self):
	# 	dicom_image = self.pix_pyosirix.series_obj()
	# 	print(dicom_image.modality)
	#
	# def testDCMPixDicomStudy(self):
	# 	dicom_image = self.pix_pyosirix.study_object()
	# 	print(dicom_image.modality)

	def testDCMPixImage(self):
		image_array = self.pix_pyosirix.image
		response = self.stub.DCMPixImage(self.pix)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.rows > 0)
		self.assertTrue(response.columns > 0)
		print("# rows/columns: %d/%d" % (response.rows, response.columns))


		if response.is_argb:
			self.assertEqual(len(response.image_data_argb), response.rows * response.columns * 4)
			array = np.array(response.image_data_argb).reshape(response.rows, response.columns, 4)
			print("Numpy output:\n", array)
			self.assertTrue(np.array_equal(array, image_array))

		else:
			self.assertEqual(len(response.image_data_float), response.rows * response.columns)
			array = np.array(response.image_data_float).reshape(response.rows, response.columns)
			print("Numpy output:\n", array)
			self.assertTrue(np.array_equal(array, image_array))


	def testDCMPixSetImage(self):
		response = self.stub.DCMPixImage(self.pix)

		print(type(response.image_data_float))
		request = viewercontroller_pb2.ViewerControllerPixListRequest(viewer_controller=self.viewer_controller,
																	  movie_idx=0)
		response_pix_list = self.stub.ViewerControllerPixList(request)
		pix2 = response_pix_list.pix[15]
		print(pix2)
		response_dcm_pix2 = self.stub.DCMPixImage(pix2)
		print(type(response_dcm_pix2.image_data_float))

		if response_dcm_pix2.is_argb:
			# request = dcmpix_pb2.DCMPixSetImageRequest(pix=self.pix, image_data_argb=response.image_data_argb)
			request = dcmpix_pb2.DCMPixSetImageRequest(pix=pix2, image_data_argb=response_dcm_pix2.image_data_argb)

			array = np.array(response_dcm_pix2.image_data_argb).reshape(response_dcm_pix2.rows, response_dcm_pix2.columns, 4)

			self.pix_pyosirix.set_image(response_dcm_pix2.image_data_argb, response_dcm_pix2.is_argb)
		else:
			# request = dcmpix_pb2.DCMPixSetImageRequest(pix=self.pix, image_data_float=response.image_data_float)
			request = dcmpix_pb2.DCMPixSetImageRequest(pix=pix2, image_data_float=response_dcm_pix2.image_data_float)

			array = np.array(response_dcm_pix2.image_data_float).reshape(response_dcm_pix2.rows, response_dcm_pix2.columns)

			self.pix_pyosirix.set_image(response_dcm_pix2.image_data_float, response_dcm_pix2.is_argb)

		response = self.stub.DCMPixSetImage(request)
		self.viewer_controller_pyosirix = self.osirix.frontmost_viewer()
		self.viewer_controller_pyosirix.needs_display_update()

		self.assertEqual(response.status.status, 1)


class PyOsirixTestROI(GrpcTest):
	"""Test case for ROI messaging

	"""

	def setUp(self):
		super().setUp()
		self.viewer_controller_pyosirix = self.osirix.frontmost_viewer()
		self.pix_pyosirix = self.viewer_controller_pyosirix.cur_dcm()
		self.roi_pyosirix = self.viewer_controller_pyosirix.rois_with_name(name="test_grpc", movie_idx=0)[0]
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.pix = self.stub.ViewerControllerCurDCM(self.viewer_controller).pix
		roi_request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(viewer_controller=self.viewer_controller,
																			   name="test_grpc", movie_idx=0)
		self.roi = self.stub.ViewerControllerROIsWithName(roi_request).rois[0]

	def testROIFlipHorizontally(self):
		self.roi_pyosirix.flip_horizontally()
		response = self.stub.ROIFlipHorizontally(self.roi)
		self.assertEqual(response.status.status, 1)

	def testROIFlipVertically(self):
		self.roi_pyosirix.flip_vertically()
		response = self.stub.ROIFlipVertically(self.roi)
		self.assertEqual(response.status.status, 1)

	def testROIArea(self):
		area = self.roi_pyosirix.roi_area()
		response = self.stub.ROIArea(self.roi)
		self.assertEqual(response.status.status, 1)
		print("ROI area: %f" % response.area)
		self.assertEqual(area, response.area)

	def testROICentroid(self):
		x, y = self.roi_pyosirix.centroid
		response = self.stub.ROICentroid(self.roi)
		self.assertEqual(response.status.status, 1)
		print("ROI centroid: x = %.2f, y = %.2f" % (response.x, response.y))
		self.assertEqual(x, response.x)
		self.assertEqual(y, response.y)

	def testROIRotate(self):
		x, y = self.roi_pyosirix.centroid
		self.roi_pyosirix.rotate(theta=45, center=(x,y))

		centroid_response = self.stub.ROICentroid(self.roi)
		request = roi_pb2.ROIRotateRequest(roi=self.roi, degrees=45, x=centroid_response.x, y=centroid_response.y)
		response = self.stub.ROIRotate(request)
		self.assertEqual(response.status.status, 1)

	def testROIMove(self):
		x, y = self.roi_pyosirix.centroid
		self.roi_pyosirix.roi_move(columns=30, rows=-10)
		x_post, y_post = self.roi_pyosirix.centroid

		centroid_response = self.stub.ROICentroid(self.roi)
		request = roi_pb2.ROIMoveRequest(roi=self.roi, columns=30, rows=-10)
		response = self.stub.ROIMove(request)
		centroid_response_post = self.stub.ROICentroid(self.roi)
		self.assertEqual(response.status.status, 1)
		self.assertAlmostEqual(centroid_response_post.x - centroid_response.x, 30, places=2)
		self.assertAlmostEqual(centroid_response_post.y - centroid_response.y, -10, places=2)
		self.assertAlmostEqual(x_post - x, 30, places=2)
		self.assertAlmostEqual(y_post - y, -10, places=2)

		request = roi_pb2.ROIMoveRequest(roi=self.roi, columns=-30, rows=10)

	def testROIPix(self):
		dcm_pix = self.roi_pyosirix.pix
		response = self.stub.ROIPix(self.roi)
		self.assertEqual(response.pix, dcm_pix.osirixrpc_uid)
		self.assertEqual(response.status.status, 1)

	def testROIName(self):
		name = self.roi_pyosirix.name
		response = self.stub.ROIName(self.roi)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response.name, "test_grpc")
		self.assertEqual(response.name, name)

	def testROISetName(self):
		self.roi_pyosirix.name = "test_grpc"
		self.assertEqual(self.roi_pyosirix.name, "test_grpc")

	def testROIColor(self):
		r, g, b = self.roi_pyosirix.color
		response = self.stub.ROIColor(self.roi)
		self.assertEqual(response.status.status, 1)
		print("ROI RGB color: %d/%d/%d" % (response.r, response.g, response.b))

		self.assertEqual(response.r, r)
		self.assertEqual(response.g, g)
		self.assertEqual(response.b, b)

	def testROISetColor(self):
		r, g, b = self.roi_pyosirix.color
		self.roi_pyosirix = (r, g, b)

	def testROIOpacity(self):
		opacity = self.roi_pyosirix.opacity
		response = self.stub.ROIOpacity(self.roi)
		self.assertEqual(response.status.status, 1)
		print("ROI opacity: %.2f" % response.opacity)
		self.assertEqual(response.opacity, opacity)

	def testROISetOpacity(self):
		opacity = self.roi_pyosirix.opacity
		self.roi_pyosirix.opacity = opacity

	def testROIThickness(self):
		thickness = self.roi_pyosirix.thickness
		response = self.stub.ROIThickness(self.roi)
		self.assertEqual(response.status.status, 1)
		print("ROI thickness: %.2f" % response.thickness)
		self.assertEqual(response.thickness, thickness)

	def testROISetThickness(self):
		thickness = self.roi_pyosirix.thickness
		self.roi_pyosirix.thickness = thickness

	def testROIPoints(self):

		points_py = self.roi_pyosirix.points
		response = self.stub.ROIPoints(self.roi)
		self.assertEqual(response.status.status, 1)
		points = []
		for i in range(len(response.points)):
			points.append([response.points[i].x, response.points[i].y])
		points = np.array(points)
		print("ROI points:\n", points)

		self.assertTrue(np.array_equal(points, points_py))

	def testROISetPoints(self):
		# points_array = self.roi_pyosirix.points
		# self.roi_pyosirix.points = points_array

		points_response = self.stub.ROIPoints(self.roi)
		points_request = []
		for i in range(len(points_response.points)):
			points_request.append(
				roi_pb2.ROISetPointsRequest.Point2D(x=points_response.points[i].x, y=points_response.points[i].y))
		request = roi_pb2.ROISetPointsRequest(roi=self.roi, points=points_request)
		response = self.stub.ROISetPoints(request)
		self.assertEqual(response.status.status, 1)


class PyOsirixTestVRController(GrpcTest):
	"""Test case for VRController messaging

	"""

	def setUp(self):
		super().setUp()
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.vr_controller = self.stub.ViewerControllerVRControllers(self.viewer_controller).vr_controllers[0]

		self.viewer_controller_pyosirix = self.osirix.frontmost_viewer()
		self.vr_controller_pyosirix = self.osirix.frontmost_vr_controller()

	def testVRControllerWLWW(self):
		wlww = self.vr_controller_pyosirix.wlww
		response = self.stub.VRControllerWLWW(self.vr_controller)
		print("VRController wl/ww: %.2f/%.2f" % (response.wl, response.ww))
		self.assertEqual(response.wl, wlww[0])
		self.assertEqual(response.ww, wlww[1])
		self.assertEqual(response.status.status, 1)

	def testVRControllerSetWLWW(self):
		test = (200.0, 500.0)
		self.vr_controller_pyosirix.wlww = test
		wlww_pyosirix = self.vr_controller_pyosirix.wlww
		request = vrcontroller_pb2.VRControllerSetWLWWRequest(vr_controller=self.vr_controller, wl=200, ww=500)
		response = self.stub.VRControllerSetWLWW(request)
		response2 = self.stub.VRControllerWLWW(self.vr_controller)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response2.wl, wlww_pyosirix[0])
		self.assertEqual(response2.ww, wlww_pyosirix[1])

	def testVRControllerRenderingMode(self):
		rendering_mode = self.vr_controller_pyosirix.rendering_mode
		response = self.stub.VRControllerRenderingMode(self.vr_controller)
		print("VRController rendering mode: %s" % response.rendering_mode)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response.rendering_mode, rendering_mode)

	def testVRControllerSetRenderingMode(self):
		self.vr_controller_pyosirix.rendering_mode = "MIP"
		rendering_mode = self.vr_controller_pyosirix.rendering_mode
		request = vrcontroller_pb2.VRControllerSetRenderingModeRequest(vr_controller=self.vr_controller,
																	   rendering_mode="MIP")
		response2 = self.stub.VRControllerRenderingMode(self.vr_controller)
		response = self.stub.VRControllerSetRenderingMode(request)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response2.rendering_mode, rendering_mode)

	def testVRControllerViewer2D(self):
		viewer_2d = self.vr_controller_pyosirix.viewer_2d()
		response = self.stub.VRControllerViewer2D(self.vr_controller)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response.viewer_controller.osirixrpc_uid, self.viewer_controller.osirixrpc_uid)
		self.assertEqual(viewer_2d.osirixrpc_uid.osirixrpc_uid, response.viewer_controller.osirixrpc_uid)

	def testVRControllerBlendingController(self):
		blending_controller = self.vr_controller_pyosirix.blending_controller()
		response = self.stub.VRControllerBlendingController(self.vr_controller)
		# What is blending controller? It is empty
		print(response.viewer_controller)
		self.assertEqual(response.status.status,1)  # TODO - not much of a test.  May need some better test data that allows for this.
		self.assertIsNotNone(response.viewer_controller)
		self.assertIsNotNone(blending_controller.osirixrpc_uid)

	def testVRControllerStyle(self):
		style = self.vr_controller_pyosirix.style
		response = self.stub.VRControllerStyle(self.vr_controller)
		self.assertEqual(response.status.status, 1)
		print("VRController style: %s" % response.style)
		self.assertEqual(response.style, style)

	def testVRControllerTitle(self):
		title = self.vr_controller_pyosirix.title
		response = self.stub.VRControllerTitle(self.vr_controller)
		self.assertEqual(response.status.status, 1)
		print("VRController title: %s" % response.title)
		self.assertEqual(response.title, title)

	def testVRControllerROIVolumes(self):
		# Not implemented in pyOsirix yet
		# self.vr_controller_pyosirix
		response = self.stub.VRControllerROIVolumes(self.vr_controller)
		print(response.roi_volumes[0])
		self.assertEqual(response.status.status, 1)

class PyOsirixTestBrowserController(GrpcTest):
	"""Test case for ROI messaging

	"""

	def setUp(self):
		super().setUp()
		self.browser_controller = self.stub.OsirixCurrentBrowser(utilities_pb2.Empty()).browser_controller
		self.browser_controller_pyosirix = self.osirix.current_browser()

	def testBrowserControllerDatabaseSelection(self):
		study_series = self.browser_controller_pyosirix.database_selection()
		response = self.stub.BrowserControllerDatabaseSelection(self.browser_controller)
		self.assertEqual(response.status.status, 1)
		print("Studies: ", response.studies)
		print("Series: ", response.series)
		self.assertEqual(len(response.studies), len(study_series[0]))
		self.assertEqual(len(response.series), len(study_series[1]))


if __name__ == '__main__':
    unittest.main()
