#pragma once

#include "types.h"

namespace engines {

class HuffmanCoding {
public:
  HuffmanCoding();
  huffman_code_t encode(mtf_code_t mtf_result);
  mtf_code_t decode(huffman_code_t huffman_result);

  static std::vector<char> pack_result(huffman_code_t huffman_result);
  static huffman_code_t unpack_result(std::vector<char> raw_content);

private:
};

} // namespace engines