// Server to be used by evaluator.
//
// Usage: TASK_server input_file log_file output_file
//
// To test locally:
//   mkfifo temp
//   ./TASK_server test/TASK.in.1 flog foutput < temp | ./MY_SOLUTION > temp
//

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstdarg>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <unistd.h>

using namespace std;

#ifdef ENGLISH

/******************************* ENGLISH ***************************************/

#define CANNOT_READ_S "Input file error: cannot read the string."
#define SENDING_N "Sending n to contestant program..."
#define WAITING "Waiting for queries..."
#define WA_PREMATURE_TERMINATION "Wrong answer: Contestant program terminated execution without sending a solution."
#define COMMAND_RECEIVED_PRE "Received command '"
#define COMMAND_RECEIVED_POST "' from the contestant program."
#define WA_TOO_MANY_QUERIES "Wrong answer: Contestant program asked too many queries."
#define WA_UNKNOWN_COMMAND "Wrong answer: Unknown command '%s'."
#define WA_CANNOT_READ_L_AND_R "Wrong answer: Cannot read l and r in the %d-th query."
#define WA_INVALID_L_AND_R "Wrong answer: l and r in the %d-th query are not valid."
#define LOG_QUERY  "Query: "
#define LOG_ANSWER ", Answer: "
#define WA_CANNOT_READ_SOLUTION "Wrong answer: Cannot read the solution."
#define CONTESTANT_SOLUTION "Contestant reported solution: "
#define WA_INCORRECT "Wrong answer: the solution is not correct."
#define CORRECT "Correct! Queries used: "

#else

/******************************* CROATIAN ***************************************/

#define CANNOT_READ_S "Neispravna ulazna datoteka: ne mogu procitati string."
#define SENDING_N "Saljem broj n programu..."
#define WAITING "Cekam upite..."
#define WA_PREMATURE_TERMINATION "Krivo rjesenje: Program je zavrsio izvodjenje prije nego sto je poslao rjesenje."
#define COMMAND_RECEIVED_PRE "Primio naredbu '"
#define COMMAND_RECEIVED_POST "' od programa."
#define WA_TOO_MANY_QUERIES "Krivo rjesenje: Program je postavio previse upita."
#define WA_UNKNOWN_COMMAND "Krivo rjesenje: Nepoznata naredba '%s'."
#define WA_CANNOT_READ_L_AND_R "Krivo rjesenje: Ne mogu procitati l i r u %d-tom upitu."
#define WA_INVALID_L_AND_R "Krivo rjesenje: l i r u %d-tom upitu nisu ispravni."
#define LOG_QUERY  "Upit: "
#define LOG_ANSWER ", Odgovor: "
#define WA_CANNOT_READ_SOLUTION "Krivo rjesenje: Ne mogu procitati rjesenje."
#define CONTESTANT_SOLUTION "Natjecatelj kaze da je rjesenje: "
#define WA_INCORRECT "Krivo rjesenje: Rjesenje nije ispravno."
#define CORRECT "Tocno! Broj upita: "

#endif

ifstream finput;   // read from the input file (test case description)
ofstream flog;     // write to an unofficial log for debugging purposes
ofstream foutput;  // write the output, first the score for the test case,
                   // then the output the contestants will see in the system

// assert a condition, awards 0 points if condition fails, same format as a regular printf
void test_condition(bool condition, const char* format, ...) {
  if (!condition) {
    static char dest[1024 * 16];
    va_list argptr;
    va_start(argptr, format);
    vsprintf(dest, format, argptr);
    va_end(argptr);

    foutput << 0 << endl << dest << endl;
    flog << dest << endl;
    exit(0);
  }
}


// https://cp-algorithms.com/string/manacher.html
vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}


// - read the test case from finput,
// - read the contestant's output from cin
// - write to the contestant's input with cout
// - log with flog
// - score and explanation to foutput
void main_problem_interaction() {
  const string QUERY_COMMAND = "?";
  const string END_COMMAND = "!";

  const int QUERY_LIMIT = 3e5;

  string s;
  test_condition(bool(finput >> s), CANNOT_READ_S);

  // Manacher's algorithm
  // d[2i] and d[2i+1] are the increased by 1 lengths of the largest odd- and
  // even-length palindromes centered in i correspondingly
  int n = s.size();
  vector<int> d = manacher(s);
  int sol = *max_element(d.begin(), d.end()) - 1;

  // Start interaction
  int query_count = 0;

  // Send n and t to program.
  flog << SENDING_N << endl;
  flog << "n = " << n << endl;
  cout << n << endl;

  flog << WAITING << endl;
  // Loop.
  while (true) {
    string cmd;
    test_condition(bool(cin >> cmd), WA_PREMATURE_TERMINATION);

    flog << COMMAND_RECEIVED_PRE << cmd << COMMAND_RECEIVED_POST << endl;

    if (cmd == END_COMMAND) {
      break ;
    }

    ++query_count;
    test_condition(query_count <= QUERY_LIMIT, WA_TOO_MANY_QUERIES);
    test_condition(cmd == QUERY_COMMAND, WA_UNKNOWN_COMMAND);

    int l, r;
    test_condition(bool(cin >> l >> r), WA_CANNOT_READ_L_AND_R, query_count);
    test_condition(1 <= l && l <= r && r <= n, WA_INVALID_L_AND_R, query_count);

    // Calculate the result
    int center = (l - 1) + (r - 1), len = r - l + 1;
    int answer = (d[center] > len);

    flog << LOG_QUERY << query_count << ": " << l << " " << r;
    flog << LOG_ANSWER << answer << endl;

    // Send the answer
    cout << answer << endl;
  }

  // Read and check the output
  int contestant_sol;
  test_condition(bool(cin >> contestant_sol), WA_CANNOT_READ_SOLUTION);

  // Check the answers
  flog << CONTESTANT_SOLUTION << contestant_sol << endl;

  test_condition(sol == contestant_sol, WA_INCORRECT);

  foutput << "1" << endl;
  foutput << CORRECT << query_count << endl;

  flog << CORRECT << query_count << endl;
}

int main(int argc, char *argv[])
{
  assert(argc == 4);
  finput.open(argv[1]);
  flog.open(argv[2]);
  foutput.open(argv[3]);
  assert(!finput.fail() && !flog.fail() && !foutput.fail());
  main_problem_interaction();
  return 0;
}
