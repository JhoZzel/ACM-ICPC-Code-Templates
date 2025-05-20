void remove(idx);  // TODO: remove value at idx from data structure
void add(idx);     // TODO: add value at idx from data structure
int get_answer();  // TODO: extract the current answer of the data structure

const int B = 317;

struct Query {
    int l, r, idx;
    bool operator < (const Query other) const {
        int block_a = l / B, block_b = other.l / B;
        if (block_a != block_b) return block_a < block_b;
        return ((block_a & 1) ? (r > other.r) : (r < other.r)); 
    }
};

vector<int> mo_algorithm(vector<Query> Q) {
    vector<int> ans(size(Q));

    sort(Q.begin(), Q.end());

    int cur_l = 1, cur_r = 0;
    for (Query q : Q) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        ans[q.idx] = get_answer();
    }
    return ans;
}
