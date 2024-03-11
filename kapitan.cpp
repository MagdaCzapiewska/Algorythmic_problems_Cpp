#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>
#include <list>
#include <cmath>
#include <unordered_set>
using namespace std;

#define MAX_N 200000
#define INF 1000000001
int d[MAX_N + 1];
pair<int, int> with_x[MAX_N];
pair<int, int> with_y[MAX_N];
pair<int, int> coordinates[MAX_N + 1];
unordered_set<int> adjacency_list[MAX_N + 1];

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    d[1] = 0;
    for (int i = 2; i <= n; ++i) {
        d[i] = INF;
    }

    int x, y;
    for (int i = 1; i <= n; ++i) {
        cin >> x >> y;
        with_x[i - 1] = make_pair(x, i);
        with_y[i - 1] = make_pair(y, i);
        coordinates[i] = make_pair(x, y);
    }
    sort(with_x, with_x + n);
    sort(with_y, with_y + n);
    /*
    cout << "Posortowanie po x:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Wspolrzedna: " << with_x[i].first << ", numer: " << with_x[i].second << "\n";
    }


    cout << "Posortowanie po y:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Wspolrzedna: " << with_y[i].first << ", numer: " << with_y[i].second << "\n";
    }
    */
    adjacency_list[with_x[0].second].insert(with_x[1].second);
    adjacency_list[with_x[n - 1].second].insert(with_x[n - 2].second);

    for (int i = 1; i < n - 1; ++i) {
        adjacency_list[with_x[i].second].insert(with_x[i - 1].second);
        adjacency_list[with_x[i].second].insert(with_x[i + 1].second);
    }

    adjacency_list[with_y[0].second].insert(with_y[1].second);
    adjacency_list[with_y[n - 1].second].insert(with_y[n - 2].second);

    for (int i = 1; i < n - 1; ++i) {
        adjacency_list[with_y[i].second].insert(with_y[i - 1].second);
        adjacency_list[with_y[i].second].insert(with_y[i + 1].second);
    }
    /*
    for (int i = 1; i <= n; ++i) {
        cout << "Moj numer: " << i << ", moi sasiedzi: ";
        for (int j : adjacency_list[i]) {
            cout << j << " ";
        }
        cout << "\n";
    }
    */

    priority_queue<pair<int, int>> dijkstra_queue;
    for (int i = 1; i <=n; ++i) {
        dijkstra_queue.push(make_pair(-d[i], i));
    }

    while(!empty(dijkstra_queue)) {
        int vertex = dijkstra_queue.top().second;
        int distance = (-1) * dijkstra_queue.top().first;
        dijkstra_queue.pop();

        if (!(d[vertex] < distance)) {
            for (int neighbour: adjacency_list[vertex]) {
                int min_dist = min(abs(coordinates[vertex].first - coordinates[neighbour].first),
                                   abs(coordinates[vertex].second - coordinates[neighbour].second));
                if (d[vertex] + min_dist < d[neighbour]) {
                    d[neighbour] = d[vertex] + min_dist;
                    dijkstra_queue.push(make_pair(-d[neighbour], neighbour));
                }
            }
        }
    }

    cout << d[n] << "\n";

    return 0;
}
