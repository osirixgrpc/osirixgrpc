import numpy as np

from grpc_test import GrpcTest
import utilities_pb2
import roi_pb2
import viewercontroller_pb2
import types_pb2

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
        # TODO - create test case with known area.

	def testROICentroid(self):
		response = self.stub.ROICentroid(self.roi)
		self.assertEqual(response.status.status, 1)
		# TODO - create test case with known centroid.

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
		self.assertEqual(response.status.status, 1)

	def testROIColor(self):
		response = self.stub.ROIColor(self.roi)
		self.assertEqual(response.status.status, 1)
		# TODO - create test case with known color.

	def testROISetColor(self):
		color_response = self.stub.ROIColor(self.roi)
		request = roi_pb2.ROISetColorRequest(roi = self.roi, r = color_response.r, g = color_response.g, b = color_response.b)
		response = self.stub.ROISetColor(request)
		self.assertEqual(response.status.status, 1)

	def testROIOpacity(self):
		response = self.stub.ROIOpacity(self.roi)
		self.assertEqual(response.status.status, 1)

	def testROISetOpacity(self):
		opacity_response = self.stub.ROIOpacity(self.roi)
		request = roi_pb2.ROISetOpacityRequest(roi = self.roi, opacity = opacity_response.opacity)
		response = self.stub.ROISetOpacity(request)
		self.assertEqual(response.status.status, 1)

	def testROIThickness(self):
		response = self.stub.ROIThickness(self.roi)
		self.assertEqual(response.status.status, 1)

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
		# TODO - create test case with known points.

	def testROISetPoints(self):
		points_response = self.stub.ROIPoints(self.roi)
		points_request = []
		for i in range(len(points_response.points)):
			points_request.append(roi_pb2.ROISetPointsRequest.Point2D(x = points_response.points[i].x, y = points_response.points[i].y))
		request = roi_pb2.ROISetPointsRequest(roi = self.roi, points = points_request)
		response = self.stub.ROISetPoints(request)
		self.assertEqual(response.status.status, 1)
