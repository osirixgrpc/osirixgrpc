#!/usr/bin/env bash

# This will run all pyosirix unit tests.  It assumes that a single study exists within
# the OsiriX database, with no ROIs present. The study should be that provided within the
# test data for the project.
#
# To run, use the nomenclature:
#    bash run_tests.sh "/path/to/output"

# The output directory provided by the user as first argument.
outdir="${1:-.}"  # Default is current directory ('.')

# Run pytest on the entire test directory: -s flag ensures print statements are available; -x stops after first fail.
pytest test_osirix_utilities.py -s -x --html="$outdir/pyosirix_report_osirix_utilities.html" --self-contained-html --color=yes
pytest test_browser_controller.py -s -x --html="$outdir/pyosirix_report_browser_controller.html" --self-contained-html --color=yes
pytest test_dicom_image.py -s --html="$outdir/pyosirix_report_dicom_image.html" --self-contained-html --color=yes
pytest test_dicom_series.py -s --html="$outdir/pyosirix_report_dicom_series.html" --self-contained-html --color=yes
pytest test_dicom_study.py -s --html="$outdir/pyosirix_report_dicom_study.html" --self-contained-html --color=yes
pytest test_viewer_controller.py -s --html="$outdir/pyosirix_report_viewer_controller.html" --self-contained-html --color=yes
pytest test_dcm_pix.py -s --html="$outdir/pyosirix_report_dcm_pix.html" --self-contained-html --color=yes
pytest test_roi.py -s --html="$outdir/pyosirix_report_roi.html" --self-contained-html --color=yes
pytest test_vr_controller.py -s --html="$outdir/pyosirix_report_vr_controller.html" --self-contained-html --color=yes
pytest test_roi_volume.py -s --html="$outdir/pyosirix_report_roi_volume.html" --self-contained-html --color=yes
pytest cleanup.py -s --html="$outdir/pyosirix_report_cleanup.html" --self-contained-html --color=yes