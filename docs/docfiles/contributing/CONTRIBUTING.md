# Contributing
Welcome to the contributions sections. If you are interested in contributing to the project then please do let us know.
The contents of this section should be enough to get you started, but the complexity and detail of these pages will grow 
over time, so watch this space!

If you wish to 

## Project Structure
There are several core files and directories at the [root of the project](https://github.com/osirixgrpc/osirixgrpc)

| Name             | Description                                                                                                      |
|------------------|------------------------------------------------------------------------------------------------------------------|
| __cpp__          | Auto-generated C++ protobuf files (not under version control).                                                   |
| __docs__         | All externally-facing documentation (definition files in markdown).                                              |
| __protos__       | gRPC protocol files, which need to be modified to provide additional OsiriX functionality.                       |
| __python__       | Source code for the osirixgrpc pip project. Sub-folder `osirixgrpc` is automatically generated (not under vc).   |
| __src__          | Source files for building the OsiriXgrpc plugin. This is also where grpc methods are implemented.                |
| __tests__        | Integration tests for the plugin and protobuf files. Note these are not automated and run manually.              |
| .bumpversion.cfg | Rules to increment version numbers scattered throughout the project                                              |
| build.sh         | A bash shell script used to compile gRPC from source and build all protobuf files from defintion (.proto) files. |

## Version Control

OsiriXgrpc uses semantic versioning as illustrated in the figure below. If you wish to contribute to OsiriXgrpc,
please fork the repository and make your changes. Please contact us if you wish to merge your planned additions with
OsiriXgrpc so that we are aware of your intended changes and ensure that they are inline with planned milestones.

Note that all development should take place within separate branches/forks and then merged with the `dev` branch prior 
to release using pull requests.  This branch will exist in two core phases:

1. __Development__ phase. Each version will be appended by the `_devX`, where `X` increments after each additional
  feature is merged. New features are accepted in this stage.
2. __Release Candidate__ phase. Each version will be appended by the `_rcX`, where `X` increments after each additional
  hot-fix applied during user testing. No new features will be accepted during this phase.

![OsiriXgrpc version control](../assets/osirixgrpc.drawio.svg)

Versioning is controlled by [bump version](https://pypi.org/project/bumpversion/). This should only be performed 
on the `dev` or `main` branches and is therefore not for public use.  Any changes to the version numbers in a fork or 
branch will be ignored and no pull request accepted until versioning is normalised to baseline.

## Developers
| Name                | Contact                      |
|---------------------|------------------------------|
| Matt Blackledge     | matthew.blackledge@icr.ac.uk |
| Timothy Sum Hon Mun | timothy.sumhonmun@icr.ac.uk  |