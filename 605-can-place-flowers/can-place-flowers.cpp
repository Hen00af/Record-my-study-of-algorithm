class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int size = flowerbed.size();
        
        if (n == 0) return true;

        for (int i = 0; i < size; ++i) {
            if (flowerbed[i] == 1) continue;

            // 左側が空いているか（または左端か）
            bool leftEmpty = (i == 0) || (flowerbed[i - 1] == 0);
            
            // 右側が空いているか（または右端か）
            bool rightEmpty = (i == size - 1) || (flowerbed[i + 1] == 0);

            // 両側が空いていれば植える
            if (leftEmpty && rightEmpty) {
                flowerbed[i] = 1; // 花を植える
                n--;              // 残りのノルマを減らす
                
                // ノルマ達成したら終了
                if (n == 0) return true;
            }
        }

        // 最後まで見てノルマが残っていたら失敗
        return n == 0;
    }
};