""" Exceptions classes for pyOsiriX.

"""


class GrpcException(Exception):
    """Exception raised when connection to OsiriX cannot be established.

    Attributes:
        message (str): An explanation of the error
    """
    def __init__(self, message: str = ""):
        self.message = message
        super().__init__(self.message)
