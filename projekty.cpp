#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 100000
vector<pair<int, int>> dependent[MAXN + 1];
int edges_left[MAXN + 1];
int weights[MAXN + 1];

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k, a, b;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> weights[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> a >> b;
        dependent[b].push_back(make_pair(weights[a], a)); // Bo pary porownywane najpierw od pierwszej wartosci
        // Pamietam, ze kolejka priorytetowa jest od najwiekszych, wiec wrzucam wagi z minusem, a potem go usuwam
        // przy szukaniu maxa
        edges_left[a]++;
    }

    priority_queue<pair<int, int>> queue;
    for (int i = 1; i <= n; ++i) {
        if (edges_left[i] == 0) {
            queue.push(make_pair(-weights[i], i));
        }
    }
    int max = 0;
    int projects = 0;
    while (projects < k) {
        pair<int, int> element_on_top = queue.top();
        queue.pop();
        if ((-1)*element_on_top.first > max) {
            max = -element_on_top.first;
        }
        for (auto dep : dependent[element_on_top.second]) {
            edges_left[dep.second]--;
            if (edges_left[dep.second] == 0) {
                queue.push(make_pair(-dep.first, dep.second));
            }
        }
        projects++;
    }

    cout << max << "\n";

    return 0;
}
