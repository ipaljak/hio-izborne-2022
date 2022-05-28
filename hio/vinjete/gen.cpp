#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ll long long
#define ra(a, b) uniform_int_distribution<int>(a, b)(rng)

using namespace std;

int index[10];

#define LANAC  1
#define DUBOKO 2
#define RANDOM 3

#define VELIKI      1
#define DISJUNKTNI  2
#define RANDOM      3
#define SINGLE      4
#define CIJELI      5

mt19937 rng;

void generate_test(int cluster, int N, int K, int graph_type, int edge_type) {
    vector <int> ind;
    REP(i, N) ind.push_back(i + 1);
    random_shuffle(ind.begin(), ind.end());

    char test_name[20];
    sprintf(test_name, "test\\vinjete.in.%d%c", cluster, 'a' + index[cluster]);
    FILE* pFile;
    pFile = fopen(test_name, "w");

    fprintf(pFile, "%d\n", N);

    set <int> bla;
    if (edge_type == CIJELI || edge_type == DISJUNKTNI) {
        // cout << "....";
        if (edge_type == CIJELI) bla.insert(1), bla.insert(K);
        while (bla.size() < (N - 1) * 2) {
            int x = ra(1, K);
            while (bla.find(x) != bla.end()) x = ra(1, K);
            bla.insert(x);
        }
    }

    REP(i, N - 1) {
        int x, y, a, b;

        if (graph_type == LANAC)  x = i + 1, y = i + 2;
        if (graph_type == DUBOKO) x = ind[i + 1], y = ind[ra(max(0, i - 10), i)];
        if (graph_type == RANDOM) x = ind[i + 1], y = ind[ra(0, i)];


        if (edge_type == VELIKI)     {a = ra(1, 100); b = ra(K - 100, K);}
        if (edge_type == DISJUNKTNI) {a = *bla.begin(); bla.erase(bla.begin()); b = *bla.begin(); bla.erase(bla.begin());}
        if (edge_type == CIJELI)     {a = *bla.begin(); bla.erase(bla.begin()); b = *bla.begin(); bla.erase(bla.begin());}
        if (edge_type == RANDOM)     {a = ra(1, K - 1), b = ra(a, K);}
        if (edge_type == SINGLE)     {a = ra(1, K); b = a;}

        fprintf(pFile, "%d %d %d %d\n", x, y, a, b);
    }

    fclose(pFile);

    /*sprintf(test_name, "test\\vinjete.out.%d%c", cluster, 'a' + index[cluster]);
    pFile = fopen(test_name, "w");
    fclose(pFile);*/

    char command[100];
    sprintf(command, "vinjete_pravo.exe < test\\vinjete.in.%d%c > test\\vinjete.out.%d%c", cluster, 'a' + index[cluster], cluster, 'a' + index[cluster]);
    system(command);

    printf("Generated test\\vinjete.in.%d%c\n", cluster, 'a' + index[cluster]);
    index[cluster]++;

    return;
}

int main() {
    mt19937 rng = mt19937(420);
    srand(420);

    //////////////////////////////

    FILE* pFile;
    pFile = fopen("test\\vinjete.dummy.in.1", "w");
    fprintf(pFile, "6\n");
    fprintf(pFile, "1 2 2 4\n");
    fprintf(pFile, "1 3 1 4\n");
    fprintf(pFile, "2 4 3 5\n");
    fprintf(pFile, "2 5 5 6\n");
    fprintf(pFile, "3 6 2 3\n");
    fclose(pFile);

    system("vinjete_pravo.exe < test\\vinjete.dummy.in.1 > test\\vinjete.dummy.out.1");
    printf("Generated test\\vinjete.dummy.in.1\n");

    ///

    pFile = fopen("test\\vinjete.dummy.in.2", "w");
    fprintf(pFile, "5\n");
    fprintf(pFile, "1 2 2 2\n");
    fprintf(pFile, "2 3 3 3\n");
    fprintf(pFile, "3 5 1 5\n");
    fprintf(pFile, "3 4 1 1\n");
    fclose(pFile);

    system("vinjete_pravo.exe < test\\vinjete.dummy.in.2 > test\\vinjete.dummy.out.2");
    printf("Generated test\\vinjete.dummy.in.2\n");


    //////////////////////////////

    generate_test(1, 1000, 1000, LANAC, VELIKI);
    generate_test(1, 1000, 1000, LANAC, VELIKI);
    generate_test(1, 1000, 1000, LANAC, RANDOM);
    generate_test(1, 1000, 1000, LANAC, RANDOM);
    generate_test(1, 1000, 1000, LANAC, SINGLE);
    generate_test(1, 1000, 1000, LANAC, SINGLE);
    generate_test(1,  100, 1000, LANAC, CIJELI);
    generate_test(1,  100, 1000, LANAC, CIJELI);

    generate_test(1, 1000, 1000, DUBOKO, VELIKI);
    generate_test(1, 1000, 1000, DUBOKO, VELIKI);
    generate_test(1, 1000, 1000, DUBOKO, RANDOM);
    generate_test(1, 1000, 1000, DUBOKO, RANDOM);
    generate_test(1, 1000, 1000, DUBOKO, SINGLE);
    generate_test(1, 1000, 1000, DUBOKO, SINGLE);
    generate_test(1,  100, 1000, DUBOKO, CIJELI);
    generate_test(1,  100, 1000, DUBOKO, CIJELI);

    generate_test(1, 1000, 1000, RANDOM, VELIKI);
    generate_test(1, 1000, 1000, RANDOM, VELIKI);
    generate_test(1, 1000, 1000, RANDOM, RANDOM);
    generate_test(1, 1000, 1000, RANDOM, RANDOM);
    generate_test(1, 1000, 1000, RANDOM, SINGLE);
    generate_test(1, 1000, 1000, RANDOM, SINGLE);
    generate_test(1,  100, 1000, RANDOM, CIJELI);
    generate_test(1,  100, 1000, RANDOM, CIJELI);

    //////////////////////////////

    generate_test(2, 1000, 1e9, LANAC, VELIKI);
    generate_test(2, 1000, 1e9, LANAC, VELIKI);
    generate_test(2, 1000, 1e9, LANAC, RANDOM);
    generate_test(2, 1000, 1e9, LANAC, RANDOM);
    generate_test(2, 1000, 1e9, LANAC, SINGLE);
    generate_test(2, 1000, 1e9, LANAC, SINGLE);
    generate_test(2, 1000, 1e9, LANAC, DISJUNKTNI);
    generate_test(2, 1000, 1e9, LANAC, DISJUNKTNI);
    generate_test(2, 1000, 1e9, LANAC, CIJELI);
    generate_test(2, 1000, 1e9, LANAC, CIJELI);

    generate_test(2, 1000, 1e9, DUBOKO, VELIKI);
    generate_test(2, 1000, 1e9, DUBOKO, VELIKI);
    generate_test(2, 1000, 1e9, DUBOKO, RANDOM);
    generate_test(2, 1000, 1e9, DUBOKO, RANDOM);
    generate_test(2, 1000, 1e9, DUBOKO, SINGLE);
    generate_test(2, 1000, 1e9, DUBOKO, SINGLE);
    generate_test(2, 1000, 1e9, DUBOKO, DISJUNKTNI);
    generate_test(2, 1000, 1e9, DUBOKO, CIJELI);

    generate_test(2, 1000, 1e9, RANDOM, VELIKI);
    generate_test(2, 1000, 1e9, RANDOM, VELIKI);
    generate_test(2, 1000, 1e9, RANDOM, RANDOM);
    generate_test(2, 1000, 1e9, RANDOM, RANDOM);
    generate_test(2, 1000, 1e9, RANDOM, SINGLE);
    generate_test(2, 1000, 1e9, RANDOM, SINGLE);
    generate_test(2, 1000, 1e9, RANDOM, DISJUNKTNI);
    generate_test(2, 1000, 1e9, RANDOM, CIJELI);

    //////////////////////////////

    generate_test(3, 40000, 40000, LANAC, VELIKI);
    generate_test(3, 40000, 40000, LANAC, VELIKI);
    generate_test(3, 40000, 40000, LANAC, RANDOM);
    generate_test(3, 40000, 40000, LANAC, RANDOM);
    generate_test(3, 40000, 40000, LANAC, SINGLE);
    generate_test(3, 40000, 40000, LANAC, SINGLE);
    generate_test(3,  5000, 40000, LANAC, DISJUNKTNI);
    generate_test(3,  5000, 40000, LANAC, DISJUNKTNI);
    generate_test(3,  5000, 40000, LANAC, CIJELI);
    generate_test(3,  5000, 40000, LANAC, CIJELI);

    generate_test(3, 40000, 40000, DUBOKO, VELIKI);
    generate_test(3, 40000, 40000, DUBOKO, VELIKI);
    generate_test(3, 40000, 40000, DUBOKO, RANDOM);
    generate_test(3, 40000, 40000, DUBOKO, RANDOM);
    generate_test(3, 40000, 40000, DUBOKO, SINGLE);
    generate_test(3, 40000, 40000, DUBOKO, SINGLE);
    generate_test(3,  5000, 40000, DUBOKO, DISJUNKTNI);
    generate_test(3,  5000, 40000, DUBOKO, CIJELI);

    generate_test(3, 40000, 40000, RANDOM, VELIKI);
    generate_test(3, 40000, 40000, RANDOM, VELIKI);
    generate_test(3, 40000, 40000, RANDOM, RANDOM);
    generate_test(3, 40000, 40000, RANDOM, RANDOM);
    generate_test(3, 40000, 40000, RANDOM, SINGLE);
    generate_test(3, 40000, 40000, RANDOM, SINGLE);
    generate_test(3,  5000, 40000, RANDOM, DISJUNKTNI);
    generate_test(3,  5000, 40000, RANDOM, CIJELI);

    //////////////////////////////

    generate_test(4, 100000, 100000, LANAC, VELIKI);
    generate_test(4, 100000, 100000, LANAC, VELIKI);
    generate_test(4, 100000, 100000, LANAC, RANDOM);
    generate_test(4, 100000, 100000, LANAC, RANDOM);
    generate_test(4, 100000, 100000, LANAC, SINGLE);
    generate_test(4, 100000, 100000, LANAC, SINGLE);
    generate_test(4,  20000, 100000, LANAC, DISJUNKTNI);
    generate_test(4,  20000, 100000, LANAC, DISJUNKTNI);
    generate_test(4,  20000, 100000, LANAC, CIJELI);
    generate_test(4,  20000, 100000, LANAC, CIJELI);

    generate_test(4, 100000, 100000, DUBOKO, VELIKI);
    generate_test(4, 100000, 100000, DUBOKO, VELIKI);
    generate_test(4, 100000, 100000, DUBOKO, RANDOM);
    generate_test(4, 100000, 100000, DUBOKO, RANDOM);
    generate_test(4, 100000, 100000, DUBOKO, SINGLE);
    generate_test(4, 100000, 100000, DUBOKO, SINGLE);
    generate_test(4,  20000, 100000, DUBOKO, DISJUNKTNI);
    generate_test(4,  20000, 100000, DUBOKO, CIJELI);

    generate_test(4, 100000, 100000, RANDOM, VELIKI);
    generate_test(4, 100000, 100000, RANDOM, VELIKI);
    generate_test(4, 100000, 100000, RANDOM, RANDOM);
    generate_test(4, 100000, 100000, RANDOM, RANDOM);
    generate_test(4, 100000, 100000, RANDOM, SINGLE);
    generate_test(4, 100000, 100000, RANDOM, SINGLE);
    generate_test(4,  20000, 100000, RANDOM, DISJUNKTNI);
    generate_test(4,  20000, 100000, RANDOM, CIJELI);

    //////////////////////////////

    generate_test(5, 100000, 1e9, LANAC, VELIKI);
    generate_test(5, 100000, 1e9, LANAC, VELIKI);
    generate_test(5, 100000, 1e9, LANAC, RANDOM);
    generate_test(5, 100000, 1e9, LANAC, RANDOM);
    generate_test(5, 100000, 1e9, LANAC, SINGLE);
    generate_test(5, 100000, 1e9, LANAC, SINGLE);
    generate_test(5,  20000, 1e9, LANAC, DISJUNKTNI);
    generate_test(5,  20000, 1e9, LANAC, DISJUNKTNI);
    generate_test(5,  20000, 1e9, LANAC, CIJELI);
    generate_test(5,  20000, 1e9, LANAC, CIJELI);

    generate_test(5, 100000, 1e9, DUBOKO, VELIKI);
    generate_test(5, 100000, 1e9, DUBOKO, VELIKI);
    generate_test(5, 100000, 1e9, DUBOKO, RANDOM);
    generate_test(5, 100000, 1e9, DUBOKO, RANDOM);
    generate_test(5, 100000, 1e9, DUBOKO, SINGLE);
    generate_test(5, 100000, 1e9, DUBOKO, SINGLE);
    generate_test(5,  20000, 1e9, DUBOKO, DISJUNKTNI);
    generate_test(5,  20000, 1e9, DUBOKO, CIJELI);

    generate_test(5, 100000, 1e9, RANDOM, VELIKI);
    generate_test(5, 100000, 1e9, RANDOM, VELIKI);
    generate_test(5, 100000, 1e9, RANDOM, RANDOM);
    generate_test(5, 100000, 1e9, RANDOM, RANDOM);
    generate_test(5, 100000, 1e9, RANDOM, SINGLE);
    generate_test(5, 100000, 1e9, RANDOM, SINGLE);
    generate_test(5,  20000, 1e9, RANDOM, DISJUNKTNI);
    generate_test(5,  20000, 1e9, RANDOM, CIJELI);

    //////////////////////////////



    return 0;
}