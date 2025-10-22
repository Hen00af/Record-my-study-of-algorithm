#include <bits/stdc++.h>
#include <cassert>
#include <numeric>

using namespace std;

string gcdOfStrings(string str1, string str2) {
	if(str1 + str2 != str2 + str1)
		return("");
	int n = 0;

	n = gcd(str1.size(),str2.size());
	return(str1.substr(0,n));
}

int main()
{
	string str1 = "ABCABC";
	string str2 = "ABC";
	string ans ;

	ans = gcdOfStrings(str1,str2);

	cout << str1 + str2 << endl;	
	cout << ans << endl;
	return (0);
}
