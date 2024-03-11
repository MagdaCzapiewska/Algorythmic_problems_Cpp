#include <iostream>
using namespace std;

#define MAX_N 20000
#define MAX_K 10
#define MOD 1000000000
#define MAX_2B 65536

int permutation[MAX_N + 1];
int T[MAX_N + 1][MAX_K + 1];
int compartment_tree[MAX_2B];

int how_many_leaves(int n) {
    int B = 1;
    while (B < n) {
        B *= 2;
    }
    return B;
}

int array_size(int leaves) {
    return 2 * leaves;
}

int parent_index(int i) {
    return i / 2;
}

bool is_left_child(int i) {
    return (i % 2 == 0);
}

void add_to_compartment_tree(int B, int i, int val) {
    int index = B + i - 1;
    compartment_tree[index] = val;
    while(parent_index(index) != 0) {
        compartment_tree[parent_index(index)] += val;
        compartment_tree[parent_index(index)] %= MOD;
        index = parent_index(index);
    }
}

int sum_from_greater_than(int B, int i) {
    int sum = 0;

    int index = B + i - 1;
    if (index == 2 * B - 1) {
        return 0;
    }
    int left = index + 1;
    int right = 2 * B - 1;

    if (left == right) {
        return compartment_tree[left];
    }

    sum += compartment_tree[left];
    sum %= MOD;
    sum += compartment_tree[right];
    sum %= MOD;

    while (parent_index(left) != parent_index(right)) {
        if (is_left_child(left)) {
            sum += compartment_tree[left + 1];
            sum %= MOD;
        }
        if (!is_left_child(right)) {
            sum += compartment_tree[right - 1];
            sum %= MOD;
        }
        left = parent_index(left);
        right = parent_index(right);
    }


    return sum;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;

    cin >> n >> k;

    for(int i = 1; i <= n; ++i) {
        cin >> permutation[i];
    }

    for (int i = 1; i <= n; ++i) {
        T[i][1] = 1; // 1 - inwersje kończące się na a_i
    }

    int B = how_many_leaves(n);
    int j = array_size(B);

    for (int l = 2; l <= k; ++l) {
        for (int i = 1; i < j; ++i) { // Tworzę nowe drzewo przedziałowe, czyli
            compartment_tree[i] = 0; // zeruję komórki, których będe używać.
        }

        for (int i = 1; i <= n; ++i) {
            T[i][l] = sum_from_greater_than(B, permutation[i]);
            add_to_compartment_tree(B, permutation[i], T[i][l - 1]);
        }
    }

    int result = 0;
    for (int i = 1; i <= n; ++i) {
        result += T[i][k];
        result %= MOD;
    }

    cout << result << "\n";

    return 0;
}