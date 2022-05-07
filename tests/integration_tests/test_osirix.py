from grpc_test import GrpcTest
import utilities_pb2

class TestOsirix(GrpcTest):
	"""Test case for core osirix messaging

	"""
	def testOsirixCurrentBrowser(self):
		response = self.stub.OsirixCurrentBrowser(utilities_pb2.Empty())
		self.assertEqual(response.status.status, 1)
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
