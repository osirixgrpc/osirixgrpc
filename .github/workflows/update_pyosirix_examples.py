""" Used to update the list of pyOsiriX examples as part of the GitHub deploy-docs workflow. """

import os
import argparse
from typing import Dict, Tuple, List

from PIL import Image
import numpy as np


class UpdatePyosirixExamples:
    """ Updates pyOsiriX doc files to incorporate all examples prior to external upload.

    To be used during execution of GitHub actions.  Updates the following files:

        1. mkdocs.yaml: The mkdocs configuration file.
        2. gallery.md: The documentation definition file containing a visual table of examples.
        3. README.md: For each example, the script will be appended as a mkdocs-material snippet.

    """
    def __init__(self, examples_path: str, mkdocs_yaml_path: str, gallery_md_path: str,
                 dry_run: bool = True):
        self._examples_path = examples_path
        self._mkdocs_yaml_path = mkdocs_yaml_path
        self._gallery_md_path = gallery_md_path
        self._dry_run = dry_run

    @property
    def examples_path(self):
        """ The root location of the examples directories. """
        return self._examples_path

    @property
    def mkdocs_yaml_path(self):
        """ The location of the mkdocs configuration file. """
        return self._mkdocs_yaml_path

    @property
    def gallery_md_path(self):
        """ The location of the gallery markdown definition file. """
        return self._gallery_md_path

    @property
    def dry_run(self):
        """ Whether to perform a dry run.  If True, files are not affected, results are printed. """
        return self._dry_run

    @property
    def short_description_tag(self) -> str:
        """ The tag used for short descriptions. """
        return "<!-- shortdesc -->"

    @property
    def readme_filename(self) -> str:
        """ The expected name of the README file. """
        return "README.md"

    @property
    def script_filename(self) -> str:
        """ The expected name of the script file. """
        return "script.py"

    @property
    def screenshot_filename(self) -> str:
        """ The expected name of the screenshot file. """
        return "screenshot.png"

    @property
    def requirements_filename(self) -> str:
        """ The expected name of the requirements file. """
        return "requirements.txt"

    @property
    def image_resolution(self) -> Tuple[int, int]:
        """ The expected resolution (columns, rows) of the screenshot file. """
        return 800, 600

    @property
    def mkdocs_yaml_examples_tag(self) -> str:
        """ What we will search for and replace in the mkdocs.yaml file. """
        return "      - Gallery: pyosirix/examples/gallery.md"

    @property
    def mkdocs_yaml_examples_tag_leading_blanks(self) -> int:
        """ The number of leading blanks in the mkdocs yaml tag. """
        return self.count_leading_blanks(self.mkdocs_yaml_examples_tag)

    @property
    def gallery_md_tag(self) -> str:
        """ What we will search for and replace in the gallery.md file. """
        return "  </tr>"

    @staticmethod
    def count_leading_blanks(s: str) -> int:
        """ Counts the number of leading blank spaces in a string.

        Args:
            s (str): The string to check.

        Returns:
            int: The number of leading blank spaces.
        """
        return len(s) - len(s.lstrip(' '))

    def check_valid_example_requirements(self, requirements_path:str) -> Tuple[bool, str]:
        """ Check that an example requirements.txt file is valid.

        Checks:
            1. The file exists.
            2. It has the right filename.

        Args:
            requirements_path (str): The path to the requirements.txt file.

        Returns:
              bool: Whether the requirements file is valid.
              str: A comment about why there was a failure (empty if not used).
        """
        if not os.path.exists(requirements_path):
            return False, "No requirements.txt at specified location."

        if not os.path.basename(requirements_path) == self.requirements_filename:
            return False, f"Invalid filename {requirements_path}"

        return True , ""

    def check_valid_example_readme(self, readme_path: str) -> Tuple[bool, str]:
        """ Check that an example README.md file is valid.

        Checks:
            1. The file exists.
            2. It has the right filename.
            3. The tag for the short description exists.
            4. There is at least 1 category defined.

        Args:
            readme_path (str): The path to the README.md file.

        Returns:
              bool: Whether the README is valid.
              str: A comment about why there was a failure (empty if not used).
        """
        if not os.path.exists(readme_path):
            return False, "No README.md at specified location."

        if not os.path.basename(readme_path) == self.readme_filename:
            return False, f"Invalid filename {readme_path}"

        # Check the author has provided a short description
        with open(readme_path, "r") as fhandle:
            content = fhandle.read()
            if self.short_description_tag not in content:
                return False, "Invalid README file - no short description found."

        # Check for at least one category
        categories = self.categories_for_readme(readme_path)
        if len(categories) == 0:
            return False, "Invalid README file - no categories found."

        return True, ""

    def check_valid_example_screenshot(self, screenshot_path: str) -> Tuple[bool, str]:
        """ Check that an example screenshot.png file is valid.

        Checks:
            1. The file exists.
            2. It has the right filename.
            3. The image has size 800 x 600.

        Args:
            screenshot_path (str): The path to the screenshot.png file.

        Returns:
              bool: Whether the screenshot is valid.
              str: A comment about why there was a failure (empty if not used).

        """
        if not os.path.exists(screenshot_path):
            return False, "Could not find a screenshot.png file within the example directory."

        if not os.path.basename(screenshot_path) == self.screenshot_filename:
            return False, f"Invalid filename {screenshot_path}"

        image = Image.open(screenshot_path)
        cols, rows = image.size
        if not rows == 400 and not cols == 800:
            return False, f"Bad screenshot resolution rows = {rows}, cols = {cols}"

        return True, ""

    def check_valid_example_script(self, script_path: str) -> Tuple[bool, str]:
        """ Check that an example scripy.py file is valid.

        Checks:
            1. The file exists.
            2. It has the right filename.

        Args:
            script_path (str): The path to the screenshot.png file.

        Returns:
              bool: Whether the script is valid.
              str: A comment about why there was a failure (empty if not used).

        """
        if not os.path.exists(script_path):
            return False, "Could not find a script.py file within the example directory."

        if not os.path.basename(script_path) == self.script_filename:
            return False, f"Invalid filename {script_path}"

        return True, ""

    def check_valid_template_path(self, path: str) -> Tuple[bool, str]:
        """ Check whether an example directory is complete.

        Checks:
            1. Presence of README.md
            2. Presence of screenshot.png (at resolution 800 x 400)
            3. Presence of script.py
            4. Presence of requirements.txt
            5. Presence of the tag for the short description within README.md
            6. No additional files/directories other than "additional files"

        Args:
            path (str): The template directory to check.

        Returns:
            bool: Whether the template structure is valid.
            str: A comment about why there was a failure (empty if not used).
        """
        # Check it is a valid directory
        if not os.path.isdir(path):
            return False, f"Path {path} is not a directory."

        # Check README file
        readme_path = os.path.join(path, "README.md")
        bok, message = self.check_valid_example_readme(readme_path)
        if not bok:
            return False, message

        # Check screenshot file
        screenshot_path = os.path.join(path, "screenshot.png")
        bok, message = self.check_valid_example_screenshot(screenshot_path)
        if not bok:
            return False, message

        # Check there is a script.py file
        script_path = os.path.join(path, "script.py")
        bok, message = self.check_valid_example_script(script_path)
        if not bok:
            return False, message

        # Check there is a requirements.txt file
        requirements_path = os.path.join(path, "requirements.txt")
        bok, message = self.check_valid_example_script(script_path)
        if not bok:
            return False, message

        # Check there are no erroneous files/folders
        erroneous_files = []
        for f in os.listdir(path):
            if f not in ["script.py",
                         "screenshot.png",
                         "README.md",
                         "requirements.txt",
                         "additional files"]:
                erroneous_files.append(f)
        if len(erroneous_files) > 0:
            return False, f"Erroneous files detected: {erroneous_files}"

        return True, ""

    def example_names(self) -> Dict:
        """ Return the names of all examples within the pyOsiriX documentation.

        Returns:
            Dict: The dictionary of pyOsiriX examples using format: {name (str): path (str)}.
        """
        names = {}
        for name in os.listdir(self.examples_path):
            name_path = os.path.join(self.examples_path, name)
            if os.path.isdir(name_path):
                bok, message = self.check_valid_template_path(name_path)
                if bok:
                    names[name] = name_path
                else:
                    print(f"Invalid example path {name_path}! Reason: {message}")
        return names

    def short_description_for_readme(self, readme_path: str) -> str:
        """ Extract the short description from the README file.

        Args:
            readme_path (str): The path to the README file.

        Returns:
            str: The short description defined by the author. Empty string if none found.
        """
        bok, message = self.check_valid_example_readme(readme_path)
        if not bok:
            return ""

        description = ""
        with open(readme_path, "r") as fhandle:
            lines = fhandle.readlines()
            for line in lines:
                if self.short_description_tag in line and description == "":
                    description = line[len(self.short_description_tag)::].replace("\n", "").strip()
        return description

    @staticmethod
    def categories_for_readme(readme_path: str) -> List:
        """ Extract the categories defined for the README file.

        Args:
            readme_path (str): The path to the README file.

        Returns:
            List: Contains the list of img.shields.io badges for the example.
        """

        def __html_spice__(url: str, alt: str = "") -> str:
            return f"<img alt='{alt}' src='{url}'>"

        categories = []
        with open(readme_path, "r") as fhandle:
            contents = fhandle.read()

        surl = "https://img.shields.io/badge"
        if f"{surl}/Database-blue" in contents:
            categories.append(__html_spice__(f"{surl}/Database-blue", "Database"))
        if f"{surl}/Image-green" in contents:
            categories.append(__html_spice__(f"{surl}/Image-green", "Image Viewer"))
        if f"{surl}/ROI-purple" in contents:
            categories.append(__html_spice__(f"{surl}/ROI-purple", "Region of Interest"))
        if f"{surl}/VR-red" in contents:
            categories.append(__html_spice__(f"{surl}/VR-red", "Volume Render Viewer"))

        return categories

    def mkdocs_yaml_replacement_string(self, names: Dict) -> str:
        """ Create string to replace what is present in the mkdocs yaml.

        Args:
            names (Dict): The discovered names of the examples (see `example_names`)

        Returns:
            str: The replacement string.
        """
        ordered_names = np.sort([name for name in names.keys()])
        replacement = self.mkdocs_yaml_examples_tag
        for name in ordered_names:
            replacement = replacement +\
                          f"\n{' ' * self.mkdocs_yaml_examples_tag_leading_blanks}- {name}:" +\
                          f" pyosirix/examples/{names[name].split('/')[-1]}/{self.readme_filename}"
        return replacement

    def updated_mkdocs_yaml_contents(self, names: Dict) -> str:
        """ Update the mkdocs.yaml file to add doc menu items for all contained examples.

        Args:
            names (Dict): The discovered names of the examples (see `example_names`)

        Returns:
            str: The new contents of the mkdocs yaml file.
        """
        with open(self.mkdocs_yaml_path, "r") as fhandle:
            contents = fhandle.read()
            contents = contents.replace(self.mkdocs_yaml_examples_tag,
                                        self.mkdocs_yaml_replacement_string(names))
        return contents

    def gallery_replacement_string(self, names: Dict) -> str:
        """ Create string to replace what is present in the example gallery file.

        Args:
            names (Dict): The discovered names of the examples (see `example_names`)

        Returns:
            str: The replacement string.
        """
        ordered_names = np.sort([name for name in names.keys()])
        replacement = self.gallery_md_tag
        for name in ordered_names:
            readme_path = os.path.join(names[name], self.readme_filename)
            description = self.short_description_for_readme(readme_path)
            categories = "<br>".join([c for c in self.categories_for_readme(readme_path)])
            replacement = replacement +\
                  f"\n  <tr>" +\
                  f"\n    <td><a href='{name.lower()}'>{name}</a></td>" +\
                  f"\n    <td>{description}</td>" +\
                  f"\n    <td>{categories}</td>" +\
                  f"\n    <td><img src='{name}/screenshot.png' alt='{name}' width='400'></td>" +\
                  f"\n  </tr>"
        return replacement

    def updated_gallery_md_contents(self, names: Dict) -> str:
        """ Update the gallery.md file to include all examples.

        Args:
            names (Dict): The discovered names of the examples (see `example_names`)

        Returns:
            str: The new contents of the gallery.md file.
        """
        with open(self.gallery_md_path, "r") as fhandle:
            contents = fhandle.read()
            contents = contents.replace(self.gallery_md_tag,
                                        self.gallery_replacement_string(names))
        return contents

    @staticmethod
    def readme_append_string(readme_path: str) -> str:
        """ Create string to append the script code to the end of a README file.

        Args:
            readme_path (str): The path to the example README.md file.

        Returns:
            str: The string to append to the end of the readme.
        """
        append_str = f"\n" +\
                     f"## Script\n" +\
                     f"```python\n" +\
                     f"----8<----\n" +\
                     f"{readme_path.split('/')[-2]}/script.py\n" +\
                     f"----8<----\n" +\
                     f"```\n"
        return append_str

    @staticmethod
    def readme_append_requirements(requirements_path: str) -> str:
        """ Create string to append the requirements to the end of a README file.

        Args:
            requirements_path (str): The path to the example requirements.txt file.

        Returns:
            str: The string to append to the end of the readme.
        """
        append_str = f"\n" + \
                     f"## Requirements\n" + \
                     f"```python\n" + \
                     f"----8<----\n" + \
                     f"{requirements_path.split('/')[-2]}/requirements.txt\n" + \
                     f"----8<----\n" + \
                     f"```"
        return append_str

    def updated_readme_contents(self, readme_path: str) -> str:
        """ Update the README.md file to include the python script at the end.

        Args:
            readme_path (str): The path to the example README.md file.

        Returns:
            str: The new contents of the README.md file.
        """
        with open(readme_path, "r") as fhandle:
            contents = fhandle.read()
            contents = contents + self.readme_append_string(readme_path)
            contents = contents + self.readme_append_requirements(readme_path)
        return contents

    def run(self):
        """ Run the script.
        """
        # Obtain a list of examples within the docs
        names = self.example_names()

        # Update the gallery
        updated_gallery_md_contents = self.updated_gallery_md_contents(names)
        if not self.dry_run:
            with open(self.gallery_md_path, "w") as fhandle:
                fhandle.write(updated_gallery_md_contents)
        else:
            print(f"=======================")
            print(f"New gallery.md contents")
            print(f"=======================")
            print(updated_gallery_md_contents)

        # Update the mkdocs config file
        updated_mkdocs_yaml_contents = self.updated_mkdocs_yaml_contents(names)
        if not self.dry_run:
            with open(self.mkdocs_yaml_path, "w") as fhandle:
                fhandle.write(updated_mkdocs_yaml_contents)
        else:
            print(f"========================")
            print(f"New mkdocs.yaml contents")
            print(f"========================")
            print(updated_mkdocs_yaml_contents)

        # Update the README files for each example
        for name, path in names.items():
            readme_path = os.path.join(path, self.readme_filename)
            updated_readme_contents = self.updated_readme_contents(readme_path)
            if not self.dry_run:
                with open(readme_path, "w") as fhandle:
                    fhandle.write(updated_readme_contents)
            else:
                print(f"{'=' * (20 + len(name))}")
                print(f"New {name} README contents")
                print(f"{'=' * (20 + len(name))}")
                print(updated_readme_contents)


def parse_args():
    parser = argparse.ArgumentParser(description="Update document files with examples.")
    parser.add_argument("--dry-run", action="store_true", help="Whether to just perform a dry run")
    return parser.parse_args()


if __name__ == "__main__":
    args = parse_args()
    upe = UpdatePyosirixExamples(examples_path="docs/docs/pyosirix/examples",
                                 mkdocs_yaml_path="docs/mkdocs.yaml",
                                 gallery_md_path="docs/docs/pyosirix/examples/gallery.md",
                                 dry_run=args.dry_run)
    upe.run()
