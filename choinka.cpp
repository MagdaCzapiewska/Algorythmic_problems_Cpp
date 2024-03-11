// Źródła fragmentów kodu:
// Implementacja drzewa przedzialowego ze strony https://cp-algorithms.com/data_structures/segment_tree.html
// Reprezentacja grafu i koncept ponumerowania wierzchołków w kolejności dfs preorder z zadania Megalopolis z XIV OI
// plik meg.cpp autorstwa Anny Niewiarowskiej

#include <iostream>
#include <list>
#include <tuple>
#include <unordered_map>
using namespace std;

#define MAX_N 200000
#define MAX_TREE 524288 // tzn. 2 * 262144 = 2 * 2^18

#define getx getchar_unlocked

inline int wczytaj(){
    int res = 0;
    char c;
    do{
        c = getx();
    }while(c < '0' || c > '9');
    do{
        res = res*10 + c - '0';
        c = getx();
    }while(c >= '0' && c <= '9');
    return res;
}

int first_son[MAX_N + 1];
int next_brother[MAX_N + 1];
int preorder_num[MAX_N + 1];
int subtree_end[MAX_N + 1];

int n;
int tree_size;

tuple<bool, bool, int, int, int, int> t[MAX_TREE]; // one_c, almost_one_c, c1, q1, c2, q2

tuple<bool, bool, int, int, int, int> combine(tuple<bool, bool, int, int, int, int> a, tuple<bool, bool, int, int, int, int> b) {
    if (get<0>(a) && get<0>(b)) {
        if (get<2>(a) == 0) {
            return make_tuple(true, true, get<2>(b), get<3>(b), 0, 0);
        }
        else if (get<2>(b) == 0) {
            return make_tuple(true, true, get<2>(a), get<3>(a), 0, 0);
        }
        else if (get<2>(a) == get<2>(b)) {
            return make_tuple(true, true, get<2>(a), get<3>(a) + get<3>(b), 0, 0);
        }
        else if (get<3>(a) == 1) {
            return make_tuple(false, true, get<2>(b), get<3>(b), get<2>(a), get<3>(a));
        }
        else if (get<3>(b) == 1) {
            return make_tuple(false, true, get<2>(a), get<3>(a), get<2>(b), get<3>(b));
        }
        else {
            return make_tuple(false, false, 0, 0, 0, 0);
        }
    }
    else if (get<0>(a) && get<1>(b)) {
        if (get<2>(a) == 0) {
            return make_tuple(false, true, get<2>(b), get<3>(b), get<4>(b), get<5>(b));
        }
        else if (get<2>(a) == get<2>(b)) {
            return make_tuple(false, true, get<2>(a), get<3>(a) + get<3>(b), get<4>(b), get<5>(b));
        }
        else if (get<2>(a) == get<4>(b) && get<3>(b) == 1) {
            return make_tuple(false, true, get<2>(a), get<3>(a) + get<5>(b), get<2>(b), get<3>(b));
        }
        else {
            return make_tuple(false, false, 0, 0, 0, 0);
        }
    }
    else if (get<1>(a) && get<0>(b)) {
        if (get<2>(b) == 0) {
            return make_tuple(false, true, get<2>(a), get<3>(a), get<4>(a), get<5>(a));
        }
        else if (get<2>(a) == get<2>(b)) {
            return make_tuple(false, true, get<2>(a), get<3>(a) + get<3>(b), get<4>(a), get<5>(a));
        }
        else if (get<2>(b) == get<4>(a) && get<3>(a) == 1) {
            return make_tuple(false, true, get<2>(b), get<3>(b) + get<5>(a), get<2>(a), get<3>(a));
        }
        else {
            return make_tuple(false, false, 0, 0, 0, 0);
        }
    }
    else {
        return make_tuple(false, false, 0, 0, 0, 0);
    }
}

tuple<bool, bool, int, int, int, int> get_colours(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return make_tuple(true, true, 0, 0, 0, 0);
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return combine(get_colours(v*2, tl, tm, l, min(r, tm)),
                   get_colours(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(int v, int tl, int tr, int pos, tuple<bool, bool, int, int, int, int> new_val) {
    if (tl == tr) {
        t[v] = make_tuple(get<0>(new_val), get<1>(new_val), get<2>(new_val), get<3>(new_val), get<4>(new_val), get<5>(new_val));
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}


int dfs_numbers_preorder(int v, int var_to_order) { // numeruje wierzchoki, nadajac korzeniowi numer 0
    int son = first_son[v];
    preorder_num[v] = var_to_order;
    var_to_order++;
    while (son!=0) {
        var_to_order = dfs_numbers_preorder(son, var_to_order);
        son = next_brother[son];
    }
    subtree_end[v]=var_to_order - 1;
    return var_to_order;
}

void create_graph_representation() {
    int parent;
    for (int i = 1; i <= n; ++i) {
        first_son[i] = 0;
        next_brother[i] = 0;
    }

    for (int i = 2; i <= n; ++i) {
        parent = wczytaj();
        next_brother[i] = first_son[parent];
        first_son[parent] = i;
    }
}

void make_tree() {
    tree_size = 2;
    while (tree_size<n) tree_size*=2;
    tree_size*=2;

    for (int i=0; i < tree_size; i++) t[i] = make_tuple(true, true, 0, 0, 0, 0);
}

void change(int v, int x) {
    update(1, 0, n - 1, preorder_num[v], make_tuple(true, true, x, 1, 0, 0));
}

bool almost_one_colour(int v) {
    if (get<1>(get_colours(1, 0, n - 1, preorder_num[v], subtree_end[v]))) {
        return true;
    }
    return false;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q, k, x, v;
    char question;

    n = wczytaj();
    q = wczytaj();

    //cout << n << " " << q << "\n";

    create_graph_representation();
    dfs_numbers_preorder(1, 0);
    make_tree();

    for (int i = 1; i <= n; ++i) {
        k = wczytaj();
        change(i, k);
    }

    for (int i = 0; i < q; ++i) {
        int c = getchar();
        if (c == int('z')) {
            c = getchar(); // spacja
            v = wczytaj();
            x = wczytaj();
            change(v, x);
        }
        else if (c == int('?')) {
            c = getchar(); // spacje
            v = wczytaj();
            if (almost_one_colour(v)) {
                cout << "TAK\n";
            }
            else {
                cout << "NIE\n";
            }
        }
    }

    return 0;
}