#! /bin/sh

# Build the Python definitions
python -m grpc_tools.protoc -I protos --python_out=python --grpc_python_out=python osirix.proto
python -m grpc_tools.protoc -I protos --python_out=python roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto
