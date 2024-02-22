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
           "ROIVolume",
           "VRController",
           "GrpcException",
           "OsirixServiceException"]

__version__ = "0.2.1-dev1"

__author__ = "Timothy Sum Hon Mun & Matthew D Blackledge"

import sys
import os
import json
import warnings
from typing import Tuple

from .exceptions import GrpcException, OsirixServiceException
from .viewer_controller import ViewerController, DCMPix, ROI
from .vr_controller import VRController, ROIVolume
from .dicom import DicomSeries, DicomStudy, DicomImage
from .browser_controller import BrowserController
from .osirix_utils import Osirix, OsirixService

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

    if __port__ is None  or __domain__ is None:
        warnings.warn("No valid port or domain found. You may need to start one in OsiriX.")
        return

    channel_opt = [('grpc.max_send_message_length', 512 * 1024 * 1024),
                   ('grpc.max_receive_message_length', 512 * 1024 * 1024)]
    __osirix_service__ = OsirixService(channel_opt=channel_opt,
                                       domain=__domain__,
                                       port=__port__).get_service()
    __osirix__ = Osirix(__osirix_service__)


__init_setup__()


def current_browser() -> BrowserController:
    """
    Provides the Osirix browser window

    Returns:
        BrowserController
    """
    global __osirix__
    if __osirix__ is None:
        raise ConnectionError("No connection established")
    return __osirix__.current_browser()


def frontmost_viewer() -> ViewerController:
    """
    Provides the 2D viewer that is currently selected

    Returns:
        ViewerController
    """
    global __osirix__
    if __osirix__ is None:
        raise ConnectionError("No connection established")
    return __osirix__.frontmost_viewer()


def frontmost_vr_controller() -> VRController:
    """
    Provides the VR Controller that is currently selected

    Returns:
        VRController
    """
    global __osirix__
    if __osirix__ is None:
        raise ConnectionError("No connection established")
    return __osirix__.frontmost_vr_controller()


def displayed_2d_viewers() -> Tuple[ViewerController, ...]:
    """
    Provides all 2D viewers that are displayed

    Returns:
        Tuple containing each 2D Viewer
    """
    global __osirix__
    if __osirix__ is None:
        raise ConnectionError("No connection established")
    return __osirix__.displayed_2d_viewers()


def displayed_vr_controllers() -> Tuple[VRController, ...]:
    """
    Provides all VR controllers that are displayed

    Returns:
        Tuple containing each VRController
    """
    global __osirix__
    if __osirix__ is None:
        raise ConnectionError("No connection established")
    return __osirix__.displayed_vr_controllers()
