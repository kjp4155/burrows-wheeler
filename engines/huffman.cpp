#include <map>
#include <queue>
#include <cassert>
#include "huffman.h"

using namespace std;

engines::HuffmanCoding::HuffmanCoding() {}

vector<int>
engines::HuffmanCoding::make_code_lengths(const vector<int> &weights) {
  vector<int> nodes;
  vector<int> parent;
  map<int, int> key_node;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

  for (int k = 0; k < NUM_CHAR; k++) {
    int w = weights[k];
    int node = nodes.size();
    key_node[k] = node;
    nodes.push_back(w);
    pq.push(make_pair(w, node));
  }

  while (pq.size() >= 2) {
    auto [c1, n1] = pq.top();
    pq.pop();
    auto [c2, n2] = pq.top();
    pq.pop();

    int num = nodes.size();
    nodes.push_back(c1 + c2);
    parent[n1] = num;
    parent[n2] = num;
    pq.push(make_pair(c1 + c2, num));

  }

  vector<int> code_lengths(NUM_CHAR);
  for (int i = 0; i < NUM_CHAR; i++) {
    int curr = i;
    int len = 0;
    while (parent[curr] != curr) {
      curr = parent[curr];
      len++;
    }
    code_lengths[i] = len;
    assert (code_lengths[i] <= 32);
  }
  return code_lengths;
}

vector<unsigned int>
engines::HuffmanCoding::assign_codes(const vector<int> &code_lengths) {
  vector<unsigned int> codes(NUM_CHAR);
  unsigned int vec = 0U;
  for (int len = 1; len < NUM_CHAR; len++) {
    for (int i = 0; i < NUM_CHAR; i++) {
      if (code_lengths[i] == len) {
        codes[i] = vec;
        vec++;
      }
    }
    vec <<= 1;
  }
  return codes;
}

huffman_code_t
engines::HuffmanCoding::encode(mtf_code_t mtf_result) {
  // move-to-front result consists of integer 0 to NUM_CHAR-1
  vector<int> weights(NUM_CHAR);
  for (auto x : mtf_result) {
    weights[x]++;
  }

  auto code_lengths = make_code_lengths(weights);
  auto codes = assign_codes(code_lengths);

  vector<bool> result;
  for (auto c : mtf_result) {
    auto code = codes[c];
    int pos = code_lengths[c] - 1;
    while (pos > 0 && !(code & (1U << pos))) pos--;
    for (; pos >= 0; pos--) {
      result.push_back(bool(code & (1U << pos)));
    }
  }

  return make_pair(result, code_lengths);
}

mtf_code_t
engines::HuffmanCoding::decode(huffman_code_t huffman_result) {
  auto &[bs, code_lengths] = huffman_result;

  auto codes = assign_codes(code_lengths);
  map<unsigned int, int> code_map;
  for(int i = 0; i < NUM_CHAR; i++) {
    code_map[codes[i]] = i;
  }

  vector<int> result;

  unsigned int curr = 0U;
  for(bool b : bs) {
    curr = (curr << 1) | int(b);
    if (code_map.count(curr)) {
      result.push_back(code_map[curr]);
      curr = 0U;
    }
  }
  return result;
}

vector<char_t>
engines::HuffmanCoding::pack_result(pair<huffman_code_t, size_t> input) {
  // TODO: Think & implement how to pack encoded string with code table
  // into a striNg
  return vector<char_t>();
}

pair<huffman_code_t, size_t>
engines::HuffmanCoding::unpack_result(vector<char_t> raw_content) {
  // TODO: Think & implement how to pack encoded string with code table
  // into a string
  return make_pair(huffman_code_t(), 0);
}
