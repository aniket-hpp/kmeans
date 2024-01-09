# K-means

Implementation of k-means clustering in C.

Use `random.c` to generate random data-points & `main.c` for clustering them.

### Dependencies:

+ C compiler [gcc/clang]
+ Cmake [optional]
+ runnr [optional]

### Installation:

+ Using Cmake: run the included `build.sh`
```bash
$ chmod u+x ./build.sh
$ ./build.sh
```

To install in `/usr/lcoal/bin`:
```bash
$ cd ./build/
$ sudo make install
```

### Build & Use:

+ For cmake:
``` bash
$ cd ./build/bin
$ ls
kmeans random
```
You will find the executables in `./build/bin`.

+ For runnr:
```bash
$ chmod u+x ./runnr.sh
$ ./runnr.sh
```

+ General:
```bash
$ gcc -Wall -Wextra -Werror main.c -o kmeans -lm
$ gcc -Wall -Wextra -Werror random.c -o random
```

### Usage:

+ Random Data-Points generator
```bash
$ random <max-value> <rows> <cols> <files...
```

Random data-points generator takes atleast 4 arguments.
+ max-value: for setting the maximum value of each data-points
+ rows: no. of rows
+ cols : no. of columns
+ files... : files to save the data-points

+ kmeans
```bash
$ kmeans <clusters> <file>
```

Kmeans takes 2 arguments.
+ clusters: no. of clusters to be made [K]
+ file: takes only one file from which kmeans will read the data-points

### Data-Points file:

Data-Points file is a simple txt files with integer data-points. In this file
columns are separated with only one space ' ', whereas rows are separted in
individual lines. Unnecessary spaces and lines in file will produce bad clusters.

### Test:
+ For Cmake:
```bash
$ chmod u+x ./cmake_test.sh
$ ./cmake_test.sh
```