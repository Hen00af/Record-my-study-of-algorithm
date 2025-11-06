#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define repp(i, a, n) for (int i = a; i <= n; ++i)
#define ll long long
using ull = unsigned long long;
// #include "atcoder/modint.hpp"
// using mint = atcoder::modint998244353;

// ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    int A,B,C,D;
    
    cin >> A >> B >> C >> D;
    if(C >= A)
    {
        if(D >= B)
        {
            cout << "No" << endl;
        }
        else
        {
            cout << "Yes" << endl;
        }
    }
    else
    {
        cout << "No" << endl;
    }
    return 0;
}
