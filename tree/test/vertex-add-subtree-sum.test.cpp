#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../heavy_light_decomposition.hpp"
#include <cassert>
#include <iostream>
#include <atcoder/fenwicktree>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<long long> A(N);
    vector<pair<int, int>> edges;
    for (auto &a : A) cin >> a;
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        edges.emplace_back(p, i);
    }

    heavy_light_decomposition tour(N, edges);
    tour.build();

    vector<long long> v;
    for (auto i : tour.vis_order) v.push_back(A[i]);
    assert(int(v.size()) == N);
    atcoder::fenwick_tree<long long> ft(N);
    for (int i = 0; i < N; i++) ft.add(i, v[i]);

    while (Q--) {
        int q;
        cin >> q;
        if (q) {
            int u;
            cin >> u;
            printf("%lld\n", ft.sum(tour.subtree_begin[u], tour.subtree_end[u]));
        } else {
            int u, x;
            cin >> u >> x;
            ft.add(tour.subtree_begin[u], x);
        }
    }
}
