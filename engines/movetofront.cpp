#include "movetofront.h"
#include <algorithm>
#include <iterator>
#include <list>

using std::list;

list<char_t> unique_characters() {
  list<char_t> res;
  for (unsigned int c = 0; c < NUM_CHAR; c++) {
    res.push_back((char_t)c);
  }
  return res;
}

engines::MoveToFrontCoding::MoveToFrontCoding() {}

mtf_code_t engines::MoveToFrontCoding::encode(std::vector<char_t> s) {
  list<char_t> char_list = unique_characters();
  vector<int> res;
  for (char_t c : s) {
    auto it = find(char_list.begin(), char_list.end(), c);
    res.push_back(distance(char_list.begin(), it));
    char_list.erase(it);
    char_list.push_front(c);
  }
  return res;
}

vector<char_t> engines::MoveToFrontCoding::decode(mtf_code_t mtf_result) {
  list<char_t> char_list = unique_characters();
  vector<char_t> res;
  res.reserve(mtf_result.size());
  for (auto i : mtf_result) {
    auto it = char_list.begin();
    std::advance(it, i);
    char_t c = *it;
    char_list.erase(it);
    res.push_back(c);
    char_list.push_front(c);
  }
  return res;
}
