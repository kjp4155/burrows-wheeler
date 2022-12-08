#include <string>
#include <vector>

namespace utils {

std::vector<char> read_textfile(std::string fname);
void dump_textfile(std::string fname, std::vector<char> content);

} // namespace utils
