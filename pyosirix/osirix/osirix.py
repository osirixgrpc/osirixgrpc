""" Provide access to the core OsiriX objects: 2D/3D viewers and the database (browser).

"""

from __future__ import annotations
from typing import List

import osirixgrpc.utilities_pb2 as utilities_pb2

from osirix.viewer_controller import ViewerController
from osirix.vr_controller import VRController
from osirix.browser_controller import BrowserController
from osirix.base import OsirixBase


class Osirix(OsirixBase):
    """ Provides access functionality to core OsiriX objects (2D/3D viewers and Dicom browser).

    Note that it is better not to use this class directly, unless you know what you are doing.
    There is a global instance of this class, set-up according to the OsiriXgrpc plugin
    configuration, as described in the main `__init__.py` module.
    """

    def current_browser(self) -> BrowserController:
        """ Return an instance of the current Dicom database browser.

        Note that it is better not use this method directly. Use the following instead:

        ```python
        import osirix
        browser = osirix.current_browser()
        ```

        Returns:
            The main Dicom browser instance.
        """
        request = utilities_pb2.Empty()
        response = self.osirix_service_stub.OsirixCurrentBrowser(request)
        self.response_check(response)
        browser_controller = response.browser_controller
        browser_controller_obj = BrowserController(self.osirix_service,
                                                   browser_controller)
        return browser_controller_obj

    def frontmost_viewer(self) -> ViewerController:
        """ Return an instance of the front-most 2D viewer.

        If there are more than one, look for the viewer highlighted by a red boundary.
        Note that it is better not use this method directly. Use the following instead:

        ```python
        import osirix
        viewer = osirix.frontmost_viewer()
        ```

        Returns:
            The front-most 2D viewer.
        """
        request = utilities_pb2.Empty()
        response = self.osirix_service_stub.OsirixFrontmostViewer(request)
        self.response_check(response)
        viewer_controller = response.viewer_controller
        viewer_controller_obj = ViewerController(self.osirix_service,
                                                 viewer_controller)
        return viewer_controller_obj

    def displayed_2d_viewers(self) -> List[ViewerController, ...]:
        """ Return all displayed 2D viewer instances.

        Note that it is better not use this method directly. Use the following instead:

        ```python
        import osirix
        viewers = osirix.displayed_2d_viewers()
        ```

        Returns:
            A list of 2D viewer instances.
        """
        request = utilities_pb2.Empty()
        response = self.osirix_service_stub.OsirixDisplayed2DViewers(request)
        self.response_check(response)
        viewer_controller_objs = []
        for viewer_controller in response.viewer_controllers:
            viewer_controller_obj = ViewerController(self.osirix_service,
                                                     viewer_controller)
            viewer_controller_objs.append(viewer_controller_obj)
        return viewer_controller_objs

    def frontmost_vr_controller(self) -> VRController:
        """ Return an instance of the front-most 3D viewer.

        Note that it is better not use this method directly. Use the following instead:

        ```python
        import osirix
        vr_controller = osirix.frontmost_vr_controller()
        ```

        Returns:
            The front-most 3D viewer.
        """
        request = utilities_pb2.Empty()
        response = self.osirix_service_stub.OsirixFrontmostVRController(request)
        self.response_check(response)
        vr_controller = response.vr_controller
        vr_controller_obj = VRController(self.osirix_service,
                                         vr_controller)
        return vr_controller_obj

    def displayed_vr_controllers(self) -> List[VRController, ...]:
        """ Return all displayed 3D viewer instances.

        Note that it is better not use this method directly. Use the following instead:

        ```python
        import osirix
        vr_controllers = osirix.displayed_vr_controllers()
        ```

        Returns:
            A list of 3D viewer instances.
        """
        request = utilities_pb2.Empty()
        response = self.osirix_service_stub.OsirixDisplayedVRControllers(request)
        self.response_check(response)
        vr_controller_objs = []
        for vr_controller in response.vr_controllers:
            vr_controller_obj = VRController(self.osirix_service,
                                             vr_controller)
            vr_controller_objs.append(vr_controller_obj)
        return vr_controller_objs
