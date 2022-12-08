#include "bwt.h"

namespace engines {

BurrowsWheelerTransform::BurrowsWheelerTransform() {}

bwt_result_t BurrowsWheelerTransform::transform(vector<char> s) {
  // TODO: Implement BWT
  return {s, 0};
}

vector<char>
BurrowsWheelerTransform::inverse_transform(bwt_result_t bwt_result) {
  // TODO: Implement inverse-BWT
  return bwt_result.first;
}

} // namespace engines