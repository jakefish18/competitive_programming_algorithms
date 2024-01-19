struct segtree {
    struct node {
        int min;
    };
    node zero = {(int)1e9 + 1};
    ve <node> tree;
    int size = 1;

    explicit segtree(int n) {
        while (size < n) size *= 2;
        tree.assign(2 * size - 1, zero);
    }

    node merge(node a, node b) {
        node res = {min(a.min, b.min)};
        return res;
    }

    void build() {
        for (int v = size - 2; v >= 0; v--) {
            tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }

    void set(int i, int x, int v, int tl, int tr) {
        if (tr == tl) {
            tree[v].min = x;
            return;
        }
        int tm = (tr + tl) / 2;
        if (i <= tm) {
            set(i, x, 2 * v + 1, tl, tm);
        } else {
            set(i, x, 2 * v + 2, tm + 1, tr);
        }
        tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
    }

    void set(int i, int x) {
        set(i, x, 0, 0, size - 1);
    }

    node get(int l, int r, int v, int tl, int tr) {
        if (l <= tl && tr <= r) {
            return tree[v];
        }
        if (r < tl || l > tr) {
            return zero;
        }
        int tm = (tr + tl) / 2;
        return merge(get(l, r, 2 * v + 1, tl, tm), get(l, r, 2 * v + 2, tm + 1, tr));
    }

    int get(int l, int r) {
        return get(l, r, 0, 0, size - 1).min;
    }
};

void use_case() {
    // n is elements count in array.
    int n = 10;
    segtree t(n);
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
    t.tree[t.size + i - 1] = {x};
    }
}
