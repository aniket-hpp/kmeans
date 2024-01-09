set -e

runnr --version
cc --version

data_file="data.txt"
clusters=4

runnr -debug -args "100 10 5 $data_file" random.c
runnr -debug -out kmeans -args "$clusters $data_file" -link m main.c