#!/bin/bash

# Define the grpc version
GRPC_VERSION="1.74.0"
BUILD_PATH="build"

if ! [ -d grpc ]; then

    # Install dependencies
    brew install cmake protobuf zlib c-ares

    # Clone grpc with submodules
    git clone --recurse-submodules -b v"$GRPC_VERSION" https://github.com/grpc/grpc

    pushd grpc

    # Build/install grpc libraries (universal arm64+x86_64)
    # ====================================================
    mkdir -p cmake/build-universal
    mkdir -p install-universal
    pushd cmake/build-universal

    cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          -DgRPC_ZLIB_PROVIDER=package \
          -DCMAKE_INSTALL_PREFIX=../../install-universal \
          -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64" \
          -DgRPC_CARES_PROVIDER=package \
          ../..

    make -j 4
    make install
    popd

    # Copy binaries/headers
    cp -r install-universal/bin install
    cp -r install-universal/include install
    cp -r install-universal/lib install

    popd
fi

# Build the cpp definitions
mkdir -p cpp
grpc/install-universal/bin/protoc -I protos --grpc_out=cpp --plugin=protoc-gen-grpc=grpc/install-universal/bin/grpc_cpp_plugin osirix.proto
grpc/install-universal/bin/protoc -I protos --cpp_out=cpp osirix.proto roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto

# Build the Python definitions
mkdir -p python/osirixgrpc
grpc/install-universal/bin/protoc -I protos --grpc_python_out=python/osirixgrpc --plugin=protoc-gen-grpc_python=grpc/install-universal/bin/grpc_python_plugin osirix.proto
grpc/install-universal/bin/protoc -I protos --python_out=python/osirixgrpc osirix.proto roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto

# Update the requirements file
echo "grpcio>=$GRPC_VERSION" > python/requirements.txt
echo "grpcio-tools>=$GRPC_VERSION" >> python/requirements.txt

# Build project
mkdir -p src/"$BUILD_PATH"
xcodebuild -project src/osirixgrpc.xcodeproj -scheme osirixgrpc_build -destination "generic/platform=macOS" CONFIGURATION_BUILD_DIR="$BUILD_PATH" build

# Zip plugin
cd src/$BUILD_PATH
zip -r osirixgrpc.osirixplugin.zip osirixgrpc.osirixplugin

echo "Finished build!"
