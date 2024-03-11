#include <iostream>
#include <set>
#include <bitset>
using namespace std;

#define MAX_N 40000
long long labels[MAX_N]; // 64-bitowe etykiety zawodników.

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; // Liczba zawodników
    int m; // Liczba meczy
    int participant; // Zmienna do wczytywania id gracza.

    cin >> n >> m;

    // Drużyna A w i-tym meczu będzie symbolizowana przez
    // ustawienie bitu i-tego na 0, a drużyna B na 1.

    int half_n = n/2;

    for (long long i = 0; i < m; ++i) { // Ile meczy
        for (int j = 0; j < half_n; ++j) {
            cin >> participant; // Drużyna A symbolizowana przez 0.
        }
        for (int j = half_n; j < n; ++j) {
            cin >> participant;
            labels[participant - 1] = labels[participant - 1] | (1LL << i);
        }
    }

    set<long long> different_labels;
    for (int i = 0; i < n; ++i) {
        different_labels.insert(labels[i]);
    }

    if (different_labels.size() == n) {
        cout << "TAK\n";
    }
    else {
        cout << "NIE\n";
    }


    return 0;
}
