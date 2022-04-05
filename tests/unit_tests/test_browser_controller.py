from grpc_test import GrpcTest
import utilities_pb2
import browsercontroller_pb2
import types_pb2

# TODO
# - BrowserControllerCopyFilesIfNeeded

class TestBrowserController(GrpcTest):
	"""Test case for Browser Controller messaging

	"""
	def setUp(self):
		super().setUp()
		self.browser_controller = self.stub.OsirixCurrentBrowser(utilities_pb2.Empty()).browser_controller

	def testBrowserControllerDatabaseSelection(self):
		response = self.stub.BrowserControllerDatabaseSelection(self.browser_controller)
		self.assertEqual(response.status.status, 1)
