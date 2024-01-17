#! /bin/bash

# Remove the current grpc clone
# =============================
if [ -d grpc ]; then
    sudo rm -r grpc
fi

# Clone grpc
# ==========
git clone --recurse-submodules -b v1.50.0 https://github.com/grpc/grpc

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

# Build/install arm64 (M1) grpc libraries
# ========================================
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

# TODO: Build for arm64e currently not working.
## Build/install arm64e (M2) grpc libraries
## ========================================
#mkdir -p cmake/build-arm64e
#mkdir -p install-arm64e
#pushd cmake/build-arm64e
#cmake -DgRPC_INSTALL=ON \
#      -DgRPC_BUILD_TESTS=OFF \
#      -DCMAKE_INSTALL_PREFIX=../../install-arm64e \
#      -DCMAKE_OSX_ARCHITECTURES=arm64e\
#      ../..
#make -j 4
#make install
#popd

# Create universal libraries
# ==========================
universal_library_output="install/lib"
mkdir -p "$universal_library_output"

# Loop through files in dir1 (assuming they have the same names in dir2)
for file1 in install-arm64/lib/*.a; do
    # Extract file name without extension
    filename=$(basename "$file1" .a)

    # Check if the corresponding file exists in dir2
    file2="install-x86_64/lib/$filename.a"
    if [ -f "$file2" ]; then
        # Combine the two libraries using lipo and save to the output directory
        lipo -create -output "$universal_library_output/$filename.a" "$file1" "$file2"
        echo "Combined $filename.a"
    else
        echo "Skipping $filename.a, corresponding file not found in $dir2"
    fi
done

# Copy the relevant binaries/headers
# ==================================
machine_arch=$(arch)
cp -r install-$machine_arch/bin install
cp -r install-$machine_arch/include install

popd

# Build the protocol files
# ========================
mkdir -p cpp
mkdir -p python

# Build the cpp definitions
grpc/install/bin/protoc -I protos --grpc_out=cpp --plugin=protoc-gen-grpc=grpc/install/bin/grpc_cpp_plugin osirix.proto

grpc/install/bin/protoc -I protos --cpp_out=cpp osirix.proto roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto

# Build the Python definitions
python -m grpc_tools.protoc -I protos --python_out=python/osirixgrpc --grpc_python_out=python/osirixgrpc osirix.proto

python -m grpc_tools.protoc -I protos --python_out=python/osirixgrpc roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto
