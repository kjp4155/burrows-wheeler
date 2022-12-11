#include "huffman.h"

engines::HuffmanCoding::HuffmanCoding() {}

huffman_code_t engines::HuffmanCoding::encode(mtf_code_t mtf_result) {
  // TODO: Implement huffman encoding
  return huffman_code_t();
}

mtf_code_t engines::HuffmanCoding::decode(huffman_code_t huffman_result) {
  // TODO: Implement huffman decoding
  return mtf_code_t();
}

std::vector<char_t>
engines::HuffmanCoding::pack_result(std::pair<huffman_code_t, size_t> input) {
  // TODO: Think & implement how to pack encoded string with code table
  // into a string
  return std::vector<char_t>();
}

std::pair<huffman_code_t, size_t>
engines::HuffmanCoding::unpack_result(std::vector<char_t> raw_content) {
  // TODO: Think & implement how to pack encoded string with code table
  // into a string
  return std::make_pair(huffman_code_t(), 0);
}
