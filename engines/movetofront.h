#pragma once

#include <vector>
#include "types.h"

using std::vector;

namespace engines {

class MoveToFrontCoding {
public:
  MoveToFrontCoding();
  mtf_code_t encode(vector<char_t> s);
  vector<char_t> decode(mtf_code_t mtf_result);

private:
};

} // namespace engines
