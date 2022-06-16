// Checker to be used by HSIN evaluator.
//
// This should *not* be used for CMS!
//
// Usage: [checker] [input] [official_output] [contestant_output] [configuration_file (optional)]
//
// Output (stdout):
//     Score.
//     Textual description (optional).
//
// Score should be output as an integer (0 or 1), or a real (between 0.0 and
// 1.0) or a fraction (between `0/1` and `1/1`, you don't have to
// simplify/reduce the fraction).

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <ccomplex>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;
typedef long double ld;
typedef vector <int> vi;
typedef complex <ld> comp;

const ld PI = acos(-1.0);

// Use one of the following functions to output the points to the contestant.
// The first accepts a double and outputs it.
// The second accepts a fraction and outputs it.

void finish(double score) {
  cout << score << endl;
  exit(0);
}

void finish(llint points_awarded, llint points_max) {
  cout << points_awarded << "/" << points_max << endl;
  exit(0);
}

void fft(vector <comp> &v, bool invert) {
  int n = v.size();
  if (n == 1)
    return;
  vector <comp> even(n / 2), odd(n / 2);
  for (int i = 0; i < n / 2; i++) {
    even[i] = v[2 * i];
    odd[i] = v[2 * i + 1];
  }
  fft(even, invert);
  fft(odd, invert);
  ld angle = 2 * PI / n * (invert ? -1 : 1);
  comp pot(1), omega(cos(angle), sin(angle));
  for (int i = 0; i < n / 2; i++) {
    v[i] = even[i] + pot * odd[i];
    v[i + n / 2] = even[i] - pot * odd[i];
    if (invert) {
      v[i] /= 2;
      v[i + n / 2] /= 2;
    }
    pot *= omega;
  }
}

vi convolution(const vi &x, const vi &y) {
  vector <comp> fx(x.begin(), x.end());
  vector <comp> fy(y.begin(), y.end());
  int n = 1;
  while (n < x.size() + y.size())
    n *= 2;
  fx.resize(n);
  fy.resize(n);
  fft(fx, false);
  fft(fy, false);
  for (int i = 0; i < n; i++)
    fx[i] *= fy[i];
  fft(fx, true);
  vi res(n);
  for (int i = 0; i < n; i++)
    res[i] = round(fx[i].real());
  return res;
}

vi convert(const string &s) {
  vi res;
  for (auto it : s)
    res.push_back(it - '0');
  return res;
}

int get_count(const string &s, char c) {
  return count(s.begin(), s.end(), c);
}

bool check_second_part(int n, int k, int l, int official_val, string a, string b) {
  if (a.size() != n || b.size() != n)
    return false;
  if (get_count(a, '1') != k || get_count(a, '0') != n - k)
    return false;
  if (get_count(b, '1') != l || get_count(b, '0') != n - l)
    return false;
  reverse(a.begin() + 1, a.end());
  vi cnt(n), diff_conv = convolution(convert(a), convert(b));
  for (int i = 0; i < diff_conv.size(); i++) 
    cnt[i % n] += diff_conv[i];
  return *max_element(cnt.begin(), cnt.end()) == official_val;
}

/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */
void checker(ifstream &fin, ifstream &foff, ifstream &fout) {
  // Read official input
  int N, K, L;
  if (!(fin >> N)) finish(0);
  if (!(fin >> K)) finish(0);
  if (!(fin >> L)) finish(0);
  
  // Read official output
  int official_output_val;
  if (!(foff >> official_output_val)) finish(0);

  // Read contestant's output
  int c_output;
  if (!(fout >> c_output)) finish(0);

  string c_recon1, c_recon2;
  if (!(fout >> c_recon1))
    finish(0);
  if (!(fout >> c_recon2))
    finish(0);
  
  string excess;
  if (fout >> excess)
    finish(0);

  bool first_part = (official_output_val == c_output);
  bool second_part = check_second_part(N, K, L, official_output_val, c_recon1, c_recon2);

  if (first_part && second_part) {
    finish(1.0);
  } else if (first_part) {
    finish(0.2);
  } else {
    finish(0.0);
  }

  // The function MUST terminate before this line via finish()!
}

int main(int argc, char *argv[]) {
  assert(argc >= 4);

  ifstream fin(argv[1]);
  ifstream foff(argv[2]);
  ifstream fout(argv[3]);

  // Optional, uncomment when using the configuration file for additional
  // information about the testcase.
  // ifstream fconf(argv[4]);

  assert(!fin.fail() && !fout.fail());
  checker(fin, foff, fout);

  // Checker must terminate via finish() before exiting!
  assert(false);

  return 0;
}
