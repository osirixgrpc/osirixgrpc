import pytest

import osirix


@pytest.fixture(scope="function")
def global_osirix_instance():
    yield osirix.global_osirix_instance()


@pytest.fixture(scope="function")
def secondary_port():
    yield 50003


@pytest.fixture(scope="function")
def secondary_service(secondary_port):
    service = osirix.osirix_utilities.OsirixService(domain="127.0.0.1",
                                                    port=secondary_port,
                                                    max_send_message_length=500000000,
                                                    max_receive_message_length=500000000)
    service.start_service()
    yield service
    service.stop_service()
