vvi get_permutations(int a, int b) {
    vvi P;
    vi idx(b - a + 1); // len_max = 10
    iota(all(idx),a);
    do {
        P.push_back(idx);
    } while( next_permutation(all(idx)));
    return P;
}
