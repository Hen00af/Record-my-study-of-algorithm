class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> all_nums = nums1;
        

        all_nums.insert(all_nums.end(), nums2.begin(), nums2.end());
        sort(all_nums.begin(), all_nums.end());
        int n = all_nums.size();

        if (n % 2)
            return all_nums[n / 2];
        else
            return (double)(all_nums[n / 2] +  all_nums[n / 2 - 1] ) / 2;

    }
};