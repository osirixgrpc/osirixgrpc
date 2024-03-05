import pytest
import grpc

from osirixgrpc import osirix_pb2_grpc


class GrpcTestException(Exception):
    """Exception raised when connection to OsiriX cannot be established

    Attributes:
        message (str): explanation of the error
    """
    def __init__(self, message=""):
        self.message = message
        super().__init__(self.message)


@pytest.fixture(scope="function")
def grpc_stub():
    try:
        port = 50001
        server_url_localhost = 'localhost:' + str(port)
        channel_opt = [('grpc.max_send_message_length', 512 * 1024 * 1024),
                       ('grpc.max_receive_message_length', 512 * 1024 * 1024)]
        channel = grpc.insecure_channel(server_url_localhost, options=channel_opt)
        stub = osirix_pb2_grpc.OsiriXServiceStub(channel)
    except Exception as exc:
        raise GrpcTestException(f"No connection to OsiriX can be established: {exc}")

    yield stub
    channel.close()
