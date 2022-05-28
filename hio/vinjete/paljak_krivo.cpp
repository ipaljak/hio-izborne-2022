#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, m, tick;

int l[MAXN], r[MAXN], t[MAXN], sol[MAXN];

vector<pair<int, int>> v[MAXN];

struct Node {
  int sum;
  Node *l, *r;

  Node() {};
  Node(int sum, Node *l, Node *r) : sum(sum), l(l), r(r) {}
};

class Tournament {
  private:
    int offset;
    Node *NIL;
    vector<Node*> root;

    Node *merge(Node* L, Node *R) {
      return new Node(L->sum + R->sum, L, R);
    }

    Node *insert(Node *node, int lo, int hi, int from, int to) {
      if (lo >= to || hi <= from) return node;
      if (lo >= from && hi <= to) return new Node(hi - lo, NIL, NIL);
      int mid = (lo + hi) / 2;
      Node *L = insert(node->l, lo, mid, from, to);
      Node *R = insert(node->r, mid, hi, from, to);
      return merge(L, R);
    }

  public:
    Tournament(int n) {
      NIL = new Node(0, nullptr, nullptr);
      NIL->l = NIL->r = NIL;
      for (offset = 1; offset <= n; offset *= 2);
      root.emplace_back(NIL);
    }

    void insert(int t, int from, int to) {
      root.emplace_back(insert(root[t], 0, offset, from, to));
    }

    int query(int t) {
      return root[t]->sum;
    }
};

void dfs(int node, int dad, int li, int ri, Tournament &T) {
  //printf("%d\n", node); fflush(stdout);
  t[node] = tick;
  ++tick;
  if (dad != -1) {
    T.insert(t[dad], li, ri + 1);
    sol[node] = T.query(t[node]);
  }
  for (auto &p : v[node]) {
    int nxt = p.first, li = l[p.second], ri = r[p.second];
    if (nxt == dad) continue;
    dfs(nxt, node, li, ri, T);
  }
}

int main(void) {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    scanf("%d%d%d%d", &a, &b, &l[i], &r[i]);
    --a; --b;
    v[a].emplace_back(b, i);
    v[b].emplace_back(a, i);
  }

  Tournament T(m + 10);
  dfs(0, -1, -1, -1, T);

  for (int i = 1; i < n; ++i)
    printf("%d\n", sol[i]);

  return 0;
}
