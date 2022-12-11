#include <string>
#include <vector>

namespace utils {

std::vector<unsigned char> read_textfile(std::string fname);
void dump_textfile(std::string fname, std::vector<unsigned char> content);

} // namespace utils
