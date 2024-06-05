# pyOsiriX

<img src="https://raw.githubusercontent.com/osirixgrpc/osirixgrpc/dev/docs/docs/assets/logo/logo.svg" width="150" class="center" alt="OsiriXgrpc">

[![Powered By gRPC](https://img.shields.io/badge/powered_by-gRPC-green?labelColor=red)](https://grpc.io)
[![GitHub License](https://img.shields.io/github/license/osirixgrpc/osirixgrpc?color=blue)](https://github.com/osirixgrpc/osirixgrpc/blob/main/LICENSE)
![PyPI - Downloads](https://img.shields.io/pypi/dm/pyosirix)
[![Static Badge](https://img.shields.io/badge/issues-pyosirix-red?logo=github)](https://github.com/osirixgrpc/osirixgrpc/issues)
[![Static Badge](https://img.shields.io/badge/citation-AI2ASE-green?logo=googlescholar)](https://ai-2-ase.github.io/papers/29%5cCameraReady%5cAAAI_OsiriXgrpc__Rapid_prototyping_and_development_of_state_of_the_art_artificial_intelligence_in_OsiriX_cam_ready.pdf)

pyOsiriX provides a pythonic interface to the [OsiriXgrpc plugin](https://osirixgrpc.github.io/osirixgrpc/index.html) 
for the OsiriX medical image viewing platform. Our vision is to accelerate the development of robust research image 
processing tools for the medical community, including straight-forward deployment of AI algorithms.

Example functionality includes:

 1. Interrogating metadata of studies/series/imaging included within the OsiriX database.
 2. Accessing and adjusting pixel values within a 2D OsiriX viewer.
 3. Adjusting visualization settings of 3D volume rendering windows.
 4. Obtaining and creating regions of interest (ROIs) within image viewing windows.

Please ensure you check our [official documentation](https://osirixgrpc.github.io/osirixgrpc/) to find out more!

## Installation
```
pip install -i https://pypi.org/simple/ --extra-index-url https://test.pypi.org/simple/ pyosirix==0.2.1-dev68
```

## Requirements
 - [`osirixgrpc`](https://pypi.org/project/osirixgrpc/)
 - [`numpy`](https://pypi.org/project/numpy/)

## Contributions
If you would like to contribute to pyOsiriX, please have a look at our 
[contributing](https://osirixgrpc.github.io/osirixgrpc/contributing/CONTRIBUTING.html) page. We are always eager to hear
your ideas and improve pyOsiriX. Example ways to contribute include:
 1. Publishing example scripts of pyOsiriX in use. For example, something small that helps your day-to-day workflows.
 2. Editing documentation or suggesting changes.
 3. Reporting any bugs you find by [raising an issue](https://github.com/osirixgrpc/osirixgrpc/issues).
 4. Testing new version of pyOsiriX (and OsiriXgrpc!) prior to release.
 5. Contributing to or suggesting changes to the whole project, including requests for more OsiriX function exposure.

Please contact us at [osirixgrpc@gmail.com](mailto:osirixgrpc@gmail.com) to find out more.

## Examples of use
(please see the [documentation](https://osirixgrpc.github.io/osirixgrpc/pyosirix)) for more complete examples).

### Accessing the 2D viewer
If 2D OsiriX viewers are open, it is possible to obtain its instance by simply running: 
```python
import osirix
displayed_viewers = osirix.displayed_2d_viewers()  # Returns a list of all open viewers
frontmost_viewer = osirix.frontmost_viewer()  # Returns the viewer that is currently active (red frame)
```

### Accessing image data
It is straightforward to obtain image data within the 2D viewer and manipulate it. The following doubles the pixel 
values.
```python
import osirix
frontmost_viewer = osirix.frontmost_viewer()
pixels = frontmost_viewer.cur_dcm().image  # Obtain pixel data (as 2D NumPy array) from currently displayed image slice.
new_pixels = pixels * 2  # Manipulate the array
frontmost_viewer.cur_dcm().image = new_pixels  # Update the image data for the currently shown image slice.
frontmost_viewer.needs_display_update()  # Tell OsiriX to redraw 
```