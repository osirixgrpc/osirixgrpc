import numpy as np

from grpc_test import GrpcTest
import utilities_pb2
import viewercontroller_pb2
import types_pb2

# TODO:
# - ViewerControllerBlendingController
# - ViewerControllerOpenVRViewerForMode
# - ViewerControllerCopyViewerWindow

class TestViewerController(GrpcTest):
	"""Test case for ViewerController messaging

	"""
	def setUp(self):
		super().setUp()
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller

	def testViewerControllerPixList(self):
		request = viewercontroller_pb2.ViewerControllerPixListRequest(viewer_controller = self.viewer_controller, movie_idx = 0)
		response = self.stub.ViewerControllerPixList(request)
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

	def testViewerControllerNewROI_Mask(self):
		buffer_array = np.random.randn(40 * 40) > 0
		buffer = viewercontroller_pb2.ViewerControllerNewROIRequest.Buffer(buffer =  1 * buffer_array, rows = 40, columns = 40)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 255, g = 0, b = 200)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, movie_idx = 0, position = 0, itype = 20, buffer = buffer, color = color, opacity = 0.5, name = "random")
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerNewROI_Oval(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x = 66., origin_y = 42., width = 20., height = 10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 255, g = 100, b = 200)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, movie_idx = 0, position = 0, itype = 9, rectangle = rect, color = color, opacity = 0.5, name = "oval", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerNewROI_Arrow(self):
		# Points seem to go in order [head, tail]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 0, g = 255, b = 0)
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=66., y=42.), viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=99., y=24.)]
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, points=points, movie_idx = 0, position = 0, itype = 14, color = color, opacity = 0.5, name = "arrow", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerNewROI_Point(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x = 66., origin_y = 42., width = 20., height = 10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 0, g = 255, b = 255)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, rectangle=rect, movie_idx = 0, position = 0, itype = 19, color = color, opacity = 1.0, name = "point", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)

	# A rectangle...
	def testViewerControllerNewROI_TROI(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x = 66., origin_y = 42., width = 20., height = 10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 255, g = 100, b = 100)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, rectangle=rect, movie_idx = 0, position = 0, itype = 6, color = color, opacity = 1.0, name = "tROI", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerNewROI_Text(self):
		rect = viewercontroller_pb2.ViewerControllerNewROIRequest.Rect(origin_x = 66., origin_y = 42., width = 20., height = 10.)
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 255, g = 100, b = 100)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, rectangle=rect, movie_idx = 0, position = 0, itype = 13, color = color, opacity = 1.0, name = "Some text", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerNewROI_TTAGT(self):
		points = [[ 50.20499802, 32.32217407], [ 53.27367783, 38.77323914], [ 64.68674469, 25.43341637], [ 69.71873474, 36.01180649], [ 41.8967247, 36.27430344], [ 68.91729736, 23.42099953]]
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=p[0], y=p[1]) for p in points]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 100, g = 250, b = 220)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, points=points, movie_idx = 0, position = 0, itype = 29, color = color, opacity = 1.0, name = "tTAGT", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerNewROI_Pencil(self):
		points = [[ 50.20499802, 32.32217407], [ 53.27367783, 38.77323914], [ 64.68674469, 25.43341637], [ 69.71873474, 36.01180649], [ 41.8967247, 36.27430344], [ 68.91729736, 23.42099953]]
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=p[0], y=p[1]) for p in points]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 100, g = 50, b = 220)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, points=points, movie_idx = 0, position = 0, itype = 15, color = color, opacity = 1.0, name = "pencil", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerNewROI_Angle(self):
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=71., y=-2.),\
				  viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=67., y=11.),\
				  viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=90., y=9.)]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 100, g = 50, b = 220)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, points=points, movie_idx = 0, position = 0, itype = 12, color = color, opacity = 1.0, name = "pencil", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerNewROI_Measure(self):
		points = [viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=71., y=-2.),\
				  viewercontroller_pb2.ViewerControllerNewROIRequest.Point2D(x=67., y=11.)]
		color = viewercontroller_pb2.ViewerControllerNewROIRequest.Color(r = 100, g = 50, b = 0)
		request = viewercontroller_pb2.ViewerControllerNewROIRequest(viewer_controller = self.viewer_controller, points=points, movie_idx = 0, position = 0, itype = 5, color = color, opacity = 1.0, name = "measure", thickness = 3.0)
		response = self.stub.ViewerControllerNewROI(request)
		self.assertEqual(response.status.status, 1)

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

	def testViewerControllerIsDataVolumic(self):
		request = viewercontroller_pb2.ViewerControllerIsDataVolumicRequest(viewer_controller= self.viewer_controller, in_4d = False)
		response = self.stub.ViewerControllerIsDataVolumic(request)
		self.assertTrue(response.is_volumic)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerResampleViewerController(self):
		viewer_controller_fake = types_pb2.ViewerController(osirixrpc_uid = "bad_id")
		request = viewercontroller_pb2.ViewerControllerResampleViewerControllerRequest(viewer_controller = viewer_controller_fake, fixed_viewer_controller = self.viewer_controller)
		response = self.stub.ViewerControllerResampleViewerController(request)
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

	def testViewerControllerMovieIdx(self):
		response = self.stub.ViewerControllerMovieIdx(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.movie_idx == 0)

	def testViewerControllerSetMovieIdx(self):
		request = viewercontroller_pb2.ViewerControllerSetMovieIdxRequest(viewer_controller = self.viewer_controller, movie_idx = 0)
		response = self.stub.ViewerControllerSetMovieIdx(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerMaxMovieIdx(self):
		response = self.stub.ViewerControllerMaxMovieIdx(self.viewer_controller)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerIdx(self):
		response = self.stub.ViewerControllerIdx(self.viewer_controller)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerSetIdx(self):
		request = viewercontroller_pb2.ViewerControllerSetIdxRequest(viewer_controller = self.viewer_controller, idx = 0)
		response = self.stub.ViewerControllerSetIdx(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerSetWLWW(self):
		request = viewercontroller_pb2.ViewerControllerSetWLWWRequest(viewer_controller=self.viewer_controller, wl = 100, ww = 200)
		response = self.stub.ViewerControllerSetWLWW(request)
		self.assertEqual(response.status.status, 1)

	def testViewerControllerWLWW(self):
		response = self.stub.ViewerControllerWLWW(self.viewer_controller)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.wl == 100)
		self.assertTrue(response.ww == 200)
