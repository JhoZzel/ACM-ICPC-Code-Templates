#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds; 

using ll = long long;
using ordered_set = tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>;


int main() {
    ordered_set os;
    os.insert(120);
    os.insert(20);
    os.insert(10);
    os.insert(120);
 
    // insert(x): Inserta el elemento x.
    // erase(x): Borra el elemento x.
    // find_by_order(k): Retorna un iterador al elemento en la posición k (0-indexado).
    // order_of_key(x): Retorna cuántos elementos son estrictamente menores que x.

    cout << os.order_of_key(11) << endl;

    return 0;
}
