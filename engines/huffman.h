#pragma once

#include "types.h"

namespace engines {

class HuffmanCoding {
public:
  HuffmanCoding();
  huffman_code_t encode(mtf_code_t mtf_result);
  mtf_code_t decode(huffman_code_t huffman_result);

  static std::vector<char_t> pack_result(std::pair<huffman_code_t, size_t> input);
  static std::pair<huffman_code_t, size_t> unpack_result(std::vector<char_t> raw_content);

private:
};

} // namespace engines
