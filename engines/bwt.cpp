#include "bwt.h"

// Slightly modified Manber-Myers' suffix array algorithm to sort rotations.
class RotationArray {
public:
  vector<int> compute(const vector<char_t> s) {
    int size = s.size();
    vector<int> rank(size), _rank(size);
    vector<int> sa(size);
    for (int i = 0; i < size; i++) {
      rank[i] = s[i];
      sa[i] = i;
    }

    for(int k = 1; k < size; k <<= 1) {
      auto cmp = [&](int a, int b) {
        return rank[a] == rank[b] ? rank[(a + k) % size] < rank[(b + k) % size] : rank[a] < rank[b];
      };

      int c = std::max(size, NUM_CHAR);
      vector<int> cnt(c + 1), idx(size);

      fill(cnt.begin(), cnt.end(), 0);
      for (int i = 0; i < size; i++) cnt[rank[(i + k) % size]]++;
      for (int i = 1; i <= c; i++) cnt[i] += cnt[i-1];
      for (int i = size - 1; i >= 0; i--) idx[--cnt[rank[(i + k) % size]]] = i;

      fill(cnt.begin(), cnt.end(), 0);
      for (int i = 0; i < size; i++) cnt[rank[i]]++;
      for (int i = 1; i <= c; i++) cnt[i] += cnt[i-1];
      for (int i = size - 1; i >= 0; i--) sa[--cnt[rank[idx[i]]]] = idx[i];

      int r = _rank[sa[0]] = 0;
      for (int i = 1; i < size; i++) {
        r += cmp(sa[i-1], sa[i]);
        _rank[sa[i]] = r;
      }
      rank.swap(_rank);
      if (r == size-1) break;
    }
    return sa;
  }
};

namespace engines {

BurrowsWheelerTransform::BurrowsWheelerTransform() {}

bwt_result_t
BurrowsWheelerTransform::transform(vector<char_t> s) {
  RotationArray rotationArray;
  auto sa = rotationArray.compute(s);
  int size = s.size();

  vector<char_t> res(size);
  int idx = 0;

  for (int i = 0; i < size; i++) {
    res[i] = s[(sa[i] + size - 1) % size];
    if (sa[i] == 0) idx = i;
  }

  return {res, idx};
}

vector<char_t>
BurrowsWheelerTransform::inverse_transform(bwt_result_t bwt_result) {
  auto &[L, I] = bwt_result;
  int N = L.size();

  // D1
  vector<int> cnt(NUM_CHAR);
  for (int i = 0; i < N; i++) cnt[L[i]]++;
  vector<char_t> F;
  for (int c = 0; c < NUM_CHAR; c++) {
    for (int i = 0; i < cnt[c]; i++) {
      F.push_back((char_t)c);
    }
  }

  // D2
  vector<int> idx(NUM_CHAR);
  for (int i = 1; i < NUM_CHAR; i++) idx[i] = idx[i-1] + cnt[i-1];

  vector<int> T(N);
  for (int i = 0; i < N; i++) T[i] = idx[L[i]]++;

  // D3
  vector<char_t> S(N);
  int Ti_I = I;
  for (int i = 0; i < N; i++) {
    S[N - 1 - i] = L[Ti_I];
    Ti_I = T[Ti_I];
  }

  return S;
}

} // namespace engines



