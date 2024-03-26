#!/usr/bin/env bash

# Create a new virtual environment
python -m venv test_pyosirix_env

# Activate the virtual environment
source test_pyosirix_env/bin/activate

# Install the dependencies
pip install -r requirements.txt

# Clean up previous installations
pip uninstall -y osirixgrpc pyosirix

# Get the current version
export PYOSIRIXVERSION=$(cat ../../VERSION)

# Install the package from the test PYPI
pip install -i https://pypi.org/simple/ --extra-index-url https://test.pypi.org/simple/ pyosirix==$PYOSIRIXVERSION

# Run pytest on the entire test directory: -s flag ensures print statements are available; -x stops after first fail.
pytest test_osirix_utilities.py -s -x
pytest test_browser_controller.py -s -x
pytest test_dicom_image.py -s
pytest test_dicom_series.py -s
pytest test_dicom_study.py -s

# Deactivate the virtual environment
deactivate

# Remove the virtual environment after testing
rm -rf test_pyosirix_env