#include <iostream>
#include <cmath>
#include <utility>
#include <map>
#include <vector>
#include <list>

#define MAX_N 300000
#define log_n 18

using namespace std;

char s[MAX_N + 1];
int nazwa[MAX_N + 1][log_n + 1];
pair<int, int> tymczasowa[MAX_N + 1];

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, a, b, c, d, new_b, new_d, max_k_for_quest;
    cin >> n >> m;

    for(int i = 1; i <= n; ++i) {
        cin >> s[i];
    }

    for (int i = 1; i <= n; ++i) {
        nazwa[i][0] = int(s[i]) - int('a') + 1;
        //cout << nazwa[i][0];
    }
    int max_k = floor(log2(double(n))); // nazwa[1..n][0..max_k]
    for (int j = 1; j <= max_k; ++j) {
        list<tuple<int, int, int>> lista;
        int max_kubelek_1 = 0, max_kubelek_2 = 0;
        for (int i = 1; i <= n - int(pow(2, j - 1)); ++i) {
            tymczasowa[i] = make_pair(nazwa[i][j - 1], nazwa[i + int(pow(2, j - 1))][j - 1]);
            if (tymczasowa[i].second > max_kubelek_2) {
                max_kubelek_2 = tymczasowa[i].second;
            }
            if (tymczasowa[i].first > max_kubelek_1) {
                max_kubelek_1 = tymczasowa[i].first;
            }
            lista.emplace_back(nazwa[i][j - 1], nazwa[i + int(pow(2, j - 1))][j - 1], i);
        }
        vector<list<tuple<int, int, int>>> kubelki;
        for (int i = 0; i < max_kubelek_2 + 1; ++i) {
            kubelki.emplace_back();
        }

        while (!lista.empty()) {
            kubelki[get<1>(*lista.begin())].splice(kubelki[get<1>(*lista.begin())].end(), lista, lista.begin());
        }

        for (auto& kubelek : kubelki) {
            lista.splice(lista.end(), kubelek);
        }

        if (max_kubelek_2 < max_kubelek_1) {
            for (int i = 0; i < max_kubelek_1 - max_kubelek_2; ++i) {
                kubelki.emplace_back();
            }
        }

        while (!lista.empty()) {
            kubelki[get<0>(*lista.begin())].splice(kubelki[get<0>(*lista.begin())].end(), lista, lista.begin());
        }

        for (auto& kubelek : kubelki) {
            lista.splice(lista.end(), kubelek);
        }

        int licznik = 1;
        auto it = lista.begin();

        nazwa[get<2>(*it)][j] = licznik;
        ++it;

        for (; it != lista.end(); ++it) {
            if (get<0>(*it) != get<0>(*(--it)) || get<1>(*(++it)) != get<1>(*(--it))) {
                ++licznik;
            }
            nazwa[get<2>(*(++it))][j] = licznik;
        }
        /*
        // tworze max_kubelek_2 + 1 kubelkow i wrzucam tam pary razem z indeksem
        vector<tuple<int, int, int>> kubelki_na_druga[max_kubelek_2 + 1];
        for (int i = 1; i <= n - int(pow(2, j - 1)); ++i) {
            kubelki_na_druga[tymczasowa[i].second].emplace_back(tymczasowa[i].first, tymczasowa[i].second, i);
        }
        vector<tuple<int, int, int>> kubelki_na_pierwsza[max_kubelek_1 + 1];
        for (int i = 1; i <= max_kubelek_2; ++i) {
            for (auto x : kubelki_na_druga[i]) {
                kubelki_na_pierwsza[get<0>(x)].emplace_back(get<0>(x), get<1>(x), get<2>(x));
            }
        }
        vector<tuple<int, int, int>> ostateczna;
        for (int i = 1; i <= max_kubelek_1; ++i) {
            for (auto x : kubelki_na_pierwsza[i]) {
                ostateczna.emplace_back(get<0>(x), get<1>(x), get<2>(x));
            }
        }
        int licznik = 1;
        if (!ostateczna.empty()) {
            int x = get<0>(ostateczna[0]);
            int y = get<1>(ostateczna[0]);
            nazwa[get<2>(ostateczna[0])][j] = licznik;

            for (int i = 1; i < ostateczna.size(); ++i) {
                if (get<0>(ostateczna[i]) != x || get<1>(ostateczna[i]) != y) {
                    licznik++;
                    x = get<0>(ostateczna[i]);
                    y = get<1>(ostateczna[i]);
                }
                nazwa[get<2>(ostateczna[i])][j] = licznik;
            }
        }*/

        //map<pair<int, int>, int> tymczasowa_sort;
        //for (int i = 1; i <= n - int(pow(2, j - 1)); ++i) {
        //    tymczasowa_sort.insert(make_pair(tymczasowa[i], 0));
        //}
        //int numer = 1;
        //for (auto it = tymczasowa_sort.begin(); it != tymczasowa_sort.end(); ++it) {
        //    tymczasowa_sort.insert_or_assign(it->first, numer);
        //    ++numer;
        //}
        //for (int i = 1; i <= n - int(pow(2, j - 1)); ++i) {
        //    nazwa[i][j] = tymczasowa_sort.at(tymczasowa[i]);
        //}
        //map<pair<int, int>, vector<int>> tymczasowa_sort;
        //for (int i = 1; i <= n - int(pow(2, j - 1)); ++i) {
        //    bool inserted = (tymczasowa_sort.insert(make_pair(tymczasowa[i], vector<int>{i}))).second;
        //    if (!inserted) {
        //        auto it = tymczasowa_sort.find(tymczasowa[i]);
        //        (it->second).push_back(i);
        //    }
        //}
        //int numer = 1;
        //for (auto it = tymczasowa_sort.begin(); it != tymczasowa_sort.end(); ++it) {
        //    for (auto val : it->second) {
        //        nazwa[val][j] = numer;
        //    }
        //    numer++;
        //}
    }

    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c >> d;
        if (b - a > d - c) { // dluzsze jest pierwsze podslowo
            new_d = d;
            new_b = b - ((b - a) - (d - c)); // b pomniejszamy o roznice dlugosci
        }
        else {
            new_b = b;
            new_d = d - ((d - c) - (b - a)); // jesli slowa rownej dlugosci, to nic nie zmienimy
        }
        max_k_for_quest = floor(log2(double(new_b - a + 1)));
        pair<int, int> w1 = make_pair(nazwa[a][max_k_for_quest], nazwa[new_b - int(pow(2, max_k_for_quest)) + 1][max_k_for_quest]);
        pair<int, int> w2 = make_pair(nazwa[c][max_k_for_quest], nazwa[new_d - int(pow(2, max_k_for_quest)) + 1][max_k_for_quest]);
        if (w1 < w2) {
            cout << "<\n";
        }
        else if (w1 > w2) {
            cout << ">\n";
        }
        else if (b - a > d - c) {
            cout << ">\n";
        }
        else if (b - a < d - c) {
            cout << "<\n";
        }
        else {
            cout << "=\n";
        }
    }

    return 0;
}
