# Basics

> ___Note___: This is the long-winded way to do things. We _strongly_ encourage using the 
  [pyosirix](../pyosirix/README.md) library for day-to-day development. However, this does provide an indication of
  what is happening "under the hood".
 
gRPC supports many [languages](https://grpc.io/docs/languages/), including C++, Java, Go, Node.js, and PHP. 
We currently only support use of Python because the libraries available image processing and machine-learning,
and offers a relatively short learning curve. All examples are therefore shown in Python, but if you are 
interested in generating the GRPC code for other client languages, then please see the 
[contributing](../contributing/README.md) section and enclosed pages.

## Requirements
The requirements for working with the Python osirixgrpc library are
``` {.txt .no-copy} 
----8<----
python/requirements.txt
----8<----
```

## Connecting to the Server
To establish a connection with the OsiriXgrpc plugin server, you initiate a ___service___ instance (`OsiriXServiceStub`) 
provided by the `osirix_pb2_grpc` module. Currently, this process necessitates the use of an insecure channel on the 
local system (localhost), as detailed below. Please be aware that the specified port must align with one of the active 
ports displayed in the OsiriXgrpc plugin.(see [Server Configuration](../getting_started.md#server-configuration)).

``` { .py .annotate title="Example Python code to establish gRPC connection"}
import grpc
from osirixgrpc import osirix_pb2_grpc

port = 50001  # (1)
server_url_localhost = 'localhost:' + str(port)
channel_opt = [('grpc.max_send_message_length', 512 * 1024 * 1024), 
               ('grpc.max_receive_message_length', 512 * 1024 * 1024)] # (2)
channel = grpc.insecure_channel(server_url_localhost, options=channel_opt)
stub = osirix_pb2_grpc.OsiriXServiceStub(channel)
```

1. Must match activated port in the OsiriX plugin.  See [Server Configuration](../getting_started.md#server-configuration).
2. This could change depending on intended use.

## Requests and Responses
After establishing a connection, following the conventions of standard 
[gRPC practices](https://grpc.io/docs/what-is-grpc/core-concepts/), OsiriXgrpc utilizes two classes of 'message' for 
communication with the OsiriX plugin server: ___requests___ and ___responses___ . Similar to conventional functions, 
requests encapsulate all arguments passed to defined service methods, while responses encapsulate the returned results. 
The definitions for all service methods are outlined in the `osirix.proto` source file. Details about available methods
are provided in specific pages in the API documentation.   

In order to replicate methods that don't necessitate input arguments (e.g., getters) or those that don't require 
returning results (e.g., setters), we have introduced a base response and request for these specific cases. 
These base definitions are located in the `utilities.proto` file
``` { .c++ title="Empty response and request definition (utilities.proto)"}
----8<----
protos/utilities.proto:10:
----8<----
```

Note that even empty responses contain a field called `Status`
``` { .c++ title="Status definition (utilities.proto)"}
----8<----
protos/utilities.proto:5:8
----8<----
```

This message contains a single (binary) integer `status`, with values 0 and 1 representing unsuccessful and successful 
method execution respectively, and a string `message`, which contains an error message in the even that `status=0`.

## OsiriXGRPC types
By default, gRPC is designed to work with standard data types (`int32`, `int64`, `uint32`, `uint64`, `float`, `double`, 
`bool`, `and` `string`) within messages. However, OsiriXgrpc goes beyond this default capability by introducing support 
for arbitrary classes defined within OsiriX. This extension is achieved through the definition of several "types" in the 
`types.proto` file.

In each defined type, there is an `osirixrpc_uid` field, containing a Universally Unique Identifier (UUID) string, 
specifically a NextStep UUID string 
([NSSUID string](https://developer.apple.com/documentation/foundation/nsuuid?language=objc)). This UUID is managed by 
the OsiriXgrpc plugin and serves as a unique identifier linked to elements within the OsiriX application. This mechanism 
enables seamless access to and interaction with various elements of the OsiriX app through gRPC communication.

``` { .c++ title="Type definitions (types.proto)"}
----8<----
protos/types.proto:5:
----8<----
```

## Core OsirXgrpc methods
"The secret of getting ahead is getting started" (Mark Twain). 

To begin accessing elements of OsiriX, it is first necessary to get a hook onto one of the core objects it contains.
There are five methods that can be used for this.

``` { .c++ title="Core OsiriX access methods (osirix.proto)"}
----8<----
protos/osirix.proto:20:24
----8<----
```

All methods require `Empty` requests, but have the following responses.
``` { .c++ title="Core OsiriX responses (osirix.proto)"}
----8<----
protos/osirix.proto:173:
----8<----
```

## Examples
Below are examples of how to use these functions using Python.  These all assume that a connection
has been established as detailed in [Connecting to the Server](#connecting-to-the-server).

### Accessing information from the database (BrowserController)
This code can be used obtain a hook for the OsiriX database browser.
``` { .py}
from osirixgrpc import utilities_pb2

empty_request = utilities_pb2.Empty()  # (1)
browser_response = stub.OsirixCurrentBrowser(empty_request)
if browser_response.status.status == 0: # (2)
    raise Exception(f"Could not get browser.  Reason: {browser_response.status.message}")
browser_controller = browser_response.browser_controller # (3)
```

1. Used for methods that do not require arguments 
2. Check that the method did not end in error and deal with it.
3. A `BrowserController` type.

This may subsequently be used get the current user selection (series and/or studies) within the browser.
``` { .py}
from osirixgrpc import browsercontroller_pb2

selection_response = stub.BrowserControllerDatabaseSelection(browser_controller)
series = selection_response.series # (1)
studies = selection_response.studies # (2)
```

1. A list of `DicomSeries` types. 
2. A list of `DicomStudy` types.

In turn, we can access and print the selected study names.
``` { .py}
from osirixgrpc import dicomstudy_pb2

for dicom_study in studies:
    studyname_response = stub.DicomStudyName(dicom_study)
    print("Study name: ", studyname_response.name)
```

Other methods are documented in the API documents for BrowserController.

### Accessing displayed images (ViewerController)
There are two ways to access a 2D viewer from OsiriX; either by accessing a list of all displayed viewers
or by accessing the "front-most" viewer (currently selected).
``` { .py}
from osirixgrpc import utilities_pb2

empty_request = utilities_pb2.Empty()
frontmostviewer_response = stub.OsirixFrontmostViewer(empty_request)
frontmost_viewer = frontmostviewer_response.viewer_controller  # (1)

viewers_response = stub.OsirixDisplayed2DViewers(empty_request)
viewers = viewers_response.viewer_controllers  # (2)
```

1. A `ViewerController` type.
2. A list of `ViewerController` types.

It is then possible to access the list of `DCMPix` objects attributed to the particular viewer
``` { .py}
from osirixgrpc import viewercontroller_pb2

pixlist_request = viewercontroller_pb2.ViewerControllerPixListRequest(viewer_controller=frontmost_viewer, 
                                                                      movie_idx=0) # (1)
pixlist_response = stub.ViewerControllerPixList(pixlist_request) # (2)
dcm_pix = pixlist_response.pix # (3)
```

1. Note that the requested frame number _must_ be provided (0 is first frame).
2. A `ViewerControllerPixListResponse`.
3. A list of `DCMPix` types.

It then possible to get access to the contained image data.
``` { .py}
import numpy as np

pix_0 = dcm_pix[0]
image_response = stub.DCMPixImage(pix_0) # (1)
rows = image_response.rows
columns = image_response.columns
if image_response.is_argb: # (2)
    image_array = np.array(image_response.image_data_argb).reshape(rows, columns, 4)
else:
    image_array = np.array(image_response.image_data_float).reshape(rows, columns) # (3)
```

1. An example of using a type as a request
2. Images are either float (greyscale) or ARGB format
3. The datastream does not contain dimensional information.

This example introduced a case where the method request is a data type rather than an `Empty` request. This is typical 
where the method obtains information about a given OsiriX object (`DCMPix` in this instance). The request for the list
if `DCMPix` (`ViewerControllerPixListRequest`), however, is a dedicated request that must be built prior to calling the 
method.

### Manipulating regions of interest (ROI)
There are different kind of Region of Interest (ROI) available within OsiriX, but this can be somewhat broken into two
core types: brush and polygon.  The former is defined by a boolean array, where true values are considered to be part of
the ROI and false values outside, and the latter is defined by an ordered set of vertices. 

The following example demonstrates how ROIs can be obtained from a (2D) viewer controller, and subsequently rotates them 
about the centroid by 30 degrees. Note that will not operate on brush ROIs, though no error is raised if attempted.
``` { .py}
from osirixgrpc import roi_pb2

roilist_request = viewercontroller_pb2.ViewerControllerROIListRequest(viewer_controller=frontmost_viewer, 
                                                                      movie_idx=0) # (1)
roilist_response = stub.ViewerControllerROIList(roilist_request) # (2)
for roi_slice in roilist_response.roi_slices:
    for roi in roi_slice.rois:
        centroid_response = stub.ROICentroid(roi)
        rotate_request = roi_pb2.ROIRotateRequest(roi=roi,
                                                  x=centroid_response.x,
                                                  y=centroid_response.y,
                                                  degrees=30.0)
        rotate_response = stub.ROIRotate(rotate_request)
        if rotate_response.status.status == 0:
            raise ValueError(f"Could not rotate: {rotate_response.status.meessage}")
```

1. As for the `ViewerControllerPixListRequest`, this requires definition of the frame from which ROIs are needed.
2. `ViewerControllerROIListResponse` contains a list of ROI slices, one per image slice, each containing >= 0 ROIs.

A full breakdown of the other methods, requests and responses is provided in the remainder of the API documentation.
