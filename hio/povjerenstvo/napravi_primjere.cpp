#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

string task_name = "povjerenstvo";
string code_name = "povjerenstvo_nezmah";
int subtask_cnt[10];

void call_system (string tmp) {
    int n = tmp.size();
    char char_array[n + 1];
    strcpy(char_array, tmp.c_str());
    system(char_array);
}

void gen_dummy () {
    for (int i = 1; i <= 3; i++) {
        string tmp = "gen.exe DUMMY_" + to_string(i) + " > test/" + task_name + ".dummy.in." + to_string(i);
        call_system(tmp);
    }
}

void add_input (int subtask, string s) {
    string tmp = "gen.exe " + s + " > test/" + task_name + ".in." + to_string(subtask) + string(1, 'a' + subtask_cnt[subtask]);
    subtask_cnt[subtask]++;
    call_system(tmp);
}

void gen_dummy_output () {
    for (int i = 1; i <= 3; i++) {
        string tmp = code_name + ".exe < test/" + task_name + ".dummy.in." + to_string(i) + " > test/" + task_name + ".dummy.out." + to_string(i);
        call_system(tmp);
    }
}

void gen_input () {
    system("rmdir test /s /q");
    system("mkdir test");

    //dummy
    gen_dummy();

    //subtask 1
    add_input(1, "LANAC 1 0");
    add_input(1, "LANCI 1 1");
    add_input(1, "CVOR 1 2");
    add_input(1, "IZOLIRANI 1 3");
    add_input(1, "EDGEVI 1 4");
    add_input(1, "ZVIJEZDA1 1 5");
    add_input(1, "ZVIJEZDA2 1 6");
    add_input(1, "ZVIJEZDA3 1 7");
    add_input(1, "STABLO1 1 8");
    add_input(1, "STABLO2 1 9");
    add_input(1, "STABLO3 1 10");
    add_input(1, "RANDOM_DAG1 1 11");
    add_input(1, "RANDOM_DAG2 1 12");
    add_input(1, "RANDOM_DAG3 1 13");
    add_input(1, "RANDOM_DAG4 1 14");
    add_input(1, "RANDOM_DAG5 1 15");
    add_input(1, "GUSTO_DAG 1 16");
    add_input(1, "POTPUN 1 17");

    //subtask 2
    add_input(2, "LANAC 2 0");
    add_input(2, "ZVIJEZDA1 2 1");
    add_input(2, "ZVIJEZDA2 2 2");
    add_input(2, "STABLO3 2 3");
    add_input(2, "RANDOM_BIPARTITAN1 2 4");
    add_input(2, "RANDOM_BIPARTITAN2 2 5");
    add_input(2, "RANDOM_BIPARTITAN3 2 6");
    add_input(2, "RANDOM_BIPARTITAN4 2 7");
    add_input(2, "RANDOM_BIPARTITAN5 2 8");
    add_input(2, "GUSTO_BIPARTITAN 2 9");
    add_input(2, "SCC_BIPARTITAN 2 10");
    add_input(2, "SCC_BIPARTITAN_STABLO 2 11");
    add_input(2, "CIKLUS 2 12");
    add_input(2, "CIKLUSI 2 13");

    //subtask 3
    add_input(3, "LANAC 3 0");
    add_input(3, "ZVIJEZDA1 3 1");
    add_input(3, "ZVIJEZDA2 3 2");
    add_input(3, "STABLO3 3 3");
    add_input(3, "RANDOM_BIPARTITAN1 3 4");
    add_input(3, "RANDOM_BIPARTITAN2 3 5");
    add_input(3, "RANDOM_BIPARTITAN3 3 6");
    add_input(3, "RANDOM_BIPARTITAN4 3 7");
    add_input(3, "GUSTO_BIPARTITAN 3 8");
    add_input(3, "SCC_BIPARTITAN 3 9");
    add_input(3, "SCC_BIPARTITAN_STABLO 3 10");
    add_input(3, "CIKLUS 3 11");
    add_input(3, "CIKLUSI 3 12");
    add_input(3, "SCC_BIPARTITAN_DAG 3 13");
    add_input(3, "RANDOM_DAG1 3 14");
    add_input(3, "RANDOM_DAG2 3 15");
    add_input(3, "RANDOM_DAG3 3 16");
    add_input(3, "GUSTO_DAG 3 17");

    //subtask 4
    add_input(4, "LANAC 4 0");
    add_input(4, "ZVIJEZDA1 4 1");
    add_input(4, "ZVIJEZDA2 4 2");
    add_input(4, "STABLO3 4 3");
    add_input(4, "RANDOM_BIPARTITAN1 4 4");
    add_input(4, "RANDOM_BIPARTITAN2 4 5");
    add_input(4, "RANDOM_BIPARTITAN3 4 6");
    add_input(4, "RANDOM_BIPARTITAN4 4 7");
    add_input(4, "GUSTO_BIPARTITAN 4 8");
    add_input(4, "SCC_BIPARTITAN 4 9");
    add_input(4, "SCC_BIPARTITAN_STABLO 4 10");
    add_input(4, "CIKLUS 4 11");
    add_input(4, "CIKLUSI 4 12");
    add_input(4, "SCC_BIPARTITAN_DAG 4 13");
    add_input(4, "RANDOM_DAG1 4 14");
    add_input(4, "RANDOM_DAG2 4 15");
    add_input(4, "RANDOM_DAG3 4 16");
    add_input(4, "GUSTO_DAG 4 17");
}

void gen_output () {
    gen_dummy_output();
    for (int i = 1; i < 10; i++) {
        if (subtask_cnt[i] == 0) continue;
        for (int j = 0; j < subtask_cnt[i]; j++) {
            string tmp = code_name + ".exe < test/" + task_name + ".in." + to_string(i) + string(1, 'a' + j);
            tmp += " > test/" + task_name + ".out." + to_string(i) + string(1, 'a' + j);
            call_system(tmp);
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    gen_input();
    gen_output();
    return 0;
}
