#!/usr/bin/env bash

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
pip install -i https://pypi.org/simple/ --extra-index-url https://test.pypi.org/simple/ osirixgrpc==0.2.1-dev16

# Run pytest on the entire test directory
pytest tests/

# Deactivate the virtual environment
deactivate

# Remove the virtual environment after testing
rm -rf venv