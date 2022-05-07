from grpc_test import GrpcTest
import utilities_pb2
import vrcontroller_pb2
import types_pb2

class TestVRController(GrpcTest):
	"""Test case for VRController messaging

	"""
	def setUp(self):
		super().setUp()
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.vr_controller = self.stub.ViewerControllerVRControllers(self.viewer_controller).vr_controllers[0]

	def testVRControllerViewer2D(self):
		response = self.stub.VRControllerViewer2D(self.vr_controller)
		self.assertEqual(response.status.status, 1)
		self.assertEqual(response.viewer_controller.osirixrpc_uid, self.viewer_controller.osirixrpc_uid)

	def testVRControllerBlendingController(self):
		response = self.stub.VRControllerBlendingController(self.vr_controller)
		self.assertEqual(response.status.status, 1)  # TODO - not much of a test.  May need some better test data that allows for this.

	def testVRControllerStyle(self):
		response = self.stub.VRControllerStyle(self.vr_controller)
		self.assertEqual(response.status.status, 1)

	def testVRControllerTitle(self):
		response = self.stub.VRControllerTitle(self.vr_controller)
		self.assertEqual(response.status.status, 1)

	def testVRControllerROIVolumes(self):
		response = self.stub.VRControllerROIVolumes(self.vr_controller)
		self.assertEqual(response.status.status, 1)

	def testVRControllerNeedsDisplayUpdate(self):
		response = self.stub.VRControllerNeedsDisplayUpdate(self.vr_controller)
		self.assertEqual(response.status.status, 1)

	def testVRControllerRenderingMode(self):
		response = self.stub.VRControllerRenderingMode(self.vr_controller)
		self.assertEqual(response.status.status, 1)

	def testVRControllerSetRenderingMode(self):
		request = vrcontroller_pb2.VRControllerSetRenderingModeRequest(vr_controller = self.vr_controller, rendering_mode = "MIP")
		response = self.stub.VRControllerSetRenderingMode(request)
		self.assertEqual(response.status.status, 1)

	def testVRControllerWLWW(self):
		response = self.stub.VRControllerWLWW(self.vr_controller)
		self.assertEqual(response.status.status, 1)

	def testVRControllerSetWLWW(self):
		request = vrcontroller_pb2.VRControllerSetWLWWRequest(vr_controller = self.vr_controller, wl = 200, ww = 500)
		response = self.stub.VRControllerSetWLWW(request)
		self.assertEqual(response.status.status, 1)
