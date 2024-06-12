#! /bin/bash

# Define the grpc version
GRPC_VERSION="1.55.0"
BUILD_PATH="build"

if ! [ -d grpc ]; then

    brew install cmake

    # Clone grpc
    # ==========
    git clone --recurse-submodules -b v"$GRPC_VERSION" https://github.com/grpc/grpc

    pushd grpc

    # Build/install x86_64 grpc libraries
    # ===================================
    mkdir -p cmake/build-x86_64
    mkdir -p install-x86_64
    pushd cmake/build-x86_64
    cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          -DCMAKE_INSTALL_PREFIX=../../install-x86_64 \
          -DCMAKE_OSX_ARCHITECTURES=x86_64\
          ../..
    make -j 4
    make install
    popd

    # Build/install arm64 grpc libraries
    # ==================================
    mkdir -p cmake/build-arm64
    mkdir -p install-arm64
    pushd cmake/build-arm64
    cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          -DCMAKE_INSTALL_PREFIX=../../install-arm64 \
          -DCMAKE_OSX_ARCHITECTURES=arm64\
          ../..
    make -j 4
    make install
    popd

    # Create universal libraries
    # ==========================
    universal_library_output="install/lib"
    mkdir -p "$universal_library_output"
    for file1 in install-arm64/lib/*.a; do
        # Extract file name without extension
        filename=$(basename "$file1" .a)
        file2="install-x86_64/lib/$filename.a"
        if [ -f "$file2" ]; then
            # Combine the two libraries using lipo and save to the output directory
            lipo -create -output "$universal_library_output/$filename.a" "$file1" "$file2"
            echo "Combined $filename.a"
        else
            echo "Skipping $filename.a, corresponding file not found in install-x86_64"
        fi
    done

    # Copy the relevant binaries/headers
    # ==================================
    machine_arch=$(arch)
    cp -r install-$machine_arch/bin install
    cp -r install-$machine_arch/include install

    popd
fi

# Build the cpp definitions
# =========================
mkdir -p cpp
grpc/install/bin/protoc -I protos --grpc_out=cpp --plugin=protoc-gen-grpc=grpc/install/bin/grpc_cpp_plugin osirix.proto
grpc/install/bin/protoc -I protos --cpp_out=cpp osirix.proto roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto

# Build the Python definitions
# ============================
mkdir -p python/osirixgrpc
grpc/install/bin/protoc -I protos --grpc_python_out=python/osirixgrpc --plugin=protoc-gen-grpc_python=grpc/install/bin/grpc_python_plugin osirix.proto 
grpc/install/bin/protoc -I protos --python_out=python/osirixgrpc osirix.proto roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto
          
# Update the requirements file
# ============================
echo "grpcio>=$GRPC_VERSION" > python/requirements.txt
echo "grpcio-tools>=$GRPC_VERSION" >> python/requirements.txt

# Build project
# =============
mkdir -p src/"$BUILD_PATH"
xcodebuild -project src/osirixgrpc.xcodeproj -scheme osirixgrpc_build -destination "generic/platform=macOS" CONFIGURATION_BUILD_DIR="$BUILD_PATH" build

# Zip plugin
# ==========
cd src/$BUILD_PATH
zip -r osirixgrpc.osirixplugin.zip osirixgrpc.osirixplugin

# Remind user to re-import libraries in XCode: Only needs to be done if grpc version is altered.
echo "Finished installation! Don't forget to re-link the compiled libraries (in grpc/install/lib) with the 'Build Phases' stage of XCode project (if grpc version is changed)."