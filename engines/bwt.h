#pragma once

#include "types.h"

#include <algorithm>
#include <string>

using std::pair;
using std::string;
using std::vector;

namespace engines {

class BurrowsWheelerTransform {
public:
  BurrowsWheelerTransform();
  bwt_result_t transform(vector<char> s);
  vector<char> inverse_transform(bwt_result_t bwt_result);

private:
};

} // namespace engines
