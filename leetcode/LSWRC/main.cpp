#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

 int lengthOfLongestSubstring(string s) {
	unordered_map<char,int> mp;
	int maxi = 0;
	int ans = 0;
	int start = 0;
	for(int i = 0;s[i] ;i++)
	{
		//mpを走査してゆき、最後のイテレータを指し示せば重複が無いとみなせる。
		if(mp.find(s[i])!= mp.end())
			start = max(start,mp[s[i]]+1);
		ans = i - start + 1;
		if(ans > maxi) 
			maxi = ans;
		mp[s[i]] = i;
		cout << "s[i]" << s[i] << "\n" << mp[s[i]] << "\n" << "maxi = " <<maxi << "\n";
	}
	return(maxi);
}

int main()
{
	string s;
	int ans;
	s = "abcabcbb";
	ans = lengthOfLongestSubstring(s);
	cout << "ans = " << ans << endl;
}
