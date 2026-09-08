#include <bits/stdc++.h>

int main() {
    int N;
    std::cin >> N;
    std::vector<int> P(N);
    for(int i = 0; i < N; ++i) std::cin >> P[i];
    bool flag = true;
    for(int i = 0; i < N && flag; ++i) {
        int dig = i / 10;
        if (dig == ((P[i] - 1) / 10)) {
            flag = true;
            continue;;
        }
        else {
            flag = false;
            break;;
        }
    }
    if (flag) 
        std::cout << "Yes";
    else
        std::cout << "No";

    return 0;
}