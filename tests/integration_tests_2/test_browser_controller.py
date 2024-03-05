import pytest

from osirixgrpc import utilities_pb2


@pytest.fixture(scope="function")
def browser_controller(grpc_stub):
    browser_controller = grpc_stub.OsirixCurrentBrowser(utilities_pb2.Empty()).browser_controller
    yield browser_controller


def test_browser_controller_database_selection(grpc_stub, browser_controller):
    response = grpc_stub.BrowserControllerDatabaseSelection(browser_controller)
    assert response.status.status == 1
