# Contributing
__Welcome__ to the contributions section!

OsiriXgrpc is an emerging open-source initiative by the Institute of Cancer Research, dedicated to accelerating the 
field of medical image science and processing. At the heart of our mission lies a commitment to the democratization of 
knowledge and empowerment of medical imaging researchers worldwide. By harnessing the advanced capabilities of OsiriX's 
user interface and DICOM database, our project aims to streamline the development process of robust medical imaging 
tools, allowing researchers to concentrate on groundbreaking scientific discoveries, including pioneering AI. 

As a community-driven project, we invite contributors from diverse backgrounds to join us in shaping the future of 
medical research, fostering an environment of collaboration and innovation.

# Ways to Contribute
<table>
<tr>
    <td><b>Example Scripts</b></td>
    <td>We strongly encourage developers to share scripts of OsiriXgrpc in use.  Please see our <a href="404.html">
        submitting examples</a> section for more information.</td>
</tr>
<tr>
    <td><b>Plugin Development</b></td>
    <td>If you would like to help develop the core OsiriXgrpc plugin, we are keen to improve and evolve every 
        aspect of it. This includes: 
        <ul>
            <li>Expose additional OsiriX functionality to OsiriXgrpc</li>
            <li>Optimize CI/CD of the plugin (all performed in GitHub)</li>
            <li>Improve the user experience through additional plugin features</li>
            <li>Boost security of the GRPC connections through SSL connections.</li>
            <li>Ensure that key updates to OsiriX are monitored and fixed within the plugin</li>
        </ul>
        Please see the remainder of this documentation to see how this can be done, and <a href="contact">let us 
        know</a> about your ideas!
    </td>
</tr>
<tr>
    <td><b>Documentation</b></td>
    <td>We encourage feedback on our documentation to improve the user experience and ensure it makes sense. We 
        currently do not support localization, but should the project be successful we would encourage this moving
        forward. Please see our <a href="#documentation">instructions for project documentation</a> for more 
        information.   
    </td>
</tr>
<tr>
    <td><b>Testing</b></td>
    <td>We greatly appreciate our testers, who provide core feedback on OsiriXgrpc and have a key role in deciding the 
        future of the project. Please <a href="#contact">contact us</a> if you would like to become an official tester!
    </td>
</tr>
<tr>
    <td><b>Bug Tracking</b></td>
    <td>We will endeavour to fix all bugs encountered in OsiriXgrpc as soon as possible. If you encounter a bug, please
        see our <a href="#bug-reporting">bug reporting</a> section.
    </td>
</tr>
</table>

# Code of Conduct


# Documentation

# Bug Reporting

# Coding Guidelines
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

# Version Control

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

# Contact
| Name                | Contact                      |
|---------------------|------------------------------|
| Matt Blackledge     | matthew.blackledge@icr.ac.uk |
| Timothy Sum Hon Mun | timothy.sumhonmun@icr.ac.uk  |