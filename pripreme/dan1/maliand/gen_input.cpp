#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> pii;

const int MAXN = 5e5;
const string PROBLEM = "maliand";

mt19937 rng;

int get_rand(int a, int b) { // [a, b]
  return uniform_int_distribution <int> (a, b)(rng);
}

class Test {
  int N, K, L;
public:
  Test(int N, int K, int L) : N(N), K(K), L(L) {}
  bool validate() const {
    if (N < 1 || N > MAXN)
      return false;
    if (K < 0 || K > N)
      return false;
    if (L < 0 || L > N)
      return false;
    return true;
  }
  void output(FILE *out) {
    if (get_rand(0, 1))
      swap(K, L);
    fprintf(out, "%d %d %d\n", N, K, L);
  }
};

Test generate_random(int maxn) {
  int n = get_rand(1, maxn);
  int k = get_rand(0, n);
  int l = get_rand(0, n);
  return Test(n, k, l);
}

vector <Test> dummies;
vector <vector <Test>> subtasks;
vector <int> divisors[MAXN + 5];

vector <int> find_best(int n, int k) {
  vector <pii> all;
  for (int i = 1; i <= n; i++)
    all.push_back({divisors[i].size(), i});
  sort(all.begin(), all.end(), greater <pii> ());
  vector <int> res;
  for (int i = 0; i < k; i++)
    res.push_back(all[i].second);
  return res;
}

vector <int> get_first(vector <int> v, int k) {
  assert(v.size() >= k);
  v.resize(k);
  return v;
}

int random_elt(const vector <int> &v) {
  assert(!v.empty());
  return v[get_rand(0, (int)v.size() - 1)];
}

int get_num(int n, int d) {
  assert(!(n % d));
  n /= d;
  vector <int> coprime;
  for (int i = 1; i <= n; i++)
    if (__gcd(n, i) == 1)
      coprime.push_back(i);
  return d * random_elt(coprime);
}

int get_non_coprime(int n, int bound) {
  vector <int> non_coprime;
  for (int i = 1; i * i <= n && i <= bound; i++)
    if (__gcd(n, i) > 1)
      non_coprime.push_back(i);
  return random_elt(non_coprime);
}

void dummy() {
  dummies.push_back(Test(6, 3, 4));
  dummies.push_back(Test(5, 2, 0));
  dummies.push_back(Test(10, 6, 7));
}

void subtask1() {
  vector <Test> tmp;
  tmp.push_back(Test(7, 1, 4));
  tmp.push_back(Test(8, 2, 3));
  tmp.push_back(Test(9, 7, 4));
  tmp.push_back(Test(10, 6, 8));
  tmp.push_back(Test(11, 0, 6));
  tmp.push_back(Test(12, 8, 5));
  tmp.push_back(Test(12, 4, 6));
  tmp.push_back(Test(12, 8, 9));
  tmp.push_back(Test(13, 7, 8));
  tmp.push_back(Test(13, 7, 6));
  subtasks.push_back(tmp);
}

void subtask2() {
  vector <Test> tmp;
  vector <int> three = find_best(5000, 3);
  for (auto it : three) {
    shuffle(divisors[it].begin(), divisors[it].end(), rng);
    vector <int> gcd_k = get_first(divisors[it], 5);
    shuffle(divisors[it].begin(), divisors[it].end(), rng);
    vector <int> gcd_l = get_first(divisors[it], 5);
    for (int i = 0; i < 5; i++)
      tmp.push_back(Test(it, get_num(it, gcd_k[i]), it - gcd_l[i]));
    for (int i = 0; i < 5; i++)
      tmp.push_back(Test(it, get_non_coprime(it, 1000), it - get_non_coprime(it, 50)));
  }
  subtasks.push_back(tmp);
}

void subtask3() {
  vector <Test> tmp;
  vector <int> six = find_best(500000, 6);
  for (auto it : six) {
    shuffle(divisors[it].begin(), divisors[it].end(), rng);
    vector <int> gcd_k = get_first(divisors[it], 5);
    shuffle(divisors[it].begin(), divisors[it].end(), rng);
    vector <int> gcd_l = get_first(divisors[it], 5);
    for (int i = 0; i < 5; i++)
      tmp.push_back(Test(it, get_num(it, gcd_k[i]), it - gcd_l[i]));
    for (int i = 0; i < 5; i++) 
      tmp.push_back(Test(it, get_non_coprime(it, 1000), it - get_non_coprime(it, 50)));
  }
  subtasks.push_back(tmp);
}

string convert(int num, int len) {
  string res = "";
  while (len--) {
    res += (char)('a' + num % 26);
    num /= 26;
  }
  reverse(res.begin(), res.end());
  return res;
}

void finish() {
  system("rm -f ./test/*");
  for (int i = 0; i < dummies.size(); i++) {
    assert(dummies[i].validate());
    string name = "./test/" + PROBLEM + ".dummy.in." + to_string(i + 1);
    FILE *f = fopen(name.c_str(), "w");
    dummies[i].output(f);
    fclose(f);
  }
  for (int i = 0; i < subtasks.size(); i++) {
    shuffle(subtasks[i].begin(), subtasks[i].end(), rng);
    int idx = 0, letters = ceil(log(subtasks[i].size()) / log(26));
    for (auto test : subtasks[i]) {
      assert(test.validate());
      string name = "./test/" + PROBLEM + ".in." + to_string(i + 1) + convert(idx++, letters);
      FILE *f = fopen(name.c_str(), "w");
      test.output(f);
      fclose(f);
    }
  }
}

void init() {
  for (int i = 1; i <= MAXN; i++)
    for (int j = i; j <= MAXN; j += i)
      divisors[j].push_back(i);
}

int main() {
  rng.seed(459381);
  init();
  dummy();
  subtask1();
  subtask2();
  subtask3();
  finish();
  return 0;
}
