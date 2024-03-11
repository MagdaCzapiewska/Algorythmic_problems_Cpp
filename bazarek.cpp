#include <iostream>

using namespace std;

#define MAX 1000000 // Maksymalna liczba rodzajów produktów dostępnych na bazarku.

/* Wczytuje n wartości do tablicy do komórek o najmniejszych indeksach.
 * array - wskaźnik na zerowy element tablicy
 * n - liczba elementów do wczytania
 */
void read_array(int *array, int n) {
    for(int i = 0; i < n; ++i) {
        cin >> array[i];
    }
}

/* Wyznacza tablicę sumR, gdzie na k-1-szej pozycji jest zapisana
 * suma k największych elementów tablicy array.
 * array - wskaźnik na tablicę, sumy elementów której liczymy
 * n - długość tablicy array
 * sumR - tablica, którą wypełnia funkcja
 */
void fill_sumR(int *array, int n, long long *sumR) {
    sumR[0] = array[n - 1];
    for (int i = 1; i < n; ++i) {
        sumR[i] = sumR[i - 1] + array[n - 1 - i];
    }
}

/* Wyznacza tablicę maxL, gdzie:
 * maxL[k][0] - maksymalna liczba parzysta w array[0]...array[n-k-1]
 * lub -1, gdy nie istnieje
 * max[k][1] - maksymalna liczba nieparzysta w array[0]...array[n-k-1]
 * lub -1, gdy nie istnieje
 * array - wskaźnik na początek tablicy, której elementy przeglądamy
 * n - długość tablicy array
 * maxL - wskaźnik na dwuwymiarową tablicę wynikową
 */
void fill_maxL(int *array, int n, int **maxL) {
    int modulo = array[0] % 2;
    maxL[n - 1][modulo] = array[0];
    maxL[n - 1][1 - modulo] = -1;

    for (int i = n - 2; i >= 0; --i) {
        modulo = array[n - 1 - i] % 2;
        maxL[i][modulo] = array[n - 1 - i];
        maxL[i][1 - modulo] = maxL[i + 1][1 - modulo];
    }
}

/* Wyznacza tablicę minR, gdzie:
 * minR[k - 1][0] - minimalna liczba parzysta w array[n - k]...array[n - 1]
 * lub -1, gdy nie istnieje
 * minR[k - 1][1] - minimalna liczba nieparzysta w array[n - k]...array[n - 1]
 * lub -1, gdy nie istnieje
 * array - wskaźnik na początek tablicy, której elementy przeglądamy
 * n - długość tablicy array
 * maxL - wskaźnik na dwuwymiarową tablicę wynikową
 */
void fill_minR(int *array, int n, int **minR) {
    int modulo = array[n - 1] % 2;
    minR[0][modulo] = array[n - 1];
    minR[0][1 - modulo] = -1;

    for (int i = n - 2; i >= 0; --i) {
        modulo = array[i] % 2;
        minR[n - 1 - i][modulo] = array[i];
        minR[n - 1 - i][1 - modulo] = minR[n - 2 - i][1 - modulo];

    }
}

// Wyznacza liczbę będącą odpowiedzią na pytanie postawione w treści zadania.
long long get_question_give_answer(int **array1, int **array2, long long *array3, int n) {
    int k;
    long long result;
    cin >> k;

    if (array3[k - 1] % 2 == 1) {
        return array3[k - 1];
    }
    else {
        result = -1;
        if (k != n) {
            if ((array1[k][0] != -1) && (array2[k - 1][1] != -1)) {
                result = array3[k - 1] - array2[k - 1][1] + array1[k][0];
            }
            if ((array1[k][1] != -1) && (array2[k - 1][0] != -1)) {
                long long calc = array3[k - 1] - array2[k - 1][0] + array1[k][1];
                if (calc > result) {
                    result = calc;
                }
            }
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    /* n - Liczba rodzajów produktów dostępnych na bazarku.
     * m - Liczba dni, które Bajtek spędzi jeszcze u babci.
     */
    int *prices = {new int[MAX]{}}; // Ceny poszczególnych produktów.

    cin >> n;
    read_array(prices, n);

    long long *sumR = {new long long [MAX]{}};
    int **maxL = {new int *[MAX]{}};
    int **minR = {new int *[MAX]{}};

    for(int i = 0; i < MAX; ++i) {
        maxL[i] = {new int[2]{}};
        minR[i] = {new int[2]{}};
    }

    fill_sumR(prices, n, sumR);
    fill_maxL(prices, n, maxL);
    fill_minR(prices, n, minR);

    cin >> m;

    for (int i = 0; i < m; ++i) {
        cout << get_question_give_answer(maxL, minR, sumR, n) << "\n";
    }

    return 0;
}
