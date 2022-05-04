# osirixgrpc

Have you ever wanted to rapidly develop tools for medical imaging? Do you wish you could focus on the development of great imaging analysis ideas without the overhead of needing to write complex UIs that in the end no clinician wants to use? Perhaps with the ability to incorporate state-of-the-art libraries including AI?  Fear not, __osirixgrpc__ is here!      

__osirixgrpc__ is a research plugin for the popular [OsiriX](https://www.osirix-viewer.com) medical image viewing platform for Mac OS. It leverages the [gRPC](https://grpc.io) architecture to provide fast communication between the functionality exposed within OsiriX and  custom-built software or script running on a different process. This inter-operability is achieved by running a gRPC server from within the OsiriX run-time within the localhost of the machine on which it is deployed.  More information about inter-process communication can be found on the [gRPC website](https://grpc.io).

Whilst gRPC is a very well-built standard for inter-process communication in numerous [languages](https://grpc.io/docs/languages) (including C++, Java, Ruby, Python and Go), the in-built message passing syntax through 'requests' and subsequent 'responses' can be a little daunting for the uninitiated.  We therefore suggest using our supporting library [pyOsiriX](https://pyosirix.com) for script development.

Currently, Python is the only supported language, though [contributions](docs/CONTRIBUTING.md) are welcome in future versions.

## Installation
To install the plugin please download the [latest release](releaseurl.com) of the plugin. Once unzipped, open the _osirixgrpc.osirixplugin_ file and you will be directed through the rest of the installation process.

## Usage
### Server management
 - Open the server window by selecting "Plugins" &rarr; "Database" &rarr; "osirixgrpc" &rarr; "Server Configuration" from the OsiriX menubar.
 
<img src="docs/figures/server_config_list.jpg" alt="Server Window" style="width:70%" align="center">

 - To add a server, click on the "+" symbol and add a port in the opening splash screen. _The port should be an integer number swithin the range 1024 to 65535 inclusive_
 - A server can be started by selecting the relevant line and pressing the "▸" symbol. _If the port is already in use, this will be stated on the server window and you will not be able to activate this port_. Likewise, a server can be stopped at any time.
 - The order of servers can be modified using the "⌃" and "⌄" buttons. The order may be used by clients (including pyosirix) to determine user preference when automatically determining which port to attempt connection with.
 - All server settings are automatically saved and loaded when OsiriX is relaunched.    

### Registering a script
It is possible to register a client script  
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
 1. Timothy Sum Hon Mun, et. al., AAAI, 2022
