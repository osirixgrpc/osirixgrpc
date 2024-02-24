__all__ = ["Osirix",
           "OsirixService",
           "ViewerController",
           "DCMPix",
           "ROI",
           "VRController",
           "BrowserController",
           "DicomSeries",
           "DicomStudy",
           "DicomImage",
           "VRController",
           "GrpcException",
           "OsirixServiceException"]

__version__ = "0.2.1-dev3"

__author__ = "Timothy Sum Hon Mun & Matthew D Blackledge"

import os
import json
import warnings
from typing import Tuple

from .exceptions import GrpcException, OsirixServiceException
from .viewer_controller import ViewerController, DCMPix, ROI
from .vr_controller import VRController
from .dicom import DicomSeries, DicomStudy, DicomImage
from .browser_controller import BrowserController
from .osirix import Osirix, OsirixService

global __port__, __domain__, __osirix__, __osirix_service__


def __init_setup__():
    global __port__, __domain__, __osirix__, __osirix_service__

    home = os.path.expanduser("~")
    support_directory = os.path.join(home,
                                     "Library/Application Support/OsirixGRPC")
    server_configs = os.path.join(support_directory,
                                  "server_configs.json")
    with open(server_configs) as file:
        server_configs_dict = json.load(file)
        for item in server_configs_dict:
            if item["active"] == "YES":
                __port__ = item["port"]
                __domain__ = item["ipaddress"] + ":"
                break

    if __port__ is None or __domain__ is None:
        warnings.warn("No valid port or domain found. You may need to start one in OsiriX.")
        return

    __osirix_service__ = OsirixService(domain=__domain__,
                                       port=__port__,
                                       max_send_message_length=500000000,
                                       max_receive_message_length=500000000).osirix_service
    __osirix__ = Osirix(__osirix_service__)


__init_setup__()


# The following functions are defined for ease of access.
def current_browser() -> BrowserController:
    """ The main Dicom browser instance.

    Returns:
        The main Dicom browser.

    Example:
        ```python
        import osirix
        browser = osirix.current_browser2()
        ```
    """
    global __osirix__
    if __osirix__ is None:
        raise ConnectionError("No connection established")
    return __osirix__.current_browser()


def frontmost_viewer(some_value: float) -> Tuple[ViewerController, int]:
    """ The front-most 2D viewer.

    Args:
        some_value (float): Not sure what this is for.

    Returns:
        The viewer controller instance (osirix.viewer_controller.ViewerController)
        A random integer.

    Example:
        ```python
        import osirix
        viewer = osirix.frontmost_viewer()
        ```
    """
    global __osirix__
    if __osirix__ is None:
        raise ConnectionError("No connection established")
    return __osirix__.frontmost_viewer()


def displayed_2d_viewers() -> Tuple[ViewerController, ...]:
    """ All currently active 2D viewers.

    Returns:
        List

    Example:
        ```python
        import osirix
        viewers = osirix.displayed_2d_viewers()
        ```
    """
    global __osirix__
    if __osirix__ is None:
        raise ConnectionError("No connection established")
    return __osirix__.displayed_2d_viewers()


def frontmost_vr_controller() -> VRController:
    """ The front-most 3D viewer.

    Returns:
        osirix.viewer_controller.VRController

    Example:
        ```python
        import osirix
        vr_controller = osirix.frontmost_vr_controller()
        ```
    """
    global __osirix__
    if __osirix__ is None:
        raise ConnectionError("No connection established")
    return __osirix__.frontmost_vr_controller()


def displayed_vr_controllers() -> Tuple[VRController, ...]:
    """ All currently active 3D viewers.

    Returns:
        List

    Example:
        ```python
        import osirix
        vr_controllers = osirix.displayed_vr_controllers()
        ```
    """
    global __osirix__
    if __osirix__ is None:
        raise ConnectionError("No connection established")
    return __osirix__.displayed_vr_controllers()
