#include <iostream>
using namespace std;

// Zwraca mniejszą z dwóch liczb.
int min(int a, int b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

/* Liczy minimalną odległość między różnymi literami w łańcuchu znaków,
 * nie traktując '*' jako litery, ale licząc je jako element łańcucha.
 * chain - łańcuch znaków
 */
int minimum_l_prime(string chain) {
    char previous_char = NULL;
    int previous_index = NULL;
    int n = chain.size();
    int result = -1;

    for (int i = 0; i < n; ++i) {
        if (chain[i] != '*') {
            if ((previous_char != NULL) && (chain[i] != previous_char)) {
                if (result == -1) {
                    result = i + 1 - previous_index;
                }
                else {
                    result = min(result, i + 1 - previous_index);
                }
            }
            previous_char = chain[i];
            previous_index = i;
        }
    }

    if (result == -1) {
        result = n + 1;
    }

    return result;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string paperwall;
    cin >> paperwall;
    int n = paperwall.size();

    int l_prime = minimum_l_prime(paperwall);
    int k_prime = n - l_prime + 1;

    cout << k_prime + 1 << "\n";

    return 0;
}
