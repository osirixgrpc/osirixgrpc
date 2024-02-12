# Contributing
__Welcome__ to the contributions section!

OsiriXgrpc is an emerging open-source initiative by the Institute of Cancer Research, dedicated to accelerating the 
field of medical image science and processing. At the heart of our mission lies a commitment to the democratization of 
knowledge and empowerment of medical imaging researchers worldwide. By harnessing the advanced capabilities of OsiriX's 
user interface and DICOM database, our project aims to streamline the development process of robust medical imaging 
tools, allowing researchers to concentrate on groundbreaking scientific discoveries, including pioneering AI. 

As a community-driven project, we invite contributors from diverse backgrounds to join us in shaping the future of 
medical research, fostering an environment of collaboration and innovation.

## Ways to Contribute
<table>
  <tr>
    <td><b>Example Scripts</b></td>
    <td>We strongly encourage developers to share scripts of OsiriXgrpc in use.  Please see our <a href="404.html">
        submitting examples</a> section for more information.</td>
  </tr>
  <tr>
    <td><b>Documentation</b></td>
    <td>We encourage feedback on our documentation to improve the user experience and ensure it makes sense. We 
        currently do not support localization, but should the project be successful we would encourage this moving
        forward. Please see our <a href="#documentation">instructions for project documentation</a> for more 
        information.</td>
  </tr>
  <tr>
    <td><b>Testing</b></td>
    <td>We greatly appreciate our testers, who provide core feedback on OsiriXgrpc and have a key role in deciding the 
        future of the project. Please <a href="#contact">contact us</a> if you would like to become an official 
        tester!</td>
  </tr>
  <tr>
    <td><b>Bug Tracking</b></td>
    <td>We will endeavour to fix all bugs encountered in OsiriXgrpc as soon as possible. If you encounter a bug, please
        see our <a href="#bug-reporting">bug reporting</a> section.</td>
  </tr>
  <tr>
    <td><b>Feature Suggestions</b></td>
    <td>We cannot improve OsiriXgrpc without good ideas coming from users. If you would like to request a new feature
        this can be done as a feature request on the project    
        <a href="https://github.com/osirixgrpc/osirixgrpc/issues"> issue tracker</a>.  Please note that acceptance and 
        importance of features will be discussed and agreed by our developers following discussion with you. We cannot 
        guarantee that all feature requests will be implemented, or how quickly they will be delivered.</td>
  </tr>
  <tr>
    <td><b>Feature Development</b></td>
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
      know</a> about your ideas!</td>
  </tr>
</table>

## Code of Conduct
Please see our [Code of Conduct](CODE_OF_CONDUCT.md) for more information.

## Prerequisites
In order to help contribute to the OsiriXgrpc project there are a few things you will need. Some may not be required 
depending on the level contributions you want to make.

<table>
  <tr>
    <td><b>Mac</b></td>
    <td>OsiriX works on macOS.  We currently support (and have tested) compatability of OsiriXgrpc on macOS Monterey and
        above, on both Intel and M1/M2/M3 native processors. We always advise ensuring that your operating system is 
        up-to-date.</td>
  </tr>
  <tr>
    <td><b>OsiriX</b></td>
    <td>A copy of the <a href="https://www.osirix-viewer.com/osirix/osirix-md/download-osirix-lite/">latest OsiriX 
        app</a> downloaded on your system. This will be crucial for testing the OsiriXgrpc plugin, developing new 
        features, and authoring new OsiriXgrpc scripts.</td>
  </tr>
  <tr>
    <td><b>Xcode</b></td>
    <td>Xcode is freely available from the App store, and is only required if you want to develop new features for the
        core OsiriXgrpc plugin, or build the source code.</td>
  </tr>
  <tr>
    <td><b>GitHub Account</b></td>
    <td>You will need a GitHub account to interact with the OsiriXgrpc source code, create pull requests for new
        features that you have developed, and raise new issues or report bugs on the project 
        <a href="https://github.com/osirixgrpc/osirixgrpc/issues"> issue tracker</a>.</td>
  </tr>
</table>

## Coding Guidelines
### Project Structure
There are several core files and directories at the [root of the project](https://github.com/osirixgrpc/osirixgrpc)

| Name             | Description                                                                                                                            |
|------------------|----------------------------------------------------------------------------------------------------------------------------------------|
| __cpp__          | Auto-generated C++ protobuf files (not under version control).                                                                         |
| __docs__         | All externally-facing documentation (definition files in markdown).                                                                    |
| __protos__       | gRPC protocol files, which need to be modified to provide additional OsiriX functionality.                                             |
| __python__       | Source code for the osirixgrpc pip project. Sub-folder `osirixgrpc` is automatically generated (not under version control).            |
| __src__          | Source files for building the OsiriXgrpc plugin. This is also where grpc methods are implemented.                                      |
| __tests__        | Integration tests for the plugin and protobuf files. Note these are not automated and run manually.                                    |
| .bumpversion.cfg | Rules to increment version numbers scattered throughout the project                                                                    |
| build.sh         | A utility shell script used to compile gRPC from source and build all protobuf files from definition (.proto) files on a host machine. |

### Version Control

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

## Documentation
All documentation is written in Markdown format and compiled using [MkDocs](https://www.mkdocs.org/). The organization 
of documentation should be kept consistent, and any changes to layout need to be fully discussed and agreed with all
developers before being implemented. 

| Name                    | Description                                                                          |
|-------------------------|--------------------------------------------------------------------------------------|
| docs/api                | Description files for all OsiriXgrpc client API (in Python).                         |
| docs/assets             | Location for all figures and other supporting information not in Markdown format.    |
| docs/contributing       | Instruction for how to contribute to the project.                                    |
| docs/getting_started.md | Core instructions on how to install and use the OsiriX plugin (e.g. user-interface). |
| docs/README.md          | The homepage for the documentation.                                                  |
| mkdocs.yaml             | yaml configuration file for the mkdocs build                                         | 

### Requirements
Building documentation requires both [mkdocs](https://www.mkdocs.org/) and 
[mkdocs-material](https://squidfunk.github.io/mkdocs-material/) to be installed.  These can be installed using the 
Python Package Index:
```bash
pip install mkdocs mkdocs-material
```

### Building Documentation
To build the documentation from source it is sufficient to run the following command, from the `docs` folder within the
project root:
```bash
mkdocs build
```
This will create a new directory, `site`, which contains all built html documentation for deployment.

When developing documentation, however, it can be beneficial to run the MkDocs server (again from the `docs` folder):
```bash
mkdocs serve
```
By connecting to the established service (linking to `http://localhost:8000/` in a we-browser), it is then possible to 
view changes to documentation in real-time.

### Deploying Documentation
Collaborators should and will never directly modify the deployed documentation. Instead, this will be performed as part
of OsiriXgrpc continuous integration. The OsiriXgrpc documentation will be deployed from either the `main` or `dev` 
branches to one of two sites, following a push to the GitHub repository:

| Branch | Site                                                                               |                                                                         |
|--------|------------------------------------------------------------------------------------|-------------------------------------------------------------------------|
| `main` | [https://osirixgrpc.github.io/osirixgrpc](https://osirixgrpc.github.io/osirixgrpc) | All documentation for OsiriXgrpc releases                               |
| `dev`  | [https://osirixgrpc.netlify.app](https://osirixgrpc.netlify.app)                   | Documentation in development mode and for user testing of next release. |

### Suggesting Changes
If you would like to suggest a change to the documentation rather than altering the source code, then please let us 
know through the project <a href="https://github.com/osirixgrpc/osirixgrpc/issues"> issue tracker</a>, ensuring you 
choose a `documentation` label for the issue.

## Bug Reporting
If you encounter any bugs with the OsiriXgrpc plugin then please let us know through the 
<a href="https://github.com/osirixgrpc/osirixgrpc/issues"> issue tracker</a>, ensuring you choose a `bug` label.  When 
you raise the issue, please using the relevant template for bugs, which will include the following information:

<ul>
  <li> Is the bug a plugin issue (e.g. inability to start a server or install the plugin), or an issue with creating 
    some functionality using the client API? </li>
  <li> What steps could we use to reproduce the bug? </li>
  <li> If the issue is related to a script that you used, please send us (where possible):
    <ol>
      <li> The script that caused the issue. </li>
      <li> The output of the Task Console (from OsiriX click `Plugins` &rarr; `Database` &rarr; `osirixgrpc` &rarr; 
         `Task Console`) </li>
    </ol>
  </li>
  <li> If the issue is plugin related, please send us any information provided by Mac when the error occurred. </li>
  <li> OsiriX version. </li>
  <li> OsiriXgrpc version. </li>
  <li> macOS version. </li>
  <li> Processor (Intel or Mac M1/M2/M3). </li>
</ul>

## User Testing
OsiriXgrpc relies on frequent user testing to ensure stability and usability of all developed features. We are keen to
[hear](#contact) from anyone who would like to contribute to testing and help us improve OsiriXgrpc (please check our 
[prerequisites](#prerequisites) for user testing).

User testing takes place prior to each major and minor release of OsiriXgrpc. Each user test consists of completing a
Google Form that checks successful completion and obtains feedback on each of the following general operations:

1. Installation of OsiriXgrpc.
2. Initiating an OsiriXgrpc server.
3. Installing a script.
4. Running a script.

In addition, we will ask testers to run some automated unit tests. Automated unit testing for OsiriXgrpc presents 
substantial challenges - this complexity arises from its dependency on symbols and functions embedded within the OsiriX 
executable. Consequently, to maintain the quality and reliability of OsiriXgrpc, we incorporate unit testing into our 
user tests. This approach also ensures comprehensive validation through real-world usage scenarios. These unit tests 
will deploy an output file (`osirixgrpc_unit_tests.txt`) on the testers Desktop, which will be requested to be sent back
to us for processing. This file will not capture any personal information, other than the versions of macOS, OsiriX,
and OsiriXgrpc the tester has used.

## Feature Requests

We warmly invite fresh insights and suggestions for enhancing OsiriXgrpc. Your contributions could range from extending 
OsiriX features via our API, refining our user interface, to offering ideas for optimizing our workflow or enhancing our 
documentation. Every piece of feedback is invaluable to us. While we are committed to incorporating your suggestions to 
the best of our ability, please remember that OsiriXgrpc thrives on community involvement and operates on a voluntary 
basis. Consequently, we cannot provide specific timelines for the introduction of new features. Additionally, it's 
crucial to acknowledge that our ability to implement certain enhancements is contingent upon the functionalities 
available within the OsiriX application itself.

If you wish request new features, please use our 
<a href="https://github.com/osirixgrpc/osirixgrpc/issues"> issue tracker</a> ensuring that you use a `feature request` 
label, using the feature request issue template.  This includes the following information
<ul>
  <li>To which aspect of OsiriXgrpc is the feature request intended?</li>
  <li>Short description of the new functionality</li>
  <li>Why would this improve the functionality of OsiriXgrpc?</li>
  <li>Have you been using any work-around so far?</li>
  <li>How urgent is the new functionality to you?</li>
  <li>Would you be willing to help develop/test the new functionality?</li>
</ul>

## Contact
| Name                | Contact                      |
|---------------------|------------------------------|
| Matt Blackledge     | matthew.blackledge@icr.ac.uk |
| Timothy Sum Hon Mun | timothy.sumhonmun@icr.ac.uk  |