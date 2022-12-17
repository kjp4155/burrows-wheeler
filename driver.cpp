#include <string>
#include <vector>

#include "engines/engines.h"
#include "spdlog/spdlog.h"
#include "utils/utils.h"

using std::pair;
using std::string;
using std::vector;

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
  utils::Argparser argparser(argc, argv);

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

  parse_args(argc, argv);

  engines::BurrowsWheelerTransform bwt_engine;
  engines::MoveToFrontCoding mtf_engine;
  engines::HuffmanCoding huffman_engine;

  if (run_compression) {
    vector<char_t> input_content = utils::read_textfile(input_fname);
    bwt_result_t bwt_result = bwt_engine.transform(input_content);
    mtf_code_t mtf_result = mtf_engine.encode(bwt_result.first);
    huffman_code_t huffman_result = huffman_engine.encode(mtf_result);
    vector<char_t> compressed_content = engines::HuffmanCoding::pack_result(
        make_pair(huffman_result, bwt_result.second));
    utils::dump_textfile(output_fname, compressed_content);

    spdlog::info("Compression done!");
    double compression_ratio =
        (double)input_content.size() / compressed_content.size();
    spdlog::info("Compression ratio: {}", compression_ratio);
  }

  if (run_decompression) {
    vector<char_t> compressed_content = utils::read_textfile(input_fname);
    pair<huffman_code_t, size_t> huffman_result =
        engines::HuffmanCoding::unpack_result(compressed_content);
    mtf_code_t mtf_result = huffman_engine.decode(huffman_result.first);
    vector<char_t> bwt_result = mtf_engine.decode(mtf_result);
    vector<char_t> original_content = bwt_engine.inverse_transform(
        make_pair(bwt_result, huffman_result.second));
    utils::dump_textfile(output_fname, original_content);
    spdlog::info("Decompression done!");
  }
}
