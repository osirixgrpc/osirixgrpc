# Contributing to pyOsiriX
For general notes on contributing, please see the main [contributing page](../../contributing/CONTRIBUTING.md) page
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
 - All 