#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, m, tick;

int l[MAXN], r[MAXN], t[MAXN], sol[MAXN];

vector<pair<int, int>> v[MAXN];

struct Node {
  int sum;
  bool prop;
  Node *l, *r;

  Node() {};
  Node(int sum, bool prop, Node *l, Node *r) : sum(sum), prop(prop), l(l), r(r) {}
};

class Tournament {
  private:
    int offset;
    Node *NIL;
    vector<Node*> root;

    Node *merge(Node* L, Node *R) {
      return new Node(L->sum + R->sum, false, L, R);
    }

    void propagate(Node *node) {
      if (node->sum == 1 || !node->prop) return;
      node->l = new Node(node->sum / 2, true, NIL, NIL);
      node->r = new Node(node->sum / 2, true, NIL, NIL);
      node->prop = false;
    }

    Node *insert(Node *node, int lo, int hi, int from, int to) {
      propagate(node);
      if (lo >= to || hi <= from) return node;
      if (lo >= from && hi <= to) return new Node(hi - lo, true, NIL, NIL);
      int mid = (lo + hi) / 2;
      Node *L = insert(node->l, lo, mid, from, to);
      Node *R = insert(node->r, mid, hi, from, to);
      return merge(L, R);
    }

  public:
    Tournament(int n) {
      NIL = new Node(0, false, nullptr, nullptr);
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

Tournament *T;

void dfs(int node, int dad) {
  for (auto &p : v[node]) {
    int nxt = p.first, li = l[p.second], ri = r[p.second];
    if (nxt == dad) continue;
    ++tick;
    t[nxt] = tick;
    T->insert(t[node], li, ri + 1);
    sol[nxt] = T->query(t[nxt]);
    dfs(nxt, node);
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

  T = new Tournament(m + 10);
  dfs(0, -1);

  for (int i = 1; i < n; ++i)
    printf("%d\n", sol[i]);

  return 0;
}
