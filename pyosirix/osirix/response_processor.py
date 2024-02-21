import datetime
from typing import Tuple, Dict

import sys
import numpy as np
from numpy import ndarray

from osirix.exceptions import GrpcException

# sys.path.append("../../src/python")
import osirixgrpc.osirix_pb2 as osirix_pb2
import osirixgrpc.dicomstudy_pb2 as dicomstudy_pb2

class ResponseProcessor(object):
    """
    Class that processes all the gRPC response to extract the information required from it
    to build the pyOsirix objects
    """

    def __init__(self) -> None:
        # print("Response Processor Started")
        pass

    def response_check(self, response) -> None:
        """
          Checks whether the status of the response is success or not
          Args:
              response: response returned by Osirix service for the request made

          Returns:
               None
          """
        if (response.status.status == 1):
            pass

        elif (response.status.message != ""):
            raise GrpcException(response.status.message)
        else:
            raise GrpcException("No response")













