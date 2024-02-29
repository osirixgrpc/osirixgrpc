# OsiriXgrpc    

![Welcome to OsiriXgrpc!](https://raw.githubusercontent.com/osirixgrpc/osirixgrpc/dev/docs/docs/assets/logo/logo-large.png)

[![Powered By gRPC](https://img.shields.io/badge/powered_by-gRPC-green?labelColor=red)](https://grpc.io)
[![GitHub License](https://img.shields.io/github/license/osirixgrpc/osirixgrpc?color=blue)](https://github.com/osirixgrpc/osirixgrpc/blob/main/LICENSE)
![PyPI - Downloads](https://img.shields.io/pypi/dm/osirixgrpc)
[![Static Badge](https://img.shields.io/badge/issues-osirixgrpc-red?logo=github)](https://github.com/osirixgrpc/osirixgrpc/issues)
[![Static Badge](https://img.shields.io/badge/citation-AI2ASE-green?logo=googlescholar)](https://ai-2-ase.github.io/papers/29%5cCameraReady%5cAAAI_OsiriXgrpc__Rapid_prototyping_and_development_of_state_of_the_art_artificial_intelligence_in_OsiriX_cam_ready.pdf)

__Welcome to OsiriXgrpc__, a research plugin for the popular [OsiriX](https://www.osirix-viewer.com) medical image 
viewing platform for macOS. It leverages the [gRPC](https://grpc.io) architecture to provide fast communication between 
OsiriX (the _server_) and custom-built software or scripts running on a different local process (the _client_).  This 
enables fast development of additional OsiriX functionality, including the adoption of state-of-the-art libraries for 
image processing and artificial intelligence.  Currently, Python is the only in-built supported language, though
adoption of [other languages](https://grpc.io/docs/languages) can be easily achieved.  

!!! note "Using osirixgrpc versus pyosirix"
    It can be much simpler to interact with OsiriXgrpc using the more pythonic __pyOsiriX__ glue code. See the
    dedicated [documentation](https://osirixgrpc.github.io/osirixgrpc/pyosirix/) for further information.

## Installation
For instructions on how to install and set up the plugin, please see the 
[getting started](https://osirixgrpc.github.io/osirixgrpc/api/) page.

## Any suggestions?
We are always happy to receive suggestions for future versions of the plugin, or just to hear about what is or isn't 
working. We would appreciate if this is done by raising an [issue](https://github.com/osirixgrpc/osirixgrpc/issues). 
Please see more information in our [contributing](contributing/CONTRIBUTING.md) section.

## Any questions?
We are happy to answer any questions on the use of osirixgrpc, but please do so by raising an 
[issue](https://github.com/osirixgrpc/osirixgrpc/issues) so that others can benefit from the answer. Please ensure that 
you use the relevant issue template so that we get all the information we need!

## Future Ambitions
We are always looking to improve things. We have a few suggestions in our roadmap, and would be happy to hear your 
thoughts - please let us know using a `feature request` [issue](https://github.com/osirixgrpc/osirixgrpc/issues) 
template.

 - Support for other scripting languages including Java and Ruby.
 - Improve security through SSL/TCL encryption.

## Examples
### Establishing a connection with grpc
```
import grpc
import osirix_pb2_grpc

port = 12345  # Must match activated port in OsiriX plugin
server_url_localhost = 'localhost:' + str(port)
channel_opt = [('grpc.max_send_message_length', 512 * 1024 * 1024), ('grpc.max_receive_message_length', 512 * 1024 * 1024)]
channel = grpc.insecure_channel(server_url_localhost, options=channel_opt)
stub = osirix_pb2_grpc.OsiriXServiceStub(channel)
```
### Obtain a copy of the current browser
```
import utilities_pb2

request = utilities_pb2.Empty()  # For functions with no input, use an empty request
response = stub.OsirixCurrentBrowser(request)
if response.status.status == 0:
    raise Exception("Could not get browser.  Reason: %s" % response.status.message)
browser_controller = response.browser_controller
```
### Get the current database selection within the browser controller
```
import browsercontroller_pb2

response = stub.BrowserControllerDatabaseSelection(browser_controller)
series = response.series
studies = response.studies
```
### Obtain the names of the selected studies
```
import dicomstudy_pb2

for dicom_study in studies:
    response = stub.DicomStudyName(dicom_study)
    print("Study name: ", response.name)
```
