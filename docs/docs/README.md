# OsiriXgrpc	

![Welcome to OsiriXgrpc!](assets/logo/logo-large.png)

__Welcome to OsiriXgrpc__, a research plugin for the popular [OsiriX](https://www.osirix-viewer.com) medical image 
viewing platform for macOS. It leverages the [gRPC](https://grpc.io) architecture to provide fast communication between 
OsiriX (the _server_) and custom-built software or scripts running on a different local process (the _client_).  This 
enables fast development of additional OsiriX functionality, including the adoption of state-of-the-art libraries for 
image processing and artificial intelligence.  Currently, Python is the only in-built supported language, though
adoption of [other languages](https://grpc.io/docs/languages) can be easily achieved.  

Note that it can be much simpler to interact with OsiriXgrpc using the more pythonic __pyOsiriX__ glue code. See the
dedicated [documentation](pyosirix/README.md) for further information.

## Getting Started
For instructions on how to install and set up the plugin, please see the [getting started](getting_started.md) page.

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
 
## Citations

 1. [Timothy Sum Hon Mun, et. al., AAAI, 2022](https://ai-2-ase.github.io/papers/29%5cCameraReady%5cAAAI_OsiriXgrpc__Rapid_prototyping_and_development_of_state_of_the_art_artificial_intelligence_in_OsiriX_cam_ready.pdf)
 