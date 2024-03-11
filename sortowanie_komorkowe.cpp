#include <iostream>
using namespace std;

#define MOD 1000000000
#define MAX 1000

int array[MAX + 7];
int L[MAX + 7][MAX + 7];
int R[MAX + 7][MAX + 7];

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    // Wypełnianie przekątnej, gdzie i = j.
    for (int i = 0; i < n; ++i) {
        L[i][i] = 1;
        R[i][i] = 1;
    }

    // Wypełnianie przekątnej, gdzie j - i = 1. Jeśli n = 1, to się nie wykona.
    for (int j = 1; j < n; ++j) {
        L[j - 1][j] = (array[j - 1] < array[j]);
        R[j - 1][j] = (array[j] > array[j - 1]);
    }

    // Wypełnianie wszystkich pozostałych przekątnych. Jeśli n < 2, to się nie wykona.
    for (int difference = 2; difference < n; ++difference) {
        for (int j = difference; j < n; ++j) {
            int i = j - difference;
            L[i][j] = ((array[i] < array[i + 1]) * L[i + 1][j] + (array[i] < array[j]) * R[i + 1][j]) % MOD;
            R[i][j] = ((array[j] > array[i]) * L[i][j - 1] + (array[j] > array[j - 1]) * R[i][j - 1]) % MOD;
        }
    }

    cout << (L[0][n - 1] + R[0][n - 1]*(n > 1)) % MOD;

    return 0;
}
