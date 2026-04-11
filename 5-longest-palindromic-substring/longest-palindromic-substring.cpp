class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        
        if (n < 2) return s;
        if (n == 2) {
            if (s[0] == s[1]) return s;
            return s.substr(0, 1);
        }

        int start = 0, maxLen = 1;
        for (int i = 0; i < n; ) {
            if (n - i <= maxLen / 2) break;

            int l = i, r = i;
            while (r < n - 1 && s[r + 1] == s[r]) r++;
            
            i = r + 1; 
            while (l > 0 && r < n - 1 && s[l - 1] == s[r + 1]) {
                l--;
                r++;
            }

            if (r - l + 1 > maxLen) {
                start = l;
                maxLen = r - l + 1;
            }
        }
        return s.substr(start, maxLen);
    }
};