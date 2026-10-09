#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll modpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

struct Node {
    int l, r;
    mutable ll v;
    Node(int L, int R = -1, ll V = 0) : l(L), r(R), v(V) {}
    bool operator<(const Node& o) const {
        return l < o.l;
    }
};

// ODT (Chtholly tree)

set<Node> odt;

using iter = set<Node>::iterator;

// split at position pos, returns iterator to segment starting at pos
iter split(int pos) {
    iter it = odt.lower_bound(Node(pos));
    if (it != odt.end() && it->l == pos) return it;
    --it;
    int L = it->l, R = it->r;
    ll V = it->v;
    odt.erase(it);
    odt.insert(Node(L, pos - 1, V));
    return odt.insert(Node(pos, R, V)).first;
}

// assign all values in [l, r] to x
void assign_range(int l, int r, ll x) {
    auto itr = split(r + 1), itl = split(l);
    odt.erase(itl, itr);
    odt.insert(Node(l, r, x));
}

// add x to all in [l, r]
void add_range(int l, int r, ll x) {
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; ++it) {
        it->v += x;
    }
}

// kth smallest in [l, r]
ll kth(int l, int r, int k) {
    auto itr = split(r + 1), itl = split(l);
    vector<pair<ll, int>> seg;
    for (auto it = itl; it != itr; ++it) {
        seg.emplace_back(it->v, it->r - it->l + 1);
    }
    sort(seg.begin(), seg.end());
    for (auto &p : seg) {
        if (k <= p.second) return p.first;
        k -= p.second;
    }
    return -1;
}

// sum of v^x over [l, r] mod y
ll sum_pow(int l, int r, int x, int y) {
    auto itr = split(r + 1), itl = split(l);
    ll ans = 0;
    for (auto it = itl; it != itr; ++it) {
        ll cnt = it->r - it->l + 1;
        ans = (ans + cnt * modpow(it->v, x, y)) % y;
    }
    return ans;
}

int main2() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    ll seed, vmax;
    cin >> n >> m >> seed >> vmax;

    auto rnd = [&]() {
        ll ret = seed;
        seed = (seed * 7 + 13) % 1000000007;
        return ret;
    };

    vector<ll> a(n+1);
    for (int i = 1; i <= n; ++i) {
        a[i] = (rnd() % vmax) + 1;
        odt.insert(Node(i, i, a[i]));
    }

    for (int i = 0; i < m; ++i) {
        int op = (rnd() % 4) + 1;
        int l = (rnd() % n) + 1;
        int r = (rnd() % n) + 1;
        if (l > r) swap(l, r);
        ll x, y;
        if (op == 3) x = (rnd() % (r - l + 1)) + 1;
        else x = (rnd() % vmax) + 1;
        if (op == 4) y = (rnd() % vmax) + 1;

        if (op == 1) {
            add_range(l, r, x);
        } else if (op == 2) {
            assign_range(l, r, x);
        } else if (op == 3) {
            ll ans = kth(l, r, (int)x);
            cout << ans << '\n';
        } else if (op == 4) {
            ll ans = sum_pow(l, r, (int)x, (int)y);
            cout << ans << '\n';
        }
    }
    return 0;
}
