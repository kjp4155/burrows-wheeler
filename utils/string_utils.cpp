#include "string_utils.h"

#include <fstream>
#include <iostream>

namespace utils {

std::vector<unsigned char> read_textfile(std::string fname) {
  std::vector<unsigned char> s;
  char c;
  std::basic_ifstream<char> fs(fname,
                               std::ios_base::in | std::ios_base::binary);
  while (fs.get(c))
    s.push_back((unsigned char)c);
  return s;
}

void dump_textfile(std::string fname, std::vector<unsigned char> content) {
  std::basic_ofstream<char> fs(fname, std::ios_base::out);
  for (unsigned char c : content) {
    fs << (char)c;
  }
}

} // namespace utils
