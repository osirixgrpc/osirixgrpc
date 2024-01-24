#! /bin/bash

# Define the name of the temporary conda environment and grpc version
env_name="grpc_build_env"
grpc_version="1.55.0"

# Create the temporary conda environment
conda create --name "$env_name" python=3.8
conda init bash

# Activate the environment
conda activate "$env_name"

# Remove the current grpc clone
# =============================
if [ -d grpc ]; then
    sudo rm -r grpc
fi

# Clone grpc
# ==========
git clone --recurse-submodules -b v"$grpc_version" https://github.com/grpc/grpc

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
make -j 1
make install
popd

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

# Copy the relevant binaries/headers for protocol compilation
# ===========================================================
machine_arch=$(arch)
cp -r install-$machine_arch/bin install
cp -r install-$machine_arch/include install

popd

# Build the cpp definitions
# =========================
mkdir -p cpp
grpc/install/bin/protoc -I protos --grpc_out=cpp --plugin=protoc-gen-grpc=grpc/install/bin/grpc_cpp_plugin osirix.proto
grpc/install/bin/protoc -I protos --cpp_out=cpp osirix.proto roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto

# Build the Python definitions
# ============================
mkdir -p python/osirixgrpc

# see https://stackoverflow.com/questions/72620996/apple-m1-symbol-not-found-cfrelease-while-running-python-app)
export GRPC_PYTHON_LDFLAGS=" -framework CoreFoundation"

# Install packages or perform other actions in the environment
pip install grpcio=="$grpc_version" grpcio-tools=="$grpc_version" --no-binary :all:

# Build the Python definitions
python -m grpc_tools.protoc -I protos --python_out=python/osirixgrpc --grpc_python_out=python/osirixgrpc osirix.proto

python -m grpc_tools.protoc -I protos --python_out=python/osirixgrpc roi.proto roivolume.proto dcmpix.proto vrcontroller.proto viewercontroller.proto browsercontroller.proto dicomimage.proto dicomstudy.proto dicomseries.proto utilities.proto types.proto

# Update the requirements file
echo "grpcio>=$grpc_version" > python/requirements.txt
echo "grpcio-tools>=$grpc_version" >> python/requirements.txt

# Deactivate the environment when done
conda deactivate

# Remove the temporary environment (optional)
conda env remove --name "$env_name" --yes

# Remind user to re-import libraries in XCode
# ===========================================
echo "Finished installation! Don't forget to re-link the compiled libraries (in grpc/install/lib) with the 'Build Phases' stage of XCode project."