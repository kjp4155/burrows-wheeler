#pragma once

#include <algorithm>
#include <string>
#include <vector>

#define NUM_CHAR 256

// Pair of (Transformed string, hint index)
typedef std::pair<std::vector<char>, size_t> bwt_result_t;

// List of codes
typedef std::vector<int> mtf_code_t;

// Pair of (Binary string, Code table)
typedef std::pair<std::vector<bool>, std::vector<int>> huffman_code_t;