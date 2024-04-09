#!/bin/bash

# Define and create the output directory
OUTDIR="$HOME/Desktop/osirixgrpc_tests"
if [ ! -d "$OUTDIR" ]; then
    mkdir "$OUTDIR/osirixgrpc"
    mkdir "$OUTDIR/pyosirix"
fi

# Create a new virtual environment
python -m venv test_osirixgrpc_env

# Activate the virtual environment
source test_osirixgrpc_env/bin/activate

# Install the dependencies
pip install -r requirements.txt

# Clean up previous installations
pip uninstall -y osirixgrpc

# Get the current version
export OSIRIXGRPCVERSION=$(cat ../VERSION)

# Install the package from the test PYPI
pip install -i https://pypi.org/simple/ --extra-index-url https://test.pypi.org/simple/ pyosirix==$OSIRIXGRPCVERSION

# Run osirixgrpc tests and append output to the file
echo "Running osirixgrpc tests. Please do not touch OsiriX."
cd integration_tests_osirixgrpc
bash run_tests.sh "$OUTDIR/osirixgrpc" >> "$OUTDIR/osirixgrpc_out.txt" 2>&1

# Run pyosirix tests and append output to the file
echo "Running pyosirix tests. Please do not touch OsiriX."
cd ../integration_tests_pyosirix
bash run_tests.sh "$OUTDIR/pyosirix" >> "$OUTDIR/pyosirix_out.txt" 2>&1

# Merge the output html files
pytest_html_merger -i "$OUTDIR/osirixgrpc" -o "$OUTDIR/osirixgrpc/test_results.html" -t "OsiriXgrpc test results"
pytest_html_merger -i "$OUTDIR/pyosirix" -o "$OUTDIR/pyosirix/test_results.html" -t "pyOsiriX test results"

# Remove the unneeded html reports
rm "$OUTDIR/pyosirix"/pyosirix_report_*.html
rm "$OUTDIR/osirixgrpc"/osirixgrpc_report_*.html

# Deactivate the virtual environment
deactivate

# Remove the virtual environment after testing
cd ../
rm -rf test_osirixgrpc_env

# Tell the user tests have finished.
echo "Tests finished. It is now safe to run OsiriX again."
