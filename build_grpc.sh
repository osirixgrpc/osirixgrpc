#! /bin/bash

git clone --recurse-submodules -b v1.35.0 https://github.com/grpc/grpc
cd grpc

mkdir -p cmake/build
mkdir install
pushd cmake/build
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=../../install \
      ../..

make -j
make install
popd
