class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2) return s;

        // DPテーブル: dp[i][j] は s[i...j] が回文かどうか
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int start = 0;
        int maxLen = 1;

        // 全ての1文字は回文
        for (int i = 0; i < n; ++i) dp[i][i] = true;

        // 長さ2から順にチェック（diff + 1 が現在の長さ）
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                
                if (s[i] == s[j]) {
                    if (len == 2 || dp[i + 1][j - 1]) {
                        dp[i][j] = true;
                        if (len > maxLen) {
                            start = i;
                            maxLen = len;
                        }
                    }
                }
            }
        }

        return s.substr(start, maxLen);
    }
};