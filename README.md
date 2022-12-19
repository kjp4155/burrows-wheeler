# burrows-wheeler

Implementation of Burrows-Wheeler Transform


## Build & Run

### Clone this repository

```
$ git clone --recurse-submodules https://github.com/kjp4155/burrows-wheeler
$ cd burrows-wheeler
```

### Make build directory, then build
```
$ mkdir build && cd build
$ cmake .. && make -j
```

### Run 

Compression
```
$ ./driver -c -i ../data/1.in -o 1.compressed
```

Decompression
```
$ ./driver -d -i 1.compressed -o 1.out
```


## Directory Structure

- `utils`: Contains the implementation of utilities such as timer and argparser.

- `engines`: Contains the implementation of core algorithms

    - `bwt.h` & `bwt.cpp`: Implementation of Burrows-Wheeler Transform
    
    - `movetofront.h` & `movetofront.cpp`: Implementation of Move-to-Front coding.
    
    - `huffman.h` & `huffman.cpp`: Implementation of Huffman coding.

- `data`: Contains dataset used to test the implementation (See dataset section)

- `spdlog`: [A logging library](https://github.com/gabime/spdlog).

- `driver.cpp`: Driver program (where `main()` is in).


## Dataset

| **File Name** | **Description**     | **Size** | **Compressed Size** | **Ratio** |
|---------------|---------------------|----------|---------------------|-----------|
| 1.in          | Lorem Ipsum         | 28 KB    |        7.8 KB       |    3.49   |
| 2.in          | Dense File          | 1015 KB  |        276 KB       |    3.67   |
| 3.in          | Sparse File         | 1015 KB  |        785 KB       |    1.29   |
| 4.in          | Pride and Prejudice | 701 KB   |        215 KB       |    3.26   |
| 5.in          | Moby-Dick           | 1227 KB  |        419 KB       |    2.93   |