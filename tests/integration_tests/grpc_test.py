import unittest

import grpc
import osirix_pb2_grpc


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
			port = 50501
			server_url_localhost = 'localhost:' + str(port)
			channel_opt = [('grpc.max_send_message_length', 512 * 1024 * 1024),
						   ('grpc.max_receive_message_length', 512 * 1024 * 1024)]
			self.channel = grpc.insecure_channel(server_url_localhost, options=channel_opt)
			self.stub = osirix_pb2_grpc.OsiriXServiceStub(self.channel)
		except Exception as exc:
			raise GrpcTestException(f"No connection to OsiriX can be established: {exc}")
