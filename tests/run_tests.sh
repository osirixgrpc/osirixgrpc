#!/usr/bin/env bash

cd integration_tests_osirixgrpc
bash run run_tests.sh
cd ../integration_tests_pyosirix
bash run run_tests.sh