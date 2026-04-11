class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        
        // 【枝切り1】 1文字ならそのまま返す
        if (n < 2) return s;
        
        // 【枝切り2】 2文字で同じならそのまま返す
        if (n == 2) {
            if (s[0] == s[1]) return s;
            return s.substr(0, 1); // 違うなら1文字目だけ返す
        }

        // --- 3文字以上の処理 ---
        int start = 0, maxLen = 1;
        for (int i = 0; i < n; ) {
            // 残り文字数が maxLen の半分以下ならこれ以上見つからない
            if (n - i <= maxLen / 2) break;

            int l = i, r = i;
            // 同じ文字が続く間は「中心」としてまとめる（"aa" などの偶数回文対策）
            while (r < n - 1 && s[r + 1] == s[r]) r++;
            
            i = r + 1; // 次の探索位置を更新

            // 中心から左右へ広げる
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