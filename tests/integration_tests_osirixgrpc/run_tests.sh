#!/usr/bin/env bash

# To run:
#  1. Ensure an empty OsiriX database is created and selected.
#  2. Run this script from within the directory it is contained.

# Create a new virtual environment
python -m venv test_osirixgrpc_env

# Activate the virtual environment
source test_osirixgrpc_env/bin/activate

# Install the dependencies
pip install -r requirements.txt

# Clean up previous installations
pip uninstall -y osirixgrpc

# Get the current version
export OSIRIXGRPCVERSION=$(cat ../../VERSION)

# Install the package from the test PYPI
pip install -i https://pypi.org/simple/ --extra-index-url https://test.pypi.org/simple/ osirixgrpc==$OSIRIXGRPCVERSION

# Run pytest on the entire test directory: -s flag ensures print statements are available; -x stops after first fail.
pytest test_browser_controller.py -s -x
pytest test_dicom_image.py -s -x
pytest test_dicom_series.py -s -x

# Deactivate the virtual environment
deactivate

# Remove the virtual environment after testing
rm -rf test_osirixgrpc_env