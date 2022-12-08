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

std::vector<char>
engines::HuffmanCoding::pack_result(huffman_code_t huffman_result) {
  // TODO: Think & implement how to pack encoded string with code table
  // into a string
  return std::vector<char>();
}

huffman_code_t
engines::HuffmanCoding::unpack_result(std::vector<char> raw_content) {
  // TODO: Think & implement how to pack encoded string with code table
  // into a string
  return huffman_code_t();
}
