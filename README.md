# osirixgrpc

This project controls the source code for the main grpc plugin (to be installed within OsiriX).

The core components include:

 - build_grpc.sh: Run to create a local copy of the latest grpc libraries (within a directory called 'grpc').  The plugin will not compile unless this is run once beforehand on a nely cloned repository.
 - docs: The documentation files for the plugin (currently just the uml designs)
 - LICENSE: The license should be BSD-3
 - logo: Contains the latest of the plugin logo.  Please do not add additional figures (e.g. png, jpeg to the repository).
- protos: Contians the protobuf definition files, build script and derived protobuf files in the specified languages.
- src: contains the xcode implementation files for the plugin.
- tests: Describes and documents the manual test results for the plugin.


## Contact
If you have any requirements then please do add a ticket and we will aim to provide an update as soon as possible

## Develop
We are always interested in developers for this project.  If you are interested then please contact matthew.blackledge@icr.ac.uk
