# The test below must be at the top of the file.
"""
# Example Title

Please provide a brief description of what this code is and what
it is trying to achieve.

It will be helpful to add a screenshot to the example:

<img src="figures/logo.png" alt="name of image" width=200px/>

_Contact_: authors.email@address.com

"""
import osirix

def example_function(a: float, b: float) -> float:
    """ Please add docstrings to your functions.

    Params
    ======
        a : float
            Input 1
        b : float
            Input 2

    Returns
    =======
        value : float
    """
    return a + b

class example_class:
    """ It is possible to add classes if required, just ensure documentation.

    Please follow basic PEP coding guidelines.
     - Classes should be in CamelCase
     - methods and functions should be snake_case

    Attributes
    ==========
        att_1 : float
    """

    def example_method(self, a: float) -> float:
        return a * 2
