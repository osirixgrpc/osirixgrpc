""" The main osirix module.

This module contains some core methods for access to the core OsiriX objects.

Typical usage example:

    import osirix
    frontmost_viewer = osirix.frontmost_viewer()
    vr_controller = osirix.vr_controller()
"""

from __future__ import annotations

__version__ = "0.2.1-dev71"

__author__ = "Timothy Sum Hon Mun & Matthew D Blackledge"

import os
import json
import warnings
from typing import List, AnyStr, Tuple

from . import base
from . import browser_controller
from . import dcm_pix
from . import dicom
from . import exceptions
from . import osirix_utilities
from . import roi
from . import viewer_controller
from . import vr_controller

# An instance of the automatically established OsiriX class.
# Do not change or access directly.
_osirix = None


def plugin_support_directory() -> AnyStr:
    """ Determine the location of the OsiriXgrpc plugin support directory.

    Returns:
        The plugin support directory as an absolute path.
    """
    home = os.path.expanduser("~")
    support_directory = os.path.join(home,
                                     "Library",
                                     "Application Support",
                                     "OsirixGRPC")
    return support_directory


def osirixgrpc_port_preference() -> int:
    """ Extract the preferred port set by the user in the OsiriXgrpc plugin.

    It will iterate through the ports set-up by the user in order, and return
    the first open one. If you want more refinement (e.g. using a different
    port), then you must set up your own service.

    Returns:
        The preferred port. If one is not found or none are open, the `None`
            is returned.
    """
    port = None
    support_directory = plugin_support_directory()
    server_configs = os.path.join(support_directory,
                                  "server_configs.json")
    with open(server_configs, "rb") as fhandle:
        server_configs_dict = json.load(fhandle)
        for item in server_configs_dict:
            if item["active"] == "YES":
                port = item["port"]
    return port


def global_osirix_instance() -> osirix_utilities.Osirix:
    """ Get the global osirix instance.

    This should be set-up on first import of the osirix package, and uses the
    default set by the OsiriXgrpc plugin.

    Returns:
        The global osirix instance used to access the core OsiriX functions.
    """
    global _osirix

    if _osirix is None:
        port = osirixgrpc_port_preference()
        if port is not None:
            service = osirix_utilities.OsirixService(domain="127.0.0.1",
                                                     port=port,
                                                     max_send_message_length=500000000,
                                                     max_receive_message_length=500000000)
            try:
                service.start_service()
            except exceptions.GrpcException:
                print("Could not start global service."
                      "OsiriX may not be running and you may need to start it.")
            _osirix = osirix_utilities.Osirix(service)
    return _osirix


def _establish_global_osirix_instance():
    """ Establish that a connection can be established on import.
    """
    if global_osirix_instance() is None:
        warnings.warn("No connection with OsiriX established on initialization."
                      "You may need to set one up yourself.")


# The following functions are defined for ease of access.
def current_browser() -> browser_controller.BrowserController:
    """ The main Dicom browser instance.

    Returns:
        The main Dicom browser.

    Example:
        ```python
        import osirix
        browser = osirix.current_browser()
        ```
    """
    osirix_ = global_osirix_instance()
    if osirix_ is None:
        raise exceptions.GrpcException("No connection could be established with OsiriX")
    return osirix_.current_browser()


def frontmost_viewer() -> viewer_controller.ViewerController:
    """ The front-most 2D viewer.

    If there are more than one, look for the viewer highlighted by a red boundary.

    Returns:
        The viewer controller instance.

    Example:
        ```python
        import osirix
        viewer = osirix.frontmost_viewer()
        ```
    """
    osirix_ = global_osirix_instance()
    if osirix_ is None:
        raise exceptions.GrpcException("No connection could be established with OsiriX")
    return osirix_.frontmost_viewer()


def displayed_2d_viewers() -> List[viewer_controller.ViewerController]:
    """ All currently active 2D viewers.

    Returns:
        A list of all displayed 2D viewers.

    Example:
        ```python
        import osirix
        viewers = osirix.displayed_2d_viewers()
        ```
    """
    osirix_ = global_osirix_instance()
    if osirix_ is None:
        raise exceptions.GrpcException("No connection could be established with OsiriX")
    return osirix_.displayed_2d_viewers()


def frontmost_vr_controller() -> vr_controller.VRController:
    """ The front-most 3D viewer.

    Returns:
        The VR controller instance.

    Example:
        ```python
        import osirix
        vr_controller = osirix.frontmost_vr_controller()
        ```
    """
    osirix_ = global_osirix_instance()
    if osirix_ is None:
        raise exceptions.GrpcException("No connection could be established with OsiriX")
    return osirix_.frontmost_vr_controller()


def displayed_vr_controllers() -> List[vr_controller.VRController]:
    """ All currently active 3D viewers.

    Returns:
        A list of all displayed 3D viewers.

    Example:
        ```python
        import osirix
        vr_controllers = osirix.displayed_vr_controllers()
        ```
    """
    osirix_ = global_osirix_instance()
    if osirix_ is None:
        raise exceptions.GrpcException("No connection could be established with OsiriX")
    return osirix_.displayed_vr_controllers()


def osirix_version() -> Tuple[str, str]:
    """ The version of OsiriX being linked to.

    This function can also be used as a 'ping' to check that a connection is established.

    Returns:
        str: The OsiriX version.

    Example:
        ```python
        import osirix
        version = osirix.osirix_version()
        ```
    """
    osirix_ = global_osirix_instance()
    if osirix_ is None:
        raise exceptions.GrpcException("No connection could be established with OsiriX")
    return osirix_.osirix_version()


_establish_global_osirix_instance()
