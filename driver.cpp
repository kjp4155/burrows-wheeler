#include <string>

#include "spdlog/spdlog.h"
#include "utils/utils.h"

using std::string;

/*
 * Program options
 */
static string input_fname;
static string output_fname;
static bool run_compression, run_decompression;

void print_usage_exit() {
  spdlog::info("Usage: ./driver [-c|-d] -i <input> -o <output>");
  spdlog::info("");
  spdlog::info("    {:<16s} {:<30s}", "-i=FILENAME",
               "Input file name (required)");
  spdlog::info("    {:<16s} {:<30s}", "-o=FILENAME",
               "Output file name (required)");
  spdlog::info("    {:<16s} {:<30s}", "-c", "Run compression of input file");
  spdlog::info("    {:<16s} {:<30s}", "-d", "Run decompression of input file");
  exit(0);
}

void parse_args(int argc, char **argv) {
  Argparser argparser(argc, argv);

  input_fname = argparser.get_string_option("-i");
  if (input_fname.size() == 0) {
    spdlog::error("Input filename is missing");
    print_usage_exit();
  }

  output_fname = argparser.get_string_option("-o");
  if (input_fname.size() == 0) {
    spdlog::error("Output filename is missing");
    print_usage_exit();
  }

  run_compression = argparser.cmd_option_exists("-c");
  run_decompression = argparser.cmd_option_exists("-d");

  if (run_compression == run_decompression) {
    spdlog::error(
        "Exactly one of -c (compression) or -d (decompression) must be given");
    print_usage_exit();
  }
}

int main(int argc, char **argv) {

  /*
   * Parse arguments
   */
  parse_args(argc, argv);
}