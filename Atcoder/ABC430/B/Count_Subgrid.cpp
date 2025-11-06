#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    set<string> patterns;

    for (int si = 0; si + M <= N; si++) {
        for (int sj = 0; sj + M <= N; sj++) {

            string t = "";
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < M; j++) {
                    t += S[si + i][sj + j];
                }
            }

            patterns.insert(t);
        }
    }

    cout << patterns.size() << endl;
    return 0;
}
