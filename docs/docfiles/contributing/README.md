# Contributing
Welcome to the contributions sections. If you are interested in contributing to the project then please do let us know.
The contents of this section should be enough to get you started, but the complexity and detail of these pages will grow 
over time, so watch this space!

## Project Structure
There are several core files and directories at the [root of the project](https://github.com/osirixgrpc/osirixgrpc)

| Name             | Description                                                                                                      |
|------------------|------------------------------------------------------------------------------------------------------------------|
| __cpp__          | Auto-generated C++ protobuf files (do not edit).                                                                 |
| __docs__         | All externally-facing documentation (definition files in markdown).                                              |
| __protos__       | gRPC protocol files, which need to be modified to provide additional OsiriX functionality.                       |
| __python__       | Source code for the osirixgrpc pip project. Sub-folder `osirixgrpc` is automatically generated (do not edit).    |
| __src__          | Source files for building the OsiriXgrpc plugin. This is also where grpc methods are implemented.                |
| __tests__        | Integration tests for the plugin and protobuf files. Note these are not automated and run manually.              |
| .bumpversion.cfg | Rules to increment version numbers scattered throughout the project                                              |
| build.sh         | A bash shell script used to compile gRPC from source and build all protobuf files from defintion (.proto) files. |

## Developers
| Name                | Contact                      |
|---------------------|------------------------------|
| Matt Blackledge     | matthew.blackledge@icr.ac.uk |
| Timothy Sum Hon Mun | timothy.sumhonmun@icr.ac.uk  |