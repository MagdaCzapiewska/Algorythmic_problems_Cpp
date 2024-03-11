#include <iostream>
#include <vector>

#define MAX_N 500000

using namespace std;

int left_child[MAX_N + 1], right_child[MAX_N + 1], depth[MAX_N + 1],
subtree_size[MAX_N + 1], preorder[MAX_N + 1], furthest[MAX_N + 1];
vector<int> up[MAX_N + 1];

void dfs_for_depth(int dep, int v) {
    depth[v] = dep;
    if (left_child[v] != -1) {
        dfs_for_depth(dep + 1, left_child[v]);
    }
    if (right_child[v] != -1) {
        dfs_for_depth(dep + 1, right_child[v]);
    }
}

void dfs_for_subtree_size(int v) {
    subtree_size[v] = 1;
    if (left_child[v] != -1) {
        dfs_for_subtree_size(left_child[v]);
        subtree_size[v] += subtree_size[left_child[v]];
    }
    if (right_child[v] != -1) {
        dfs_for_subtree_size(right_child[v]);
        subtree_size[v] += subtree_size[right_child[v]];
    }
}

void dfs_for_preorder(int v, int *counter) {
    //printf("Dfs for %d\n", v);
    preorder[v] = *counter;
    (*counter)++;
    if (left_child[v] != -1) {
        dfs_for_preorder(left_child[v], counter);
    }
    if (right_child[v] != -1) {
        dfs_for_preorder(right_child[v], counter);
    }
}

int jump_up(int v, int steps) {
    for(int i = 20; i >= 0; i--) {
        if((1 << i) > steps) continue;
        steps -= (1 << i);
        v = up[v][i];
    }

    return v;
}

void fillFurthest(int v, int d, int from) {
    furthest[v] = d;
    if (left_child[v] != -1 && left_child[v] != from) {
        fillFurthest(left_child[v], d + 1, v);
    }
    if (right_child[v] != -1 && right_child[v] != from) {
        fillFurthest(right_child[v], d + 1, v);
    }
    if (v != 1 && up[v][0] != from) {
        fillFurthest(up[v][0], d + 1, v);
    }
}

bool is_a_ancestor_of_b(int a, int b, int n) {
    if (a >= 1 && a <= n && b >= 1 && b <= n &&
    preorder[b] >= preorder[a] && preorder[b] < preorder[a] + subtree_size[a]) {
        return true;
    }
    return false;
}

int lca(int a, int b, int n) {
    if (is_a_ancestor_of_b(a, b, n)) {
        return a;
    }
    if (is_a_ancestor_of_b(b, a, n)) {
        return b;
    }

    for(int i = 20; i >= 0; i--) {
        if (up[a].size() <= i) continue;
        if (!is_a_ancestor_of_b(up[a][i], b, n)) a = up[a][i];
    }

    return up[a][0];
}

void fillUp(int n) {
    bool goOn = true;
    int help = 0;
    while (goOn) {
        goOn = false;
        help++;
        for (int i = 1; i <= n; ++i) {
            if (!(up[i].size() < help || up[up[i][help - 1]].size() < help)) {
                up[i].push_back(up[up[i][help - 1]][help - 1]);
                goOn = true;
            }
        }
    }
}

void calculate_diameter(int &diam1, int &diam2, int n) {
    int maxDepth = 0;
    int maxDepthId = 0;
    for (int i = 1; i <= n; ++i)
        if (depth[i] > maxDepth) {
            maxDepth = depth[i];
            maxDepthId = i;
        }
    diam1 = maxDepthId;

    fillFurthest(diam1, 0, diam1);

    maxDepth = 0;
    maxDepthId = diam1;
    for (int i = 1; i <= n; ++i) {
        if (furthest[i] > maxDepth) {
            maxDepth = furthest[i];
            maxDepthId = i;
        }
    }
    diam2 = maxDepthId;
}

void query(int a, int d, int diameter1, int diameter2, int n) {
    //printf("I'm in query\n");
    int diameter = diameter1;
    int l_c_ancestor = lca(a, diameter, n);
    if (depth[a] + depth[diameter] - 2 * depth[l_c_ancestor] < d) {
        diameter = diameter2;
        l_c_ancestor = lca(a, diameter, n);
        if (depth[a] + depth[diameter] - 2 * depth[l_c_ancestor] < d) {
            printf("%d\n", -1);
            return;
        }
    }
    if (depth[a] - depth[l_c_ancestor] >= d) {
        printf("%d\n", jump_up(a, d));
    }
    else {
        printf("%d\n", jump_up(diameter, depth[diameter] + depth[a] - 2 * depth[l_c_ancestor] - d));
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, a, d;
    cin >> n;

    for(int i = 0; i <= n; ++i) {
        left_child[i] = -1;
        right_child[i] = -1;
    }

    for (int i = 1; i <= n; ++i) {
        cin >> left_child[i] >> right_child[i]; // Wczytuje -1, gdy dane dziecko nie istnieje
        if (left_child[i] != -1) {
            up[left_child[i]].push_back(i);
        }
        if (right_child[i] != -1) {
            up[right_child[i]].push_back(i);
        }
    }


    fillUp(n);
    dfs_for_subtree_size(1);
    int counter = 0;
    dfs_for_preorder(1, &counter);
    dfs_for_depth(0, 1);
    int diameter1, diameter2;
    //printf("Tu ok\n");
    calculate_diameter(diameter1, diameter2, n);
    //printf("I tu też\n");

    cin >> m;
    //printf("M = %d\n", m);
    for (int i = 1; i <= m; ++i) {
        //printf("Chce wczytac\n");
        cin >> a >> d;
        //printf("Chce wypisac\n");
        //int to_write = query(a, d, diameter1, diameter2, n);
        //cout << to_write << "\n";
        query(a, d, diameter1, diameter2, n);
        //printf("Po wypisaniu");
    }

    return 0;
}
