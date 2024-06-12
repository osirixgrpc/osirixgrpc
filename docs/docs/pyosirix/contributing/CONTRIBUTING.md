# Contributing to pyOsiriX
For general notes on contributing, please see the main [contributing page](../../contributing/CONTRIBUTING.md)
for OsiriXgrpc as this sub-package follows the same processes. Specific instructions for code standards for conding 
conventions are provided below.

## Code Conventions
All code must follow [PEP-8 guidelines](https://peps.python.org/pep-0008/). Docstrings are written using the Google
[docstring standard](https://google.github.io/styleguide/pyguide.html#38-comments-and-docstrings). If in doubt, please
look at existing code and follow the same syntax used, and/or raise an 
[issue](https://github.com/osirixgrpc/osirixgrpc/issues), so we can provide more clarity.

### Package Structure
 - The main pyOsiriX _package_ directory is called `osirix`.
 - Each python file within the package directory constitutes a distinct _module_.

### Module Structure
 - Each module contains _classes_, each providing exposure to a specific aspect of OsiriX.
 - Except for the `osirix.__init__` module, no functions are permitted within modules.
 - Each module should only contain classes that represent the same family of OsiriX objects (e.g. 
   regions-of-interest, viewers, dicoms accessors).

### Class structure
 - All methods must have the decorator `@pyosirix_connection_check`.
 - All class properties (get/set or just get) must include the decorator `@property`. Please ensure
   that attributes are chosen properly.  For example `color` is an attribute. The method `rotate` is not.
 - Please include a docstring for each method. Ideally with an example if deemed necessary.
 - Please name the method appropriately using snake case. For example, if the method in OsiriXgrpc is `ROIRotate`, name
   it `rotate`.

## Contributing pyOsiriX Example Scripts
We welcome example scripts from developers to help showcase its functionality to other users.  We follow a blog-like 
format for examples so that information provided can be quite flexible. However, examples should follow the following 
basic premises:

1. Keep examples simple. We like to ensure that each example performs a specific operation rather than a complex 
   processing pipeline. This ensures that examples remain modular and can be reused within different contexts. If your 
   example contains different steps, think about how these can be broken down and submit as multiple example scripts. 
2. Do not use complex/private datasets. This helps us reduce the need for hosting bespoke datasets within the pyOsiriX 
   project. If certain data is needed (processing PET data for example), try to use public datasets, such as those 
   provided by [The Cancer Imaging Archive](https://www.cancerimagingarchive.net/), and provide the data source in your 
   example description.
3. Follow the [Example Template](#example-template) when structuring the example description.
4. Ensure that the example covers one of the following script categories:

    - __Database__: Performs operations on the OsiriX database.
    - __Image__: Filters images displayed in the 2D viewer windows (including generation of regions of interest).
    - __ROI__: Generates results from existing regions of interest within the 2D image viewer.
    - __VR__: Filters data displayed within the volume render window.

5. Each example should consist of its own directory with the following content:

    - `README.md`: A markdown page consisting of key information about the example, the script type, how it should be 
      run, what data is needed (and the source if applicable), and the expected outcome 
      ([see below](#example-template)).
    - `script.py`: A single python file containing the script that users can run.
    - `screenshot.py`: A helpful, simple image that provides users with a pictorial representation of what the script 
      does.
    - `requirements.txt`: Any python requirements needed by the script. The user should be able to use this to install
      the necessary third-party packages needed to run your file using `pip install -r requirements.txt`. See the 
      [Requirements File Format](https://pip.pypa.io/en/stable/reference/requirements-file-format/) for more 
      information. Please try and minimize the number of requirements (do not just dump your current environment). 
      __Note__: If no additional packages are required, please explicitly state this by providing an
      empty `requirements.txt` file.
    - `additional files` (optional): Any other files that might be needed for running the script. Whilst it is 
      possible to include additional dependent python module files to support you script, it is encouraged not to do 
      this as it violates _premise 1_.

### Example template
This file is also available in the 
[project repository](https://github.com/osirixgrpc/osirixgrpc/tree/dev/docs/docs/pyosirix/examples/template).
```
----8<----
Template/README.md::54
----8<----
```
