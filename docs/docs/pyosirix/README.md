# pyOsiriX

![Welcome to pyOsiriX!](https://raw.githubusercontent.com/osirixgrpc/osirixgrpc/dev/docs/docs/assets/logo/logo-python.png)

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

## Installation
```
pip install -i https://pypi.org/simple/ --extra-index-url https://test.pypi.org/simple/ pyosirix==0.2.1-dev71
```

## Requirements
 - [`osirixgrpc`](https://pypi.org/project/osirixgrpc/)
 - [`numpy`](https://pypi.org/project/numpy/)

## Contributions
If you would like to contribute to pyOsiriX, please have a look at our 
[contributing](https://osirixgrpc.github.io/osirixgrpc/contributing/CONTRIBUTING.html) page. We are always eager to hear
your ideas and improve pyOsiriX. Examples include:

 1. Publishing example scripts of pyOsiriX in use. For example, something small that helps your day-to-day workflows.
 2. Editing documentation or suggesting changes.
 3. Reporting any bugs you find by [raising an issue](https://github.com/osirixgrpc/osirixgrpc/issues).
 4. Testing new version of pyOsiriX (and OsiriXgrpc!) prior to release.
 5. Contributing to or suggesting changes to the whole project, including requests for more OsiriX function exposure.

Please contact us at [osirixgrpc@gmail.com](mailto:osirixgrpc@gmail.com) to find out more.

## Examples of use
__Note__: These are for exemplary use only and just touch on what is capable with OsiriXgrpc. Over time we will compile 
a list of more complete examples as found in the [documentation](https://osirixgrpc.github.io/osirixgrpc/pyosirix).

### Accessing the 2D viewer
If 2D OsiriX viewers are open, it is possible to obtain its instance by simply running: 
```python
import osirix
displayed_viewers = osirix.displayed_2d_viewers()  # Returns a list of all open viewers
frontmost_viewer = osirix.frontmost_viewer()  # Returns the viewer that is currently active (red frame)
```

### Accessing image data
It is straightforward to obtain image data within the 2D viewer and manipulate it. The following doubles the pixel 
values of the currently displayed image.
```python
import osirix
frontmost_viewer = osirix.frontmost_viewer()
pixels = frontmost_viewer.cur_dcm().image  # Obtain pixel data (as 2D NumPy array) from currently displayed image slice.
new_pixels = pixels * 2  # Manipulate the array
frontmost_viewer.cur_dcm().image = new_pixels  # Update the image data for the currently shown image slice.
frontmost_viewer.needs_display_update()  # Tell OsiriX to redraw itself
```

### Accessing (all) image data
Images in the viewer are stored in arrays, one array per frame, each array having the same length as the number of 
displayed slices. The following does the same as the example above, but applies to all images in the viewer.
```python
import osirix
frontmost_viewer = osirix.frontmost_viewer()
pix_list = frontmost_viewer.pix_list(0)  # Obtain an array of DCMPix objects for the first (zeroth) frame. 
for pix in pix_list:  # Loop through all DCMPix
    pixels = pix.image
    new_pixels = pixels * 2  # Manipulate the array
    pix.image = new_pixels
frontmost_viewer.needs_display_update()  # Tell OsiriX to redraw itself
```

### Accessing ROIs
Similarly to images, ROIs can be obtained as an array for each requested frame in the 2D OsiriX viewer. Each element of 
the array is another array, containing however, many ROIs are on that slice (some may be empty). This will produce a 
list of unique ROI names in the viewer.
```python
import osirix
frontmost_viewer = osirix.frontmost_viewer()
roi_list = frontmost_viewer.roi_list(0)  # ROI list for the first (zeroth) frame.
unique_names = []  # Empty storage
for roi_slice in roi_list:
    for roi in roi_slice:  # There may be more than one ROI in a slice!
        if roi.name not in unique_names:  # You could also use numpy.unique...  
            unique_names.append(roi.name)
if len(unique_names) == 0:
    print("No ROIs found in the viewer!")
else:
    print(f"Unique names are: {unique_names}")
```

### Accessing ROIs by name
If you know the name of the ROI it is easy to avoid looping through
```python
import osirix
frontmost_viewer = osirix.frontmost_viewer()
roi_name = "my_perfect_roi"
rois = frontmost_viewer.rois_with_name(roi_name)
print(f"Number of ROIs with name {roi_name}: {len(rois)}")
```

### Converting an ROI to a mask
Another useful thing to do is obtain a mask (a 2D array of boolean values) representing the region of the ROI. To do
this you need a DCMPix instance to compute it from. Luckily, this is easy to obtain!
```python
import osirix
import numpy as np
frontmost_viewer = osirix.frontmost_viewer()
roi_name = "my_perfect_roi"
rois = frontmost_viewer.rois_with_name(roi_name)
if len(rois) == 0:
    raise ValueError(f"Could not find any ROIs with the name {roi_name}")
voxels = []  # Storage
for roi in rois:
    pix = roi.pix  # The DCMPix on which the ROI was drawn
    mask = pix.get_map_from_roi(roi)  # The mask we wanted.
    voxels = np.r_[pix.image[mask], voxels]  # Append the voxel values
mean = np.mean(voxels)  # Let's get some statistics
std = np.std(voxels, ddof=1)
print(f"ROIs with name {roi_name} have mean {mean:.2f} and std-dev {std: .2f}") 
```

### Accessing Dicom files in the OsiriX database
It is possible to get access to the selected series and studies in the OsiriX database. This example sorts the 
DicomImages in the first selected DicomSeries by slice location and then opens them in a new 2D viewer.
```python
import osirix
import numpy as np
browser_controller = osirix.current_browser()  #The main window (database) of OsiriX
studies, series = browser_controller.database_selection()  # User selection as lists of DicomStudy/DicomSeries
if len(series) == 0:
    raise ValueError("No series have been selected")
dicom_images = np.array(series[0].images)  # An array of DicomImage instances
sorted_idx = np.argsort([image.slice_location for image in dicom_images])  # Sort the images by slice location
dicom_images = dicom_images[sorted_idx]
viewer_controller = browser_controller.open_viewer_2d(dicom_images)  # Open up and view
```

### Accessing the VRController
Once a user has opened a VRController (or done so programmatically via pyOsiriX!), it is possible to access it as per
the 2D viewer. This example shows this and also how to make the contained ROIVolumes display themselves.
```python
import osirix
frontmost_viewer = osirix.frontmost_viewer()
vr_controllers = frontmost_viewer.vr_controllers()  # Get a list of currently open ones.
if len(vr_controllers) == 0:
    print("No open VR Controller.  Creating one.")
    vr_controller = frontmost_viewer.open_vr_viewer(mode="MIP")  # Only other alternative is "VR"
else:
    vr_controller = vr_controllers[0]
roi_volumes = vr_controller.roi_volumes()
if len(roi_volumes) == 0:
    print("No valid ROI volumes available")  # Note that ROIs defined on a single slice do not count!
for roi_volume in roi_volumes:
    print(f"Displaying ROI volume with name {roi_volume.name} and modifying is attributes")
    roi_volume.visible = True
    roi_volume.color = (1., 0., 1.)  # Purple color in unit RGB space
    roi_volume.opacity = 0.5
    roi_volume.texture = False  # Generally looks better to us
```