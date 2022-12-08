#pragma once

#include <string>
#include <vector>

namespace utils {

// Simple Argparser based on https://stackoverflow.com/a/868894
class Argparser {
public:
  Argparser(int &argc, char **argv);

  std::string get_string_option(const std::string &option,
                                std::string default_val = "") const;
  double get_double_option(const std::string &option,
                           double default_val = 0.0) const;
  double get_int_option(const std::string &option, int default_val = 0) const;
  bool cmd_option_exists(const std::string &option) const;

private:
  std::vector<std::string> tokens;
};

} // namespace utils