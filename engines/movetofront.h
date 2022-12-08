#pragma once

#include "types.h"

namespace engines {

class MoveToFrontCoding {
public:
  MoveToFrontCoding();
  mtf_code_t encode(bwt_result_t bwt_result);
  bwt_result_t decode(mtf_code_t mtf_result);

private:
};

} // namespace engines