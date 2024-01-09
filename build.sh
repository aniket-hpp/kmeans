set -e

cmake --version
mkdir -p ./build
cmake -S . -B ./build
cd ./build
make

echo "Excutables Directory: ./build/bin"