#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

string task_name = "m";
string code_name = "nezmah";
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
    add_input(1, "MALI 1 0");
    add_input(1, "EDGE 1 1");
    add_input(1, "DUPLI 1 2");
    add_input(1, "PRAZAN 1 3");
    add_input(1, "POTPUN 1 4");
    add_input(1, "STABLO 1 5");
    add_input(1, "CIKLUS 1 5");
    add_input(1, "RANDOM_100 1 6");
    add_input(1, "RANDOM_100 1 7");
    add_input(1, "RANDOM_1000 1 8");
    add_input(1, "RANDOM_1000 1 9");
    add_input(1, "RANDOM_10000 1 10");
    add_input(1, "RANDOM_10000 1 11");
    add_input(1, "RANDOM_100000 1 12");
    add_input(1, "RANDOM_100000 1 13");
    add_input(1, "RANDOM_MAX 1 14");
    add_input(1, "RANDOM_MAX 1 15");
    add_input(1, "TLE_1 1 16");
    add_input(1, "TLE_2 1 17");
    add_input(1, "PUNO 1 18");
    add_input(1, "STABLO2 1 19");
    add_input(1, "LANAC2 1 20");

    //subtask 2
    add_input(2, "DUPLI 2 0");
    add_input(2, "PRAZAN 2 1");
    add_input(2, "TLE_1 2 2");
    add_input(2, "STABLO2 2 3");
    add_input(2, "STABLO2 2 4");
    add_input(2, "STABLO2 2 5");
    add_input(2, "STABLO2 2 6");
    add_input(2, "STABLO2 2 7");
    add_input(2, "STABLO2 2 8");
    add_input(2, "STABLO2 2 9");
    add_input(2, "LANAC2 2 10");

    //subtask 3
    add_input(3, "MALI 3 0");
    add_input(3, "EDGE 3 1");
    add_input(3, "DUPLI 3 2");
    add_input(3, "PRAZAN 3 3");
    add_input(3, "POTPUN 3 4");
    add_input(3, "STABLO 3 5");
    add_input(3, "CIKLUS 3 5");
    add_input(3, "RANDOM_100 3 6");
    add_input(3, "RANDOM_100 3 7");
    add_input(3, "RANDOM_100 3 8");
    add_input(3, "RANDOM_100 3 9");
    add_input(3, "RANDOM_100 3 10");
    add_input(3, "RANDOM_100 3 11");
    add_input(3, "RANDOM_100 3 12");
    add_input(3, "RANDOM_100 3 13");
    add_input(3, "RANDOM_100 3 14");
    add_input(3, "RANDOM_100 3 15");
    add_input(3, "TLE_1 3 16");
    add_input(3, "TLE_2 3 17");
    add_input(3, "PUNO 3 18");
    add_input(3, "STABLO2 3 19");
    add_input(3, "LANAC2 3 20");

    //subtask 4
    add_input(4, "MALI 4 0");
    add_input(4, "EDGE 4 1");
    add_input(4, "DUPLI 4 2");
    add_input(4, "PRAZAN 4 3");
    add_input(4, "POTPUN 4 4");
    add_input(4, "STABLO 4 5");
    add_input(4, "CIKLUS 4 5");
    add_input(4, "RANDOM_100 4 6");
    add_input(4, "RANDOM_100 4 7");
    add_input(4, "RANDOM_1000 4 8");
    add_input(4, "RANDOM_1000 4 9");
    add_input(4, "RANDOM_10000 4 10");
    add_input(4, "RANDOM_10000 4 11");
    add_input(4, "RANDOM_100000 4 12");
    add_input(4, "RANDOM_100000 4 13");
    add_input(4, "RANDOM_MAX 4 14");
    add_input(4, "RANDOM_MAX 4 15");
    add_input(4, "TLE_1 4 16");
    add_input(4, "TLE_2 4 17");
    add_input(4, "PUNO 4 18");
    add_input(4, "STABLO2 4 19");
    add_input(4, "LANAC2 4 20");
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
