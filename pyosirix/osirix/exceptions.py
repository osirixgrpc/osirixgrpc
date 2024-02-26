class GrpcException(Exception):
	"""Exception raised when connection to OsiriX cannot be established.

	Attributes:
		message -- explanation of the error
	"""
	def __init__(self, message: str = ""):
		self.message = message
		super().__init__(self.message)


class OsirixServiceException(Exception):
	"""Exception raised when Osirix Service Stub does not exist.

	Attributes:
		message -- explanation of the error
	"""
	def __init__(self, message: str = ""):
		self.message = message
		super().__init__(self.message)
