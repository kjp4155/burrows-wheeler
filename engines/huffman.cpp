#include "huffman.h"
#include <cassert>
#include <map>
#include <queue>

using namespace std;

engines::HuffmanCoding::HuffmanCoding() {}

vector<int>
engines::HuffmanCoding::make_code_lengths(const vector<int> &weights) {
  vector<int> nodes;
  vector<int> parent(NUM_CHAR * 2 - 1, -1);
  map<int, int> key_node;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;

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
    parent[n1] = num, parent[n2] = num;
    pq.push(make_pair(c1 + c2, num));
  }

  vector<int> code_lengths(NUM_CHAR);
  for (int i = 0; i < NUM_CHAR; i++) {
    int curr = i;
    int len = 0;
    while (parent[curr] != -1) {
      curr = parent[curr];
      len++;
    }
    code_lengths[i] = len;
    assert(code_lengths[i] <= 256);
  }
  return code_lengths;
}

vector<vector<bool>>
engines::HuffmanCoding::assign_codes(const vector<int> &code_lengths) {
  vector<vector<bool>> codes(NUM_CHAR);
  unsigned int vec = 0U;
  for (int len = 1; len < NUM_CHAR; len++) {
    for (int i = 0; i < NUM_CHAR; i++) {
      if (code_lengths[i] == len) {
        for (int k = code_lengths[i] - 1; k >= 0; k--) {
          codes[i].push_back((vec & (1 << k)) >> k);
        }
        vec++;
      }
    }
    vec <<= 1;
  }
  return codes;
}

huffman_code_t engines::HuffmanCoding::encode(mtf_code_t mtf_result) {
  // move-to-front result consists of integer 0 to NUM_CHAR-1
  vector<int> weights(NUM_CHAR);
  for (auto x : mtf_result) {
    weights[x]++;
  }

  auto code_lengths = make_code_lengths(weights);
  auto codes = assign_codes(code_lengths);

  vector<bool> result;
  for (auto c : mtf_result) {
    for (bool b : codes[c]) {
      result.push_back(b);
    }
  }

  return make_pair(result, code_lengths);
}

mtf_code_t engines::HuffmanCoding::decode(huffman_code_t huffman_result) {
  auto &[bs, code_lengths] = huffman_result;

  auto codes = assign_codes(code_lengths);
  vector<int> char_idx(NUM_CHAR * 2 - 1, -1);
  vector<int> lchild(NUM_CHAR * 2 - 1, -1), rchild(NUM_CHAR * 2 - 1, -1);

  int num_nodes = 1;
  for (int i = 0; i < NUM_CHAR; i++) {
    vector<bool> &code = codes[i];
    unsigned int cur = 0;
    for (bool b : code) {
      if (b && lchild[cur] == -1)
        lchild[cur] = num_nodes++;
      if (!b && rchild[cur] == -1)
        rchild[cur] = num_nodes++;
      cur = b ? lchild[cur] : rchild[cur];
    }
    char_idx[cur] = i;
  }

  vector<int> result;

  unsigned int curn = 0;
  for (bool b : bs) {
    curn = b ? lchild[curn] : rchild[curn];
    if (char_idx[curn] != -1) {
      result.push_back(char_idx[curn]);
      curn = 0;
    }
  }

  return result;
}

vector<char_t> int64_to_chars(size_t x) {
  vector<char_t> result(8, 0);
  for (int k = 7; k >= 0; k--) {
    for (int i = (k + 1) * 8 - 1; i >= k * 8; i--) {
      result[k] |= ((x >> i) & 1) << (i - k * 8);
    }
  }
  return result;
}

vector<char_t> int8_to_chars(int x) {
  assert(x < (1 << 8));
  vector<char_t> result(1, 0);
  for (int k = 0; k >= 0; k--) {
    for (int i = (k + 1) * 8 - 1; i >= k * 8; i--) {
      result[k] |= ((x >> i) & 1) << (i - k * 8);
    }
  }
  return result;
}

size_t chars_to_int64(vector<char_t> &cv, size_t start) {
  size_t result = 0;
  for (int k = 7; k >= 0; k--) {
    for (int i = (k + 1) * 8 - 1; i >= k * 8; i--) {
      result |= (cv[start + k] >> (i - k * 8)) << i;
    }
  }
  return result;
}

int chars_to_int8(vector<char_t> &cv, size_t start) {
  int result = 0;
  for (int k = 0; k >= 0; k--) {
    for (int i = (k + 1) * 8 - 1; i >= k * 8; i--) {
      result |= (cv[start + k] >> (i - k * 8)) << i;
    }
  }
  return result;
}

vector<char_t>
engines::HuffmanCoding::pack_result(pair<huffman_code_t, size_t> input) {

  vector<int> &code_lengths = input.first.second;
  vector<bool> &compressed = input.first.first;

  vector<char_t> result;
  for (char_t c : int64_to_chars(input.second))
    result.push_back(c);

  for (size_t i = 0; i < NUM_CHAR; i++) {
    for (char_t c : int8_to_chars(code_lengths[i]))
      result.push_back(c);
  }

  for (char_t c : int64_to_chars(compressed.size()))
    result.push_back(c);

  int j = 7;
  char_t curc = 0;
  for (bool b : compressed) {
    if (b)
      curc |= (1 << j);
    j -= 1;
    if (j < 0) {
      j = 7;
      result.push_back(curc);
      curc = 0;
    }
  }
  result.push_back(curc);

  return result;
}

pair<huffman_code_t, size_t>
engines::HuffmanCoding::unpack_result(vector<char_t> raw_content) {
  size_t pos = 0;
  size_t hint_idx = chars_to_int64(raw_content, pos);
  pos += 8;

  vector<int> code_lengths(NUM_CHAR);
  vector<bool> compressed;
  size_t sz;

  for (size_t i = 0; i < NUM_CHAR; i++) {
    code_lengths[i] = chars_to_int8(raw_content, pos);
    pos += 1;
  }

  sz = chars_to_int64(raw_content, pos);
  pos += 8;

  for (; pos < raw_content.size(); pos++) {
    for (int j = 7; j >= 0; j--) {
      compressed.push_back((raw_content[pos] >> j) & 1);
      sz--;
      if (sz == 0)
        break;
    }
  }

  return make_pair(huffman_code_t(compressed, code_lengths), hint_idx);
}
