# Contributing to OsiriXgrpc
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
| __.github__      | Issue templates and CI/CD workflows for GitHub Actions.                                                                                |
| __cpp__          | Auto-generated C++ protobuf files (not under version control).                                                                         |
| __docs__         | All externally-facing documentation (definition files in markdown).                                                                    |
| __protos__       | gRPC protocol files, which need to be modified to provide additional OsiriX functionality.                                             |
| __pyosirix__     | Source code for the pyOsiriX sub-project, including translation of all functionality into Python classes. .                            |
| __python__       | Source code for the osirixgrpc pip project. Sub-folder `osirixgrpc` is automatically generated (not under version control).            |
| __src__          | Source files for building the OsiriXgrpc plugin. This is also where gRPC methods are implemented.                                      |
| __tests__        | Integration tests for the plugin and protobuf files. Note these are not automated and run manually.                                    |
| .bumpversion.cfg | Rules to increment version numbers scattered throughout the project.                                                                   |
| build.sh         | A utility shell script used to compile gRPC from source and build all protobuf files from definition (.proto) files on a host machine. |

### Modifying Source Code
When making changes to the source code, we recommend the following process to ensure your contributions can be 
efficiently reviewed and integrated:

1. __Fork the Repository__ Start by forking the repository. This creates your own copy of the project where you can make 
   your changes. 
2. __Build the Plugin__ Before making any changes, please familiarize yourself with the [build process](#building). 
3. __Make Your Changes__ Implement your changes in your forked repository. To facilitate a smooth review process, we 
   suggest:
    - Isolate Changes: Keep your changes focused. Large or complex modifications may require more extensive review and 
      have a higher chance of being rejected.
    - Communicate Intentions: Let us know about your planned changes in advance. This helps us coordinate contributions 
      and include them in our release planning.
4. __Submit a Pull Request (PR)__ Once you're satisfied with your changes, submit them back to the main project via a 
   pull request. Ensure your PR targets the `dev` branch. For guidance on creating a pull request, see GitHub's 
   [documentation](https://docs.github.com/articles/creating-a-pull-request-from-a-fork) on Creating a pull request from 
   a fork. 
5. __Review Process__ Your pull request will undergo a review by the project maintainers. During this phase:
    - Merge Upstream Changes: You may be asked to merge changes from the upstream `dev` branch into your fork to resolve 
      any conflicts. 
    - Version Bumping: If your changes are accepted, you'll be asked to bump the version by executing bumpversion build. 
       This step is crucial for maintaining version control and ensuring compatibility. 
6. __Final Steps__ After addressing any review comments and completing the version bump, your changes will be merged into 
   the `dev` branch.

__Additional Tips for a Successful Contribution__

  - __Follow Coding Standards__ Adhere to the coding standards and guidelines provided in the repository documentation to 
    increase the likelihood of your changes being accepted. 
  - __Test Thoroughly__ Before submitting your pull request, thoroughly test your changes to ensure they work as expected 
    and do not introduce any new issues.

By following these guidelines, you can contribute valuable improvements to osirixgrpc and help enhance its 
functionality and user experience.

### Version Control

OsiriXgrpc uses semantic versioning (`major.minor.patch-releasebuild`) using a traditional Gitflow scheme as illustrated 
in the figure below. All development takes place within the `dev` branch prior to release in the main branch. This 
branch exists in one of two phases:

1. __Development__ phase. Each version is appended by the `_devX`, where `X` increments after each additional
  feature is merged. New features are accepted in this stage.
2. __Release Candidate__ phase. Each version will be appended by the `_rcX`, where `X` increments after each additional
  hot-fix applied during user testing. No new features will be accepted during this phase.

Once all tests are complete, the `dev` branch is merged with `main`, and the software remains a beta release for an
incubation period of 2 months, before being fully released. During this period, only hotfixes may be made with no 
change to the core infrastructure (i.e. nomenclature to remain consistent). This provides us with some buffer to perform 
tests on the main branch and obtain feedback from external users.

Any release with `major` = 0 means that we may make subtle changes to the technology prior to 1.0.0 (i.e. no promises!).

![OsiriXgrpc version control](../assets/osirixgrpc.drawio.svg)

Versioning is controlled by [bump2version](https://pypi.org/project/bump2version/). Please don't bump the version until 
your code is ready to be merged after review of the pull request to ensure it uses the intended version. Below are the
commands available to bump2version within this project, and example increments in each case:
<table>
  <tr>
    <td><code>bumpversion build</code></td>
    <td>1.0.0-dev0 &rarr; 1.0.0-dev1 &rarr; 1.0.0-dev2 &rarr; ... <br> <i>or</i> <br>
        1.0.0-rc0 &rarr; 1.0.0-rc1 &rarr; 1.0.0-rc2 &rarr; ...</td>
  </tr>
  <tr>
    <td><code>bumpversion release</code></td>
    <td>1.0.0-dev5 &rarr; 1.0.0-rc0 &rarr; 1.0.0-beta0 &rarr; 1.0.0</td>
  </tr>
  <tr>
    <td><code>bumpversion patch</code></td>
    <td>1.0.0 &rarr; 1.0.1-dev0 &rarr; 1.0.2-dev0 &rarr; ...</td>
  </tr>
  <tr>
    <td><code>bumpversion minor</code></td>
    <td>1.0.2 &rarr; 1.1.0-dev0 &rarr; 1.2.0-dev0 &rarr; ...</td>
  </tr>
  <tr>
    <td><code>bumpversion major</code></td>
    <td>1.2.0 &rarr; 2.0.0-dev0 &rarr; 3.0.0-dev0 &rarr; ...</td>
  </tr>
</table>

### Building
To build the plugin, please use the `build.sh` script provided, which emulates the final build performed as during 
CI/CD in the `main` and `dev` branches.  This script performs the following operations within your repository:

 1. Clone the correct version of gRPC (to a directory called `grpc`).
 2. Build Intel (x86_64) and Apple Silicon (arm64) gRPC libraries and executables.
 3. Combine the libraries into universal binary files using the `lipo` tool.
 4. Use the compiled executables to C++ and Python implementation files from the protocol files (in `protos` directory).
 5. Ensure the OsiriXgrpc python package (`Python` directory) has the correct `requirements.txt` definitions.
 6. Build and zip the plugin bundle. This will result in a file called `osirixgrpc.osirixplugin.zip`.

__Note__: The built file will not be signed and thus should not be shared. Please ensure you share your changes with us
by issuing a [pull request](#modifying-source-code), and we will ensure your changes are incorporated into a signed
plugin for distribution during the next release.

## Documentation
All documentation is written in Markdown format and compiled using [MkDocs](https://www.mkdocs.org/). The organization 
of documentation should be kept consistent, and any changes to layout need to be fully discussed and agreed with all
developers before being implemented. 

| Name                    | Description                                                                          |
|-------------------------|--------------------------------------------------------------------------------------|
| docs/api                | Description files for all OsiriXgrpc client API (in Python).                         |
| docs/assets             | Location for all figures and other supporting information not in Markdown format.    |
| docs/contributing       | Instruction for how to contribute to the project.                                    |
| docs/pyosirix           | Documentation for the pyOsiriX sub-package.                                          |
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
Collaborators should not directly modify the deployed documentation. Instead, this will be performed as part
of OsiriXgrpc continuous integration. The OsiriXgrpc documentation will be deployed from either the `main` or `dev` 
branches to one of two sites, following a push to the GitHub repository:

| Branch | Site                                                                               |                                                                         |
|--------|------------------------------------------------------------------------------------|-------------------------------------------------------------------------|
| `main` | [https://osirixgrpc.github.io/osirixgrpc](https://osirixgrpc.github.io/osirixgrpc) | All documentation for OsiriXgrpc releases                               |
| `dev`  | [https://osirixgrpc.netlify.app](https://osirixgrpc.netlify.app)                   | Documentation in development mode and for user testing of next release. |

### Suggesting Changes
If you would like to suggest a change to the documentation please let us know through the project 
<a href="https://github.com/osirixgrpc/osirixgrpc/issues"> issue tracker</a>, ensuring you 
choose a `documentation` label for the issue. If you wish to help contribute to the documentation, then please fork the
latest copy of the repository, modify it, and submit a pull request to the main branch. 

## Bug Reporting
If you encounter any bugs with the OsiriXgrpc plugin then please let us know through the 
<a href="https://github.com/osirixgrpc/osirixgrpc/issues"> issue tracker</a>, ensuring you choose a `bug` label.  When 
you raise the issue, please using the relevant template for bugs, which will include the following information:

<ul>
  <li> Is the bug related to the plugin (OsiriXgrpc) or a client issue (pyOsiriX)? </li>
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
user tests. This approach also ensures comprehensive validation through real-world usage scenarios. 

To run automated unit tests:

1. Clone the latest [repository](https://github.com/osirixgrpc/osirixgrpc), or pull changes.
2. Switch to the `dev` branch (`git checkout dev`).
3. Open up OsiriX and move to or create an empty database (no Dicom studies/series displayed).
4. Ensure that an OsiriXgrpc port `50001` is established and running (see [Getting Started](../getting_started.md#server-configuration))
5. Change directory to `tests` (`cd tests` from the main repository).
6. Run the shell script: `bash run_tests.sh`

Please wait while OsiriX runs through all the tests (many screen will open and close). The shell script will indicate 
testing is complete. Unit tests will save results to an output directory on your Desktop `osirixgrpc_tests`. Please
zip this folder and [send it to us](#contact). Contained files do not capture any personal information, other than the 
versions of macOS, OsiriX, and OsiriXgrpc.

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
label, using the `feature_request` issue template.  This includes the following information
<ul>
  <li>To which aspect of OsiriXgrpc is the feature request intended?</li>
  <li>Short description of the new functionality</li>
  <li>Why would this improve the functionality of OsiriXgrpc?</li>
  <li>Have you been using any work-around so far?</li>
  <li>How urgent is the new functionality to you?</li>
  <li>Would you be willing to help develop/test the new functionality?</li>
</ul>

## Issues
Please use the relevant label for each issue that you submit on the GitHub project.

| Label             | Description                                                                                                                                           |
|-------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------|
| `bug`             | If you encounter a bug then please let us know using the provided template. See [Bug Reporting](#bug-reporting) for more information.                 |
| `feature_request` | What else would you like see from OsiriXgrpc? Is there any functionality in OsiriX that you think warrant exposure through API?                       |
| `documentation`   | Tell us how we can improve our [documentation](#documentation). This includes everything from fixing spelling mistakes to improving interpretability. |
| `generic`         | Any other issue you have with OsiriXgrpc.                                                                                                             |


## Contact
| Name                | Contact                      |
|---------------------|------------------------------|
| Matt Blackledge     | matthew.blackledge@icr.ac.uk |
| Timothy Sum Hon Mun | timothy.sumhonmun@icr.ac.uk  |