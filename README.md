# burrows-wheeler

Implementation of Burrows-Wheeler Trasnform


## Build & Run

```
$ mkdir build && cd build
$ cmake .. && make -j
$ ./driver
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
| 1.in          | Lorem Ipsum         | 28 KB    |                     |           |
| 2.in          | Dense File          | 1015 KB  |                     |           |
| 3.in          | Sparse File         | 1015 KB  |                     |           |
| 4.in          | Pride and Prejudice | 701 KB   |                     |           |
| 5.in          | Moby-Dick           | 1227 KB  |                     |           |