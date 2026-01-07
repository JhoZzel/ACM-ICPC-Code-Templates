// Mo algorithm (hilbert order)
//

ll hilbert(int x, int y, int pw, int k = 0) {
    if (pw == 0) return 0;
    int hpw = 1 << (pw - 1);
    int seg = (x < hpw) ? (y < hpw ? 0 : 3) : (y < hpw ? 1 : 2);
    seg = (seg + k) & 3;
    const int del[] = {3, 0, 0, 1};
    int nx = x & (x ^ hpw), ny = y & (y ^ hpw);
    int nk = (k + del[seg]) & 3;
    ll sub_sq = 1ll << (2 * pw - 2);
    ll ans = seg * sub_sq;
    ll add = hilbert(nx, ny, pw - 1, nk);
    ans += (seg == 1 or seg == 2) ? add : (sub_sq - add - 1);
    return ans;
}

vector<ll> mo_algorithm(vector<Query> Q) {
    const int q = Q.size();

    int pw = 0;
    while ((1 << pw) <= n) pw++;

    vector<int> order(q);
    iota(all(order), 0);

    vector<ll> key(q);
    for (int i = 0; i < q; i++) key[i] = hilbert(Q[i].l, Q[i].r, pw);

    sort(all(order), [&](int i, int j) { return key[i] < key[j]; });

    vector<ll> ans(q);

    int cur_l = 0, cur_r = -1; // 0-indexed

    for (int id : order) {
        const Query& q = Q[id];

        while (cur_l > q.l) update(--cur_l, +1);
        while (cur_r < q.r) update(++cur_r, +1);
        while (cur_l < q.l) update(cur_l++, -1);
        while (cur_r > q.r) update(cur_r--, -1);

        ans[q.idx] = get_answer();
    }

    return ans;
}
