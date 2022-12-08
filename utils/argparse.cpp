#include "argparse.h"

#include <algorithm>

Argparser::Argparser(int &argc, char **argv) {
  for (int i = 1; i < argc; ++i)
    this->tokens.push_back(std::string(argv[i]));
}

std::string Argparser::get_string_option(const std::string &option,
                                         std::string default_val) const {
  std::vector<std::string>::const_iterator itr;

  itr = std::find(this->tokens.begin(), this->tokens.end(), option);
  if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
    return *itr;
  }
  return default_val;
}

double Argparser::get_double_option(const std::string &option,
                                    double default_val) const {
  std::string opt = get_string_option(option, "");
  if (opt.size() == 0)
    return default_val;
  return stod(opt);
}

double Argparser::get_int_option(const std::string &option,
                                 int default_val) const {
  std::string opt = get_string_option(option, "");
  if (opt.size() == 0)
    return default_val;
  return stoi(opt);
}

bool Argparser::cmd_option_exists(const std::string &option) const {
  return std::find(this->tokens.begin(), this->tokens.end(), option) !=
         this->tokens.end();
}