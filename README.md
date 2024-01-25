# osirixgrpc

__NOTE__: This page is currently under development and will be released soon (~April 2024).

__osirixgrpc__ is a research plugin for the popular [OsiriX](https://www.osirix-viewer.com) medical image viewing platform for Mac OS. It leverages the [gRPC](https://grpc.io) architecture to provide fast communication between OsiriX (the "server") and custom-built software or script running on a different local process (the "client").  This enables fast development of additional OsiriX functionality, including the adoption of state-of-the-art libraries for image processing and artificial intelligence.  Currently, Python is the only in-built supported language, though adoption of [other languages](https://grpc.io/docs/languages) can be easily achieved.  

gRPC relies on a paradigm of message passing through 'requests' and 'responses'.  We also suggest the use our supporting library [pyOsiriX](https://pyosirix.com) for script development, which is aimed at converting these conventions to an object-oriented paradigm, that may be more familiar to users. 

[Contributions](docs/CONTRIBUTING.md) are highly welcomed to support welcome in future versions. 

## Installation
To install the plugin please download the [latest release](releaseurl.com) of the plugin. Once unzipped, open the _osirixgrpc.osirixplugin_ file and you will be directed through the rest of the installation process.

## Usage
### Server management
 - Open the server window by selecting "Plugins" &rarr; "Database" &rarr; "osirixgrpc" &rarr; "Server Configuration" from the OsiriX menubar.
 
 <p align="center">
<img src="docs/figures/server_config_list.jpg" alt="Server Window" style="width:60%" align="center">
</p>

 - Servers can be added/removed using the "+" and "-" buttons respectively.  In the resulting dialog, a port number should be specified. The port should be an integer number swithin the range 1024 to 65535 inclusive.
 - A server can be started by selecting the relevant line and pressing the play button. If the port is already in use, this will be stated on the server window and you will not be able to activate this port. Likewise, a server can be stopped at any time using the stop button.
 - The order of server addresses can be modified using the up- and down-arrow buttons. The order may be used by clients (including pyosirix) to determine user preference when automatically establishing a connection.
 - All server settings are automatically saved, and then loaded when OsiriX is launched.  

### Registering a script
It is possible to register a client script within the osirixgrpc plugin. By doing so, it enables users to run a script through a button click within OsiriX through an additional menu. 

- Open the script window by selecting "Plugins" &rarr; "Database" &rarr; "osirixgrpc" &rarr; "Server Configuration" from the OsiriX menubar.

## Any suggestions?
We are always happy to recieve suggestions for future versions of the plugin, or just to hear about what is or isn't working. We would appreciate if this is done by raising an [issue](https://github.com/osirixgrpc/osirixgrpc/issues). 

## Any questions?
We are happy to answer any questions on the use of osirixgrpc, but please do so by raising an [issue](https://github.com/osirixgrpc/osirixgrpc/issues) so that others can benefit from the answer 

## Versions
 - __1.0.0__: Initial release with core functionality.

## Potential future
Let us know your thoughts on these and we will prioritise depending on 
 - Support for other scripting languages including Java and Ruby.
 - Improve security through SSL/TCL encryption.  
 
 ## References
 1. [Timothy Sum Hon Mun, et. al., AAAI, 2022](https://ai-2-ase.github.io/papers/29%5cCameraReady%5cAAAI_OsiriXgrpc__Rapid_prototyping_and_development_of_state_of_the_art_artificial_intelligence_in_OsiriX_cam_ready.pdf)
