class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int start = 0, maxLen = 0;

        for (int i = 0; i < s.size(); i++) {
            // 1. 中心が1文字の場合 (aba)
            int len1 = expand(s, i, i);
            // 2. 中心が2文字の間の場合 (abba)
            int len2 = expand(s, i, i + 1);

            int len = max(len1, len2);
            if (len > maxLen) {
                // 最長を更新したら、その開始位置を計算して保存
                start = i - (len - 1) / 2;
                maxLen = len;
            }
        }
        return s.substr(start, maxLen);
    }

private:
    int expand(string s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            l--;
            r++;
        }
        return r - l - 1;
    }
};