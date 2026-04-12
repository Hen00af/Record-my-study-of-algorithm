class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        int left, right;
        int max_len = 0;
        string ans = "";

        for (int start = 0; start < s.size(); ++start) {
            for (int i = 0; i < 2; ++i) {
                left = start;
                right = start + i; 

                while (left >= 0 && right < s.size() && s[left] == s[right]) {
                    int current_len = right - left + 1;
                    if (current_len > max_len) {
                        max_len = current_len;
                        ans = s.substr(left, max_len);
                    }
                    --left;
                    ++right;
                }
            }
        }
        return ans;
    }
};