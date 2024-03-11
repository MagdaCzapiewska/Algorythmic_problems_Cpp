#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;

#define MOD 1000000007
#define MAX_N 500000

int a[MAX_N];
pair<int, int> segment_tree[4 * MAX_N];

pair<int, int> combine(pair<int, int> a, pair<int, int> b) {

    if (a.first < b.first) {
        return a;
    }
    else if (b.first < a.first) {
        return b;
    }
    else {
        return make_pair(a.first, (a.second + b.second) % MOD);
    }
}

pair<int, int> get_min_and_quantity(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return make_pair(MAX_N + 1, 0);
    if (l == tl && r == tr)
        return segment_tree[v];
    int tm = (tl + tr) / 2;
    return combine(get_min_and_quantity(v*2, tl, tm, l, min(r, tm)),
                   get_min_and_quantity(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(int v, int tl, int tr, int pos, int new_val_first, int new_val_second) {
    if (tl == tr) {
        segment_tree[v] = make_pair(new_val_first, new_val_second);
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val_first, new_val_second);
        else
            update(v*2+1, tm+1, tr, pos, new_val_first, new_val_second);
        segment_tree[v] = combine(segment_tree[v*2], segment_tree[v*2+1]);
    }
}

void write_pairs(int v, int tl, int tr) {
    if (tl == tr) {
        cout << "tl: " << tl << ", wartość w a[]: " << a[tl] << ", first: " << segment_tree[v].first << ", second: " <<
        segment_tree[v].second << "\n";
    } else {
        int tm = (tl + tr) / 2;
        write_pairs(v*2, tl, tm);
        write_pairs(v*2+1, tm+1, tr);
    }
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, l;
    cin >> n >> k >> l;

    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a, a + n);

    for (int i = 0; i < n; ++i) {
        update(1, 0, n - 1, i, MAX_N + 1, 0);
    }

    // Z założenia n >= 1
    update(1, 0, n - 1, 0, 1, 1);

    for (int i = 1; i < n; ++i) {
        auto x_iterator = lower_bound(a, a + n, a[i] - k);
        int x = x_iterator - a;
        // Wiem, że na pewno x >= 0, bo tablica posortowana niemalejąco. Może się zdarzyć, że x = i, gdy i-ty nie może
        // reprezentować żadnego wcześniejszego.

        if (x == 0) { // Jeśli i-ty może reprezentować wszystkich na lewo, to minimalny komitet jest jednoosobowy.
            update(1, 0, n - 1, i, 1, 1);
        }
        else { // Czyli x > 0, więc mogę się odwoływać do a[x - 1]
            auto start_iterator = lower_bound(a, a + n, a[x - 1] - k);
            int start = start_iterator - a;
            // Wiem, że na pewno start >= 0, bo tablica posortowana niemalejąco.
            // Na razie mamy przedział [start, x). Teraz binsearchujemy przez upper_bound i wyrzucamy różniących się
            // od i-tego rangą o mniej niż l.
            auto end_iterator = upper_bound(a, a + n, a[i] - l);
            int end = end_iterator - a;

            // Teraz ostatecznie mamy przedział [start, end), czyli rozważamy członków [start, end - 1].
            // Może się okazać, że nikt w tym przedziale nie istnieje i wtedy get_min_and_quantity zwróci jakieś INF.

            pair<int, int> result = get_min_and_quantity(1, 0, n - 1, start, end- 1);
            if (result.first == MAX_N + 1) {
                update(1, 0, n - 1, i, MAX_N + 1, 0);
            }
            else {
                update(1, 0, n - 1, i, result.first + 1, result.second);
            }
        }
    }

    //write_pairs(1, 0, n - 1);

    auto start_iterator = lower_bound(a, a + n, a[n - 1] - k);
    int start = start_iterator - a;

    pair<int, int> result = get_min_and_quantity(1, 0, n - 1, start, n - 1);
    cout << result.first << " " << result.second << "\n";

    return 0;
}
