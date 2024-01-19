// Updating elements on segment.

void push (int v) {
    if (t[v] != -1) {
        t[v*2] = t[v*2+1] = t[v];
        t[v] = -1;
    }
}

void update (int v, int tl, int tr, int l, int r, int color) {
    if (l > r)
        return;
    if (l == tl && tr == r)
        t[v] = color;
    else {
        push (v);
        int tm = (tl + tr) / 2;
        update (v*2, tl, tm, l, min(r,tm), color);
        update (v*2+1, tm+1, tr, max(l,tm+1), r, color);
    }
}

int get (int v, int tl, int tr, int pos) {
    if (tl == tr)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return get(v * 2, tl, tm, pos);
    else
        return get(v * 2 + 1, tm + 1, tr, pos);
}