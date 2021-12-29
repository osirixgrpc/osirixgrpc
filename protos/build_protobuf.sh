#! /bin/sh

mkdir -p cpp

# Build the cpp definitions
../grpc/install/bin/protoc --grpc_out=cpp --plugin=protoc-gen-grpc=../grpc/install/bin/grpc_cpp_plugin osirix.proto

../grpc/install/bin/protoc --cpp_out=cpp osirix.proto roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto
