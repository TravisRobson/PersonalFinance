#!/usr/bin/env bash

set -o errexit -o nounset -o pipefail

dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" /dev/null 2>&1 && pwd)"


cd ${dir}/.. # move to PersonalFinance root directory

./tools/bash/clean.sh
./tools/bash/configure.sh --install-prefix ${dir} 
./tools/bash/build.sh
./tools/bash/install.sh

cd demos # move back to demo directory

mkdir -p build
cd build
cmake .. -DPersonalFinance_DIR=lib/cmake/personalFinance -DCMAKE_INSTALL_PREFIX=${dir}
make -j install
