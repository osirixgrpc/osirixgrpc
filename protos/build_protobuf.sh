#! /bin/sh

mkdir -p cpp
mkdir -p python

# Build the cpp definitions
../grpc/install/bin/protoc --grpc_out=cpp --plugin=protoc-gen-grpc=../grpc/install/bin/grpc_cpp_plugin osirix.proto

../grpc/install/bin/protoc --cpp_out=cpp osirix.proto roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto

# Build the Python definitions
python -m grpc_tools.protoc -I . --python_out=python/osirix_pb2 --grpc_python_out=python/osirix_pb2 osirix.proto

python -m grpc_tools.protoc -I . --python_out=python/osirix_pb2 roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto
