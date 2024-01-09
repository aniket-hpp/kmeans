set -e

data_file="data.txt"

chmod u+x ./build.sh
./build.sh
./build/bin/random 100 10 5 $data_file
./build/bin/kmeans 3 $data_file