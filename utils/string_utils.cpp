#include "string_utils.h"

#include <fstream>
#include <iostream>

namespace utils {

std::vector<unsigned char> read_textfile(std::string fname) {
  std::vector<unsigned char> s;
  unsigned char c;
  std::basic_ifstream<unsigned char> fs(fname, std::ios_base::in | std::ios_base::binary);
  while (fs.get(c))
    s.push_back(c);
  return s;
}

void dump_textfile(std::string fname, std::vector<unsigned char> content) {
  std::basic_ofstream<unsigned char> fs(fname, std::ios_base::out);
  for (unsigned char c : content) {
    fs << c;
  }
}

} // namespace utils
