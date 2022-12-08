#include "string_utils.h"

#include <fstream>
#include <iostream>

namespace utils {

std::vector<char> read_textfile(std::string fname) {
  std::vector<char> s;
  char c;
  std::ifstream fs = std::ifstream(fname, std::ios_base::in);
  while (fs.get(c))
    s.push_back(c);
  return s;
}

void dump_textfile(std::string fname, std::vector<char> content) {
  std::ofstream fs = std::ofstream(fname, std::ios_base::out);
  for (char c : content) {
    fs << c;
  }
}

} // namespace utils