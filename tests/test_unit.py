import unittest
import sys

import grpc
import pytest
import numpy as np
import matplotlib.pyplot as pl

sys.path.append("../src/python")
import osirix_pb2
import utilities_pb2
import types_pb2
import viewercontroller_pb2
import vrcontroller_pb2
import dcmpix_pb2
import roi_pb2
import roivolume_pb2
import osirix_pb2_grpc

import os
import matplotlib.pyplot as plt
import numpy as np
import torch
import pydicom
import dicom2nifti
from tqdm import tqdm

from monai.losses import DiceCELoss, DiceLoss
from monai.inferers import sliding_window_inference
from monai.transforms import (
    AsDiscrete,
    AddChanneld,
    Compose,
    CropForegroundd,
    LoadImaged,
    Orientationd,
    RandFlipd,
    RandCropByPosNegLabeld,
    RandShiftIntensityd,
    ScaleIntensityRanged,
    Spacingd,
    RandRotate90d,
    ToTensord,
	EnsureChannelFirstd,
	EnsureTyped,
	Invertd,
	AsDiscreted
)

from monai.utils import first, set_determinism
from monai.handlers.utils import from_engine
from monai.networks.nets import UNet, UNETR
from monai.networks.layers import Norm
from monai.metrics import DiceMetric
from monai.data import CacheDataset, DataLoader, Dataset, decollate_batch
from monai.config import print_config
from monai.apps import download_and_extract

# The test defined here will require:
# ===================================
# 1) OsiriX/Horos application open with plugin installed
# 2) A single viewer controller open, with multiple frames
# 3) At least one ROI called test_grpc
# 4) A 3D renedered window open

class GrpcTestException(Exception):
	"""Exception raised when connection to OsiriX cannot be established

	Attributes:
		message -- explnation of the error

	"""
	def __init__(self, message=""):
		self.message = message
		super().__init__(self.message)


class GrpcTest(unittest.TestCase):
	"""Base test class

	"""
	def setUp(self):
		try:
			# port = 8890
			port = 50051
			server_url_localhost = 'localhost:' + str(port)
			server_url = "192.168.0.62:8890"
			channel_opt = [('grpc.max_send_message_length', 512 * 1024 * 1024),
			               ('grpc.max_receive_message_length', 512 * 1024 * 1024)]
			self.channel = grpc.insecure_channel(server_url_localhost, options=channel_opt)
			self.stub = osirix_pb2_grpc.OsiriXServiceStub(self.channel)
		except:
			raise GrpcTestException("No connection to OsiriX can be established")


class TestOsirix(GrpcTest):
	"""Test case for core osirix messaging

	"""
	def testOsirixCurrentBrowser(self):
		response = self.stub.OsirixCurrentBrowser(utilities_pb2.Empty())
		print(type(response))
		self.assertEqual(response.status.status, 1)  						# <-check for success
		self.assertNotEqual(response.browser_controller.osirixrpc_uid, 0)

	def testOsirixFrontmostViewer(self):
		response = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty())
		self.assertEqual(response.status.status, 1)
		self.assertNotEqual(response.viewer_controller.osirixrpc_uid, 0)

	def testOsirixDisplayed2DViewers(self):
		response = self.stub.OsirixDisplayed2DViewers(utilities_pb2.Empty())
		self.assertEqual(response.status.status, 1)
		self.assertTrue(len(response.viewer_controllers) > 0)

	def testOsirixFrontmostVRController(self):
		response = self.stub.OsirixFrontmostVRController(utilities_pb2.Empty())
		self.assertEqual(response.status.status, 1)
		self.assertNotEqual(response.vr_controller.osirixrpc_uid, "")

	def testOsirixDisplayedVRControllers(self):
		response = self.stub.OsirixDisplayedVRControllers(utilities_pb2.Empty())
		self.assertEqual(response.status.status, 1)
		self.assertTrue(len(response.vr_controllers) > 0)


class TestViewerController(GrpcTest):
	"""Test case for ViewerController messaging

	"""
	def setUp(self):
		super().setUp()
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller

	def testViewerControllerPixList(self):
		request = viewercontroller_pb2.ViewerControllerPixListRequest(viewer_controller = self.viewer_controller, movie_idx = 0)
		response = self.stub.ViewerControllerPixList(request)
		print(response)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(len(response.pix) > 0)

	def testViewerControllerNeedsDisplayUpdate(self):
		response = self.stub.ViewerControllerNeedsDisplayUpdate(self.viewer_controller)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerROIList(self):
		request = viewercontroller_pb2.ViewerControllerROIListRequest(viewer_controller = self.viewer_controller, movie_idx = 0)
		response = self.stub.ViewerControllerROIList(request)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(len(response.roi_slices) > 0)
		# print(response.roi_slices)
		for roi_slice in response.roi_slices:
			print(roi_slice)

	def testViewerControllerNewROI_Mask(self):
		buffer_array = np.random.randn(40 * 40) > 0
		buffer = viewercontroller_pb2.ViewerControllerNewROIRequest.Buffer(buffer =  1 * buffer_array, rows = 40, columns = 40)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 255, g = 0, b = 200)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, movie_idx = 0, position = 0, itype = 20, buffer = buffer, color = color, opacity = 0.5, name = "random")
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Oval(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x = 66., origin_y = 42., width = 20., height = 10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 255, g = 100, b = 200)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, movie_idx = 0, position = 0, itype = 9, rectangle = rect, color = color, opacity = 0.5, name = "oval", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Arrow(self):
		# Points seem to go in order [head, tail]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 0, g = 255, b = 0)
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=66., y=42.), viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=99., y=24.)]
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, points=points, movie_idx = 0, position = 0, itype = 14, color = color, opacity = 0.5, name = "arrow", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Point(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x = 66., origin_y = 42., width = 20., height = 10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 0, g = 255, b = 255)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, rectangle=rect, movie_idx = 0, position = 0, itype = 19, color = color, opacity = 1.0, name = "point", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	# A rectangle...
	def testViewerControllerNewROI_TROI(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x = 66., origin_y = 42., width = 20., height = 10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 255, g = 100, b = 100)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, rectangle=rect, movie_idx = 0, position = 0, itype = 6, color = color, opacity = 1.0, name = "tROI", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Text(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x = 66., origin_y = 42., width = 20., height = 10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 255, g = 100, b = 100)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, rectangle=rect, movie_idx = 0, position = 0, itype = 13, color = color, opacity = 1.0, name = "Some text", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_TTAGT(self):
		points = [[ 50.20499802, 32.32217407], [ 53.27367783, 38.77323914], [ 64.68674469, 25.43341637], [ 69.71873474, 36.01180649], [ 41.8967247, 36.27430344], [ 68.91729736, 23.42099953]]
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=p[0], y=p[1]) for p in points]
		print(len(points))
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 100, g = 250, b = 220)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, points=points, movie_idx = 0, position = 0, itype = 29, color = color, opacity = 1.0, name = "tTAGT", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Pencil(self):
		points = [[ 50.20499802, 32.32217407], [ 53.27367783, 38.77323914], [ 64.68674469, 25.43341637], [ 69.71873474, 36.01180649], [ 41.8967247, 36.27430344], [ 68.91729736, 23.42099953]]
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=p[0], y=p[1]) for p in points]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 100, g = 50, b = 220)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, points=points, movie_idx = 0, position = 0, itype = 15, color = color, opacity = 1.0, name = "pencil", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Angle(self):
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=71., y=-2.),\
				  viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=67., y=11.),\
				  viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=90., y=9.)]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 100, g = 50, b = 220)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, points=points, movie_idx = 0, position = 0, itype = 12, color = color, opacity = 1.0, name = "pencil", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerNewROI_Measure(self):
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=71., y=-2.),\
				  viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=67., y=11.)]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 100, g = 50, b = 0)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, points=points, movie_idx = 0, position = 0, itype = 5, color = color, opacity = 1.0, name = "measure", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)
		print(response.roi)

	def testViewerControllerCurDCM(self):
		response = self.stub.ViewerControllerCurDCM(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertNotEqual(response.pix.osirixrpc_uid, "")

	def testViewerControllerROIsWithName(self):
		request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(viewer_controller = self.viewer_controller, name = "test_grpc", movie_idx = 0)
		response = self.stub.ViewerControllerROIsWithName(request)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(len(response.rois) > 0)
		self.assertNotEqual(response.rois[0].osirixrpc_uid, "")

		request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(viewer_controller = self.viewer_controller, name = "test_grpc", in_4d = True)
		response = self.stub.ViewerControllerROIsWithName(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerSelectedROIs(self):
		response = self.stub.ViewerControllerSelectedROIs(self.viewer_controller)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerResampleViewerController(self):
		# Check that it doesn't work if bad viewer id provided.
		viewer_controller_fake = types_pb2.ViewerController(osirixrpc_uid = "bad_id")
		request = viewercontroller_pb2.ViewerControllerResampleViewerControllerRequest(viewer_controller = viewer_controller_fake, fixed_viewer_controller = self.viewer_controller)
		response = self.stub.ViewerControllerResampleViewerController(request)
		print(response)
		self.assertEqual(response.status.status, 0)

	def testViewerControllerVRControllers(self):
		response = self.stub.ViewerControllerVRControllers(self.viewer_controller)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerTitle(self):
		response = self.stub.ViewerControllerTitle(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertFalse(response.title == "")

	def testViewerControllerModality(self):
		response = self.stub.ViewerControllerModality(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertFalse(response.modality == "")

	def testViewerControllerSetMovieIdx(self):
		request = viewercontroller_pb2.ViewerControllerSetMovieIdxRequest(viewer_controller= self.viewer_controller, movie_idx = 0)
		response = self.stub.ViewerControllerSetMovieIdx(request)
		self.assertEqual(response.status.status, 1)

	# @pytest.mark.dependency(depends=['TestViewerController::testViewerControllerSetMovieIdx'])
	def testViewerControllerMovieIdx(self):
		response = self.stub.ViewerControllerMovieIdx(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.movie_idx == 0)

	def testViewerControllerIdx(self):
		response = self.stub.ViewerControllerIdx(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.idx == 0)

	def testViewerControllerSetWLWW(self):
		request = viewercontroller_pb2.ViewerControllerSetWLWWRequest(viewer_controller=self.viewer_controller, wl = 100, ww = 200)
		response = self.stub.ViewerControllerSetWLWW(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerWLWW(self):
		response = self.stub.ViewerControllerWLWW(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.wl == 100)
		self.assertTrue(response.ww == 200)


class TestDCMPix(GrpcTest):
	"""Test case for ViewerController messaging

	"""
	def setUp(self):
		super().setUp()
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.pix = self.stub.ViewerControllerCurDCM(self.viewer_controller).pix
		roi_request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(viewer_controller = self.viewer_controller, name = "test_grpc", movie_idx = 0)
		self.roi = self.stub.ViewerControllerROIsWithName(roi_request).rois[0]


	def testDCMPixConvertToRGB(self):
		request = dcmpix_pb2.DCMPixConvertToRGBRequest(pix = self.pix, rgb_channel = 3)
		response = self.stub.DCMPixConvertToRGB(request)
		self.assertEqual(response.status.status, 1)

	def testDCMPixConvertToBW(self):
		request = dcmpix_pb2.DCMPixConvertToBWRequest(pix = self.pix, bw_channel = 3)
		response = self.stub.DCMPixConvertToBW(request)
		self.assertEqual(response.status.status, 1)

	def testDCMPixIsRGB(self):
		response = self.stub.DCMPixIsRGB(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Is RGB: %d" % (1 * response.is_rgb))

	def testDCMPixComputeROI(self):
		request = dcmpix_pb2.DCMPixComputeROIRequest(pix = self.pix, roi = self.roi)
		response = self.stub.DCMPixComputeROI(request)
		self.assertEqual(response.status.status, 1)
		print(response)
		print(response.mean)

	def testDCMPixROIValues(self):
		request = dcmpix_pb2.DCMPixROIValuesRequest(pix = self.pix, roi = self.roi)
		response = self.stub.DCMPixROIValues(request)
		self.assertEqual(response.status.status, 1)
		print(response)
		rows = np.array(response.row_indices)
		columns = np.array(response.column_indices)
		values = np.array(response.values)
		print("Rows:\n", rows)
		print("Columns:\n", columns)
		print("Values:\n", values)

	def testDCMPixShape(self):
		response = self.stub.DCMPixShape(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Rows:%d" % response.rows)
		print("Columns: %d" % response.columns)

	def testDCMPixSpacing(self):
		response = self.stub.DCMPixSpacing(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Row spacing:%.2f" % response.spacing_rows)
		print("Column spacing: %.2f" % response.spacing_columns)

	def testDCMPixOrigin(self):
		response = self.stub.DCMPixOrigin(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Row origin:%.2f" % response.origin_rows)
		print("Column origin: %.2f" % response.origin_columns)
		print("Slice origin: %.2f" % response.origin_slices)

	def testDCMPixOrientation(self):
		response = self.stub.DCMPixOrientation(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Orientation: ", np.array(response.orientation))

	def testDCMPixSliceLocation(self):
		response = self.stub.DCMPixSliceLocation(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Slice location: ", response.slice_location)

	def testDCMPixSourceFile(self):
		response = self.stub.DCMPixSourceFile(self.pix)
		self.assertEqual(response.status.status, 1)
		self.assertFalse(response.source_file == "")
		print("Source file: %s" % response.source_file)
		print(type(response))

	def testDCMPixImage(self):
		response = self.stub.DCMPixImage(self.pix)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.rows > 0)
		self.assertTrue(response.columns > 0)
		print("# rows/columns: %d/%d" % (response.rows, response.columns))
		if response.is_argb:
			self.assertEqual(len(response.image_data_argb), response.rows * response.columns * 4)
			print("Numpy output:\n", np.array(response.image_data_argb).reshape(response.rows, response.columns, 4))
		else:
			self.assertEqual(len(response.image_data_float), response.rows * response.columns)
			print("Numpy output:\n", np.array(response.image_data_float).reshape(response.rows, response.columns))

	def testDCMPixSetImage(self):
		response = self.stub.DCMPixImage(self.pix)
		if response.is_argb:
			request = dcmpix_pb2.DCMPixSetImageRequest(pix = self.pix, image_data_argb = response.image_data_argb)
		else:
			request = dcmpix_pb2.DCMPixSetImageRequest(pix = self.pix, image_data_float = response.image_data_float)
		response = self.stub.DCMPixSetImage(request)
		self.assertEqual(response.status.status, 1)

	def testDCMPixGetMapFromROI(self):
		request = dcmpix_pb2.DCMPixGetMapFromROIRequest(pix = self.pix, roi = self.roi)
		response = self.stub.DCMPixGetMapFromROI(request)
		self.assertEqual(response.status.status, 1)
		print("Numpy output:\n", np.array(response.map).reshape(response.rows, response.columns))


class TestROI(GrpcTest):
	"""Test case for ROI messaging

	"""
	def setUp(self):
		super().setUp()
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.pix = self.stub.ViewerControllerCurDCM(self.viewer_controller).pix
		roi_request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(viewer_controller = self.viewer_controller, name = "test_grpc", movie_idx = 0)
		self.roi = self.stub.ViewerControllerROIsWithName(roi_request).rois[0]

	def testROIFlipHorizontally(self):
		response = self.stub.ROIFlipHorizontally(self.roi)
		self.assertEqual(response.status.status, 1)

	def testROIFlipVertically(self):
		response = self.stub.ROIFlipVertically(self.roi)
		self.assertEqual(response.status.status, 1)

	def testROIArea(self):
		response = self.stub.ROIArea(self.roi)
		self.assertEqual(response.status.status, 1)
		print("ROI area: %f" % response.area)

	def testROICentroid(self):
		response = self.stub.ROICentroid(self.roi)
		self.assertEqual(response.status.status, 1)
		print("ROI centroid: x = %.2f, y = %.2f" % (response.x, response.y))

	def testROIRotate(self):
		centroid_response = self.stub.ROICentroid(self.roi)
		request = roi_pb2.ROIRotateRequest(roi = self.roi, degrees = 45, x = centroid_response.x, y = centroid_response.y)
		response = self.stub.ROIRotate(request)
		self.assertEqual(response.status.status, 1)

	def testROIMove(self):
		centroid_response = self.stub.ROICentroid(self.roi)
		request = roi_pb2.ROIMoveRequest(roi = self.roi, columns = 30, rows = -10)
		response = self.stub.ROIMove(request)
		centroid_response_post = self.stub.ROICentroid(self.roi)
		self.assertEqual(response.status.status, 1)
		self.assertAlmostEqual(centroid_response_post.x - centroid_response.x, 30, places = 2)
		self.assertAlmostEqual(centroid_response_post.y - centroid_response.y, -10, places = 2)
		request = roi_pb2.ROIMoveRequest(roi = self.roi, columns = -30, rows = 10)

	def testROIPix(self):
		response = self.stub.ROIPix(self.roi)
		self.assertEqual(response.status.status, 1)

	def testROIName(self):
		response = self.stub.ROIName(self.roi)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response.name, "test_grpc")

	def testROISetName(self):
		request = roi_pb2.ROISetNameRequest(roi = self.roi, name = "test_grpc")
		response = self.stub.ROISetName(request)
		print(response)
		self.assertEqual(response.status.status, 1)

	def testROIColor(self):
		response = self.stub.ROIColor(self.roi)
		self.assertEqual(response.status.status, 1)
		print("ROI RGB color: %d/%d/%d" % (response.r, response.g, response.b))

	def testROISetColor(self):
		color_response = self.stub.ROIColor(self.roi)
		request = roi_pb2.ROISetColorRequest(roi = self.roi, r = color_response.r, g = color_response.g, b = color_response.b)
		response = self.stub.ROISetColor(request)
		self.assertEqual(response.status.status, 1)

	def testROIOpacity(self):
		response = self.stub.ROIOpacity(self.roi)
		self.assertEqual(response.status.status, 1)
		print("ROI opacity: %.2f" % response.opacity)

	def testROISetOpacity(self):
		opacity_response = self.stub.ROIOpacity(self.roi)
		request = roi_pb2.ROISetOpacityRequest(roi = self.roi, opacity = opacity_response.opacity)
		response = self.stub.ROISetOpacity(request)
		self.assertEqual(response.status.status, 1)

	def testROIThickness(self):
		response = self.stub.ROIThickness(self.roi)
		self.assertEqual(response.status.status, 1)
		print("ROI thickness: %.2f" % response.thickness)

	def testROISetThickness(self):
		thickness_response = self.stub.ROIThickness(self.roi)
		request = roi_pb2.ROISetThicknessRequest(roi = self.roi, thickness = thickness_response.thickness)
		response = self.stub.ROISetThickness(request)
		self.assertEqual(response.status.status, 1)

	def testROIPoints(self):
		response = self.stub.ROIPoints(self.roi)
		self.assertEqual(response.status.status, 1)
		points = []
		for i in range(len(response.points)):
			points.append([response.points[i].x, response.points[i].y])
		points = np.array(points)
		print("ROI points:\n", points)

	def testROISetPoints(self):
		points_response = self.stub.ROIPoints(self.roi)
		points_request = []
		for i in range(len(points_response.points)):
			points_request.append(roi_pb2.ROISetPointsRequest.Point2D(x = points_response.points[i].x, y = points_response.points[i].y))
		request = roi_pb2.ROISetPointsRequest(roi = self.roi, points = points_request)
		response = self.stub.ROISetPoints(request)
		self.assertEqual(response.status.status, 1)


class TestVRController(GrpcTest):
	"""Test case for VRController messaging 

	"""
	def setUp(self):
		super().setUp()
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.vr_controller = self.stub.ViewerControllerVRControllers(self.viewer_controller).vr_controllers[0]

	def testVRControllerWLWW(self):
		response = self.stub.VRControllerWLWW(self.vr_controller)
		print("VRController wl/ww: %.2f/%.2f" % (response.wl, response.ww))
		self.assertEqual(response.status.status, 1)

	def testVRControllerSetWLWW(self):
		request = vrcontroller_pb2.VRControllerSetWLWWRequest(vr_controller = self.vr_controller, wl = 200, ww = 500)
		response = self.stub.VRControllerSetWLWW(request)
		self.assertEqual(response.status.status, 1)

	def testVRControllerRenderingMode(self):
		response = self.stub.VRControllerRenderingMode(self.vr_controller)
		print("VRController rendering mode: %s" % response.rendering_mode)
		self.assertEqual(response.status.status, 1)

	def testVRControllerSetRenderingMode(self):
		request = vrcontroller_pb2.VRControllerSetRenderingModeRequest(vr_controller = self.vr_controller, rendering_mode = "MIP")
		response = self.stub.VRControllerSetRenderingMode(request)
		self.assertEqual(response.status.status, 1)

	def testVRControllerViewer2D(self):
		response = self.stub.VRControllerViewer2D(self.vr_controller)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response.viewer_controller.osirixrpc_uid, self.viewer_controller.osirixrpc_uid)

	def testVRControllerBlendingController(self):
		response = self.stub.VRControllerBlendingController(self.vr_controller)
		# What is blending controller? It is empty
		print(response.viewer_controller)
		self.assertEqual(response.status.status, 1)  # TODO - not much of a test.  May need some better test data that allows for this.

	def testVRControllerStyle(self):
		response = self.stub.VRControllerStyle(self.vr_controller)
		self.assertEqual(response.status.status, 1)
		print("VRController style: %s" % response.style)

	def testVRControllerTitle(self):
		response = self.stub.VRControllerTitle(self.vr_controller)
		self.assertEqual(response.status.status, 1)
		print("VRController title: %s" % response.title)

	def testVRControllerROIVolumes(self):
		response = self.stub.VRControllerROIVolumes(self.vr_controller)
		print(response.roi_volumes[0])
		self.assertEqual(response.status.status, 1)


# class TestROIVolume(GrpcTest):
# 	"""Test case for VRController messaging

# 	"""
# 	def setUp(self):
# 		super().setUp()
# 		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
# 		self.vr_controller = self.stub.ViewerControllerVRControllers(self.viewer_controller).vr_controllers[0]
# 		self.roi_volumes = self.stub.VRControllerROIVolumes(self.vr_controller).roi_volumes

# 	def testROIVolumeName(self):
# 		response = self.stub.ROIVolumeName(self.roi_volumes[0])
# 		print(response.name)
# 		self.assertEqual(response.status.status, 1)

# 	def testROIVolumeColor(self):
# 		response = self.stub.ROIVolumeColor(self.roi_volumes[0])
# 		print("ROIVolume color: %d/%d/%d" % (response.r, response.g, response.b))
# 		self.assertEqual(response.status.status, 1)

# 	def testROIVolumeVolume(self):
# 		response = self.stub.ROIVolumeVolume(self.roi_volumes[0])
# 		print("ROIVolume volume: %.2f" % response.volume)
# 		self.assertEqual(response.status.status, 1)

# 	def testROIVolumeOpacity(self):
# 		response = self.stub.ROIVolumeOpacity(self.roi_volumes[0])
# 		print("ROIVolume opacity: %.2f" % response.opacity)
# 		self.assertEqual(response.status.status, 1)

# 	def testROIVolumeFactor(self):
# 		response = self.stub.ROIVolumeFactor(self.roi_volumes[0])
# 		print("ROIVolume factor: %.2f" % response.factor)
# 		self.assertEqual(response.status.status, 1)

# 	def testROIVolumeVisible(self):
# 		response = self.stub.ROIVolumeVisible(self.roi_volumes[0])
# 		if response.visible:
# 			print("ROIVolume visible")
# 		else:
# 			print("ROIVolume not visible")
# 		self.assertEqual(response.status.status, 1)

	# TODO - there appears to be a bug with Horos displaying ROI volumes, hence cannot yet test these...
	# def testROIVolumeSetVisible(self):
	# 	request = roivolume_pb2.ROIVolumeSetVisibleRequest(roi = self.roi_volumes[0], visible = True)
	# 	response = self.stub.ROIVolumeSetVisible(request)
	# 	self.assertEqual(response.status.status, 1)


class TestBrowserController(GrpcTest):
	"""Test case for ROI messaging

	"""
	def setUp(self):
		super().setUp()
		self.browser_controller = self.stub.OsirixCurrentBrowser(utilities_pb2.Empty()).browser_controller
	
	def testBrowserControllerDatabaseSelection(self):

		response = self.stub.BrowserControllerDatabaseSelection(self.browser_controller)
		self.assertEqual(response.status.status, 1)
		print("Studies: ", response.studies)
		print("Series: ", response.series)
		response_ = self.stub.DicomStudyDateAdded(response.studies[0])
		print(response_)

		# response_test = self.stub.DicomStudySeries(response.studies[0])
		# response_test_name = self.stub.DicomSeriesName(response.studies[0])
		# response_test_name_study = self.stub.DicomStudyName(response.studies[0])
		# print(response_test_name)
		# print(response_test_name_study)
		# print(response_test.series[0])
		# response_images = self.stub.DicomSeriesImages(response_test.series[0])
		# response_image_name = self.stub.DicomSeriesImages(response_test.series[0])
		#
		# print(response_image_name)
		# print(response_images)


	def testDicomStudy(self):
		response = self.stub.BrowserControllerDatabaseSelection(self.browser_controller)
		self.assertEqual(response.status.status, 1)
		print("Studies: ", response.studies)

		response_study_paths = self.stub.DicomStudyPaths(response.studies[0])
		response_study_images = self.stub.DicomStudyImages(response.studies[0])
		response_study_modalities = self.stub.DicomStudyModalities(response.studies[0])
		response_study_no_of_files = self.stub.DicomStudyNoFiles(response.studies[0])
		response_study_raw_no_of_files = self.stub.DicomStudyRawNoFiles(response.studies[0])
		response_study_no_of_files_excl_multiframes = self.stub.DicomStudyNoFilesExcludingMultiFrames(response.studies[0])
		response_study_no_of_images = self.stub.DicomStudyNumberOfImages(response.studies[0])
		response_study_series = self.stub.DicomStudySeries(response.studies[0])
		response_study_name = self.stub.DicomStudyName(response.studies[0])
		response_study_date = self.stub.DicomStudyDate(response.studies[0])
		response_study_date_added = self.stub.DicomStudyDateAdded(response.studies[0])
		# response_study_date_of_birth = self.stub.DicomStudyDateOfBirth(response.studies[0])
		# response_study_institution_name = self.stub.DicomStudyInstitutionName(response.studies[0])
		response_study_patient_id = self.stub.DicomStudyPatientID(response.studies[0])
		response_study_patient_uid = self.stub.DicomStudyPatientUID(response.studies[0])
		response_study_patient_sex = self.stub.DicomStudyPatientSex(response.studies[0])
		# response_study_performing_physician = self.stub.DicomStudyPerformingPhysician(response.studies[0])
		# response_study_referring_physician = self.stub.DicomStudyReferringPhysician(response.studies[0])
		response_study_study_instance_uid = self.stub.DicomStudyStudyInstanceUID(response.studies[0])
		response_study_study_name = self.stub.DicomStudyStudyName(response.studies[0])

		print(response_study_date_added)
		print(response_study_date_added.year)
		print(response_study_date_added.month)
		print(response_study_date_added.day)
		print(response_study_date_added.hour)
		print(response_study_date_added.minute)
		print(response_study_date_added.second)
		print(response_study_paths)
		print(response_study_images)
		print(response_study_modalities)
		print(response_study_no_of_files)
		print(response_study_raw_no_of_files)
		print(response_study_no_of_files_excl_multiframes)
		print(response_study_no_of_images)
		print(response_study_series)
		print(response_study_name)
		print(response_study_date)
		# print(response_study_date_of_birth)
		# print(response_study_institution_name) # Will have error on the Objective C side if this value is missing and the OsirixService will crash
		print(response_study_patient_id)
		print(response_study_patient_uid)
		print(response_study_patient_sex)
		# print(response_study_performing_physician)
		# print(response_study_referring_physician)
		print(response_study_study_instance_uid)
		print(response_study_study_name)

	def testDicomSeries(self):
		response = self.stub.BrowserControllerDatabaseSelection(self.browser_controller)
		self.assertEqual(response.status.status, 1)
		print("Series: ", response.series)
		print("Studies: ", response.studies)

		response_series = self.stub.DicomStudySeries(response.studies[0])
		series = response_series.series[0]

		response_series_images = self.stub.DicomSeriesImages(series)
		response_series_name = self.stub.DicomSeriesName(series)
		response_series_paths = self.stub.DicomSeriesPaths(series)
		response_series_previous_series = self.stub.DicomSeriesPreviousSeries(series)
		response_series_next_series = self.stub.DicomSeriesNextSeries(series)
		response_series_sorted_images = self.stub.DicomSeriesSortedImages(series)
		response_series_study = self.stub.DicomSeriesStudy(series)
		response_series_instance_uid = self.stub.DicomSeriesSeriesInstanceUID(series)
		response_series_sop_class_uid = self.stub.DicomSeriesSeriesSOPClassUID(series)
		response_series_series_description = self.stub.DicomSeriesSeriesDescription(series)
		response_series_modality = self.stub.DicomSeriesModality(series)
		response_series_date = self.stub.DicomSeriesDate(series)

		print(response_series_images)
		print(response_series_name)
		print(response_series_paths)
		print(response_series_previous_series)
		print(response_series_next_series)
		print(response_series_sorted_images)
		print(response_series_study)
		print(response_series_instance_uid)
		print(response_series_sop_class_uid)
		print(response_series_series_description)
		print(response_series_modality)
		print(response_series_date)


	def testDicomImage(self):
		response = self.stub.BrowserControllerDatabaseSelection(self.browser_controller)
		self.assertEqual(response.status.status, 1)
		print("Series: ", response.series)
		print("Studies: ", response.studies)

		response_series = self.stub.DicomStudySeries(response.studies[0])
		series = response_series.series[0]
		response_images = self.stub.DicomSeriesImages(series)
		response_series_single_image = response_images.images[0]

		response_image_width = self.stub.DicomImageWidth(response_series_single_image)
		response_image_height = self.stub.DicomImageHeight(response_series_single_image)
		response_image_sop_instance_uid = self.stub.DicomImageSOPInstanceUID(response_series_single_image)
		response_image_complete_path = self.stub.DicomImageCompletePath(response_series_single_image)
		response_image_date = self.stub.DicomImageDate(response_series_single_image)
		response_image_no_of_frames = self.stub.DicomImageNumberOfFrames(response_series_single_image)
		response_image_modality = self.stub.DicomImageModality(response_series_single_image)
		response_image_series = self.stub.DicomImageSeries(response_series_single_image)
		response_image_slice_location = self.stub.DicomImageSliceLocation(response_series_single_image)
		response_image_instance_number = self.stub.DicomImageInstanceNumber(response_series_single_image)

		print(response_image_width)
		print(response_image_height)
		print(response_image_sop_instance_uid)
		print(response_image_complete_path)
		print(response_image_date)
		print(response_image_no_of_frames)
		print(response_image_modality)
		print(response_image_series)
		print(response_image_slice_location)
		print(response_image_instance_number)


class TestMonaiVersionsSegmentation(GrpcTest):

	def setUp(self):
		super().setUp()

	def test_config(self):
		print_config()

# Test is currently done on patient Lymphoma 1031 of the Lymphoma Dataset
class TestMonaiModelsSpleenSegmentation(GrpcTest):

	def setUp(self):
		super().setUp()

		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.pix = self.stub.ViewerControllerCurDCM(self.viewer_controller).pix

		# Directory for model checkpoints
		save_dir = "../model_checkpoint"
		self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

		# Define models
		self.unet_model = UNet(
			dimensions=3,
			in_channels=1,
			out_channels=2,
			channels=(16, 32, 64, 128, 256),
			strides=(2, 2, 2, 2),
			num_res_units=2,
			norm=Norm.BATCH,
		).to(self.device)

		self.unetr_model = UNETR(
			in_channels=1,
			out_channels=14,
			img_size=(96, 96, 96),
			feature_size=16,
			hidden_size=768,
			mlp_dim=3072,
			num_heads=12,
			pos_embed="perceptron",
			norm_name="instance",
			res_block=True,
			dropout_rate=0.0,
		).to(self.device)

		# Load model weights
		self.unet_model.load_state_dict(torch.load(os.path.join(save_dir, "unet_spleen_best_metric_model.pth"),
											  map_location=self.device
											  ))
		self.unet_model.eval()

		# self.unetr_model.load_state_dict(torch.load(os.path.join(save_dir, "unetr_spleen_best_metric_model.pth"),
		# 									   map_location=self.device
		# 									   ))
		# self.unetr_model.eval()

		# Transforms
		self.transforms = Compose(
			[
				LoadImaged(keys=["image"]),
				EnsureChannelFirstd(keys=["image"]),

				Spacingd(keys=["image"], pixdim=(
					1.5, 1.5, 2.0), mode=("nearest")),
				# Spacingd(keys=["image"], pixdim=(
				# 	1.5, 1.5, 2.0), mode=("bilinear")),
				Orientationd(keys=["image"], axcodes="RAS"),
				ScaleIntensityRanged(
					keys=["image"], a_min=-57, a_max=164,
					b_min=0.0, b_max=1.0, clip=True,
				),
				CropForegroundd(keys=["image"], source_key="image"),
				EnsureTyped(keys=["image"]),
			]
		)

		# Invert transforms to get back to original spacing
		self.post_transforms = Compose([
			EnsureTyped(keys="pred"),
			Invertd(
				keys="pred",
				transform=self.transforms,
				orig_keys="image",
				meta_keys="pred_meta_dict",
				orig_meta_keys="image_meta_dict",
				meta_key_postfix="meta_dict",
				nearest_interp=False,
				to_tensor=True,
			),
			# AsDiscreted(keys="pred", argmax=True, to_onehot=True, num_classes=2)
			AsDiscreted(keys="pred", argmax=True, to_onehot=True, n_classes=2)

		])



	def testUNetModelInferenceOnCTImagefromOsirix(self):

		response = self.stub.DCMPixSliceLocation(self.pix)
		self.assertEqual(response.status.status, 1)
		print("Slice location: ", response.slice_location)

		response = self.stub.DCMPixSourceFile(self.pix)
		self.assertEqual(response.status.status, 1)
		self.assertFalse(response.source_file == "")
		print("Source file: %s" % response.source_file)
		dcm_image_file = response.source_file

		print(dcm_image_file)

		# Convert dicoms to nifty
		output_dir = "outputs"
		# dcm_image_folder = os.path.dirname(dcm_image_file)
		# dicom2nifti.convert_directory(dcm_image_folder, output_dir, compression=True, reorient=True)


		# request = viewercontroller_pb2.ViewerControllerPixListRequest(viewer_controller = self.viewer_controller, movie_idx = 0)
		# response = self.stub.ViewerControllerPixList(request)
		# print(response)
		# self.assertEqual(response.status.status, 1)
		# self.assertTrue(len(response.pix) > 0)

		output_dir_ct = "outputs/4_ct_hb_30_i30f_3.nii.gz"
		images = output_dir_ct
		data_dicts = [
			{"image": images}
		]

		ds = Dataset(data=data_dicts, transform=self.transforms)
		ds_loader = DataLoader(ds, batch_size=1)
		check_data = next(iter(ds_loader))

		image = check_data["image"]
		# print(f"image shape: {image.shape}")
		#
		# Plot to check transformations done on input image
		plt.figure("check", (12, 6))
		plt.subplot(1, 2, 1)
		plt.title("image")
		plt.imshow(image[0][0][:, 100, :], cmap="gray")
		print(image.shape)

		# Inference on image from Osirix
		with torch.no_grad():
			# roi_size = (160, 160, 160)
			roi_size = (240, 240, 240)

			sw_batch_size = 4
			# model inference using sliding windows
			# model(file_to_make_prediction)
			check_outputs = sliding_window_inference(
				check_data["image"].to(self.device), roi_size, sw_batch_size, self.unet_model
			)

			check_data["pred"] = sliding_window_inference(
				check_data["image"].to(self.device), roi_size, sw_batch_size, self.unet_model
			)

			# check_outputs_ori = [self.post_transforms(i) for i in decollate_batch(check_data)]
			# check_outputs_ori = from_engine(["pred"])(check_data_ori)
			# check_data_ori = self.transforms.inverse(check_data)
			# check_outputs_ori = self.transforms.inverse(check_outputs)

			# check_outputs_ori = self.post_transforms(check_data)
			plt.figure("check", (18, 6))
			plt.subplot(1, 3, 1)
			plt.title(f"image")
			plt.imshow(check_data["image"][0, 0, :, :, 240], cmap="gray")
			plt.subplot(1, 3, 2)
			plt.title(f"output")
			plt.imshow(torch.argmax(
				check_outputs, dim=1).detach().cpu()[0, :, :, 240])

			# plt.subplot(1, 3, 3)
			# plt.title(f"output spacing")
			# plt.imshow(torch.argmax(
			# 	check_outputs_ori, dim=1).detach().cpu()[0, :, :, 240])
			plt.show()


class TestMonaiModelsMultiOrganSegmentation(GrpcTest):

	def setUp(self):
		super().setUp()

		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.pix = self.stub.ViewerControllerCurDCM(self.viewer_controller).pix

		save_dir = "../model_checkpoint"
		self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

		self.unetr_model = UNETR(
			in_channels=1,
			out_channels=14,
			img_size=(96, 96, 96),
			feature_size=16,
			hidden_size=768,
			mlp_dim=3072,
			num_heads=12,
			pos_embed="perceptron",
			norm_name="instance",
			res_block=True,
			dropout_rate=0.0,
		).to(self.device)

		self.unetr_model.load_state_dict(torch.load(os.path.join(save_dir, "unetr_btcv_seg_best_metric_model.pth"),
													map_location=self.device
													))
		self.unetr_model.eval()

		self.transforms = Compose(
			[
				LoadImaged(keys=["image"]),
				AddChanneld(keys=["image"]),
				Spacingd(
					keys=["image"],
					pixdim=(1.5, 1.5, 2.0),
					mode=("bilinear"),
				),
				Orientationd(keys=["image"], axcodes="RAS"),
				ScaleIntensityRanged(
					keys=["image"], a_min=-175, a_max=250, b_min=0.0, b_max=1.0, clip=True
				),
				CropForegroundd(keys=["image"], source_key="image"),
				ToTensord(keys=["image"]),
			]
		)

	def testUNETRModelInferenceforCTImageFromOsirix(self):

		# response = self.stub.DCMPixSliceLocation(self.pix)
		# self.assertEqual(response.status.status, 1)
		# print("Slice location: ", response.slice_location)
		#
		# response = self.stub.DCMPixSourceFile(self.pix)
		# self.assertEqual(response.status.status, 1)
		# self.assertFalse(response.source_file == "")
		# print("Source file: %s" % response.source_file)
		# dcm_image_file = response.source_file
		#
		# print("Hello")
		# print(dcm_image_file)

		# Convert dicoms to nifty
		output_dir = "outputs"
		# dcm_image_folder = os.path.dirname(dcm_image_file)
		# dicom2nifti.convert_directory(dcm_image_folder, output_dir, compression=True, reorient=True)

		output_dir_ct = "outputs/4_ct_hb_30_i30f_3.nii.gz"
		images = output_dir_ct
		data_dicts = [
			{"image": images}
		]

		ds = Dataset(data=data_dicts, transform=self.transforms)
		ds_loader = DataLoader(ds, batch_size=1)
		check_data = next(iter(ds_loader))

		image = check_data["image"]
		print(f"image shape: {image.shape}")

		# Plot to check transformations done on input image
		plt.figure("check", (12, 6))
		plt.subplot(1, 2, 1)
		plt.title("image")
		plt.imshow(image[0][0][:, :, 238], cmap="gray")
		plt.show()


		with torch.no_grad():
			# roi_size = (160, 160, 160)
			roi_size = (96, 96, 96)

			sw_batch_size = 4
			# model inference using sliding windows
			check_outputs = sliding_window_inference(
				check_data["image"].to(self.device), roi_size, sw_batch_size, self.unetr_model, overlap=0.8
			)


			# check_outputs_ori = [self.post_transforms(i) for i in decollate_batch(check_data)]
			# check_outputs_ori = from_engine(["pred"])(check_data_ori)
			# check_data_ori = self.transforms.inverse(check_data)
			# check_outputs_ori = self.transforms.inverse(check_outputs)

			plt.figure("check", (18, 6))
			plt.subplot(1, 3, 1)
			plt.title(f"image")
			plt.imshow(check_data["image"][0, 0, :, :, 240], cmap="gray")
			plt.subplot(1, 3, 2)
			plt.title(f"output")
			plt.imshow(torch.argmax(
				check_outputs, dim=1).detach().cpu()[0, :, :, 240])

			# plt.subplot(1, 3, 3)
			# plt.title(f"output spacing")
			# plt.imshow(torch.argmax(
			# 	check_outputs_ori, dim=1).detach().cpu()[0, :, :, 240])
			plt.show()

if __name__ == "__main__":
	unittest.main()
