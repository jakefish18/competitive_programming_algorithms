#include <bits/stdc++.h>
using namespace std;
template<typename key> using ve = std::vector<key>;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef long double ld;


#define int long long

ll rand(ll l, ll r){
    return l + (rnd() % (r - l + 1));
}

signed main(){
    int n = rand(1, 10);
    cout << n << "\n";
    ve<bool> used(n + 1);
    ve<int> G = {rand(1, n)};
    used[G.back()] = true;
    for (int u = 1; u <= n; u++){
        if (!used[u]){
            int v = rand(0, G.size() - 1);
            cout << G[v] << " " << u << "\n";
            G.push_back(u);
        }
    }
    int m = rand(1, 10);
    cout << m << "\n";
    while (m--){
        int u = rand(1, n - 1);
        int v = rand(u + 1, n);
        if (rnd() % 2) swap(u, v);
        cout << u << " " << v << "\n";
    }
}