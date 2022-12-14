#pragma once

#include <algorithm>
#include <string>
#include <vector>

#define NUM_CHAR 256

typedef unsigned char char_t;

// Pair of (Transformed string, hint index)
typedef std::pair<std::vector<char_t>, size_t> bwt_result_t;

// List of codes
typedef std::vector<int> mtf_code_t;

// Pair of (Binary string, Code length table)
typedef std::pair<std::vector<bool>, std::vector<int>> huffman_code_t;
